#!/usr/bin/env python2
import argparse
import grpc
import os
import sys
import socket
import random
import struct
import commands

from time import sleep
from datetime import datetime
from scapy.all import sniff, sendp,send, hexdump, get_if_list, get_if_hwaddr
from scapy.all import Packet, IPOption
from scapy.all import ShortField, IntField, LongField, BitField, FieldListField, FieldLenField, ByteField
from scapy.all import Ether, IP, UDP, TCP, Raw
from scapy.layers.inet import _IPOption_HDR
from collections import deque
from collections import defaultdict

Traffic_size = 24
dst_ip="10.0.1.1" # this will be used in reply_for_pktB function as dst ip addr of H1

# Import P4Runtime lib from parent utils dir
# Probably there's a better way of doing this.
sys.path.append(
    os.path.join(os.path.dirname(os.path.abspath(__file__)),
                 '../utils/'))
import p4runtime_lib.bmv2
from p4runtime_lib.switch import ShutdownAllSwitchConnections
import p4runtime_lib.helper

#global dict for kv store
d = {}

#count no of keys inserted and helps in retrieving vlans for s1,s2,s3
keys_count = 0
# vlans is a list which contains vlan tunnel id for s1,s2,s3 for each key k
vlans = []

def ipv4_lpm_rules(p4info_helper,ingress_sw,dst_mac_addr, dst_ip_addr,dport):
    table_entry = p4info_helper.buildTableEntry(
        table_name="MyIngress.ipv4_lpm",
        match_fields={
            "hdr.ipv4.dstAddr": (dst_ip_addr, 32)
        },
        action_name="MyIngress.ipv4_forward",
        action_params={
            "dstAddr": dst_mac_addr,
            "port": dport,
        })
    ingress_sw.WriteTableEntry(table_entry)
    print "Installed ipv4_lpm_rules rule on %s" % ingress_sw.name

def ipv4_lpm_rules_set_default(p4info_helper,ingress_sw):
    table_entry = p4info_helper.buildTableEntry(
        table_name="MyIngress.ipv4_lpm",
        match_fields={
        },
        default_action="True",
        action_name="MyIngress.drop",
        action_params={
        })
    ingress_sw.WriteTableEntry(table_entry)
    print "Installed ipv4_lpm_rules_set_default rule on %s" % ingress_sw.name

def match_key_rules(p4info_helper,ingress_sw,traffic_code,code_value):
    table_entry = p4info_helper.buildTableEntry(
        table_name="MyIngress.match_key",
        match_fields={
            "hdr.data.epc_traffic_code": traffic_code
        },
        action_name="MyIngress.match_key_get_val",
        action_params={
            "val": code_value
        })
    ingress_sw.WriteTableEntry(table_entry)
    print "Installed match_key_rules on %s" % ingress_sw.name

def controller_rules(p4info_helper,ingress_sw):
    table_entry = p4info_helper.buildTableEntry(
        table_name="MyIngress.controller",
        match_fields={
        },
        action_name="MyIngress.send_to_controller",
        action_params={
        })
    ingress_sw.WriteTableEntry(table_entry)
    print "Installed controller_rules on %s" % ingress_sw.name

def kv_store_rules(p4info_helper,ingress_sw,key,value):
    table_entry = p4info_helper.buildTableEntry(
        table_name="MyIngress.kv_store",
        match_fields={
            "hdr.kv.key1" : key
        },
        action_name="MyIngress.populate_kv",
        action_params={
            "value" : value,
        })
    ingress_sw.WriteTableEntry(table_entry)
    print "Installed kv_store_rules on %s" % ingress_sw.name

#  UPlink tunnel tables populate

def s1_s2_tunnel_rules_uplink(p4info_helper,ingress_sw,ip_tunnel_s1,op_tunnel_s1,egress_port_s1):
    table_entry = p4info_helper.buildTableEntry(
        table_name="MyIngress.ip_op_tun_s1_uplink",
        match_fields={
            "hdr.vlan.vid" : ip_tunnel_s1
        },
        action_name="MyIngress.populate_ip_op_tun_s1_uplink",
        action_params={
            "op_tunnel_s1" : op_tunnel_s1,
            "egress_port_s1" : egress_port_s1,

        })
    ingress_sw.WriteTableEntry(table_entry)
    print "Installed kv_store_rules on %s" % ingress_sw.name

def s2_s3_tunnel_rules_uplink(p4info_helper,ingress_sw,ip_tunnel_s2,op_tunnel_s2,egress_port_s2):
    table_entry = p4info_helper.buildTableEntry(
        table_name="MyIngress.ip_op_tun_s2_uplink",
        match_fields={
            "hdr.vlan.vid" : ip_tunnel_s2
        },
        action_name="MyIngress.populate_ip_op_tun_s2_uplink",
        action_params={
            "op_tunnel_s2" : op_tunnel_s2,
            "egress_port_s2" : egress_port_s2,
        })
    ingress_sw.WriteTableEntry(table_entry)
    print "Installed kv_store_rules on %s" % ingress_sw.name

def s3_ip_tunnel_egress_rules_uplink(p4info_helper,ingress_sw,ip_tunnel_s3,egress_port_s3):
    table_entry = p4info_helper.buildTableEntry(
        table_name="MyIngress.tun_egress_s3_uplink",
        match_fields={
            "hdr.vlan.vid" : ip_tunnel_s3
        },
        action_name="MyIngress.populate_tun_egress_s3_uplink",
        action_params={
            "egress_port_s3" : egress_port_s3,
        })
    ingress_sw.WriteTableEntry(table_entry)
    print "Installed kv_store_rules on %s" % ingress_sw.name


#  Downlink tunnel tables populate

def s3_s2_tunnel_rules_downlink(p4info_helper,ingress_sw,ip_tunnel_s3,op_tunnel_s3,egress_port_s3):
    table_entry = p4info_helper.buildTableEntry(
            table_name="MyIngress.ip_op_tun_s3_downlink",
            match_fields={
                "hdr.vlan.vid" : ip_tunnel_s3
            },
            action_name="MyIngress.populate_ip_op_tun_s3_downlink",
            action_params={
                "op_tunnel_s3" : op_tunnel_s3,
                "egress_port_s3" : egress_port_s3,

            })
    ingress_sw.WriteTableEntry(table_entry)
    print "Installed s3_s2_tunnel_rules_downlink_rules on %s" % ingress_sw.name

def s2_s1_tunnel_rules_uplink(p4info_helper,ingress_sw,ip_tunnel_s2,op_tunnel_s2,egress_port_s2):
    table_entry = p4info_helper.buildTableEntry(
            table_name="MyIngress.ip_op_tun_s2_downlink",
            match_fields={
                "hdr.vlan.vid" : ip_tunnel_s2
            },
            action_name="MyIngress.populate_ip_op_tun_s2_downlink",
            action_params={
                "op_tunnel_s2" : op_tunnel_s2,
                "egress_port_s2" : egress_port_s2,
            })
    ingress_sw.WriteTableEntry(table_entry)
    print "Installed s2_s1_tunnel_rules_uplink_rules on %s" % ingress_sw.name

def s1_ip_tunnel_egress_rules_uplink(p4info_helper,ingress_sw,ip_tunnel_s1,egress_port_s1):
    table_entry = p4info_helper.buildTableEntry(
            table_name="MyIngress.tun_egress_s1_downlink",
            match_fields={
                "hdr.vlan.vid" : ip_tunnel_s1
            },
            action_name="MyIngress.populate_tun_egress_s1_downlink",
            action_params={
                "egress_port_s1" : egress_port_s1,
            })
    ingress_sw.WriteTableEntry(table_entry)
    print "Installed s1_ip_tunnel_egress_rules_uplink_rules on %s" % ingress_sw.name


def readTableRules(p4info_helper, sw):
    """
    Reads the table entries from all tables on the switch.

    :param p4info_helper: the P4Info helper
    :param sw: the switch connection
    """
    print '\n----- Reading tables rules for %s -----' % sw.name
    for response in sw.ReadTableEntries():
        for entity in response.entities:
            entry = entity.table_entry
            # TODO For extra credit, you can use the p4info_helper to translate
            #      the IDs in the entry to names
            table_name = p4info_helper.get_tables_name(entry.table_id)
            print '%s: ' % table_name,
            for m in entry.match:
                print p4info_helper.get_match_field_name(table_name, m.field_id),
                print '%r' % (p4info_helper.get_match_field_value(m),),
            action = entry.action.action
            action_name = p4info_helper.get_actions_name(action.action_id)
            print '->', action_name,
            for p in action.params:
                print p4info_helper.get_action_param_name(action_name, p.param_id),
                print '%r' % p.value,
            print

def printCounter(p4info_helper, sw, counter_name, index):
    """
    Reads the specified counter at the specified index from the switch. In our
    program, the index is the tunnel ID. If the index is 0, it will return all
    values from the counter.

    :param p4info_helper: the P4Info helper
    :param sw:  the switch connection
    :param counter_name: the name of the counter from the P4 program
    :param index: the counter index (in our case, the tunnel ID)
    """
    for response in sw.ReadCounters(p4info_helper.get_counters_id(counter_name), index):
        for entity in response.entities:
            counter = entity.counter_entry
            print "%s %s %d: %d packets (%d bytes)" % (
                sw.name, counter_name, index,
                counter.data.packet_count, counter.data.byte_count
            )

def printGrpcError(e):
    print "gRPC Error:", e.details(),
    status_code = e.code()
    print "(%s)" % status_code.name,
    traceback = sys.exc_info()[2]
    print "[%s:%d]" % (traceback.tb_frame.f_code.co_filename, traceback.tb_lineno)



class IPOption_MRI(IPOption):
    name = "MRI"
    option = 31
    fields_desc = [ _IPOption_HDR,
                    FieldLenField("length", None, fmt="B",
                                  length_of="swids",
                                  adjust=lambda pkt,l:l+4),
                    ShortField("count", 0),
                    FieldListField("swids",
                                   [],
                                   IntField("", 0),
                                   length_from=lambda pkt:pkt.count*4) ]

class TrafficHeader(Packet):
    name = 'Traffic Header'
    fields_desc = [
        BitField('traffic_code',0,24),
        BitField('key',0,128),
]

def get_if():
    ifs=get_if_list()
    iface=None # "h1-eth0"
    for i in get_if_list():
        if "eth0" in i:
            iface=i
            break;
    if not iface:
        print "Cannot find eth0 interface"
        exit(1)
    return iface

#since python2 does not have to_byes() function so it is implemented in user space here
def to_bytes(n, length, endianess='big'):
    h = '%x' % n
    s = ('0'*(len(h) % 2) + h).zfill(length*2).decode('hex')
    return s if endianess == 'big' else s[::-1]

def int_bytes_encoding(pkt_type,pkt_key,status):
        no_of_bits=int.bit_length(38900) # it will give no_of_bits required for key as 16 bit
        # REF : https://docs.python.org/3/library/stdtypes.html#bytes
        binary_type=to_bytes(pkt_type,3) # encode pkt_type in bytes format of length 3
        binary_key = to_bytes((pkt_key),no_of_bits)
        binary_status=to_bytes(status,1)
        a=bytearray(binary_type)
        b=bytearray(binary_key)
        c=bytearray(binary_status)
        a.extend(b)
        a.extend(c)
        return bytes(a)


#reply back to host for pkt type B
def reply_for_pktB(key,status):
    addr = socket.gethostbyname(socket.gethostname())
    iface = get_if()
    payload=int_bytes_encoding(pkt_type=2,pkt_key=key,status=status)
    print "payload = ", payload

    print "sending on interface %s to %s" % (iface, str(addr))
    pkt =  Ether(src=get_if_hwaddr(iface), dst='ff:ff:ff:ff:ff:ff')
    # setting udp dport to 65500  will help the switch to identify that it is a message from controller to populate KV pair
    pkt = pkt /IP(dst=dst_ip) / UDP(dport=65500, sport=random.randint(49152,65535)) / (payload)
    pkt.show2()
    sendp(pkt, iface=iface, verbose=False)

def generate_vlan_id(key):
    global keys_count
    global vlans
    keys_count+=3;
    vlans+=[(key+10)];
    vlans+=[(key+20)];
    vlans+=[(key+30)];
    print "vlans = ",vlans
    # return vlans

def int_bytes_encodingE(pkt_type,pkt_key):
        global vlans
        global keys_count
        no_of_bits=int.bit_length(38900) # it will give no_of_bits required for key as 16 bit
        # REF : https://docs.python.org/3/library/stdtypes.html#bytes
        binary_type=to_bytes(pkt_type,3) # encode pkt_type in bytes format of length 3
        binary_key = to_bytes((pkt_key),no_of_bits)
        for i in range(1,4):
            if i == 1:
                    # for s1 tunnel logic to get tunnel id
                    binary_vlan_s1 = to_bytes(vlans[keys_count-4+i],16)
            if i == 2:
                    # for s2 tunnel logic to get tunnel id
                    binary_vlan_s2 = to_bytes(vlans[keys_count-4+i],16)
            if i == 3:
                    # for s3 tunnel logic to get tunnel id
                    binary_vlan_s3 = to_bytes(vlans[keys_count-4+i],16)

        a=bytearray(binary_type)
        b=bytearray(binary_key)
        c=bytearray(binary_vlan_s1)
        d=bytearray(binary_vlan_s2)
        e=bytearray(binary_vlan_s3)

        a.extend(b)
        a.extend(c)
        a.extend(d)
        a.extend(e)

        return bytes(a)

def reply_for_pktE(key):
    addr = socket.gethostbyname(socket.gethostname())
    iface = get_if()
    payload=int_bytes_encodingE(pkt_type=6,pkt_key=key)
    print "payload = ", payload

    print "sending on interface %s to %s" % (iface, str(addr))
    pkt =  Ether(src=get_if_hwaddr(iface), dst='ff:ff:ff:ff:ff:ff')
    # setting udp dport to 65500  will help the switch to identify that it is a message from controller to populate KV pair
    pkt = pkt /IP(dst=dst_ip) / UDP(dport=65500, sport=random.randint(49152,65535)) / (payload)
    pkt.show2()
    sendp(pkt, iface=iface, verbose=False)

def populate_p4runtime_tables(p4info_helper,s1,s2,s3):
    global vlans
    global keys_count
    for i in range(1,4):
        if i == 1:
                # for s1 tunnel logic to get tunnel id
                ip_tunnel_s1 = vlans[keys_count-4+i]
        if i == 2:
                # for s2 tunnel logic to get tunnel id
                ip_tunnel_s2 = vlans[keys_count-4+i]
        if i == 3:
                # for s3 tunnel logic to get tunnel id
                ip_tunnel_s3 = vlans[keys_count-4+i]

    # UPLINK Rules install on s1 s2 s3
    s1_s2_tunnel_rules_uplink(p4info_helper,ingress_sw=s1,ip_tunnel_s1=ip_tunnel_s1,op_tunnel_s1=ip_tunnel_s2,egress_port_s1=2)
    s2_s3_tunnel_rules_uplink(p4info_helper,ingress_sw=s2,ip_tunnel_s2=ip_tunnel_s2,op_tunnel_s2=ip_tunnel_s3,egress_port_s2=2)
    s3_ip_tunnel_egress_rules_uplink(p4info_helper,ingress_sw=s3,ip_tunnel_s3=ip_tunnel_s3,egress_port_s3=1)
    print ("uplink rules installed on switch s1, s2 ans s3")

    # DOWNLINK Rules install on s1 s2 s3
    s3_s2_tunnel_rules_downlink(p4info_helper,ingress_sw=s3,ip_tunnel_s3=ip_tunnel_s3,op_tunnel_s3=ip_tunnel_s2,egress_port_s3=2)
    s2_s1_tunnel_rules_uplink(p4info_helper,ingress_sw=s2,ip_tunnel_s2=ip_tunnel_s2,op_tunnel_s2=ip_tunnel_s1,egress_port_s2=1)
    s1_ip_tunnel_egress_rules_uplink(p4info_helper,ingress_sw=s1,ip_tunnel_s1=ip_tunnel_s1,egress_port_s1=1)
    print ("downlink rules installed on switch s1, s2 ans s3")



def handle_pkt(pkt,p4info_helper,s1,s2,s3):
    print("got a packet")
    print("pkt length=")
    print(len(pkt))
    pkt.show()
    p1 = pkt.copy()
    p1 = p1.payload.payload.payload
    p1_bytes = bytes(p1)
    TrafficHeader(p1_bytes).show()
    x=TrafficHeader(p1_bytes)
    print x.traffic_code
    print x.key
    value = (x.key)+(5)
    status=0
    #checks duplicate key if duplicate key then don't populate it.
    if x.traffic_code == 2 :
        if x.key in d:
            print "duplicate key found !!"
            value=d[x.key]
            status=0
            reply_for_pktB(x.key,status)
        else:
            d[x.key]=value
            status=1
            #push key to switch kv store
            kv_store_rules(p4info_helper,ingress_sw=s1,key=int(x.key),value=int(value))
            # reply back to host that key value is inserted into switch kv kv_store
            reply_for_pktB(x.key,status)
        print d
    elif x.traffic_code == 5 :
        generate_vlan_id(key=int(x.key))
        populate_p4runtime_tables(p4info_helper,s1,s2,s3)
        readTableRules(p4info_helper, s1)
        readTableRules(p4info_helper, s2)
        readTableRules(p4info_helper, s3)
        reply_for_pktE(x.key)

    # readTableRules(p4info_helper, s1)

def main(p4info_file_path, bmv2_file_path):
    # Instantiate a P4Runtime helper from the p4info file
    p4info_helper= p4runtime_lib.helper.P4InfoHelper(p4info_file_path)

    try:
        # Create a switch connection object for s1 and s2;
        # this is backed by a P4Runtime gRPC connection.
        # Also, dump all P4Runtime messages sent to switch to given txt files.
        s1 = p4runtime_lib.bmv2.Bmv2SwitchConnection(
            name='s1',
            address='127.0.0.1:50051',
            device_id=0,
            proto_dump_file='logs/s1-p4runtime-requests.txt')
        s2 = p4runtime_lib.bmv2.Bmv2SwitchConnection(
            name='s2',
            address='127.0.0.1:50052',
            device_id=1,
            proto_dump_file='logs/s2-p4runtime-requests.txt')
        s3 = p4runtime_lib.bmv2.Bmv2SwitchConnection(
            name='s3',
            address='127.0.0.1:50053',
            device_id=2,
            proto_dump_file='logs/s3-p4runtime-requests.txt')

        # Send master arbitration update message to establish this controller as
        # master (required by P4Runtime before performing any other write operation)
        s1.MasterArbitrationUpdate()
        s2.MasterArbitrationUpdate()
        s3.MasterArbitrationUpdate()

        # Install the P4 program on the switches
        s1.SetForwardingPipelineConfig(p4info=p4info_helper.p4info,
                                       bmv2_json_file_path=bmv2_file_path)
        print "Installed P4 Program using SetForwardingPipelineConfig on s1"
        s2.SetForwardingPipelineConfig(p4info=p4info_helper.p4info,
                                       bmv2_json_file_path=bmv2_file_path)
        print "Installed P4 Program using SetForwardingPipelineConfig on s2"
        s3.SetForwardingPipelineConfig(p4info=p4info_helper.p4info,
                                       bmv2_json_file_path=bmv2_file_path)
        print "Installed P4 Program using SetForwardingPipelineConfig on s3"

        ipv4_lpm_rules(p4info_helper, ingress_sw=s1,dst_mac_addr="00:00:00:00:03:02",
                            dst_ip_addr="10.0.3.2",dport=2)
        ipv4_lpm_rules(p4info_helper, ingress_sw=s2,dst_mac_addr="00:00:00:00:03:02",
                            dst_ip_addr="10.0.3.2",dport=2)
        ipv4_lpm_rules(p4info_helper, ingress_sw=s3,dst_mac_addr="00:00:00:00:03:02",
                            dst_ip_addr="10.0.3.2",dport=1)

        ipv4_lpm_rules(p4info_helper, ingress_sw=s1,dst_mac_addr="00:00:00:00:01:01",
                            dst_ip_addr="10.0.1.1",dport=1)
        ipv4_lpm_rules_set_default(p4info_helper,ingress_sw=s1)

        match_key_rules(p4info_helper,ingress_sw=s1,traffic_code=1,code_value=2)
        match_key_rules(p4info_helper,ingress_sw=s1,traffic_code=3,code_value=4)

        controller_rules(p4info_helper,ingress_sw=s1)

        readTableRules(p4info_helper, s1)

        # Print the tunnel counters every 2 seconds
        while True:
            #total_packets_recvd=0;
            ifaces = filter(lambda i: 'eth' in i, os.listdir('/sys/class/net/'))
            iface = ifaces[0]
            print("sniffing on %s" % iface)
            sys.stdout.flush()
            #print ("before sniff")
            sniff(filter="udp and host 10.0.1.1 and dst port 1234", iface = iface,
                  prn = lambda x: handle_pkt(x,p4info_helper,s1,s2,s3))
            #print("total_packets_recvd = ",total_packets_recvd)
            # sleep(2)
            # print '\n----- Reading tunnel counters -----'
            # printCounter(p4info_helper, s1, "MyIngress.ingressTunnelCounter", 100)
            # printCounter(p4info_helper, s2, "MyIngress.egressTunnelCounter", 100)
            # printCounter(p4info_helper, s2, "MyIngress.ingressTunnelCounter", 200)
            # printCounter(p4info_helper, s1, "MyIngress.egressTunnelCounter", 200)

    except KeyboardInterrupt:
        print " Shutting down."
    except grpc.RpcError as e:
        printGrpcError(e)

    ShutdownAllSwitchConnections()

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='P4Runtime Controller')
    parser.add_argument('--p4info', help='p4info proto in text format from p4c',
                        type=str, action="store", required=False,
                        default='./build/advanced_tunnel.p4info')
    parser.add_argument('--bmv2-json', help='BMv2 JSON file from p4c',
                        type=str, action="store", required=False,
                        default='./build/advanced_tunnel.json')
    args = parser.parse_args()

    if not os.path.exists(args.p4info):
        parser.print_help()
        print "\np4info file not found: %s\nHave you run 'make'?" % args.p4info
        parser.exit(1)
    if not os.path.exists(args.bmv2_json):
        parser.print_help()
        print "\nBMv2 JSON file not found: %s\nHave you run 'make'?" % args.bmv2_json
        parser.exit(1)
    main(args.p4info, args.bmv2_json)

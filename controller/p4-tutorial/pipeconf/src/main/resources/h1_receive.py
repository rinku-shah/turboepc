#!/usr/bin/env python
import sys
import random
import struct
import os
import socket

from scapy.all import sniff, sendp, hexdump, get_if_list, get_if_hwaddr
from scapy.all import Packet, IPOption
from scapy.all import ShortField, IntField, LongField, BitField, FieldListField, FieldLenField
from scapy.all import IP, UDP, Raw
from scapy.all import Ether,TCP,Dot1Q
from scapy.layers.inet import _IPOption_HDR

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
        BitField('value',0,128),
]

class TunnelHeader(Packet):
    name = 'Tunnel Header'
    fields_desc = [
        BitField('traffic_code',0,24),
        BitField('key',0,128),
        BitField('s1_tunnel_id',0,128),
        BitField('s2_tunnel_id',0,128),
        BitField('s3_tunnel_id',0,128),
]

def get_if():
    ifs=get_if_list()
    iface=None
    for i in get_if_list():
        if "eth0" in i:
            iface=i
            break;
    if not iface:
        print ("Cannot find eth0 interface")
        exit(1)
    return iface

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


def int_bytes_encoding(pkt_type,key):
    if (pkt_type == 2)  or (pkt_type == 5):
        bits=int.bit_length(7)          # it gives the number of bits required for pkt_type as 3
        packet_type =(pkt_type).to_bytes(bits,byteorder='big')
        no_of_bits=int.bit_length(38900) # it will give no_of_bits required for key as 16 bit
        # REF : https://docs.python.org/3/library/stdtypes.html#bytes
        binary_key = (key).to_bytes(no_of_bits,byteorder='big')
        a=bytearray(packet_type)
        b=bytearray(binary_key)
        a.extend(b)
        # a.extend(b)
        return bytes(a)
    elif (pkt_type == 3) :
        bits=int.bit_length(7)          # it gives the number of bits required for pkt_type as 3
        packet_type =(pkt_type).to_bytes(bits,byteorder='big')
        no_of_bits=int.bit_length(38900) # it will give no_of_bits required for key as 16 bit
        # REF : https://docs.python.org/3/library/stdtypes.html#bytes
        binary_key = (key).to_bytes(no_of_bits,byteorder='big')
        value=0
        binary_value = (value).to_bytes(no_of_bits,byteorder='big')
        a=bytearray(packet_type)
        b=bytearray(binary_key)
        c=bytearray(binary_value)
        a.extend(b)
        a.extend(c)
        return bytes(a)

    else:
        bits=int.bit_length(7)
        packet_type =(pkt_type).to_bytes(bits,byteorder='big')
        return packet_type #it is a bytes object


def int_bytes_decoding(bin_pkt_type,bin_key,bin_value):
    print ("pkt_type = ",bin_pkt_type)
    print ("packet_key = ",packet_key)
    print ("packet_value = ",packet_value)

#  decoding pkt type F(6) which is response of pkt type E
def int_bytes_decoding_F(bin_pkt_type,bin_key,s1_tunnel_id,s2_tunnel_id,s3_tunnel_id):
    print ("bin_pkt_type = ",bin_pkt_type)
    print ("packet_key = ",bin_key)
    print ("s1_tunnel_id = ",s1_tunnel_id)
    addr = socket.gethostbyname("10.0.3.2")
    iface = get_if()
    print ("sending on interface %s to %s" % (iface, str(addr)))
    pkt =  Ether(src=get_if_hwaddr(iface), dst='ff:ff:ff:ff:ff:ff')/Dot1Q(vlan=s1_tunnel_id)
    #send pkt type 7 which will be routed via tunnels which were setup by packet type 5
    pkt = pkt /IP(dst=addr) / UDP(dport=1234, sport=random.randint(49152,65535)) / int_bytes_encoding(pkt_type=7,key=0)
    pkt.show2()
    sendp(pkt, iface=iface, verbose=False)

    print ("s1_tunnel_id = ",s1_tunnel_id)
    print ("s2_tunnel_id = ",s2_tunnel_id)
    print ("s3_tunnel_id = ",s3_tunnel_id)


def handle_pkt(pkt):
    print ("got a packet")
    pkt.show2()
    p1 = pkt.copy()
    p1 = p1.payload.payload.payload
    p1_bytes = bytes(p1)
    # TrafficHeader(p1_bytes).show()
    x=TrafficHeader(p1_bytes)
    if x.traffic_code == 2 :
        int_bytes_decoding(x.traffic_code,x.key,x.value)
    elif x.traffic_code == 6 :
        p2=pkt.copy()
        p2 = p2.payload.payload.payload
        p2_bytes = bytes(p2)
        # TunnelHeader(p2_bytes).show()
        y = TunnelHeader(p2_bytes)
        int_bytes_decoding_F(bin_pkt_type=y.traffic_code,bin_key=y.key,s1_tunnel_id=y.s1_tunnel_id,s2_tunnel_id=y.s2_tunnel_id,s3_tunnel_id=y.s3_tunnel_id)
    sys.stdout.flush()


def main():
    ifaces =list(filter(lambda i: 'eth' in i, os.listdir('/sys/class/net/')))
    iface = ifaces[0]
    print("sniffing on %s" % iface)
    sys.stdout.flush()
    #filter pkt type D (which is reply of pkt type C) only
    sniff(filter="udp port 65500 and host 10.0.2.15  ", iface = iface,
          prn = lambda x: handle_pkt(x))

if __name__ == '__main__':
    main()

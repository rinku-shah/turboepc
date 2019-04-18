#!/usr/bin/env python

import argparse
import sys
import socket
import random
import struct
import commands
import os
import mycontroller

from datetime import datetime
from scapy.all import sniff, sendp,send, hexdump, get_if_list, get_if_hwaddr
from scapy.all import Packet, IPOption
from scapy.all import ShortField, IntField, LongField, BitField, FieldListField, FieldLenField, ByteField
from scapy.all import Ether, IP, UDP, TCP, Raw
from scapy.layers.inet import _IPOption_HDR
from collections import deque
from collections import defaultdict

Traffic_size = 24
dst_ip="10.0.1.1" # this will be used in populate_switch_keys function as dst ip addr of switch

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
        BitField('key',0,8),
]
def infohelper(p4info_helper):
    # global p4infohelper = p4info_helper
    pass
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
#used to send key value pair to switch to add to one of the switch's table
def populate_switch_keys(key,value):
    addr = socket.gethostbyname(dst_ip)
    iface = get_if()
    print len(str(key))
    #assuming key will be of 2 digits always
    payload=str('@'+str(key)+'@'+str(value))
    print "payload = ", payload
    print "sending on interface %s to %s" % (iface, str(addr))
    pkt =  Ether(src=get_if_hwaddr(iface), dst='ff:ff:ff:ff:ff:ff')
    # setting udp dport to 97800  will help the switch to identify that it is a message from controller to populate KV pair
    pkt = pkt /IP(dst=addr) / UDP(dport=7800, sport=random.randint(49152,65535)) / (payload)
    pkt.show2()
    sendp(pkt, iface=iface, verbose=False)
    # global p4info_helper
    mycontroller.kv_store_rules(mycontroller.p4info_helper,ingress_sw=mycontroller.s1,key=key,value=value)

def handle_pkt(pkt):
    print("got a packet")
    print("pkt length=")
    print(len(pkt))
    pkt.show()
    d = dict()
    p1 = pkt.copy()
    p1 = p1.payload.payload.payload
    p1_bytes = bytes(p1)
    TrafficHeader(p1_bytes).show()
    x=TrafficHeader(p1_bytes)
    print x.traffic_code
    y=hex((x.key))
    key=int(y[2:][:(len(y[2:])-1)])
    print key
    value = (key)+(5)
    d[key]=value
    print d
    populate_switch_keys(key,value)

def main():
    #total_packets_recvd=0;
    ifaces = filter(lambda i: 'eth' in i, os.listdir('/sys/class/net/'))
    iface = ifaces[0]
    print("sniffing on %s" % iface)
    sys.stdout.flush()
    #print ("before sniff")
    sniff(filter="udp and host 10.0.1.1 and dst port 1234", iface = iface,
          prn = lambda x: handle_pkt(x))
    #print("total_packets_recvd = ",total_packets_recvd)
if __name__ == '__main__':
    main()

#!/usr/bin/env python
import sys
import struct
import os
import socket
import random

from scapy.all import sniff, sendp, hexdump, get_if_list, get_if_hwaddr
from scapy.all import Packet, IPOption
from scapy.all import ShortField, IntField, LongField, BitField, FieldListField, FieldLenField
from scapy.all import IP, UDP, Raw
from scapy.all import Ether,TCP,Dot1Q
from scapy.layers.inet import _IPOption_HDR

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
    bits=int.bit_length(7)
    packet_type =(pkt_type).to_bytes(bits,byteorder='big')
    return packet_type #it is a bytes object


def handle_pkt(pkt):
    print ("got a packet")
    pkt.show2()
    sys.stdout.flush()


def main():
    ifaces = list(filter(lambda i: 'eth' in i, os.listdir('/sys/class/net/')))
    iface = ifaces[0]
    print ("sniffing on", iface)
    sys.stdout.flush()
    sniff(filter="udp port 65500 and host 10.0.3.2", iface = iface,
          prn = lambda x: handle_pkt(x))

if __name__ == '__main__':
    main()

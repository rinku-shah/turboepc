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
    # send a packet in reply to packet code 7 which is just recieved from h1
    addr = socket.gethostbyname("10.0.1.1")
    iface = get_if()
    print ("sending on interface %s to %s" % (iface, str(addr)))
    pkt =  Ether(src=get_if_hwaddr(iface), dst='ff:ff:ff:ff:ff:ff')/Dot1Q(vlan=1330)
    #send pkt type 8 which will be routed via downlink tunnels which were setup by packet type 5
    pkt = pkt /IP(dst=addr) / UDP(dport=65500, sport=random.randint(49152,65535)) / int_bytes_encoding(pkt_type=8,key=0)
    pkt.show2()
    sendp(pkt, iface=iface, verbose=False)
    sys.stdout.flush()


def main():
    ifaces = list(filter(lambda i: 'eth' in i, os.listdir('/sys/class/net/')))
    iface = ifaces[0]
    print ("sniffing on", iface)
    sys.stdout.flush()
    sniff(filter="udp", iface = iface,
          prn = lambda x: handle_pkt(x))

if __name__ == '__main__':
    main()

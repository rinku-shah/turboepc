#!/usr/bin/env python
import sys
import argparse
import socket
import random
import struct
import os

from scapy.all import sendp, send, get_if_list, get_if_hwaddr
from scapy.all import Packet
from scapy.all import Ether, IP, UDP, TCP, Raw,Dot1Q
from scapy.layers.inet import _IPOption_HDR
from scapy.all import Packet, IPOption
from scapy.all import ShortField, IntField, LongField, BitField, FieldListField, FieldLenField, ByteField
from scapy.all import sniff, sendp,send, hexdump, get_if_list, get_if_hwaddr



def get_if():
    ifs=get_if_list()
    iface=None # "h1-eth0"
    for i in get_if_list():
        if "eth0" in i:
            iface=i
            break;
    if not iface:
        print ("Cannot find eth0 interface")
        exit(1)
    return iface

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


def send_keys(pkt_type,key,iface,addr):
    #pkt type 2 will send a key and the controller will populate the switch cache and reply back to h1
    #if key is duplicate it returns 0 else 1

    #pkt type 3 will send a key and get key value as reply from switch using the switch cache which is of type D.
    pkt =  Ether(src=get_if_hwaddr(iface), dst='ff:ff:ff:ff:ff:ff')
    pkt = pkt /IP(dst=addr) / UDP(dport=1234, sport=random.randint(49152,65535)) / int_bytes_encoding(pkt_type=pkt_type,key=key)
    pkt.show2()
    sendp(pkt, iface=iface, verbose=False)


def main():

    if len(sys.argv)<2:
        print ('pass 2 arguments: <destination> ')
        exit(1)

    addr = socket.gethostbyname(sys.argv[1])
    iface = get_if()
    print ("sending on interface %s to %s" % (iface, str(addr)))
    pkt =  Ether(src=get_if_hwaddr(iface), dst='ff:ff:ff:ff:ff:ff')
    #pkt = pkt /IP(dst=addr) / TCP(dport=1234, sport=random.randint(49152,65535)) / sys.argv[2]
    # pkt = pkt /IP(dst=addr) / UDP(dport=1234, sport=random.randint(49152,65535)) / int_bytes_encoding(pkt_type=0,key=0)
    # pkt.show2()
    # sendp(pkt, iface=iface, verbose=False)
    #
    # pkt =  Ether(src=get_if_hwaddr(iface), dst='ff:ff:ff:ff:ff:ff')
    # pkt = pkt /IP(dst=addr) / UDP(dport=1234, sport=random.randint(49152,65535)) / int_bytes_encoding(pkt_type=1,key=0)
    # pkt.show2()
    # sendp(pkt, iface=iface, verbose=False)

    #send keys for load testing for pkt type C
    # for key in range(1300,1310):
        # send_keys(pkt_type=2,key,iface,addr)
        # send_keys(pkt_type=3,key,iface,addr)
    for key in range(1300,1302):
        #send pkt type E format  : E-> Key it will ask controller to setup tunnel rules
        send_keys(5,key,iface,addr)



if __name__ == '__main__':
    main()

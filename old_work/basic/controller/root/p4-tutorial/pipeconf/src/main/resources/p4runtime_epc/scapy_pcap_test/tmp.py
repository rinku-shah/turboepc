from scapy.all import rdpcap, Packet
from scapy.all import IntField, ShortField, ByteField, BitField

class TrafficHeader(Packet):
    name = 'Traffic Header'
    fields_desc = [
        BitField('traffic_code',0,8),
        BitField('key',0,16),
        ]
packets=rdpcap('eth0_in.pcap')
for i in range(0,6):
    p1 = packets[i].copy()
    p1.show2()

    p1 = p1.payload.payload.payload

    p1_bytes = bytes(p1)

    TrafficHeader(p1_bytes).show()

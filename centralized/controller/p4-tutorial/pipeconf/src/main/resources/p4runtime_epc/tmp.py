from scapy.all import rdpcap, Packet
from scapy.all import IntField, ShortField, ByteField, BitField
packets = rdpcap('eth0_out.pcap')
class TrafficHeader(Packet):
    name = 'Traffic Header'
    fields_desc = [
        BitField('traffic_code',0,8),
        BitField('key',0,16),
        ]
for i in range(0,6):
    p1 = packets[i].copy()
    p1.show()

    p1 = p1.payload.payload.payload

    p1_bytes = bytes(p1)

    TrafficHeader(p1_bytes).show()
p1_bytes = p1_bytes[INTSize:]

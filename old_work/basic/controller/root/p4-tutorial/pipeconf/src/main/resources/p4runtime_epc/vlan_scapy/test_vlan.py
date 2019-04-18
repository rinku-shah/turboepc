import sys
from scapy.all import rdpcap, wrpcap, NoPayload, Ether, Dot1Q

# read all packets into buffer
# WARNING works only for small files
packets = []

for packet in rdpcap(sys.argv[1]):
    # gets the first layer of the current packet
    layer = packet.firstlayer()
    # loop over the layers
    while not isinstance(layer, NoPayload):
        if 'chksum' in layer.default_fields:
            del layer.chksum

        if (type(layer) is Ether):
            # adjust ether type
            layer.type = 33024
            # add 802.1q layer between Ether and IP
            dot1q = Dot1Q(vlan=42)
            dot1q.add_payload(layer.payload)
            layer.remove_payload()
            layer.add_payload(dot1q)
            layer = dot1q

        # advance to the next layer
        layer = layer.payload
    packets.append(packet)

wrpcap(sys.argv[2], packets)
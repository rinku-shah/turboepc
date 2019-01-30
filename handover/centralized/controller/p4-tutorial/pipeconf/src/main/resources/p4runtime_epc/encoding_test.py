pkt_type = 2
key = 50
bits=int.bit_length(7)          # it gives the number of bits required for pkt_type as 3
packet_type =(pkt_type).to_bytes(bits,byteorder='little')
no_of_bits=int.bit_length(38900) # it will give no_of_bits required for key as 16 bit
# REF : https://docs.python.org/3/library/stdtypes.html#bytes
binary_key = (key).to_bytes(no_of_bits,byteorder='little')
a=bytearray(packet_type)
print ("a = ",a)
b=bytearray(binary_key)
a.extend(b)
print (bytes(a))

This code is for sending UDP control Packets inside a TCP stream by using TUN device.
The normal RAW IP+UDP packet is sent to TUN device folllowed by a code which reads from TUN device and then writes it onto a TCP socket.
However, the SGW P4-code modifies the TCP payload and updates the TCP checksum but the end host drops the pcaket saying incorrect checksum so the code is not working.

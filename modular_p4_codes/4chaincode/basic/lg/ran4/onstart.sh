sudo ethtool --offload  eth1  rx off  tx off
sudo ethtool -K eth1 gso off
sudo route add -net 192.168.4.2 netmask 255.255.255.255 gw 192.168.11.2 dev eth1

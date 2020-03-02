sudo ifconfig vf0_0 down
sudo ifconfig vf0_0 hw ether 00:33:33:33:33:33
sudo ip link set vf0_0 up
sudo ip address add 192.168.2.4/24 dev vf0_0
sudo ethtool --offload  vf0_0  rx off  tx off
sudo ethtool -K vf0_0 gso off
sudo arp -s 192.168.2.2 00:11:11:11:11:11 -i vf0_0
sudo arp -s 192.168.2.3 00:22:22:22:22:22 -i vf0_0

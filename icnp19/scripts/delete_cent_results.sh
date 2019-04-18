
#Copy Cpu Util
rm /home/vikas/icnp19/scripts/*.txt 
sshpass -p qwer1234 ssh mv@192.168.100.1 -t 'rm -f /home/mv/scripts/*_util.txt'

#Delete stats for offload clone
rm /var/lib/lxc/ran1/rootfs/home/ubuntu/turboepc/modular_p4_codes/1chaincode/traditional/lg/bitwise_lg/stats.csv

#Change permissions
#chmod 777 -R *

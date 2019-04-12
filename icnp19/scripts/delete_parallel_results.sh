
#Copy Cpu Util
rm /home/vikas/icnp19/scripts/*.txt 
sshpass -p qwer1234 ssh mv@192.168.100.1 -t 'rm -f /home/mv/scripts/*_util.txt'

#Delete stats for offload clone
rm /var/lib/lxc/ran1/rootfs/home/ubuntu/clone_bitwise_lg/stats.csv
#rm /var/lib/lxc/offload_ran2/rootfs/home/ubuntu/ran2/clone_bitwise_lg/stats.csv
#rm /var/lib/lxc/offload_ran3/rootfs/home/ubuntu/ran3/clone_bitwise_lg/stats.csv
#rm /var/lib/lxc/offload_ran4/rootfs/home/ubuntu/ran4/clone_bitwise_lg/stats.csv

#Delete stats for centralized
#rm /var/lib/lxc/ran1/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv
#rm /var/lib/lxc/ran2/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv
#rm /var/lib/lxc/ran3/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv
#rm /var/lib/lxc/ran4/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv
#rm /var/lib/lxc/ran5/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv
#rm /var/lib/lxc/ran6/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv

#Change permissions
#chmod 777 -R *

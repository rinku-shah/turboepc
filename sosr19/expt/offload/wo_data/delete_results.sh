
#Copy Cpu Util
rm /home/vikas/sosr19/expt/*.txt 
sshpass -p qwer1234 ssh anshuj@192.168.100.1 -t 'rm -f /home/anshuj/sosr19/expt/*_util.txt'

#Delete stats for offload clone
rm /var/lib/lxc/ran1/rootfs/home/ubuntu/p4epc/p4runtime_epc/clone_bitwise_lg/stats.csv
rm /var/lib/lxc/ran2/rootfs/home/ubuntu/p4epc/p4runtime_epc/clone_bitwise_lg/stats.csv
rm /var/lib/lxc/ran3/rootfs/home/ubuntu/p4epc/p4runtime_epc/clone_bitwise_lg/stats.csv
rm /var/lib/lxc/ran4/rootfs/home/ubuntu/p4epc/p4runtime_epc/clone_bitwise_lg/stats.csv
rm /var/lib/lxc/ran5/rootfs/home/ubuntu/p4epc/p4runtime_epc/clone_bitwise_lg/stats.csv
rm /var/lib/lxc/ran6/rootfs/home/ubuntu/p4epc/p4runtime_epc/clone_bitwise_lg/stats.csv

#Delete stats for centralized
#rm /var/lib/lxc/ran1/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv
#rm /var/lib/lxc/ran2/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv
#rm /var/lib/lxc/ran3/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv
#rm /var/lib/lxc/ran4/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv
#rm /var/lib/lxc/ran5/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv
#rm /var/lib/lxc/ran6/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv

#Change permissions
#chmod 777 -R *

#Copy Cpu Util
cp /home/vikas/sosr19/expt/*.txt . 
scp anshuj@192.168.100.1:/home/anshuj/sosr19/expt/*.txt . 

#Copy stats for offload clone
cp /var/lib/lxc/scale_ran1/rootfs/home/ubuntu/p4epc/p4runtime_epc/clone_bitwise_lg/stats.csv stats_1.csv
#cp /var/lib/lxc/ran2/rootfs/home/ubuntu/p4epc/p4runtime_epc/clone_bitwise_lg/stats.csv stats_2.csv
#cp /var/lib/lxc/ran3/rootfs/home/ubuntu/p4epc/p4runtime_epc/clone_bitwise_lg/stats.csv stats_3.csv
#cp /var/lib/lxc/ran4/rootfs/home/ubuntu/p4epc/p4runtime_epc/clone_bitwise_lg/stats.csv stats_4.csv
#cp /var/lib/lxc/ran5/rootfs/home/ubuntu/p4epc/p4runtime_epc/clone_bitwise_lg/stats.csv stats_5.csv
#cp /var/lib/lxc/ran6/rootfs/home/ubuntu/p4epc/p4runtime_epc/clone_bitwise_lg/stats.csv stats_6.csv

#Copy stats for centralized
#cp /var/lib/lxc/ran1/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv stats_1.csv
#cp /var/lib/lxc/ran2/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv stats_2.csv
#cp /var/lib/lxc/ran3/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv stats_3.csv
#cp /var/lib/lxc/ran4/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv stats_4.csv
#cp /var/lib/lxc/ran5/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv stats_5.csv
#cp /var/lib/lxc/ran6/rootfs/home/ubuntu/p4epc/p4runtime_epc/bitwise_lg/stats.csv stats_6.csv

#Copy sink throughput
#cp /var/lib/lxc/sink/rootfs/home/ubuntu/rinku/sink/throughput.csv sink_throughput.csv

#Change permissions
chmod 777 -R *

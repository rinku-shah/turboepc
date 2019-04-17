#Copy Cpu Util
cp /home/vikas/icnp19/scripts/*.txt . 
scp mv@192.168.100.1:/home/mv/scripts/*.txt . 

#Copy stats for offload clone
#cp /var/lib/lxc/ran1/rootfs/home/ubuntu/clone_bitwise_lg/stats.csv stats_1.csv
cp /var/lib/lxc/ran1/rootfs/home/ubuntu/turboepc/modular_p4_codes/4chain_3sgwscode/series/lg/read-timeout_lg/stats.csv stats_1.csv
#cp /var/lib/lxc/offload_ran2/rootfs/home/ubuntu/ran2/clone_bitwise_lg/stats.csv stats_2.csv
#cp /var/lib/lxc/offload_ran3/rootfs/home/ubuntu/ran3/clone_bitwise_lg/stats.csv stats_3.csv
#cp /var/lib/lxc/offload_ran4/rootfs/home/ubuntu/ran4/clone_bitwise_lg/stats.csv stats_4.csv

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

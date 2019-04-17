#Copy Cpu Util
cp /home/vikas/icnp19/scripts/*.txt . 
scp mv@192.168.100.1:/home/mv/scripts/*.txt . 

#Copy stats for offload clone
cp /var/lib/lxc/ran1/rootfs/home/ubuntu//bitwise_lg/stats.csv stats_1.csv

#Change permissions
chmod 777 -R *

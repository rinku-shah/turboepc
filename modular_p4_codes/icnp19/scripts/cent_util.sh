#! /bin/bash
# run as sudo

if [ "$#" -ne 3 ] ; then
        echo "usage ./util.sh <#ue> <no_of_sim_time_in_mins> <data_rate>"
        exit 1
fi


#if [ "$#" -ne 4 ] ; then
#        echo "usage ./cpu_util.sh <#ue> <no_of_sim_time_in_secs*100> <pid_ovs-vswitchd> <output_filename> <tmp_file_name>"
#        exit 1
#fi

#rt=`sudo lxc-info -p -n onos-controller|tr -d ' '|cut -d ':' -f2`
#rt=`sudo lxc-info -p -n onos-offload-controller|tr -d ' '|cut -d ':' -f2`

dg1=`sudo lxc-info -p -n dgw1|tr -d ' '|cut -d ':' -f2`

sg11=`sudo lxc-info -p -n sgw1|tr -d ' '|cut -d ':' -f2`

pg=`sudo lxc-info -p -n pgw|tr -d ' '|cut -d ':' -f2`

ran1=`sudo lxc-info -p -n ran1|tr -d ' '|cut -d ':' -f2`

sink=`sudo lxc-info -p -n sink|tr -d ' '|cut -d ':' -f2`

#Controller utilization
#sh cpu_util.sh $1 $2 $rt controller_util.txt tmp_c $3 "^%Cpu0 " &

#DGW utilization

sh cpu_util.sh $1 $2 $dg1 dgw1_util.txt tmp_d1 $3 "^%Cpu16 \|^%Cpu17 " &


#SGW utilization

sh cpu_util.sh $1 $2 $sg11 sgw11_util.txt tmp_s11 $3 "^%Cpu18 \|^%Cpu19 " & 

#PGW utilization

sh cpu_util.sh $1 $2 $pg pgw_util.txt tmp_p $3 "^%Cpu40 \|^%Cpu41 " & 

#UE utilization

sh cpu_util.sh $1 $2 $ran1 ran1_util.txt tmp_u1 $3 "^%Cpu0 \|^%Cpu1 \|^%Cpu2 \|^Cpu3 \|^%Cpu4 \|^%Cpu5 \|^%Cpu6 \|^Cpu7 \|^%Cpu8 \|^%Cpu9 \|^%Cpu10 \|^Cpu11 \|^%Cpu12 \|^%Cpu13 \|^%Cpu14 \|^Cpu15 \|^%Cpu20 \|^%Cpu21 \|^%Cpu22 \|^Cpu23 \|^%Cpu28 \|^%Cpu29 \|^%Cpu30 \|^Cpu31 \|^%Cpu32 \|^%Cpu33 \|^%Cpu34 \|^Cpu35 \|^%Cpu36 \|^%Cpu37 \|^%Cpu38 \|^Cpu39 " & 

#SINK utilization

sh cpu_util.sh $1 $2 $sink sink_util.txt tmp_si $3 "^%Cpu42 " 





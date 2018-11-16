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
dg2=`sudo lxc-info -p -n dgw2|tr -d ' '|cut -d ':' -f2`
dg3=`sudo lxc-info -p -n dgw3|tr -d ' '|cut -d ':' -f2`
dg4=`sudo lxc-info -p -n dgw4|tr -d ' '|cut -d ':' -f2`
dg5=`sudo lxc-info -p -n dgw5|tr -d ' '|cut -d ':' -f2`
dg6=`sudo lxc-info -p -n dgw6|tr -d ' '|cut -d ':' -f2`

sg1=`sudo lxc-info -p -n sgw1|tr -d ' '|cut -d ':' -f2`
sg2=`sudo lxc-info -p -n sgw2|tr -d ' '|cut -d ':' -f2`
sg3=`sudo lxc-info -p -n sgw3|tr -d ' '|cut -d ':' -f2`
sg4=`sudo lxc-info -p -n sgw4|tr -d ' '|cut -d ':' -f2`
sg5=`sudo lxc-info -p -n sgw5|tr -d ' '|cut -d ':' -f2`
sg6=`sudo lxc-info -p -n sgw6|tr -d ' '|cut -d ':' -f2`

pg=`sudo lxc-info -p -n pgw|tr -d ' '|cut -d ':' -f2`

ran1=`sudo lxc-info -p -n ran1|tr -d ' '|cut -d ':' -f2`
ran2=`sudo lxc-info -p -n ran2|tr -d ' '|cut -d ':' -f2`
ran3=`sudo lxc-info -p -n ran3|tr -d ' '|cut -d ':' -f2`
ran4=`sudo lxc-info -p -n ran4|tr -d ' '|cut -d ':' -f2`
ran5=`sudo lxc-info -p -n ran5|tr -d ' '|cut -d ':' -f2`
ran6=`sudo lxc-info -p -n ran6|tr -d ' '|cut -d ':' -f2`


sink=`sudo lxc-info -p -n sink|tr -d ' '|cut -d ':' -f2`

#Controller utilization
#sh cpu_util.sh $1 $2 $rt controller_util.txt tmp_c $3 "^%Cpu0 " &

#DGW utilization

sh cpu_util.sh $1 $2 $dg1 dgw1_util.txt tmp_d1 $3 "^%Cpu22 " &

sh cpu_util.sh $1 $2 $dg2 dgw2_util.txt tmp_d2 $3 "^%Cpu23 " & 

sh cpu_util.sh $1 $2 $dg3 dgw3_util.txt tmp_d3 $3 "^%Cpu24 " & 

sh cpu_util.sh $1 $2 $dg4 dgw4_util.txt tmp_d4 $3 "^%Cpu25 " &

sh cpu_util.sh $1 $2 $dg5 dgw5_util.txt tmp_d5 $3 "^%Cpu26 " &

sh cpu_util.sh $1 $2 $dg6 dgw6_util.txt tmp_d6 $3 "^%Cpu27 " &

#SGW utilization

sh cpu_util.sh $1 $2 $sg1 sgw1_util.txt tmp_s1 $3 "^%Cpu28 \|^%Cpu29 " & 

sh cpu_util.sh $1 $2 $sg2 sgw2_util.txt tmp_s2 $3 "^%Cpu30 \|^%Cpu31 " & 

sh cpu_util.sh $1 $2 $sg3 sgw3_util.txt tmp_s3 $3 "^%Cpu32 \|^%Cpu33 " & 

sh cpu_util.sh $1 $2 $sg4 sgw4_util.txt tmp_s4 $3 "^%Cpu34 \|^%Cpu35 " & 

sh cpu_util.sh $1 $2 $sg5 sgw5_util.txt tmp_s5 $3 "^%Cpu36 \|^%Cpu37 " & 

sh cpu_util.sh $1 $2 $sg6 sgw6_util.txt tmp_s6 $3 "^%Cpu38 \|^%Cpu39 " & 

#PGW utilization

sh cpu_util.sh $1 $2 $pg pgw_util.txt tmp_p $3 "^%Cpu40 \|^%Cpu41 \|^%Cpu42 " & 

#UE utilization

sh cpu_util.sh $1 $2 $ran1 ran1_util.txt tmp_u1 $3 "^%Cpu0 \|^%Cpu1 \|^%Cpu2 \|^Cpu3 " & 

sh cpu_util.sh $1 $2 $ran2 ran2_util.txt tmp_u2 $3 "^%Cpu4 \|^%Cpu5 \|^%Cpu6 \|^Cpu7 " & 

sh cpu_util.sh $1 $2 $ran3 ran3_util.txt tmp_u3 $3 "^%Cpu8 \|^%Cpu9 \|^%Cpu10 \|^Cpu11 " & 

sh cpu_util.sh $1 $2 $ran4 ran4_util.txt tmp_u4 $3 "^%Cpu12 \|^%Cpu13 \|^%Cpu14 \|^Cpu15 " & 

sh cpu_util.sh $1 $2 $ran5 ran5_util.txt tmp_u5 $3 "^%Cpu16 \|^%Cpu17 \|^%Cpu18 " & 

sh cpu_util.sh $1 $2 $ran6 ran6_util.txt tmp_u6 $3 "^%Cpu19 \|^%Cpu20 \|^%Cpu21 " & 

#SINK utilization

sh cpu_util.sh $1 $2 $sink sink_util.txt tmp_si $3 "^%Cpu43 \|^%Cpu44 " 





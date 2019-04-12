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

dg1=`sudo lxc-info -p -n scale_dgw1|tr -d ' '|cut -d ':' -f2`
dg2=`sudo lxc-info -p -n scale_dgw2|tr -d ' '|cut -d ':' -f2`
dg3=`sudo lxc-info -p -n scale_dgw3|tr -d ' '|cut -d ':' -f2`
dg4=`sudo lxc-info -p -n scale_dgw4|tr -d ' '|cut -d ':' -f2`

sg11=`sudo lxc-info -p -n scale_sgw1_1|tr -d ' '|cut -d ':' -f2`
sg12=`sudo lxc-info -p -n scale_sgw1_2|tr -d ' '|cut -d ':' -f2`
sg21=`sudo lxc-info -p -n scale_sgw2_1|tr -d ' '|cut -d ':' -f2`
sg22=`sudo lxc-info -p -n scale_sgw2_2|tr -d ' '|cut -d ':' -f2`
sg31=`sudo lxc-info -p -n scale_sgw3_1|tr -d ' '|cut -d ':' -f2`
sg32=`sudo lxc-info -p -n scale_sgw3_2|tr -d ' '|cut -d ':' -f2`
sg41=`sudo lxc-info -p -n scale_sgw4_1|tr -d ' '|cut -d ':' -f2`
sg42=`sudo lxc-info -p -n scale_sgw4_2|tr -d ' '|cut -d ':' -f2`

pg=`sudo lxc-info -p -n scale_pgw|tr -d ' '|cut -d ':' -f2`

ran1=`sudo lxc-info -p -n ran1|tr -d ' '|cut -d ':' -f2`
ran2=`sudo lxc-info -p -n ran2|tr -d ' '|cut -d ':' -f2`
ran3=`sudo lxc-info -p -n ran3|tr -d ' '|cut -d ':' -f2`
ran4=`sudo lxc-info -p -n ran4|tr -d ' '|cut -d ':' -f2`
#ran5=`sudo lxc-info -p -n ran5|tr -d ' '|cut -d ':' -f2`
#ran6=`sudo lxc-info -p -n ran6|tr -d ' '|cut -d ':' -f2`


sink=`sudo lxc-info -p -n sink|tr -d ' '|cut -d ':' -f2`

#Controller utilization
#sh cpu_util.sh $1 $2 $rt controller_util.txt tmp_c $3 "^%Cpu0 " &

#DGW utilization

sh cpu_util.sh $1 $2 $dg1 dgw1_util.txt tmp_d1 $3 "^%Cpu12 \|^%Cpu36 " &

sh cpu_util.sh $1 $2 $dg2 dgw2_util.txt tmp_d2 $3 "^%Cpu13 \|^%Cpu37 " & 

sh cpu_util.sh $1 $2 $dg3 dgw3_util.txt tmp_d3 $3 "^%Cpu14 \|^%Cpu38 " & 

sh cpu_util.sh $1 $2 $dg4 dgw4_util.txt tmp_d4 $3 "^%Cpu15 \|^%Cpu39 " &


#SGW utilization

sh cpu_util.sh $1 $2 $sg11 sgw11_util.txt tmp_s11 $3 "^%Cpu16 \|^%Cpu40 " & 
sh cpu_util.sh $1 $2 $sg12 sgw12_util.txt tmp_s12 $3 "^%Cpu17 \|^%Cpu41 " &

sh cpu_util.sh $1 $2 $sg21 sgw21_util.txt tmp_s21 $3 "^%Cpu18 \|^%Cpu42 " & 
sh cpu_util.sh $1 $2 $sg22 sgw22_util.txt tmp_s22 $3 "^%Cpu19 \|^%Cpu43 " &

sh cpu_util.sh $1 $2 $sg31 sgw31_util.txt tmp_s31 $3 "^%Cpu20 \|^%Cpu44 " & 
sh cpu_util.sh $1 $2 $sg32 sgw32_util.txt tmp_s32 $3 "^%Cpu21 \|^%Cpu45 " &

sh cpu_util.sh $1 $2 $sg41 sgw41_util.txt tmp_s41 $3 "^%Cpu22 \|^%Cpu46 " & 
sh cpu_util.sh $1 $2 $sg42 sgw42_util.txt tmp_s42 $3 "^%Cpu23 \|^%Cpu47 " &


#PGW utilization

sh cpu_util.sh $1 $2 $pg pgw_util.txt tmp_p $3 "^%Cpu9 \|^%Cpu33 " & 

#UE utilization

sh cpu_util.sh $1 $2 $ran1 ran1_util.txt tmp_u1 $3 "^%Cpu1 \|^%Cpu2 \|^%Cpu25 \|^Cpu26 " & 

sh cpu_util.sh $1 $2 $ran2 ran2_util.txt tmp_u2 $3 "^%Cpu3 \|^%Cpu4 \|^%Cpu27 \|^Cpu28 " & 

sh cpu_util.sh $1 $2 $ran3 ran3_util.txt tmp_u3 $3 "^%Cpu5 \|^%Cpu6 \|^%Cpu29 \|^Cpu30 " & 

sh cpu_util.sh $1 $2 $ran4 ran4_util.txt tmp_u4 $3 "^%Cpu7 \|^%Cpu8 \|^%Cpu31 \|^Cpu32 " & 


#SINK utilization

sh cpu_util.sh $1 $2 $sink sink_util.txt tmp_si $3 "^%Cpu10 " 





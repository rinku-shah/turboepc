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

rt=`sudo lxc-info -p -n onos-controller|tr -d ' '|cut -d ':' -f2`
#rt=`sudo lxc-info -p -n onos-offload-controller|tr -d ' '|cut -d ':' -f2`

#Controller utilization
sh cpu_util.sh $1 $2 $rt controller_util.txt tmp_c $3 "^%Cpu0 " 



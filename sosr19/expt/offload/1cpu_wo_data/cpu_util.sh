#!/bin/bash

if [ "$#" -ne 7 ] ; then
        echo "usage ./cpu_util.sh <#ue> <no_of_sim_time_in_mins> <container_pid> <output_filename> <temp_filename> <data_rate> <CPU core pattern>"
        exit 1
fi

#echo "usage ./cpu_util.sh <#ue> <no_of_sim_time_in_mins> <container_pid> <output_filename> <temp_filename> <data_rate> <CPU core pattern>"




# Per Container process, for CPU cores pinned to the process. Since container is working on multiple cores, and we have captured their CPU%, we add the CPUs of all cores in second awk command

#patt=$7
#Sample pattern'^%Cpu15 \|^%Cpu31 '
#top for single core
#top -bn 1 -p $3 -d 0.01|grep "$patt" |tr -s ' '|cut -d ' ' -f3,5 | awk '{s+=$1+$2; print s}' > $5
#top command for more than one cores
#top -bn1 -p 2962| tail -n1|tr -s ' '|cut -d ' ' -f10-11

#top -bn10 -p 2962 > tmp
#cat tmp|grep 2962|tr -s ' '|cut -d ' ' -f10-11| awk '{c+=$1; m+=$2; n++}END{print c/n, m/n}' 

#multiplied by 100 because the top command would run every 10 msec(convert min to msec)
ntimes=$(( $2 * 60 ))
#ntimes=$(( $2 * 60 * 416 ))

if [ -e $5 ]; then  
	rm -f $5
fi

#top -bn $ntimes -p $3 -d 0.001 >> $5
top -bn $ntimes -p $3 -d 1 >> $5

patt=$7
#total_cpu=`cat $5| grep "$patt" |tr -s ' '|cut -d ' ' -f3,5,11,15 | awk '{s=$1+$2+$3+$4; print s}'|awk '{s+=$1;}END{print s}'`
total_cpu=`cat $5| grep "$patt" |tr ',' ' ' |tr -s ' '|cut -d ' ' -f9 | awk '{s=100-$1; print s}'|awk '{s+=$1;}END{print s}'`
avg_cpu=$( echo "$total_cpu / $ntimes" | bc -l )

total_mem=`cat $5|grep $3|tr -s ' '|cut -d ' ' -f7|awk '{s+=$1;}END{print s}'`
avg_mem=$( echo "$total_mem / $ntimes" | bc -l )

total_wait=`cat $5| grep "$patt" |tr -s ':,' ' ' |cut -d ' ' -f10 | awk '{s+=$1;}END{print s}'`
avg_wait=$( echo "$total_wait / $ntimes" | bc -l )

if [ ! -f $4 ]; then  
	echo "#UE DataRate Avg%CPU AvgMem(KiB) Avg%Wait" > $4;
fi
printf "%d %s %0.2f %0.2f %0.2f\n" $1 $6 $avg_cpu $avg_mem $avg_wait>> $4
#echo $1 $6 $avg >> $4

#############################################

#avg=`cat $5|grep $3|tr -s ' '|cut -d ' ' -f10-11| awk '{cpu+=$1; mem+=$2; n++}END{print cpu/n, mem/n}'`

#if [ ! -f $4 ]; then  
#	echo "#UE    DataRate    Avg%CPU    Avg%Mem" >> $4;
#fi
#echo $1 $6 $avg >> $4

#printf "%d %0.2f %s\n" $1 $6 $avg >> $4






#######
#top -bn 1 -p $3 -d 0.01|grep "$patt" |tr -s ' '|cut -d ' ' -f3,5 | awk '{s+=$1+$2; print s}' | awk '{t+=$1} END{print t}' > $5

#Continue top for ntimes -1
#for i in `seq 2 $ntimes`; do
#top -bn 1 -p $3 -d 0.01|grep "$patt" |tr -s ' '|cut -d ' ' -f3,5 | awk '{s+=$1+$2; print s}' | awk '{t+=$1} END{print t}' >> $5;
#done

#Calculates %CPU Average
#avg=`awk '{ sum += $1; n++ } END { if (n > 0) print av=sum/n}' $5 `


#printf "%d %0.2f %s\n" $1 $avg $6 >> $4



# Past script
#echo "Number of times 'top' would run" $ntimes
#top -b -p 1505 -d 0.01|grep '^%Cpu'>>tmp 
#for i in `seq 1 $3`; do 


#        top -bn $ntimes -p $3 -d 0.01|grep '^%Cpu' > $5
#;

#top -bn 1 -p $3 -d 0.01|tail -n1|tr -s ' '|cut -d ' ' -f10 > $5;
#for i in `seq 1 $ntimes`; do 
#top -bn 1 -p $3 -d 0.01|tail -n1|tr -s ' '|cut -d ' ' -f10 >> $5;
#done

#avg=`awk '{ sum += $2+$4; n++ } END { if (n > 0) print av=sum/n;}' $5 `

#avg=`awk '{ sum += $1; n++ } END { if (n > 0) print av=sum/n;}' $5 `


#avg=`awk '{ sum += $1; n++ } END { if (n > 0) print av=sum/(n* "'$ncores'")}' $5 `

#!/bin/bash/
BEGIN{
FS = " ";
#sum_cpu =0;
#sum_delay=0;
}
{ 
    #sum_cpu =0;
    #sum_delay=0;
    #sum_ue=0;
    sum_ue=$1+$16+$31+$46+$61+$76;	
    sum_tpt=$5+$20+$35+$50+$65+$80;
    avg_delay=(($6+$21+$36+$51+$66+$81)*1000);#/6;
    print sum_ue, sum_tpt, avg_delay
}


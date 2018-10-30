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
    sum_ue=$1+$17+$32+$47+$62+$77;	
    sum_tpt=$5+$21+$36+$51+$66+$81;
    avg_delay=(($6+$22+$37+$52+$67+$82)*1000);#/6;
    sr_avg_delay=(($16+$32+$48+$64+$80+$96)); #*1000);
    print sum_ue, sum_tpt, avg_delay, sr_avg_delay
}


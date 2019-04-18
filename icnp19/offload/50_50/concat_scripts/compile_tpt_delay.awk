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
    sum_ue=$1+$17+$33+$49; #+$61+$76;	
    sum_tpt=$5+$21+$37+$53; #+$65+$80;
    avg_delay=(($6+$22+$38+$54)*1000)/4; #+$66+$81)*1000)/6;
    avg_sr_delay=(($16+$32+$48+$64)/1000)/4;
    print sum_ue, sum_tpt, avg_delay, avg_sr_delay;
}


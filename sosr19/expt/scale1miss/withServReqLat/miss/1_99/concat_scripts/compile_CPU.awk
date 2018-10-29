#!/bin/bash/
BEGIN{
FS = " ";
sum_cpu =0;
#sum_delay=0;
}
{ 
    #sum_cpu =0;
    #sum_delay=0;
    #sum_ue=0;
    #sum_ue=$1+$12+$23;	
    sum_cpu=$3+$8+$13+$18+$23+$28;
    #avg_delay=(($6+$17+$28)*1000)/3;
    print $1, sum_cpu
}


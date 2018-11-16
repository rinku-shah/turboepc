#!/bin/bash
set autoscale #scales axes automatically
unset log #remove any log-scaling
unset label #remove any prev labels
set terminal postscript eps enhanced color font 'Arial,18'
set output 'Designs.eps'
#set xtic 3
set ytic nomirror
set y2tic nomirror
#set title "LTE-EPC: Application End-to-end Delay(ms)"
#set xlabel "TurboEPC design choices"
set ylabel "Throughput (requests per sec)"
set y2label "Latency (ms)"

set style fill pattern 4
#set style data histogram
#set style histogram gap 2
set boxwidth 0.3 relative
#set size 1,0.5
#set key at 2,44
#set xrange [0:]
set yrange[0:600]
set y2range[0.1:15]
set xtics rotate
#set logscale y2
#set xtics border in scale 0,0 nomirror rotate by 45  offset character -1, -4, 0
plot 'Designs.dat' using 2:xtic(1) axes x1y1 title 'Service Request Throughput' lc rgb 'red' lw 2 with boxes ,\
         'Designs.dat' using 3 axes x1y2 title 'Service Request Latency' lc rgb 'black' pt 5 ps 2 with points


  #'scale1miss.dat' using 3 title 'Switch Table MISS' lc rgb 'black' lw 2  , \
 #'scale1miss.dat' using 4 title 'Centralized' lc rgb 'blue' lw 2
    # 'cuttlefish.dat' using 3 title 'Cuttlefish' lc rgb 'medium-blue' lw 2

unset style data
unset style histogram

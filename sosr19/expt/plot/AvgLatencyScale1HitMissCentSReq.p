#!/bin/bash
set autoscale #scales axes automatically
unset log #remove any log-scaling
unset label #remove any prev labels
set terminal postscript eps enhanced color font 'Arial,15'
set output 'AvgLatencyScale1HitMissCentSReq.eps'
#set xtic 3
set ytic auto
#set title "LTE-EPC: Service Request End-to-end Delay(us)"
set xlabel "Traffic Mix Ratios- AttachDetach:ServiceRequest"
set ylabel "Average Response Time (us)"

set style fill pattern 4
set style data histogram
set style histogram gap 2

#set size 1,0.5
#set key at 2,44
#set xrange [0:]
set yrange[0:7500]
#set xtics border in scale 0,0 nomirror rotate by 45  offset character -1, -4, 0
plot newhistogram fs pattern 1, 'scale1miss.dat' using 5:xtic(1) title 'Switch Table HIT' lc rgb 'red' lw 2  ,\
  'scale1miss.dat' using 6 title 'Switch Table MISS' lc rgb 'black' lw 2  , \
 'scale1miss.dat' using 7 title 'Centralized' lc rgb 'blue' lw 2
    # 'cuttlefish.dat' using 3 title 'Cuttlefish' lc rgb 'medium-blue' lw 2

unset style data
unset style histogram
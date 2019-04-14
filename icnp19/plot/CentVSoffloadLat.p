#!/bin/bash
set autoscale #scales axes automatically
unset log #remove any log-scaling
unset label #remove any prev labels
set terminal postscript eps enhanced color font 'Arial,15'
set output 'CentVSoffloadLat.eps'
#set xtic 2
set ytic auto
#set title "LTE-EPC: Application Throughput"
set xlabel  "LTE-EPC Traffic Mix"
set ylabel "End to end latency (msec)"
 
set style fill pattern 4
set style data histogram
set style histogram gap 2

set size 1,0.7
#set key at 5,7500
#set xrange [0:]
set yrange[0:8]
#set xtics border in scale 0,0 nomirror rotate by 45  offset character -1, -4, 0
#plot 'cent.dat' using 2:xtic(1) title 'Traditional EPC' lw 7,\
#     'offload.dat' using 2 title 'Split mode'  lw 7 , \
#     'cuttlefish.dat' using 2 title 'Cuttlefish'  lw 7
#     #'adaptive.dat' using 4 title 'Cuttlefish: wrong initial mode'  lw 7

plot newhistogram fs pattern 1, 'cent.dat' using 3:xtic(1) title 'Traditional-EPC'  lc rgb 'red' lw 2  ,\
   'offload.dat' using 3 title 'TurboEPC-Basic'  lc rgb 'black' lw 2 #, \
  #  'cuttlefish.dat' using 2 title 'Cuttlefish'  lc rgb 'medium-blue' lw 2
unset style data
unset style histogram

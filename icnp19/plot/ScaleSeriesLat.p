#!/bin/bash
set autoscale #scales axes automatically
unset log #remove any log-scaling
unset label #remove any prev labels
set terminal postscript eps enhanced color font 'Arial,15'
set output 'SeriesLat.eps'
#set xtic 3
set ytic auto
#set title "LTE-EPC: Application End-to-end Delay(ms)"
set xlabel "LTE-EPC Traffic Mix"
set ylabel "End to end latency (msec)"

set style fill pattern 4
set style data histogram
set style histogram gap 2

#set size 1,0.5
#set key at 2,44
#set xrange [0:]
set yrange[0:]
#set xtics border in scale 0,0 nomirror rotate by 45  offset character -1, -4, 0
plot newhistogram fs pattern 1, 'series.dat' using 3:xtic(1) title '1-sgw' lc rgb 'red' lw 2  ,\
  'series.dat' using 6 title '2-sgw' lc rgb 'black' lw 2  , \
 'series.dat' using 9 title '3-sgw' lc rgb 'blue' lw 2
    # 'cuttlefish.dat' using 3 title 'Cuttlefish' lc rgb 'medium-blue' lw 2

unset style data
unset style histogram
#
# Random graph on 1000 nodes. G(100, 1000) (Fri Apr 20 16:34:54 2018)
#

set title "Random graph on 1000 nodes. G(100, 1000)"
set key bottom right
set logscale xy 10
set format x "10^{%L}"
set mxtics 10
set format y "10^{%L}"
set mytics 10
set grid
set xlabel "Rank"
set ylabel "Singular value"
set tics scale 2
set terminal png font arial 10 size 1000,800
set output 'sval.RndGraph.png'
plot 	"sval.RndGraph.tab" using 1:2 title "" with linespoints pt 6

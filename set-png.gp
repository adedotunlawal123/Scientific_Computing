set terminal push
set terminal png background '#2e3440' font "Times,16"
set minussign
set border lc rgb '#eceff4'
set border linewidth 1.5
set linetype 1 lc rgb '#2687D7' lw 1.5
set linetype 2 lc rgb '#ed462f' lw 1.5
set linetype 3 lc rgb '#408806' lw 1.5
set linetype 4 lc rgb '#afaf87' lw 1.5
set linetype cycle 3
set title textcolor '#eceff4'
set label textcolor '#eceff4'
set key textcolor '#eceff4'
#set size square
#unset key
set output ARG1
replot
unset output
set terminal pop

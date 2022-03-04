! ./smooth 5 dip.dat > dip-smooth5.dat
! ./smooth 5 dip-smooth5.dat > dip-smooth5x2.dat
! ./smooth 5 dip-smooth5x2.dat > dip-smooth5x3.dat

set terminal dumb ansi256
plot "dip.dat" title "noisy data", \
 "dip-smooth5.dat" w l title "smoothed 5",\
 "dip-smooth5x2.dat" w l title "smoothed 5x2",\
 "dip-smooth5x3.dat" w l title "smoothed 5x3"

call '../../scripts/set-png.gp' 'dip.png'


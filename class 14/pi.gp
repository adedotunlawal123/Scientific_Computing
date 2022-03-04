! make pi
! echo 10 $(./pi -n 10) > pi.dat
! echo 100 $(./pi -n 100) >> pi.dat
! echo 1000 $(./pi -n 1000) >> pi.dat
! echo 10000 $(./pi -n 10000) >> pi.dat
! echo 100000 $(./pi -n 100000) >> pi.dat
! echo 1000000 $(./pi -n 1000000) >> pi.dat
! echo 10000000 $(./pi -n 10000000) >> pi.dat
! echo 100000000 $(./pi -n 100000000) >> pi.dat

set terminal dumb ansi256
unset key
set logscale x
plot "pi.dat" using 1:2 with linespoints, pi
call '../../scripts/set-png.gp' 'pi1.png'

set terminal dumb ansi256
unset key
set logscale
plot "pi.dat" using 1:(abs($2-pi)) with lp
call '../../scripts/set-png.gp' 'pi2.png'


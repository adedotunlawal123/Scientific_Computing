! make corners
! echo 10 $(./corners 10 | cut -c3- | xargs -n 8) > corners.dat
! echo 20 $(./corners 20 | cut -c3- | xargs -n 8) >> corners.dat
! echo 50 $(./corners 50 | cut -c3- | xargs -n 8) >> corners.dat
! echo 100 $(./corners 100 | cut -c3- | xargs -n 8) >> corners.dat
! echo 200 $(./corners 200 | cut -c3- | xargs -n 8) >> corners.dat
! echo 500 $(./corners 500 | cut -c3- | xargs -n 8) >> corners.dat
! echo 1000 $(./corners 1000 | cut -c3- | xargs -n 8) >> corners.dat
! echo 2000 $(./corners 2000 | cut -c3- | xargs -n 8) >> corners.dat
! echo 5000 $(./corners 5000 | cut -c3- | xargs -n 8) >> corners.dat
! echo 10000 $(./corners 10000 | cut -c3- | xargs -n 8) >> corners.dat
! echo 20000 $(./corners 20000 | cut -c3- | xargs -n 8) >> corners.dat
! echo 50000 $(./corners 50000 | cut -c3- | xargs -n 8) >> corners.dat
! echo 100000 $(./corners 100000 | cut -c3- | xargs -n 8) >> corners.dat

set terminal dumb ansi256
unset key
set logscale x
plot for [j=2:9] "corners.dat" using 1:(column(j)) w lp, 1.0/8
call '../../scripts/set-png.gp' 'corners.png'

! ./orbit > o.dat

set terminal dumb ansi256
set size square
unset key

unset object
set title "satellite in earth orbit"
unset label
set xlabel "time [hrs]"
set ylabel "distance [km from earth's center]"
unset key

plot "o.dat" using 1:2 w l
call '../../scripts/set-png.gp' 'distance.png'

set ylabel "polar angle [radians]"
plot "o.dat" using 1:3 w l
call '../../scripts/set-png.gp' 'angle.png'

set object 1 rect from -100,-100 to 100,100 fc lt 1 lw 0
set xlabel "x position [km]"
set ylabel "y position [km]"
plot "o.dat" using ($2*cos($3)):($2*sin($3)) w l
call '../../scripts/set-png.gp' 'orbit.png'



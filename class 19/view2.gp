! ./orbit_vel > ov.dat

set terminal dumb ansi256
set size square
unset key

set title "satellite in earth orbit"
unset label
set xlabel "x position [km]"
set ylabel "y position [km]"
set object 1 rect from -100,-100 to 100,100 fc lt 1 lw 0
plot "ov.dat" using ($2*cos($3)):($2*sin($3)) w l

call '../../scripts/set-png.gp' 'orbit2.png'

unset object
set xlabel "time [hrs]"
set ylabel "radial velocity [km/hr]"
plot "ov.dat" using 1:4 w l

call '../../scripts/set-png.gp' 'rdot.png'

unset object
set xlabel "time [hrs]"
set ylabel "angular velocity [radians/hr]"
plot "ov.dat" using 1:5 w l

call '../../scripts/set-png.gp' 'thetadot.png'

set xlabel "sin(theta)"
set ylabel "speed [km/hr]"
plot "ov.dat" using (sin($3)):(sqrt($4**2+($2*$5)**2)) w l

call '../../scripts/set-png.gp' 'speed.png'

set xlabel "time [hrs]"
set ylabel "speed [km/hr]"
plot "ov.dat" using 1:(sqrt($4**2+($2*$5)**2)) w l

call '../../scripts/set-png.gp' 'speed2.png'

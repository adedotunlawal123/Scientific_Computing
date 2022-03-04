set terminal dumb ansi256
set key bottom right
plot "trajectory.dat" u 0:5 w l title "kinetic energy", \
"" u 0:6 w l title "potential energy",\
"" u 0:($5+$6) w l title "total energy"

call '../../scripts/set-png.gp' 'en.png'


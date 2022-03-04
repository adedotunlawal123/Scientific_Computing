set terminal dumb ansi256
set xlabel "time elapsed"
plot "traj.dat" u 1:2 w l title "x coord", "" u 1:3 w l title "y coord"

set size square
set xlabel "x coord"
set ylabel "y coord"
set title "decaying satellite orbit"
unset key

plot "traj.dat" u 2:3 w l

call '../../scripts/set-png.gp' 'traj.png'


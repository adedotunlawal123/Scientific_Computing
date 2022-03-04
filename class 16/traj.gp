set terminal dumb ansi256
set key bottom right
plot "trajectory.dat" u 1:2 w l title "ball 1",\
     "" u 3:4 w l title "ball 2"

call '../../scripts/set-png.gp' 'traj.png'

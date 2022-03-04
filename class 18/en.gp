! test -e traj.dat || python3 well.py

set terminal dumb ansi256

plot[0:50] "traj.dat" index 0 using 1:4 w l title "energy"

call '../../scripts/set-png.gp' 'en.png'

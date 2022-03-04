! test -e traj.dat || python3 well.py

set terminal dumb ansi256

freq=0.15915494309189535
plot[0:100] \
  cos(2*pi*freq*x), \
  -sin(2*pi*freq*x), \
  "traj.dat" using 1:2 with l title "position", \
  "" u 1:3 w l title "velocity"

call '../../scripts/set-png.gp' 'traj.png'


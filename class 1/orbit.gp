## ! test -e traj.dat || julia orbit.jl > traj.dat

set terminal dumb ansi256
#set terminal x11
#set terminal qt
plot "traj.dat" u 1:2 w l title "x coord", "" u 1:3 w l title "y coord"
pause -1
set size square
unset key
plot "traj.dat" u 2:3 w l
pause -1


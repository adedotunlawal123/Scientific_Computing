! test -e pos-trace.dat || python3 modes-read.py > pos-trace.dat

set terminal dumb ansi256
#set terminal x11
#set terminal qt
plot[0:3] "pos-trace.dat" u 1:2 w l


! ./bob.bash

set terminal dumb ansi256
set key bottom left

array m[5] = [0.95, 1, 1.25, 5, 20]

plot[][-3:2] for [j=0:4] "bob.dat" index j using 1:(-$2) \
 with lines title sprintf("%2.2f",m[j+1])

call '../../scripts/set-png.gp' 'bob.png'


! ./bob-damped.bash

set terminal dumb ansi256
set key bottom left

array m[5] = [0.95, 1, 1.25, 5, 20]

offset=0
do for [d in "0.001 0.01 0.1 1"] {
plot[][-3:2] for [j=0:4] "bob-damped.dat" index 4*j+offset using 1:(-$2) \
 with lines title sprintf("%2.2f",m[j+1])
offset=offset+1

call '../../scripts/set-png.gp' 'bob-damped-'.d.'.png'
}

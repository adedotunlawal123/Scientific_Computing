! python3 horner.py > p.dat

set terminal dumb ansi256
set xlabel "x"
set ylabel "p(x)"
plot "p.dat" using 1:2 with lines

call '../../scripts/set-png.gp' 'horner.png'

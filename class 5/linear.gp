set terminal dumb ansi256
plot "linear.dat" title "y=3x", "linear-smooth6.dat" w l title "smoothed"

call '../../scripts/set-png.gp' 'linear.png'


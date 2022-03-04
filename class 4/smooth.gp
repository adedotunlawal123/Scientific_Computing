set terminal dumb ansi256
#plot "sim-data.dat" w p
plot "sim-data-smooth4.dat" w l, "sim-data-smooth7.dat" w l

call '../../scripts/set-png.gp' 'smooth.png'

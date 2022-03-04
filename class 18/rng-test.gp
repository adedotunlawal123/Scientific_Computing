# \int_0^y dx 1 = y
# \int_{-\infty}^y dx \exp(-x^2/2)/\sqrt(2\pi) =
# (1 + \erf(y/\sqrt{2}))/2

set terminal dumb ansi256
set key bottom right

plot[][0:1] "rng-test.dat" using 2:1 title "uniform [0,1)", x

call '../../scripts/set-png.gp' 'rng1.png'

plot[][0:1] "rng-test.dat" using 3:1 title "gaussian", \
  0.5*(1+erf(x/sqrt(2)))

call '../../scripts/set-png.gp' 'rng2.png'

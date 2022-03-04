x0 = -0.01
y0 = -0.2
a = 0.8

c(x) = a*(cosh((x-x0)/a)-1)+y0

set fit errorvariables
fit c(x) "string.dat" using 1:2 via x0, y0, a

set terminal dumb ansi256
plot "string.dat", c(x)

call '../../scripts/set-png.gp' 'string.png'

print "a = ", a, " +/- ", a_err

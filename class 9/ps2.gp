! test -e ps.dat || ./partialsum-collect.bash

set terminal dumb ansi256
set logscale y
plot "ps.dat" index 0 u (1.0/$1):2 w lp title "sum 1/k^0.5",\
  "" i 1 u (1.0/$1):2 w lp title "sum 1/k",\
  "" i 2 u (1.0/$1):2 w lp title "sum 1/k^1.5",\
  "" i 3 u (1.0/$1):2 w lp title "sum 1/k^2",\
  "" i 4 u (1.0/$1):2 w lp title "sum 1/k^2.5",\
  "" i 5 u (1.0/$1):2 w lp title "sum 1/k^3"

call '../../scripts/set-png.gp' 'ps2.png'

f(x) = f0 + x*(f1 + x*f2)
g(x) = g0 + x*(g1 + x*g2)
h(x) = h0 + x*(h1 + x*h2)
i(x) = i0 + x*(i1 + x*i2)

fit f(x) "ps.dat" i 2 u (1.0/$1):2 via f0,f1,f2
fit g(x) "ps.dat" i 3 u (1.0/$1):2 via g0,g1,g2
fit h(x) "ps.dat" i 4 u (1.0/$1):2 via h0,h1,h2
fit i(x) "ps.dat" i 5 u (1.0/$1):2 via i0,i1,i2

unset logscale
plot[:0.02][1.1:2.7] \
  "ps.dat" i 2 u (1.0/$1):2 w lp title "sum 1/k^1.5", f(x),\
  "ps.dat" i 3 u (1.0/$1):2 w lp title "sum 1/k^2", g(x),\
  "ps.dat" i 4 u (1.0/$1):2 w lp title "sum 1/k^2.5", h(x),\
  "ps.dat" i 5 u (1.0/$1):2 w lp title "sum 1/k^3", i(x)

call '../../scripts/set-png.gp' 'ps3.png'

print "-------"
print "sum 1/k^1.5 = ", f0
print "sum 1/k^2 = ", g0
print "sum 1/k^2.5 = ", h0
print "sum 1/k^3 = ", i0
print "-------"



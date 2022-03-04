f(x) = f0 + f1*x
g(x) = g0 + x*(g1 + x*g2)
h(x) = h0 + x*(h1 + x*(h2 + x*h3))

fit f(x) "test-poly.dat" index 0 using 1:2 via f0, f1
fit g(x) "test-poly.dat" i 0 u 1:2 via g0,g1,g2
fit h(x) "test-poly.dat" i 0 u 1:2 via h0,h1,h2,h3

set terminal dumb ansi256
set key left bottom
plot \
  "test-poly.dat" i 1 u 1:2 w l title "Neville polynomial fit",\
  "" i 0 u 1:2 w p title "data points", f(x), g(x), h(x)

call '../../scripts/set-png.gp' 'test-poly.png'


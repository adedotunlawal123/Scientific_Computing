! test -e ps.dat || ./partialsum-collect.bash

set terminal dumb ansi256
set logscale y
plot "ps.dat" index 0 w lp title "sum 1/k^0.5",\
  "" i 1 w lp title "sum 1/k",\
  "" i 2 w lp title "sum 1/k^1.5",\
  "" i 3 w lp title "sum 1/k^2",\
  "" i 4 w lp title "sum 1/k^2.5",\
  "" i 5 w lp title "sum 1/k^3"

  call '../../scripts/set-png.gp' 'ps.png'


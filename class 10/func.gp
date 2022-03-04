! test -e func.dat || ./func.bash

array p = [-2, -1, -0.5, 0, 0.5, 1, 2, 3]

set terminal dumb ansi256
set logscale y
plot for [j=0:7] "func.dat" index j u 1:2 w l \
   title sprintf("-x^{%1.1f}log(x)",p[j+1])

call '../../scripts/set-png.gp' 'func.png'

! test -e ft.dat || python3 well.py

set terminal dumb ansi256

plot[0:2] \
  "ft.dat" using 1:2 w l title "cos",\
  "" u 1:3 w l title "sin"

call '../../scripts/set-png.gp' 'ft1.png'

plot[0:0.5] \
  "ft.dat" using 1:2 w l title "cos",\
  "" u 1:3 w l title "sin"

call '../../scripts/set-png.gp' 'ft2.png'

f(x) = 2.0/(2.0+(2*x-11)**2)

do for [m in "4 8 12 16 20 24 28"] {
   set title "mesh=".m
   plot[-1:11][-0.3:1.2] f(x) title "f(x)",\
      "poly-unif".m.".dat" u 1:2 w l title "p/u".m,\
      "poly-cheb".m.".dat" u 1:2 w l title "p/c".m,\
      "func-unif".m.".dat" u 1:2 w p title "f/u".m,\
      "func-cheb".m.".dat" u 1:2 w p title "f/c".m
   pause -1
}

set title "uniform mesh"
plot[-1:11][-0.3:1.2] for [m in "4 8 12 16 20 24 28"]\
   "poly-unif".m.".dat" u 1:2 w l title "p/u".m
pause -1

set title "Chebyshev modes"
plot[-1:11][-0.3:1.2] for [m in "4 8 12 16 20 24 28"]\
   "poly-cheb".m.".dat" u 1:2 w l title "p/c".m
pause -1


! make pairs
! test -e pairs.dat || ./pairs 10000 > pairs.dat
entries=system("wc -l pairs.dat | awk '{ print $1 }'")

set terminal dumb ansi256
plot "pairs.dat" u 1:2
call '../../scripts/set-png.gp' 'pairs1.png'

set terminal dumb ansi256
f(x) = f0 + f1*x
set fit errorvariables
fit f(x) "pairs.dat" u 0:((2*$1-1.0)*(2*$2-1.0)) via f0, f1
plot "pairs.dat" u 0:((2*$1-1.0)*(2*$2-1.0)) w l, f(x)
call '../../scripts/set-png.gp' 'pairs2.png'

print "f0 = ", f0, " +/-", f0_err
print "1/sqrt(", entries, ") = ", 1/sqrt(entries)


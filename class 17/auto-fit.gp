x0 = 0.03350028285
y0 = -0.1693016148
a = 1.036213237

c(x) = a*(cosh((x-x0)/a)-1)+y0

plot 'string.dat', c(x)

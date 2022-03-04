import math
import sys

def trapezoidIntegrator(f, a, b, N):
    width = b-a
    h = width/N
    sum = 0.5*(f(a) + f(b))
    for n in range(1,N):
        xn = a + n*h
        sum += f(xn)
    return sum*h

def negxpowlogx(n):
    def tmp(x):
        xn = math.pow(x,n)
        return -xn*math.log(x)
    return tmp

# This will fail because of the evaluation of log(0)
# I = trapezoidIntegrator(negxpowlogx(1), 0.0, 1.0, 100)
# print("int_0^1 dx -x log(x) = ", I)

p = float(sys.argv[1])

# x*log(x) -> 0*log(0) -> 0*(-inf) -> nan
# [a, b] = [0, 1] = lim_{a->0} [a, 1]
# [1/k^2, 1] for various increasing k values
for k in [10, 20, 50, 100, 200, 500, 1000]:
    I = trapezoidIntegrator(negxpowlogx(p),1.0/k/k,1.0,k)
    print(k,I)


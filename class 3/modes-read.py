import math

nu = 2.5 #Hz
omega = 2*math.pi*nu #radians/s
t0 = 1.25 #s

dt = 0.001 #s

with open ("A-coeffs.txt","r") as myfile:
    A = myfile.read().splitlines()
A = [float(a) for a in A]

def x(t):
    val = 0.0
    for n in range(len(A)):
        val += A[n]*math.cos((n+1)*omega*t)
    val *= math.exp(-t/t0)
    return val

for i in range(5000):
    t = i*dt
    print("{:10.4f} {:10.4f}".format(t,x(t)))

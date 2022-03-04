import math

nu = 2.5 #Hz
omega = 2*math.pi*nu #radians/s
t0 = 1.25 #s

dt = 0.001 #s

A = 10 #cm
B = 2  #cm

for i in range(5000):
    t = i*dt
    x = (A*math.cos(omega*t) + B*math.cos(2*omega*t))*math.exp(-t/t0)
    print("{:10.4f} {:10.4f}".format(t,x))

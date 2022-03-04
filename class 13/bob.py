import sys

# M d^2s/dt^2 = Mg - rho g (pi/3) s^2 (3R-s)
#               ^              ^
#               weight         buoyancy due to submerged portion
#
# (1/g) d^2s/dt^2 = 1 - (Mw/M) C(s/R)

def C(x):
    if x < 0.0:
        return 0.0
    elif x > 2.0:
        return 1.0
    else:
        return 0.25*x*x*(3-x)

dt = 0.00005 # s
g = 9.81    # m/s^2
R = 0.1     # m
mass_ratio = float(sys.argv[1]) # read in dimensionless
                                # mass ratio as a
                                # command line argument
s = 2.0*R # fully submerged initially
v = 0.0   # and at rest
for n in range(100001):
    t = n*dt
    if (n%20 == 0):
        print("{:10.3f} {:10.6f} {:10.6}".format(t,s,v))
    s_next = s + v*dt + 0.5*g*dt*dt*(1-mass_ratio*C(s/R))
    v = v + g*dt*(1-0.5*mass_ratio*(C(s/R) + C(s_next/R)))
    s = s_next



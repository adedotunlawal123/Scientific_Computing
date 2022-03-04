import math
import sys
import struct

def bbs():
    bbs.state = (bbs.state*bbs.state)%bbs.M
    return bbs.state & 1 # mask picks off the least significant bit
bbs.p=2888799659
bbs.q=3694568831
bbs.M=bbs.p*bbs.q
bbs.state=326694129

def bits2float(b):
    # https://docs.python.org/2/library/struct.html#format-characters
    s = struct.pack('>Q', b)
    return struct.unpack('>d', s)[0]

def R():
    u = 0
    for i in range(52):
        u = (u << 1) + bbs()
    u = (1023 << 52) + u
    return bits2float(u)-1.0

def R_alt1():
    u = 0
    v = 0
    for i in range(52):
        u = (u << 1) + bbs()
        v = (v << 1) + 1
    return float(u)/float(v+1)

def R_alt2():
    sum = 0.0;
    x = 0.5;
    for i in range(52):
        if bbs()==1:
            sum += x
        x *= 0.5
    return su

# Box-Muller transform
# https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
def RN():
    x1=R()
    x2=R()
    return math.sqrt(-2.0*math.log(x1))*math.cos(2*math.pi*x2)

m = 1.0 # kg
K = 1.0 # N/m
omega = math.sqrt(K/m) # radians/s
freq = omega/(2.0*math.pi) # Hz
period = 1.0/freq # s
dt = period/200.0
N = 15000 # total number of time steps
runtime = N*dt

gamma = 0.25
kBT = 0.75
b=math.exp(-gamma*dt/(2.0*m))
c=math.sqrt(2*gamma*kBT*dt)

print("runtime =", runtime, file=sys.stderr)
print(" period =", period, file=sys.stderr)
print("   freq =", freq, file=sys.stderr)
print("", file=sys.stderr)

traj = []

# quadratic potential energy
def V(x):
    return 0.5*K*x*x

# linear restoring force
def F(x):
    return -K*x

# total energy
def energy(x,v):
    return 0.5*m*v*v + V(x)

print("Running simulation...", file=sys.stderr)
f = open("traj.dat","w")
x = 1.0 # m
v = 0.0 # m/2, released from rest
for n in range(N):
    f.write("{:10.6f} {:10.6f} {:10.6} \
            {:10.6}\n".format(n*dt,x,v,energy(x,v)))
    a = F(x)/m
    beta_m = c*RN()/m
    x_next = x + b*v*dt + 0.5*b*dt*(a*dt + beta_m)
    a_next = F(x_next)/m
    v_next = v + 0.5*(a+a_next)*dt \
            - (gamma/m)*(x_next-x) + beta_m
    x = x_next
    v = v_next
    traj.append(x)
f.close()
print("Done.", file=sys.stderr)

print("Computing discrete Fourier Transforms...", file=sys.stderr)
cosFT_traj = []
for j in range(N):
    if (j+1)%500 == 0:
        print(j+1,"/",N, file=sys.stderr)
    sum = 0.0
    for k in range(N):
        sum += math.cos(2.0*math.pi*j*k/N)*traj[k]
    cosFT_traj.append(sum)
print("Done cos.", file=sys.stderr)

sinFT_traj = []
for j in range(N):
    if (j+1)%500 == 0:
        print(j+1,"/",N, file=sys.stderr)
    sum = 0.0
    for k in range(N):
        sum += math.sin(2.0*math.pi*j*k/N)*traj[k]
    sinFT_traj.append(sum)
print("Done sin.", file=sys.stderr)

f = open("ft.dat","w")
for j in range(N):
    f.write("{:10.6f} {:10.6f} {:10.6f}\n".format(\
            j/runtime,cosFT_traj[j],sinFT_traj[j]))
f.close()

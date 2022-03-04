import math
import sys
import struct

# Blum Blum Shub (BBS)
# https://en.wikipedia.org/wiki/Blum_Blum_Shub
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
    # a random number drawn uniformly from [0,1)
    u = 0
    for i in range(52):
        u = (u << 1) + bbs()
    u = (1023 << 52) + u # u=+1.?????? x 2^1 in [1,2)
    return bits2float(u)-1.0

def R_alt1():
    u = 0
    v = 0
    for i in range(52):
        u = (u << 1) + bbs()
        v = (v << 1) + 1
    return float(u)/float(v+1)

def R_alt2():
    sum = 0.0
    x = 0.5
    for i in range(52):
        if bbs()==1:
            sum += x
        x *= 0.5
    # b0*(1/2) + b1*(1/4) + b2(*1/8) + ...
    return sum

def RN():
    # Box-Muller transformation
    x1=R()
    x2=R()
    return math.sqrt(-2.0*math.log(x1))*math.cos(2*math.pi*x2)

print("Testing random number generator", file=sys.stderr)
r=[]
rr=[]
for n in range(1000):
    r.append(R())
    rr.append(RN())
r.sort()
rr.sort()
f = open("rng-test.dat","w")
for n in range(len(r)):
    f.write("{:8.4} {:15.8} {:15.8}\n".format(\
            (n+0.5)/len(r),r[n],rr[n]))

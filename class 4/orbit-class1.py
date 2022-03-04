from dataclasses import dataclass
from math import sqrt
from sys import stderr

@dataclass
class Coord:
   x: float
   y: float

   def __str__(self):
      return "({:.4f},{:.4f})".format(self.x,self.y)

   def __add__(self, other):
      x = self.x + other.x
      y = self.y + other.y
      return Coord(x, y)

   def __iadd__(self, other):
      self.x += other.x
      self.y += other.y
      return self

   def __mul__(self,other):
      return Coord(other*self.x,other*self.y)

   def __rmul__(self, other):
      return Coord(other*self.x, other*self.y)

   def len(self):
      return sqrt(self.x*self.x+self.y*self.y)

r = Coord(1,0)
v = Coord(0,1)

GM = 1.0
C = 0.1
R0 = 0.1 #earth's radius

dt = 0.01
for i in range(2001):
    t = i*dt
    r_len = r.len()
    print("{:10.4f} {:10.4f} {:10.4f} {:10.4f} {:10.4f}".format(t,r.x,r.y,v.x,v.y))
    r3 = r_len*r_len*r_len
    r += 0.5*v*dt
    r_len = r.len();
    if r_len < R0:
        print("Impact at time t={}".format(t), file=stderr)
        break
    r3 = r_len*r_len*r_len
    a = (-GM/r3)*r + (-C)*v
    v += a*dt
    r += 0.5*v*dt



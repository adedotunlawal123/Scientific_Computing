# For a circular orbit
# v = sqrt( GM/r)
# v^2 = GM/r
# r = GM/v^2
# T = 2 pi sqrt( r^3/GM )

let 
   GM = 1.0
   C = 0.05
   R0 = 0.1 #earth's radius

   x = 1.0 # initial radius r=1
   y = 0.0
   vx = 0.0
   vy = 1.0 #initial velocity v=1

   dt = 0.01
   for i in 0:2000
      t = i*dt
      r = sqrt(x*x+y*y)
      println("$t   $x   $y   $r")
      r3 = r*r*r
      x += 0.5*vx*dt
      y += 0.5*vy*dt
      r = sqrt(x*x+y*y)
      if r < R0
         break
      end
      r3 = r*r*r
      ax = -GM*x/r3 - C*vx
      ay = -GM*y/r3 - C*vy
      vx += ax*dt
      vy += ay*dt
      x += 0.5*vx*dt
      y += 0.5*vy*dt
   end
end



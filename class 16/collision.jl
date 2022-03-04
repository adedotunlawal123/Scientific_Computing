using Printf

mutable struct Ball
   mass::Float64
   radius::Float64
   x::Float64
   y::Float64
   vx::Float64
   vy::Float64
end

#initial condition 1
#b1 = Ball(1.0, 1.0, 0.0, 0.0, 3.0/5.0, 4.0/5.0)
#b2 = Ball(2.5, 0.75, 10, 5, -1.0, 0)

#initial condition 2
b1 = Ball(1.0, 1.0, 0.0, 0.0, 3.0/5.0, 4.0/5.0)
b2 = Ball(2.5, 0.75, 10, 5, -0.5, 0.25)

dt = 0.125
g = 0.1
function in_time_step(t::Float64)
   0.0 < t && t < dt
end

function kinetic_energy()
   0.5*( b1.mass*(b1.vx*b1.vx + b1.vy*b1.vy)
        + b2.mass*(b2.vx*b2.vx + b2.vy*b2.vy) )
end

function potential_energy()
   b1.mass*g*b1.y + b2.mass*g*b2.y
end

function advance!(b::Ball, t::Float64)
   b.x += t*b.vx
   b.y += t*b.vy - 0.5*g*t*t
   b.vy -= g*t
end

function inelastic_scatter()
   M = b1.mass + b2.mass
   vx = (b1.mass*b1.vx + b2.mass*b2.vx) / M
   vy = (b1.mass*b1.vy + b2.mass*b2.vy) / M

   b1.vx = vx
   b1.vy = vy

   b2.vx = vx
   b2.vy = vy
end

function elastic_scatter()
   dx = b1.x - b2.x
   dy = b1.y - b2.y
   R = b1.radius + b2.radius
   M = b1.mass + b2.mass
   c = dx/R
   s = dy/R

   cb_u = c*b1.vx + s*b1.vy
   cb_w = -s*b1.vx + c*b1.vy
   db_u = c*b2.vx + s*b2.vy
   db_w = -s*b2.vx + c*b2.vy

   cb_uprime = (cb_u*(b1.mass-b2.mass) + 2.0*b2.mass*db_u)/M
   db_uprime = (db_u*(b2.mass-b1.mass) + 2.0*b1.mass*cb_u)/M

   b1.vx = c*cb_uprime - s*cb_w
   b1.vy = s*cb_uprime + c*cb_w
   b2.vx = c*db_uprime - s*db_w
   b2.vy = s*db_uprime + c*db_w
end

function update()
   dx = b1.x - b2.x
   dy = b1.y - b2.y
   dvx = b1.vx - b2.vx
   dvy = b1.vy - b2.vy
   R = b1.radius + b2.radius

   drdv = dx*dvx + dy*dvy
   dr2 = dx*dx + dy*dy
   dv2 = dvx*dvx + dvy*dvy

   radical2 = drdv*drdv - dv2*(dr2-R*R)
   if radical2 < 0.0
      advance!(b1,dt)
      advance!(b2,dt)
   else
      radical = sqrt(radical2)
      t1 = (-drdv + radical)/dv2
      t2 = (-drdv - radical)/dv2

      tc = -1.0
      if in_time_step(t1) && !in_time_step(t2)
         tc = t1
      elseif !in_time_step(t1) && in_time_step(t2)
         tc = t2
      elseif in_time_step(t1) && in_time_step(t2)
         tc = min(t1,t2)
      end
      if (tc > 0.0)
         # collision occurs
         advance!(b1,tc)
         advance!(b2,tc)
         
         #inelastic_scatter()
         elastic_scatter()

         advance!(b1,dt-tc)
         advance!(b2,dt-tc)
      else
         advance!(b1,dt)
         advance!(b2,dt)
      end
   end
end

function ps(i)
   x1 = 100 + 25*b1.x
   x2 = 100 + 25*b2.x
   y1 = 200 + 25*b1.y
   y2 = 200 + 25*b2.y
   r1 = 25*b1.radius
   r2 = 25*b2.radius
   open(@sprintf("eps/outfile%d.eps",i), "w") do f
      write(f,"%!PS-Adobe-3.0 EPSF-3.0\n")
      write(f,"%%BoundingBox: 0 0 400 400\n")
      write(f,"newpath\n")
      write(f,@sprintf("%6.3f %6.3f %6.3f ",x1,y1,r1) * " 0 360 arc fill\n")
      write(f,"2 setlinewidth\n")
write(f,"0.3 setgray\n")
      write(f,"stroke\n")
      write(f,"newpath\n")
      write(f,@sprintf("%6.3f %6.3f %6.3f ",x2,y2,r2) * " 0 360 arc fill\n")
      write(f,"2 setlinewidth\n")
      write(f,"0.5 setgray\n")
      write(f,"stroke\n")
      write(f,"showpage\n")
   end
end

open("trajectory.dat","w") do f
   for i in 0:150
      ps(i)
      update()
      write(f,
            @sprintf("%10.6f  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f\n",
                     b1.x, b1.y, b2.x, b2.y, kinetic_energy(), potential_energy()))
   end
end



using Polynomials
using Printf

function neville(x::Array{Float64,1},y::Array{Float64,1})
   N = length(x)
   @assert N == length(y)
   p::Array{Polynomial,1} = []

   for i in 1:(N-1)
      dx = x[i]  - x[i+1]
      p1 = (y[i]-y[i+1])/dx;
      p0 = (-x[i+1]*y[i] + x[i]*y[i+1])/dx;
      push!(p,Polynomial([p0,p1]))
   end

   while (length(p) > 1)
      offset = N+1-length(p);
      for i in 1:(length(p)-1)
         p[i] = (1.0/(x[i]-x[i+offset]))*( Polynomial([-x[i+offset],1])*p[i] - Polynomial([-x[i],1])*p[i+1] )
      end
      pop!(p)
   end
   return p[1]
end

let
   x::Array{Float64,1} = []
   y::Array{Float64,1} = []

   open("in.dat") do file
      for ln in eachline(file)
         vals = split(ln)
         if length(vals) == 2
            push!(x,parse(Float64,vals[1]))
            push!(y,parse(Float64,vals[2]))
         end
      end
   end

   p = neville(x,y)
   dx = x[end]-x[1]

   open("out.dat","w") do file
      for i in 0:250
         xx = x[1] + dx*i/250.0
         write(file,@sprintf("%15.4f %15.4f\n",xx,p(xx)))
      end
   end
end

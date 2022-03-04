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

#open("peak.dat") do file

x = [ 1.0, 2.0, 3.0, 4.0, 5.0 ]
y = [ 0.2, 0.8, 2.3, 5.9, 5.3 ]
p = neville(x,y)
for i = 1:length(x)
   @printf("%15.3f  %15.3f\n",x[i],y[i])
end
println("")
println("")

for i in 0:96
   @printf("%15.3f   %15.3f\n",i/16.0,p(i/16.0))
end

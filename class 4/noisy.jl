using Printf

function signal(x)
   0.95*x*cos(2.1*x)*exp(-0.7*x)
end

function noise(x)
   cos(5*x) + cos(10*x) + cos(20*x) + cos(50*x) + cos(100*x) + cos(200*x) + cos(500*x)
end

for i in 0:1000
   let
      x = i*0.01
      fx = signal(x) + 0.02*noise(x)
      @printf("%6.2f  %8.5f\n", x, fx)
   end
end

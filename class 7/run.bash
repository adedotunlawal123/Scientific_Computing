#!/bin/bash

JULIA=/Applications/Julia-1.6.app/Contents/Resources/julia/bin/julia

#echo uniform mesh:
#for mesh in 4 8 12 16 20 24 28
#do
#   echo processing mesh=$mesh
#   seq 0 $mesh | awk '{ print 10.0*$1/'$mesh' }' > unif${mesh}.dat
#   awk '{ print $1, 2.0/(2.0+(2*$1-11)**2) }' unif${mesh}.dat > in.dat
#   $JULIA neville2.jl
#   mv in.dat func-unif${mesh}.dat
#   mv out.dat poly-unif${mesh}.dat
#done

echo Chebyshev nodes:
for mesh in 4 8 12 16 20 24 28
do
   echo processing mesh=$mesh
   seq 0 $mesh | awk '{ pi=atan2(0,-1); print 5.0*(1-cos(pi*($1+0.5)/('$mesh'+1))) }' > cheb${mesh}.dat
   awk '{ print $1, 2.0/(2.0+(2*$1-11)**2) }' cheb${mesh}.dat > in.dat
   $JULIA neville2.jl
   mv in.dat func-cheb${mesh}.dat
   mv out.dat poly-cheb${mesh}.dat
done

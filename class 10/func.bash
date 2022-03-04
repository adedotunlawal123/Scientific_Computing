#!/bin/bash

echo "" > func.dat

for n in -2 -1 -0.5 0 0.5 1 2 3
do
   # f(x) = -x^n log(x)
   seq 0 100 | awk '{ x=$1/100.; print x, -x**'$n'*log(x) }' >> func.dat
   echo "" >> func.dat
   echo "" >> func.dat
done


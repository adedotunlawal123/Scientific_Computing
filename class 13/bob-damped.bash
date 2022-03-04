#!/bin/bash


echo "" > bob-damped.dat
for m in 0.95 1 1.25 5 20
do
   for d in 0.001 0.01 0.1 1
   do
      echo "# mass ratio "$m >> bob-damped.dat
      python3 bob-damped.py $m $d >> bob-damped.dat
      echo "" >> bob-damped.dat
      echo "" >> bob-damped.dat
   done
done


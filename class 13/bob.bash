#!/bin/bash

echo "" > bob.dat
for m in 0.95 1 1.25 5 20
do
   echo "# mass ratio "$m >> bob.dat
   python3 bob.py $m >> bob.dat
   echo "" >> bob.dat
   echo "" >> bob.dat
done


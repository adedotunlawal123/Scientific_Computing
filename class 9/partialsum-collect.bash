#!/bin/bash

echo "" > ps.dat
for p in 0.5 1.0 1.5 2.0 2.5 3.0
do
   echo "#power p = "$p >> ps.dat
   ./partialsum $p >> ps.dat
   echo "" >> ps.dat
   echo "" >> ps.dat
done


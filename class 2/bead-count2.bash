#!/bin/bash
if (( $# != 1))
then
   echo "Looking for a single integer argument"
   exit 1
elif (( $1 < 1 ))
then
   echo "Argument must be greater than zero"
   exit 1
fi

./bead-count.bash $1 | awk '{ x += $5 } END { print x }'

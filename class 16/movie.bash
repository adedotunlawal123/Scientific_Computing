#!/bin/bash

if [[ -d eps/ ]]
then
   rm eps/*
else
   mkdir eps/
fi

if [[ -d png/ ]]
then
   rm png/*
else
   mkdir png/
fi

julia collision.jl

cd eps
for FILE in $(ls *.eps)
do
   echo converting $FILE to ${FILE%.eps}.png
   magick convert \
      -density 200 $FILE
      -resize 480x480^ - gravity center -extent 480x480 \
      -colorspace gray \
      ../png/${FILE%.eps}.png
done

echo converting eps/outfileXXX.png to traj.mpeg
ffmpeg -i "png/outfile%03d.png" traj.mpeg -y

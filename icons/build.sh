#!/bin/bash

set -e

cp icon-large.svg temp-large.svg
cp icon-medium.svg temp-medium.svg
cp icon-small.svg temp-small.svg
sed -i 's/#00ff00/#ffffff/g' temp-large.svg temp-medium.svg temp-small.svg
sed -i "s/#0000ff/$1/g" temp-large.svg temp-medium.svg temp-small.svg
sed -i 's/#ff0000/#ef7e19/g' temp-large.svg temp-medium.svg temp-small.svg
rsvg-convert temp-small.svg -w 16 -h 16 --output temp-16.png
rsvg-convert temp-small.svg -w 32 -h 32 --output temp-32.png
rsvg-convert temp-medium.svg -w 48 -h 48 --output temp-48.png
rsvg-convert temp-large.svg -w 64 -h 64 --output temp-64.png
rsvg-convert temp-large.svg -w 96  -h 96 --output temp-96.png
rsvg-convert temp-large.svg -w 256 -h 256 --output temp-256.png
convert temp-16.png temp-32.png temp-48.png temp-64.png temp-96.png temp-256.png +dither -colors 255 "$2"
rm temp-*.png temp-*.svg

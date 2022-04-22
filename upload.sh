#!/usr/bin/bash

rm -rf build/*

cd build 

cmake ..
make -j4

~/Documents/programming/pi-pico/picotool/build/picotool load test.uf2 -x 

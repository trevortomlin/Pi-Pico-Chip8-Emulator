#!/bin/bash
cd build 

cmake ..
make -j4

/home/trevor/Documents/programming/pi-pico/picotool/build/picotool load test.uf2 -x

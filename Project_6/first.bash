#!/bin/bash

for n in 1024 4096 6144 8192 10240 40960 61440 81920 102400 409600 614400 819200 1024000 4096000 6144000 8192000
do
    for s in 8 16 32 64 128 256 512
    do
        g++ -o first first.cpp -DNUM_ELEMENTS=$n -DLOCAL_SIZE=$s /usr/local/apps/cuda/10.1/lib64/libOpenCL.so.1.1 -lm -fopenmp
        ./first
    done
done
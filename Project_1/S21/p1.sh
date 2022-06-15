#!/bin/bash

# number of threads:
for t in 1 2 4 6 8
do
    echo NUMT = $t
    # number of subdivisions:
    for s in 100 1000 10000 100000 1000000 10000000 100000000
    #for s in 400 2000 10000 50000 250000 1250000 6250000
    do
        echo NUMS = $s
        g++ -DNUMT=$t -DNUMTRIALS=$s p1.cpp -o p1 -lm -fopenmp
        ./p1
    done
done

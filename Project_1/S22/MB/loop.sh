#!/bin/bash

for t in 1 2 4 8
do
    echo NUMT = $t
    for n in 1 10 100 1000 10000 100000 500000 1000000
    do
        echo NUMTRIALS = $s
        g++ -O3   montecarlo.cpp  -DNUMT=$t -DNUMTRIALS=$n  -o montecarlo  -lm  -fopenmp
        ./montecarlo
  done
done
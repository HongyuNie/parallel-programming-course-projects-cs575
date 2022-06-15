#!bin/bash

#number of threads
for t in 1 2 4 6 8
do
    echo NUMT = $t
    for n in 10 50 100 150 200 1000 2000
    do
        echo NUMNODES = $n
        g++ -o p2 p2.cpp -DNUMT=$t -DNUMNODES=$n -O3 -lm -fopenmp
        ./p2
    done
done

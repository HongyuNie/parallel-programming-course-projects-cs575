#!/bin/csh

foreach s (5792 5793 5800)
    g++ -DARRAYSIZE=$s p4.cpp -o p4 -lm -fopenmp
    ./p4
end

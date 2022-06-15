#!/bin/csh

foreach t ( 1 2 4 8 )
  foreach n (4 16 40 100 200 500)
        g++ -O3 patel.cpp -DNUMT=$t -DNUMNODES=$n -o p2 -lm -fopenmp
        ./p2
  end
end
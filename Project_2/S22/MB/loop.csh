#!/bin/csh

foreach t ( 1 2 4 6 8 )
  foreach s ( 2 4 8 16 32 64 128 256 512 1024 2048 4096 )
    g++   -DNUMNODES=$s   -DNUMT=$t   superquadric.cpp  -o superquadric  -lm  -fopenmp
    #icpc   -DNUMNODES=$s   -DNUMT=$t   superquadric.cpp  -o superquadric  -lm  -openmp
    ./superquadric
  end
end

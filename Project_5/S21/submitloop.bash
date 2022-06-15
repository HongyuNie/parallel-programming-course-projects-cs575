#!/bin/bash
#SBATCH -J MatrixMul
#SBATCH -A cs475-575
#SBATCH -p class
#SBATCH --gres=gpu:1
#SBATCH -o matrixmul.out
#SBATCH -e matrixmul.err
#SBATCH --mail-type=BEGIN,END,FAIL
#SBATCH --mail-user=nieh@oregonstate.edu
for b in 16 32 64 128
do
    for n in 16384 32768 65536 131072 262144 524288 1048576
    do
        /usr/local/apps/cuda/cuda-10.1/bin/nvcc -DNUMTRIALS=$n -DBLOCKSIZE=$b -o project_5 project_5.cu
        ./project_5
    done
done

#!/bin/bash
#SBATCH -J AutoCorr
#SBATCH -A cs475-575
#SBATCH -p class
#SBATCH -N 4 # number of nodes
#SBATCH -n 4 # number of tasks
#SBATCH --constraint=ib
#SBATCH -o autocorr.out
#SBATCH -e autocorr.err
#SBATCH --mail-type=END,FAIL
#SBATCH --mail-user=onid@oregonstate.edu


for p in 1 2 4 8
do
    #module load slurm
    #module load openmpi
    mpic++ p7.cpp -o p7 -lm
    mpiexec -mca btl self,tcp -np $p p7
done
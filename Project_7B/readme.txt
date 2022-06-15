-- to ssh COE MPI cluster:
flip3 151% ssh submit-c.hpc.engr.oregonstate.edu

-- set the path correctly
module load slurm
module load openmpi

-- to run the the submit.bash

    sbatch submit.bash --sbatch: error: Batch job submission failed: Invalid account or account/partition combination specified



-- compiling:
    mpicc                       -- for C
    mpic++      (mpic++ p7.cpp -o p7 -lm)                -- for C++
    mpiexec -mca btl self,tcp -np 4 program  -- 4 is the number of processors/cpus to use
    
    mpiexec -np 16 ./first

-- using "scancel" if the job needed to be killed

-- varying the number of processors.  Use at least 1, 2, 4, and 8.

-- Trouble shooting:
    -- error if you mess up with the size in second pair of send and receive:
        [cn-c-1][[12712,1],0][btl_tcp_frag.c:227:mca_btl_tcp_frag_recv] mca_btl_tcp_frag_recv: readv error (0x7ffeb5268de8, 8162144)
        Bad address(1)

    -- error: There are not enough slots available in the system to satisfy the 8 slots that were requested by the application:

-- can pro7b be running on rabbit?
    No.  rabbit is a single machine, not a cluster.  MPI is meant for a cluster of computers.
    However, it does appear the rabbit has had the MPI tools installed on it and it looks like you can use them from rabbit.  
    I guess that means that rabbit can double as a submit- machine.  Not sure how that happened or if that was intended, but I am going to wait until after the project is due to ask.  :-)
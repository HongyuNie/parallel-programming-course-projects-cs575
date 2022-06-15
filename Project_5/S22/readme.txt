-- Commands using makefile
    make
    /usr/local/apps/cuda/cuda-10.1/bin/nvcc -o proj5 proj5.cu
    ./proj5


-- When using the DGX, our IT people ask that you add this line to the bash script:
    #SBATCH  --constraint=v100 (That is 2 hyphens, not one.)

-- To access rabbit:
    ssh rabbit.engr.oregonstate.edu
    -- From Prof.Bailey:
        Yes, you have to be on some other machine first, then ssh to rabbit.  
        We deliberately did not make rabbit "outward-facing".  That machine is only for this class.

-- To access DGX:
    ssh submit-c.hpc.engr.oregonstate.edu -- while in flip, or'-a' or '-b'
    module load slurm -- to set path correctly

-- Use version 10 of CUDA, not version 11.  
    11 is the latest version but our notes all say version 10 because, before the quarter started, I ran some of my standard CUDA tests and they hung when using v11.  
    Today someone else got weird unexplained error messages when using v11, but they went away, and the program worked perfectly, after switching back to v10.
    

-- When I made the P5 video, I was thinking we should do a reduction on this, but later I decided to simplify it so that your first experience with GPU programming would be smoother. 
    But I forgot to re-record the video.  
    So, don’t copy the code that the video talks about.  
    Use the skeleton code that’s in the P5 handout.  
    I will re-record the P5 video this weekend.  (So that you don’t feel cheated, we will do GPU reduction in P6.  We will go over it on Monday.)

-- For remove "\r" in script file:
    Did you create this script on Windows? (notepad, wordpad, etc.)  
    If so, you probably have that extra '\r' at the end of each line.  
    If so, use the dos2unix command that you saw on Slide #43 of the Project Notes noteset.

-- For error msg "CUDA error at helper_cuda.h:744 code=35(cudaErrorInsufficientDriver) "cudaGetDeviceCount(&device_count)"" :
    Usually that message means that you are trying to execute on a non-GPU machine. -- by prof.Bailey

-- For remove result prints "GPU Device 0: ~~~"
    Comment out this line:
    int dev = findCudaDevice(argc, (const char **)argv);

-- For error msg "CUDA driver version is insufficient for CUDA runtime version" on DGX
    Means that the device you are on doesn't have a GPU, or at least doesn't have CUDA drivers.
    If you printf(...) instead of fprintf(stderr,...), then your messages will come into the .out file.

-- For redirect the results:
     send both program outputs, standard out and standard error, to a file with: ./montecarlo_script >& montecarlo.csv

-- For why using DGX:
     taking your P5 data from rabbit is OK.  Using the DGX is just performance icing on the GPU cake.

-- Why using full path of nvcc:
    When you run your script, it starts out with a different set of default paths.  So, what might work from the command line, may not work from within a script.
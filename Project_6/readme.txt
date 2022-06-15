
-- Commands for running on rabbit:

g++ -o printinfo printinfo.cpp /usr/local/apps/cuda/10.1/lib64/libOpenCL.so.1.1 -lm -fopenmp
./printinfo


-- About the results:

"Be tolerant of strange dips in the graph curves.  Many people were getting them.  Not sure why."

"Multiply+Add should be just a little slower than Multiply alone due to the FMA instruction.  
If they ran it on their own system, they might not see that.  Not all GPUs have FMA."

"I thought reduction would be slower than Multiply [alone], but it seemed to be comparable or faster than Multiply alone.  
Not sure why.  Possibly because it was avoiding a global memory store by multiplying into shared workgroup memory instead."


-- wrong function name:ArrayMul - ArrayMulAdd
clCreateKernel failed
clSetKernelArg failed (1)
clSetKernelArg failed (2)
clSetKernelArg failed (3)
clSetKernelArg failed (4)
clEnqueueNDRangeKernel failed: -48
      64          64       1048576        2513.443 GigaMultsPerSecond


-- no constant in dC and dD:
<kernel>:16:13: error: read-only variable is not assignable
    dD[gid] = (dA[gid] * dB[gid]) + dC[gid];
    ~~~~~~~ ^

clCreateKernel failed
clSetKernelArg failed (1)
clSetKernelArg failed (2)
clSetKernelArg failed (3)
clSetKernelArg failed (4)
clEnqueueNDRangeKernel failed: -48
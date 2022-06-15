kernel
void
ArrayMult( global const float *dA, global const float *dB, global float *dC, global float *dD ) // no const for C and D
{
	int gid = get_global_id( 0 ); 	// 0 for index of dimension,  0 for X, only one index is needed
	dD[gid] = (dA[gid] * dB[gid]) + dC[gid];
}

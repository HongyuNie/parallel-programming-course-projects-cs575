/******************************************
CS475/575
Spring 2021
Project 2
Numeric Integration with OpenMP Reduction
*******************************************/


#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>

#define XMIN     -1.
#define XMAX      1.
#define YMIN     -1.
#define YMAX      1.

#define N	      0.70

#ifndef NUMNODES
#define NUMNODES  10
#endif

#ifndef NUMT
#define NUMT      1
#endif

#ifndef NUMTRIES
#define NUMTRIES  100
#endif


// function prototype
float Height( int, int );

int main( int argc, char *argv[ ] )
{
#ifndef _OPENMP
    fprintf(stderr, "No OpenMP support!\n"); return 1;
#endif
    float volume = 0.0;

    // set the number of threads to use in the for-loop:
    omp_set_num_threads(NUMT);

    // the area of a single full-sized tile:
	// (not all tiles are full-sized, though)
	float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
				( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );

   // sum up the weighted heights into the variable "volume"

   // get read to record the maximum performance and the probability
    float maxPerformance = 0.; // must be declared outside the NUMTRIES loop
    for (int j = 0; j < NUMTRIES; j++) {
        double time0 = omp_get_wtime();
        // using an OpenMP for loop and a reduction:
#pragma omp parallel for default(none) shared(fullTileArea) reduction(+:volume)
        for( int i = 0; i < NUMNODES * NUMNODES; i++ ) {
            int iu = i % NUMNODES;
            int iv = i / NUMNODES;
            float z = Height(iu, iv);
            if (iu == 0 || iu == NUMNODES - 1) {
                z = z * 0.5;
            }
            if (iv == 0 || iv == NUMNODES - 1) {
                z = z * 0.5;
            }
            volume = volume + z * 2 * fullTileArea;
        }
        double time1 = omp_get_wtime();
        double megaHeightsPerSecond = (double)(NUMNODES * NUMNODES) /(time1 - time0)/1000000.;
        if(megaHeightsPerSecond > maxPerformance)
            maxPerformance = megaHeightsPerSecond;
    }
    printf("maxPerformance = %f \n", maxPerformance);
    printf("Volume : %f \n", volume / NUMTRIES);
    return 0;
}

float
Height( int iu, int iv )	// iu,iv = 0 .. NUMNODES-1
{
    float x = -1.  +  2.*(float)iu /(float)(NUMNODES-1);	// -1. to +1.
	float y = -1.  +  2.*(float)iv /(float)(NUMNODES-1);	// -1. to +1.

	float xn = pow( fabs(x), (double)N );
	float yn = pow( fabs(y), (double)N );
	float r = 1. - xn - yn;
	if( r <= 0. )
	        return 0.;
	float height = pow( r, 1./(float)N );
	return height;
}

/*************************************************
    CS 475/575 
    Spring 2021
    Project 2
    Numeric Integration with OpenMP Reduction
**************************************************/

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>

#define XMIN     -1.
#define XMAX      1.
#define YMIN     -1.
#define YMAX      1.

#ifndef NUMNODES
#define NUMNODES  10
#endif

#ifndef NUMT
#define NUMT      1
#endif

#ifndef NUMTRIES
#define NUMTRIES  100
#endif

const float N = 2.0f;
const float R = 1.0f;


float Height( int, int );	// function prototype

int main( int argc, char *argv[ ] )
{
#ifndef _OPENMP
    fprintf(stderr, "No OpenMP support!\n"); return 1;
#endif
    omp_set_num_threads(NUMT);
	float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
				( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );
    float maxPerformance = 0.;
    float volume = 0.;

    for (int j = 0; j < NUMTRIES; j++) {
        double time_0 = omp_get_wtime();
        #pragma omp parallel for default(none) shared(fullTileArea) reduction(+:volume)
        for( int i = 0; i < NUMNODES*NUMNODES; i++ )
        {
            int iu = i % NUMNODES; // which column
            int iv = i / NUMNODES; // which row
            float z = Height( iu, iv );
            if (iu == 0 || iu == NUMNODES - 1) {
                z = z * 0.5;
            }
            if (iv == 0 || iv == NUMNODES - 1) {
                z = z * 0.5;
            }
            volume += z * fullTileArea;
        }
        double time_1 = omp_get_wtime();
        double megaHeightsPerSecond = (NUMNODES * NUMNODES) / (time_1 - time_0) / 1000000;
        if (megaHeightsPerSecond > maxPerformance)
            maxPerformance = megaHeightsPerSecond;
    }
    //printf("maxPerformance = %6.2lf megaHeightsPerSecond\n", maxPerformance);
    //printf("The total Volume(Avg) : %f \n", volume / NUMTRIES);
    fprintf(stderr, " %d %d %6.2lf %6.2lf \n", NUMT, NUMNODES, maxPerformance, volume / NUMTRIES);
    return 0;
}

float
Height( int iu, int iv )	// iu,iv = 0 .. NUMNODES-1
{
	float x = -1.  +  2.*(float)iu /(float)(NUMNODES-1);	// -1. to +1.
	float y = -1.  +  2.*(float)iv /(float)(NUMNODES-1);	// -1. to +1.

	float xn = pow( fabs(x), (double)N );
	float yn = pow( fabs(y), (double)N );
	float rn = pow( fabs(R), (double)N );
	float r = rn - xn - yn;
	if( r <= 0. )
	        return 0.;
	float height = pow( r, 1./(double)N );
	return height;
}
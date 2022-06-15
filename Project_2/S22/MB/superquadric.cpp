#include <iostream>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <omp.h>

#define XMIN	 -1.
#define XMAX	  1.
#define YMIN	 -1.
#define YMAX	  1.

#ifndef NUMNODES
#define NUMNODES	128
#endif

#ifndef N
#define N		2.0
#endif

#ifndef R
#define R		1.0
#endif

#ifndef NUMT
#define NUMT		8
#endif

#ifndef NUM_TRIALS
#define NUM_TRIALS	1
#endif

float Height( int, int );

int
main( int argc, char *argv[ ] )
{
	omp_set_num_threads( NUMT );

	double prec = omp_get_wtick( );
	//fprintf( stderr, "Clock precision = %g\n", prec );

	double time0 = omp_get_wtime( );

	float volume;
	for( int t = 0; t < NUM_TRIALS; t++ )
	{
		volume = 0.;
		#pragma omp parallel for default(none), reduction(+:volume)
		for( int i = 0; i < NUMNODES*NUMNODES; i++ )
		{
			int iu = i % NUMNODES; // which element in a row
			int iv = i / NUMNODES; // which row
			
			float coef;
			if( iu == 0  ||  iu == NUMNODES-1 )
			{
				if( iv == 0  ||  iv == NUMNODES-1 )
					coef = 0.25f;
				else
					coef = 0.50f;
			}
			else
			{
				if( iv == 0  ||  iv == NUMNODES-1 )
					coef = 0.50f;
				else
					coef = 1.00f;
			}

			volume = volume + 2 * coef * Height( iu, iv );
		}

	}

	double time1 = omp_get_wtime( );
	double dt = ( time1 - time0 ) / (float)NUM_TRIALS;

	volume *= (  ( (XMAX-XMIN)/(float)(NUMNODES-1) )  *  ( ( YMAX - YMIN )/(float)(NUMNODES-1) )  ); // full tile area

	fprintf( stderr, "%6d\t%6d\t%8.1f\t%8.3f\n", NUMT, NUMNODES, (float)(NUMNODES*NUMNODES)/dt/1000000., volume );

	return 0;
}


float
Height( int iu, int iv )	// iu,iv = 0 .. NUMNODES-1
{
	float x = -1.  +  2.*(float)iu /(float)(NUMNODES-1);
	float y = -1.  +  2.*(float)iv /(float)(NUMNODES-1);

	// float xn = pow( fabs(x), (double)N );
	float xn = pow( fabs(x), (double)N );
	float yn = pow( fabs(y), (double)N );
	float rn = pow( fabs(R), (double)N );
	float r = rn - xn - yn;
	if( r <= 0. )
	        return 0.;
	float height = pow( r, 1./(double)N );
	return height;
}

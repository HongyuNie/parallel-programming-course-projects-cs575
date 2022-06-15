/******************************************
CS475/575
Spring 2020
Project 3
Functional Decomposition
*******************************************/


#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

// global variables of system:

int	NowYear;		// 2020 - 2025
int	NowMonth;		// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
int	NowNumDeer;			// number of deer in the current population
int	NowNumCougar;		// number of cougar in the current population


// const variables of system:

const float GRAIN_GROWS_PER_MONTH =	9.0;
const float ONE_DEER_EATS_PER_MONTH = 	1.0;
const float ONE_COUGAR_EATS_PER_MONTH =	5.0;

const float AVG_PRECIP_PER_MONTH =	7.0;	// average
const float AMP_PRECIP_PER_MONTH =	6.0;	// plus or minus
const float RANDOM_PRECIP =		2.0;	// plus or minus noise

const float AVG_TEMP =			60.0;	// average
const float AMP_TEMP =			20.0;	// plus or minus
const float RANDOM_TEMP =		10.0;	// plus or minus noise

const float MIDTEMP =			40.0;
const float MIDPRECIP =			10.0;


// set up random seed:

unsigned int seed = time(NULL);


// function prototypes:

void	GrainDeer();
void	Grain();
void	Cougar();
void	Watcher();
float	fRanf(unsigned int *, float, float);
int	iRanf(unsigned int *, int, int);
float	SQR(float);

// main function:

int
main (int argc, char *argv[])
{
#ifndef _OPENMP
	fprintf(stderr, "No OpenMp support!\n");
	return 1;
#endif
	// starting date and time:
	NowMonth = 0;
	NowYear	 = 2020;

	// starting state (feel free to change this is you want):
	NowNumDeer = 1;
	NowHeight = 1.;
	NowNumCougar = 0.;

	// starting temp and precip:
	float ang = (30. * (float)NowMonth + 15.) * (M_PI / 180.);
	float temp = AVG_TEMP - AMP_TEMP * cos(ang);
	NowTemp = temp + fRanf(&seed, -RANDOM_TEMP, RANDOM_TEMP);
	float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
	NowPrecip = precip + fRanf(&seed, -RANDOM_PRECIP, RANDOM_PRECIP);
	if (NowPrecip < 0.)
		NowPrecip = 0.;

	omp_set_num_threads(4);
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			GrainDeer();
		}

		#pragma omp section
		{
			Grain();
		}

		#pragma omp section
		{
			Cougar();
		}

		#pragma omp section
		{
			Watcher();
		}

	}	// implied barrier -- all functions must return in order
		// to allow any of them to get past here
	return 0;
}


// simulation functions:

void
GrainDeer(void)
{
	while(NowYear < 2026)
	{
		float NextNumDeer = NowNumDeer;
		if (NowNumDeer < NowHeight)
			NextNumDeer++;
		else if (NowNumDeer > NowHeight)
			NextNumDeer--;
		NextNumDeer -= NowNumCougar * ONE_COUGAR_EATS_PER_MONTH;
		if (NextNumDeer < 0)
			NextNumDeer = 0;
		#pragma omp barrier
		NowNumDeer = NextNumDeer;
		#pragma omp barrier
		#pragma omp barrier
	}	
}

void
Cougar()
{
	while(NowYear < 2026)
	{
		float NextNumCougar = NowNumCougar;
		if (!NowNumCougar) {
			if (NowNumDeer > ONE_COUGAR_EATS_PER_MONTH)
				NextNumCougar++;
		}
		else {
			if (NowNumDeer > NowNumCougar * ONE_COUGAR_EATS_PER_MONTH)
				NextNumCougar++;
			else if (!NowNumDeer)
				NextNumCougar = 0;
		}
		#pragma omp barrier
		NowNumCougar = NextNumCougar;
		#pragma omp barrier
		#pragma omp barrier
	}
}

void
Grain(void)
{
	while(NowYear < 2026)
	{
		float tempFactor = exp(-SQR((NowTemp - MIDTEMP) / 10));
		float precipFactor = exp(-SQR((NowPrecip - MIDPRECIP) / 10));
		float NextHeight = NowHeight + tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
		NextHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
		if (NextHeight < 0)
			NextHeight = 0;
		#pragma omp barrier
		NowHeight = NextHeight;
		#pragma omp barrier
		#pragma omp barrier
	}	
}

void
Watcher(void)
{
	while(NowYear < 2026)
	{
		#pragma omp barrier
		#pragma omp barrier
		// print results:
		float cmHeight = NowHeight * 2.54;
		float cTemp = (5. / 9.) * (NowTemp - 32);
		float cmPrecip = NowPrecip * 2.54;
		printf("%2d %4d:   C = %2d   D = %2d   G = %5.2fcm   T = %5.2fc   P = %5.2fcm\n", NowMonth + 1, NowYear, NowNumCougar, NowNumDeer, cmHeight, cTemp, cmPrecip);
		
		// step a month
		NowMonth++;
		if (NowMonth == 12)
		{
			NowMonth = 0;
			NowYear++;
		}
		
		// new temp and precip:
		float ang = (30. * (float)NowMonth + 15.) * (M_PI / 180);
		float temp = AVG_TEMP - AMP_TEMP * cos(ang);
		NowTemp = temp + fRanf(&seed, -RANDOM_TEMP, RANDOM_TEMP);
		float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
		NowPrecip = precip + fRanf(&seed, -RANDOM_PRECIP, RANDOM_PRECIP);
		if (NowPrecip < 0.)
			NowPrecip = 0.;
		#pragma omp barrier

	}	
}

// random number functions:

float
fRanf(unsigned int *seedp, float low, float high)
{
	float r = (float) rand_r(seedp);	// 0 - RAND_MAX
	
	return(low + r * (high - low) / (float)RAND_MAX);
}

int
iRanf(unsigned int *seedp, int ilow, int ihigh)
{
	float low = (float)ilow;
	float high = (float)ihigh + 0.9999f;

	return (int)(fRanf(seedp, low, high));
}


// other useful function:

float
SQR(float x)
{
	return x*x;
}

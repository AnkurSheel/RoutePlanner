// *****************************************************************************
//  Random   version:  1.0   Ankur Sheel  date: 2011/04/16
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "RandomGenerator.h"
#include <time.h>

using namespace Utilities;

// *****************************************************************************
cRandomGenerator::cRandomGenerator()
: uSeed(1)
, uSeed_sp(0)
, iMt(CMATH_N+1)
{
}

// *****************************************************************************
float cRandomGenerator::VRandom()
{
	int r = VRandom(0xffffffff);
	float divisor = (float)0xffffffff;
	return (r / divisor) + 0.5f;
}

// *****************************************************************************
unsigned int cRandomGenerator::VRandom(const unsigned int nMax)
{
	unsigned long y;
	static unsigned long mag01[2]={0x0, CMATH_MATRIX_A};

	if(nMax == 0)
	{
		return(0);
	}

	if (iMt >= CMATH_N) 
	{ 
		/* generate N words at one time */
		int kk;

		if (iMt == CMATH_N+1)   /* if sgenrand() has not been called, */
		{
			VSetRandomSeed(4357); /* a default initial seed is used   */
		}
		for (kk = 0; kk < CMATH_N-CMATH_M; kk++) 
		{
			y = (alMt[kk] & CMATH_UPPER_MASK) | (alMt[kk+1] & CMATH_LOWER_MASK);
			alMt[kk] = alMt[kk+CMATH_M] ^ (y >> 1) ^ mag01[y & 0x1];
		}
		for (; kk< CMATH_N-1; kk++) 
		{
			y = (alMt[kk] & CMATH_UPPER_MASK) | (alMt[kk+1] & CMATH_LOWER_MASK);
			alMt[kk] = alMt[kk+(CMATH_M-CMATH_N)] ^ (y >> 1) ^ mag01[y & 0x1];
		}
		y = (alMt[CMATH_N-1] & CMATH_UPPER_MASK) | (alMt[0] & CMATH_LOWER_MASK);
		alMt[CMATH_N-1] = alMt[CMATH_M-1] ^ (y >> 1) ^ mag01[y & 0x1];

		iMt = 0;
	}

	y = alMt[iMt++];
	y ^= CMATH_TEMPERING_SHIFT_U(y);
	y ^= CMATH_TEMPERING_SHIFT_S(y) & CMATH_TEMPERING_MASK_B;
	y ^= CMATH_TEMPERING_SHIFT_T(y) & CMATH_TEMPERING_MASK_C;
	y ^= CMATH_TEMPERING_SHIFT_L(y);

	return (y%nMax);
}

// *****************************************************************************
int cRandomGenerator::VRandom(const int nMin, const int nMax)
{
	if(nMax < 0)
	{
		int range = nMin -nMax; 
		int rand =  VRandom(range);
		return rand + nMax;
	}
	return VRandom(nMax - nMin) + nMin;
}

// *****************************************************************************
void cRandomGenerator::VSetRandomSeed(const unsigned int nSeed)
{
	alMt[0]= nSeed & 0xffffffff;
	for (iMt = 1; iMt < CMATH_N; iMt++)
	{
		alMt[iMt] = (69069 * alMt[iMt-1]) & 0xffffffff;
	}

	uSeed = nSeed;
}

// *****************************************************************************
unsigned int cRandomGenerator::VGetRandomSeed()
{
	return uSeed;
}

// *****************************************************************************
void cRandomGenerator::VRandomize()
{
	VSetRandomSeed((unsigned int)time(NULL));
}

// *****************************************************************************
IRandomGenerator * IRandomGenerator::CreateRandomGenerator()
{
	cRandomGenerator * pRandomGenerator = DEBUG_NEW cRandomGenerator();
	if (pRandomGenerator)
	{
		pRandomGenerator->VRandomize();
	}
	return pRandomGenerator;
}

// *****************************************************************************
//  Random   version:  1.0   Ankur Sheel  date: 2011/04/16
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// adapted from Game Coding Complete 
// *****************************************************************************
#ifndef RandomGenerator_h__
#define RandomGenerator_h__

#include "RandomGenerator.hxx"

namespace Utilities
{
	/* Period parameters */  
#define CMATH_N 624
#define CMATH_M 397
#define CMATH_MATRIX_A 0x9908b0df   /* constant vector a */
#define CMATH_UPPER_MASK 0x80000000 /* most significant w-r bits */
#define CMATH_LOWER_MASK 0x7fffffff /* least significant r bits */

	/* Tempering parameters */   
#define CMATH_TEMPERING_MASK_B 0x9d2c5680
#define CMATH_TEMPERING_MASK_C 0xefc60000
#define CMATH_TEMPERING_SHIFT_U(y)  (y >> 11)
#define CMATH_TEMPERING_SHIFT_S(y)  (y << 7)
#define CMATH_TEMPERING_SHIFT_T(y)  (y << 15)
#define CMATH_TEMPERING_SHIFT_L(y)  (y >> 18)

	class cRandomGenerator
		: public IRandomGenerator
	{
	public:
		cRandomGenerator();	
		unsigned int VRandom(const unsigned int nMax);
		int VRandom(const int nMin, const int nMax);
		float VRandom();
		void VSetRandomSeed(const unsigned int nSeed);
		unsigned int VGetRandomSeed();
		void VRandomize();

	private:
		unsigned int		uSeed;
		unsigned int		uSeed_sp;
		unsigned long		alMt[CMATH_N]; /* the array for the state vector  */
		int					iMt; /* mti==N+1 means mt[N] is not initialized */
	};
}
#endif // RandomGenerator_h__

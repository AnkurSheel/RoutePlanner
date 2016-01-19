// *****************************************************************************
//  Random   version:  1.0   Ankur Sheel  date: 2011/04/16
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// adapted from Game Coding Complete 
// *****************************************************************************
#ifndef RandomGenerator_hxx__
#define RandomGenerator_hxx__

#include "UtilitiesDefines.h"

namespace Utilities
{
	class IRandomGenerator
	{
	public:
		virtual ~IRandomGenerator() {}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns a number from 0 to max (excluding max)
		/// 
		/// @param[in] max The max number
		/// @return a number from 0 to max (excluding max)
		/// 
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual unsigned int VRandom(const unsigned int nMax) = 0;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns a number from min to max (excluding max)
		/// 
		/// @param[in] min The min number
		/// @param[in] max The max number
		/// @return a number from min to max (excluding max)
		/// 
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual int VRandom(const int nMin, const int nMax) = 0;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns a random float between 0.0f - 1.0f
		/// 
		/// @return a random float between 0.0f - 1.0f
		/// 
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual float VRandom() = 0;
		virtual void VSetRandomSeed(const unsigned int nSeed) = 0 ;
		virtual unsigned int VGetRandomSeed() = 0;
		virtual void VRandomize() = 0;
		UTILITIES_API static IRandomGenerator * CreateRandomGenerator();
	};
}
#endif // RandomGenerator_hxx__

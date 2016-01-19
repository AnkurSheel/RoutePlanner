// *****************************************************************************
//  MathIncludes   version:  1.0   Ankur Sheel  date: 2013/01/24
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef MathIncludes_h__
#define MathIncludes_h__

namespace Base
{
  template <class T>
  const T GetMaxValue()
  {
    return (std::numeric_limits<T>::max)();
  }

  template <class T>
  const T GetMinValue()
  {
    return (std::numeric_limits<T>::min)();
  }
	//const int     MaxInt    = (std::numeric_limits<int>::max)();
	//const int     MinInt    = (std::numeric_limits<int>::min)();
	//const double  MaxDouble = (std::numeric_limits<double>::max)();
	//const double  MinDouble = (std::numeric_limits<double>::min)();
	const double  EpsilonDouble = 0.0001;
	//const float   MaxFloat  = (std::numeric_limits<float>::max)();
	//const float   MinFloat  = (std::numeric_limits<float>::min)();
	const float   EpsilonFloat = 0.0001f;

	const float   Pi        = 3.14159f;
	const float   TwoPi     = Pi * 2;
	const float   HalfPi    = Pi / 2;
	const float   QuarterPi = Pi / 4;

	inline bool isZero(const float a)
	{
		if (fabs(a) < EpsilonFloat)
		{
			return true;
		}
		return false;
	}

	inline bool isEqual(const float a, const float b)
	{
		if (fabs(a-b) < EpsilonFloat)
		{
			return true;
		}

		return false;
	}

	inline float DegtoRad(const float x)
	{
		return (x * Pi /180);
	}

	inline float RadtoDeg(const float x)
	{
		return (x * 180 /Pi);
	}

	inline float ClampToTwoPi(const float x)
	{
		float val = fmod(x, TwoPi);
		if (val < 0)
		{
			val = TwoPi + val;
		}
		return val;
	}

	inline int roundUp(int numToRound, int multiple)  
	{  
		if(multiple == 0)  
		{  
			return numToRound;  
		}  

		int remainder = numToRound % multiple; 
		if (remainder == 0)
		{
			return numToRound; 
		}

		return numToRound + multiple - remainder; 
	}  

	template <class T>
	inline short Sign(const T a)
	{
		return a >=0 ? 1 : -1;
	}

	template <class T>
	inline T Clamp(T & val, const T min, const T max)
	{
		if(val < min)
		{
			val = min;
		}
		else if (val > max)
		{
			val = max;
		}
		return val;
	}

	template <class T>
	inline T Max(const T a, const T b)
	{
		if(a > b)
		{
			return a;
		}
		else
		{
			return b;
		}
	}

	template <class T>
	inline T Min(const T a, const T b)
	{
		if(a < b)
		{
			return a;
		}
		else
		{
			return b;
		}
	}

	template <class T>
	inline T Interpolate(const T from, const T to, float alpha)
	{
		T val = (from * (1.0f - alpha)) + (to * alpha);
		return val;
	}
}
#endif // MathIncludes_h__
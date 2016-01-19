//  *******************************************************************************************************************
//  EasingFunctions   version:  1.0   Ankur Sheel  date: 2015/02/03
//  *******************************************************************************************************************
//  Equations interpreted from 
//  http://www.robertpenner.com/easing
//  http://gizma.com/easing,
//  https://tweener.googlecode.com/svn/trunk/branches/elegant/caurina/transitions/Equations.as,
//  https://github.com/jesusgollonet
//  *******************************************************************************************************************
#ifndef EASINGFUNCTIONS_H__
#define EASINGFUNCTIONS_H__

namespace Base
{
	class cBaseEasing
	{
	public:
		virtual float VEaseIn(float time, float duration) = 0;
		virtual float VEaseOut(float time, float duration);
		virtual float VEaseInOut(float time, float duration);
		virtual float VEaseOutIn(float time, float duration);
	};

	class cLinearEasing
		: public cBaseEasing
	{
		float VEaseIn(float time, float duration) OVERRIDE;
	};

	class cSineEasing
		: public cBaseEasing
	{
		float VEaseIn(float time, float duration) OVERRIDE;
	};
	class cQuadraticEasing
		: public cBaseEasing
	{
		float VEaseIn(float time, float duration) OVERRIDE;
	};

	class cCubicEasing
		: public cBaseEasing
	{
		float VEaseIn(float time, float duration) OVERRIDE;
	};

	class cQuarticEasing
		: public cBaseEasing
	{
		float VEaseIn(float time, float duration) OVERRIDE;
	};

	class cQuinticEasing
		: public cBaseEasing
	{
		float VEaseIn(float time, float duration) OVERRIDE;
	};

	class cExponentialEasing
		: public cBaseEasing
	{
		float VEaseIn(float time, float duration) OVERRIDE;
	};

	class cCircularEasing
		: public cBaseEasing
	{
		float VEaseIn(float time, float duration) OVERRIDE;
	};

	class cElasticEasing
		: public cBaseEasing
	{
		float VEaseIn(float time, float duration) OVERRIDE;
	};

	class cBackEasing
		: public cBaseEasing
	{
		float VEaseIn(float time, float duration) OVERRIDE;
	};

	class cBounceEasing
		: public cBaseEasing
	{
		float VEaseIn(float time, float duration) OVERRIDE;
		float VEaseOut(float time, float duration) OVERRIDE;
	};
}
#endif // EASINGFUNCTIONS_H__






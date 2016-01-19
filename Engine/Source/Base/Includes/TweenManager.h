//  *******************************************************************************************************************
//  TweenManager   version:  1.0   Ankur Sheel  date: 2015/02/02
//  *******************************************************************************************************************
//  Equations from http://gizma.com/easing
//  *******************************************************************************************************************
#ifndef TWEENMANAGER_HXX__
#define TWEENMANAGER_HXX__

#include "BaseDefines.h"

namespace Base
{
	class cBaseEasing;
}

namespace Base
{
	struct EasingTransitions
	{
		enum Enum
		{
			Linear,
			Sine,
			Quadratic,
			Cubic,
			Quartic,
			Quintic,
			Exponential,
			Circular,
			Elastic,
			Back,
			Bounce,
			Total
		};
		BASE_API static cString ToString(Enum transition);
	};

	struct EasingType
	{
		enum Enum
		{
			EaseIn,
			EaseOut,
			EaseInOut,
			EaseOutIn,
			Total,
		};

		BASE_API static cString ToString(Enum type);
	};

	class cTweenManager
	{
	public:
		~cTweenManager();
		template <class T>
		const T& Interpolate(EasingTransitions::Enum transition, EasingType::Enum version, const T& from, const T& to, float time, float duration);

		BASE_API static void CreateAsService();

	private:
		BASE_API float GetFactor(EasingTransitions::Enum transition, EasingType::Enum version, float time, float duration);

	private:
		std::map<EasingTransitions::Enum, cBaseEasing*> m_EasingFunctions;
		cTweenManager();
	};

	//  *******************************************************************************************************************
	template <class T>
	const T& cTweenManager::Interpolate(EasingTransitions::Enum transition, EasingType::Enum version, const T& from,
		const T& to, float time, float duration)
	{
		float alpha = GetFactor(transition, version, time, duration);
		const T& val = (from * (1.0f - alpha)) + (to * alpha);
		//const T& val = ((to - from) * alpha) + from;
		return val;
	}
}
#endif // TWEENMANAGER_HXX__

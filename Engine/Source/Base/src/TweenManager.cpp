#include "stdafx.h"
#include "TweenManager.h"
#include "EasingFunctions.h"

using namespace Base;

//  *******************************************************************************************************************
cString EasingTransitions::ToString(Enum transition)
{
	switch (transition)
	{
	case Linear:
		return "Linear";
		break;

	case Sine:
		return "Sinusoidal";
		break;

	case Quadratic:
		return "Quadratic";
		break;

	case Cubic:
		return "Cubic";
		break;

	case Quartic:
		return "Quartic";
		break;

	case Quintic:
		return "Quintic";
		break;

	case Exponential:
		return "Exponential";
		break;

	case Circular:
		return "Circular";
		break;

	case Elastic:
		return "Elastic";
		break;

	case Back:
		return "Back";
		break;

	case Bounce:
		return "Bounce";
		break;

	default:
		return "NA";
		break;
	}
}

//  *******************************************************************************************************************
cString EasingType::ToString(Enum type)
{
	switch (type)
	{
	case EaseIn:
		return "EaseIn";
		break;

	case EaseOut:
		return "EaseOut";
		break;

	case EaseInOut:
		return "EaseInOut";
		break;

	case EaseOutIn:
		return "EaseOutIn";
		break;

	default:
		return "NA";
		break;
	}
}

//  *******************************************************************************************************************
cTweenManager::cTweenManager()
{
	m_EasingFunctions[EasingTransitions::Linear] = DEBUG_NEW cLinearEasing();
	m_EasingFunctions[EasingTransitions::Sine] = DEBUG_NEW cSineEasing();
	m_EasingFunctions[EasingTransitions::Quadratic] = DEBUG_NEW cQuadraticEasing();
	m_EasingFunctions[EasingTransitions::Cubic] = DEBUG_NEW cCubicEasing();
	m_EasingFunctions[EasingTransitions::Quartic] = DEBUG_NEW cQuarticEasing();
	m_EasingFunctions[EasingTransitions::Quintic] = DEBUG_NEW cQuinticEasing();
	m_EasingFunctions[EasingTransitions::Exponential] = DEBUG_NEW cExponentialEasing();
	m_EasingFunctions[EasingTransitions::Circular] = DEBUG_NEW cCircularEasing();
	m_EasingFunctions[EasingTransitions::Elastic] = DEBUG_NEW cElasticEasing();
	m_EasingFunctions[EasingTransitions::Back] = DEBUG_NEW cBackEasing();
	m_EasingFunctions[EasingTransitions::Bounce] = DEBUG_NEW cBounceEasing();
}

//  *******************************************************************************************************************
cTweenManager::~cTweenManager()
{
	for (auto iter = m_EasingFunctions.begin(); iter != m_EasingFunctions.end(); iter++)
	{
		SafeDelete(&(iter->second));
	}
	m_EasingFunctions.clear();
}

//  *******************************************************************************************************************
float cTweenManager::GetFactor(EasingTransitions::Enum transition, EasingType::Enum version, float time, float duration)
{
	auto findIt = m_EasingFunctions.find(transition);

	SP_ASSERT_WARNING(findIt != m_EasingFunctions.end()).SetCustomMessage("Could not find tweening function for " 
		+ EasingTransitions::ToString(transition) + " " + EasingType::ToString(version));

	if (findIt != m_EasingFunctions.end())
	{
		cBaseEasing * pFunction = findIt->second;
		if (pFunction != NULL)
		{
			if (version == EasingType::EaseIn)
			{
				return pFunction->VEaseIn(time, duration);
			}
			else if (version == EasingType::EaseOut)
			{
				return pFunction->VEaseOut(time, duration);
			}
			else if (version == EasingType::EaseInOut)
			{
				return pFunction->VEaseInOut(time, duration);
			}
			else if (version == EasingType::EaseOutIn)
			{
				return pFunction->VEaseOutIn(time, duration);
			}
			else
			{
				SP_ASSERT_WARNING(false).SetCustomMessage("Could not find tweening function type for " + EasingType::ToString(version));
			}
		}
	}
	return 0.0f;
}

//  *******************************************************************************************************************
void cTweenManager::CreateAsService()
{
	cServiceLocator::GetInstance()->Register<cTweenManager>(shared_ptr<cTweenManager>(DEBUG_NEW cTweenManager()));
}

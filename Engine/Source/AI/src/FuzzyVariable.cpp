// ***************************************************************
//  FuzzyVariable   version:  1.0   Ankur Sheel  date: 04/05/2009
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2009 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "FuzzyVariable.h"
#include "AIDefines.h"
#include "FuzzySetTypes.h"
#include "FuzzySetProxy.h"

#pragma warning(disable:4150) 
using namespace Base;
//----------------------------------------------------------------------------
// Construction and Destruction
//----------------------------------------------------------------------------
cFuzzyVariable::cFuzzyVariable()
	: m_fMinRange(0)
	, m_fMaxRange(0)
{
}
//----------------------------------------------------------------------------

cFuzzyVariable::~cFuzzyVariable()
{
	for(auto it = m_MemberSets.begin();it!= m_MemberSets.end();it++)
	{
		SafeDelete(&(it->second));
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// assignment operator
//----------------------------------------------------------------------------
cFuzzyVariable& cFuzzyVariable::operator=(const cFuzzyVariable& var)
{
	this->m_fMaxRange = var.m_fMaxRange;
	this->m_fMinRange = var.m_fMinRange;
	this->m_MemberSets = var.m_MemberSets;
	return(*this);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// this method is called each time a new set is added to adjust the upper and 
// lower range values accordingly
//----------------------------------------------------------------------------
void cFuzzyVariable::AdjustRangeToFit(const float min, const float max)
{
	if(min < m_fMinRange)
	{
		m_fMinRange = min;
	}

	if(max > m_fMaxRange)
	{
		m_fMaxRange = max;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// adds a left shoulder set to the member set map. returns a proxy class 
// representing the newly created instance
//----------------------------------------------------------------------------
cFuzzySetProxy* cFuzzyVariable::AddLeftShoulderSet( const cString & name , const float minBound, const float peak , const float maxBound )
{
	m_MemberSets[name.GetData()] = DEBUG_NEW cFuzzySetLtShoulder(peak, peak-minBound, 
		maxBound- peak);

	//adjust range if req
	AdjustRangeToFit(minBound,maxBound);

	//It is the Callee's responsibility to free it
	cFuzzySetProxy* tmp = DEBUG_NEW cFuzzySetProxy(*m_MemberSets[name.GetData()]);

	//return  m_MemberSets[name];

	return tmp;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// adds a right shoulder set to the member set map. returns a proxy class 
// representing the newly created instance
//----------------------------------------------------------------------------
cFuzzySetProxy* cFuzzyVariable::AddRightShoulderSet(const cString & name,
	const float minBound,
	const float peak,
	const float maxBound)
{
	m_MemberSets[name.GetData()] = DEBUG_NEW cFuzzySetRtShoulder(peak, peak-minBound, 
		maxBound- peak);

	//adjust range if req
	AdjustRangeToFit(minBound,maxBound);

	cFuzzySetProxy* tmp = DEBUG_NEW cFuzzySetProxy(*m_MemberSets[name.GetData()]);

	//return  m_MemberSets[name];

	return tmp;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// adds a angle set to the member set map. returns a proxy class representing
// the newly created instance
//----------------------------------------------------------------------------
cFuzzySetProxy* cFuzzyVariable::AddangleSet(const cString & name, 
	const float minBound, 
	const float peak, 
	const float maxBound)
{
	m_MemberSets[name.GetData()] = DEBUG_NEW cFuzzySetangle(peak, peak-minBound, maxBound- peak);

	//adjust range if req
	AdjustRangeToFit(minBound,maxBound);

	cFuzzySetProxy* tmp = DEBUG_NEW cFuzzySetProxy(*m_MemberSets[name.GetData()]);

	return tmp;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// fuzzify a value by calculating its DOM in each of this variable's subsets
//----------------------------------------------------------------------------
void cFuzzyVariable::Fuzzify(const float val)
{
	//make sure the value is within the bounds of this variable
	_ASSERT((val >= m_fMinRange) && (val <= m_fMaxRange));

	//for each set in the flv calculate the DOM for the given value
	for (auto curSet = m_MemberSets.begin(); curSet != m_MemberSets.end(); ++curSet)
	{
		curSet->second->SetDOM(curSet->second->CalculateDOM(val));
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// defuzzify the variable using the MaxAv method
//----------------------------------------------------------------------------
float cFuzzyVariable::DeFuzzifyMaxAv()
{
	float fBottom = 0.0f;
	float fTop    = 0.0f;

	for (auto curSet = m_MemberSets.begin(); curSet != m_MemberSets.end(); ++curSet)
	{
		fBottom += curSet->second->GetDOM();

		fTop += curSet->second->GetRepresentativeValue() * curSet->second->GetDOM();
	}

	//make sure bottom is not equal to zero
	if (fBottom == 0.0f)
	{
		return 0.0;
	}

	return (fTop / fBottom);   

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// defuzzify the variable using the centroid method
//----------------------------------------------------------------------------
float cFuzzyVariable::DeFuzzifyCentroid(const int iNumSamples)
{
	//calculate the step size
	float fStepSize = (m_fMaxRange - m_fMinRange)/(float)iNumSamples;

	float fTotalArea    = 0.0;
	float fSumOfMoments = 0.0;

	//step through the range of this variable in increments equal to StepSize
	//adding up the conbution for each subset. 
	//
	//in addition the moment of each slice is calculated and summed. Dividing
	//the total area by the sum of the moments gives the centroid. 

	for (int iSamp=1; iSamp<=iNumSamples; ++iSamp)
	{
		//for each set get the conbution to the area. This is the lower of the 
		//value returned from CalculateDOM or the actual DOM of the fuzzified 
		//value itself   

		float conbution;
		for (auto curSet = m_MemberSets.begin(); curSet != m_MemberSets.end(); curSet++)
		{
			float fSetCalcDomVal = curSet->second->CalculateDOM(m_fMinRange+iSamp*fStepSize);
			float fGetDomVal= curSet->second->GetDOM();
			if( fSetCalcDomVal < fGetDomVal)
			{
				conbution = fSetCalcDomVal;
			}
			else
			{
				conbution = fGetDomVal;
			}
			fTotalArea += conbution;

			fSumOfMoments += (m_fMinRange + iSamp * fStepSize)  * conbution;
		}
	}

	//make sure total area is not equal to zero
	if (fTotalArea == 0.0f)
	{
		return 0.0;
	}

	return (fSumOfMoments / fTotalArea);

}
//----------------------------------------------------------------------------
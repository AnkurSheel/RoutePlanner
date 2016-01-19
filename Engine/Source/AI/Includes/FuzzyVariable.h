// ***************************************************************
//  FuzzyVariable   version:  1.0   Ankur Sheel  date: 04/05/2009
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2009 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef FUZZYVARIABLE_H
#define FUZZYVARIABLE_H

#include <map>

class cFuzzySet;
class cFuzzyModule;
class cFuzzySetProxy;

namespace Base
{
	class cString;
}

class cFuzzyVariable
{
protected:
	typedef std::map<const char * const, cFuzzySet*> MemberSets;

public:
	cFuzzyVariable();
	virtual ~cFuzzyVariable();
	cFuzzyVariable& operator=(const cFuzzyVariable& var);
	cFuzzySetProxy* AddLeftShoulderSet(const Base::cString & name , const float minBound, const float peak , const float maxBound);
	cFuzzySetProxy* AddRightShoulderSet(const Base::cString & name
									, const float minBound, const float peak
									, const float maxBound);
	cFuzzySetProxy* AddangleSet(const Base::cString & name, const float minBound
									, const float peak, const float maxBound);
	void Fuzzify(const float val);
	float DeFuzzifyMaxAv();
	float DeFuzzifyCentroid(const int iNumSamples);

protected:
	cFuzzyVariable(const cFuzzyVariable& var);
	void AdjustRangeToFit(const float min, const float max);

protected:
	friend class cFuzzyModule;
	MemberSets m_MemberSets;
	float m_fMinRange;
	float m_fMaxRange;
};
#endif
// ne Entertainment, Ltd.
// http://www.neGames.com
// Copyright (c) 2007.  All Rights Reserved
//
// FuzzySetangle: Ankur Sheel
// FuzzySetLtShoulder: Ankur Sheel
// FuzzySetRtShoulder: Ankur Sheel

#ifndef FUZZYSETTYPES_H
#define FUZZYSETTYPES_H

#include "FuzzySet.h"

class cFuzzySetangle :
	public cFuzzySet
{
public:
	cFuzzySetangle();
	virtual ~cFuzzySetangle();
	void CreateangleSet(const float fMid, const float fLeft
							, const float fRight);
	float CalculateDOM(const float val);
	cFuzzySetangle(const float fPeak, const float fLeftOffset
					 , const float fRightOffset);
protected:
	float m_fPeakPoint;
	float m_fLeftOffset;
	float m_fRightOffset;
};

class cFuzzySetLtShoulder :
	public cFuzzySet
{
public:
	cFuzzySetLtShoulder();
	virtual ~cFuzzySetLtShoulder();
	void CreateLtShoulderSet(const float fMid, const float fLeft
							, const float fRight);
	float CalculateDOM(const float val);
	cFuzzySetLtShoulder(const float fPeak, const float fLeftOffset
					   , const float fRightOffset);

protected:
	float m_fPeakPoint;
	float m_fLeftOffset;
	float m_fRightOffset;
};

class cFuzzySetRtShoulder :
	public cFuzzySet
{
public:
	cFuzzySetRtShoulder();
	virtual ~cFuzzySetRtShoulder();
	void CreateRtShoulderSet(const float fMid, const float fLeft
							, const float fRight);
	float CalculateDOM(const float val);
	cFuzzySetRtShoulder(const float fPeak, const float fLeftOffset
					   , const float fRightOffset);

protected:
	float m_fPeakPoint;
	float m_fLeftOffset;
	float m_fRightOffset;
};
#endif
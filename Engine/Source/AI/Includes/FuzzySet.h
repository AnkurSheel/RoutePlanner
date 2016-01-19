// ***************************************************************
//  FuzzySet   version:  1.0   Ankur Sheel  date: 04/05/2009
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2009 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef FUZZYSET_H
#define FUZZYSET_H

class cFuzzySet
{
public:
	cFuzzySet();
	virtual ~cFuzzySet();
	virtual float CalculateDOM(const float val){return 0;};
	void ORwithDOM(const float val);
	float GetRepresentativeValue();
	void ClearDOM();
	void CreateFuzzySet(const float val);
	void SetDOM(const float val);
	cFuzzySet(const float fRepVal);
	float GetDOM();
	cFuzzySet* GetAddress();
protected:
	float m_fDOM;
	float m_fRepresentativeValue;
};
#endif
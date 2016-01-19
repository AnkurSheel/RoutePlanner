// ***************************************************************
//  FuzzySetProxy   version:  1.0   Ankur Sheel  date: 04/05/2009
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2009 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef FUZZYSETPROXY_H
#define FUZZYSETPROXY_H


#include "FuzzyTerm.h"

class cFuzzySet;

class cFuzzySetProxy :
	public cFuzzyTerm
{
public:
	cFuzzySetProxy();
	virtual ~cFuzzySetProxy();
	cFuzzySetProxy(cFuzzySet& fs);
	cFuzzyTerm* Clone();
	float GetDOM();
	void ClearDOM();
	void ORwithDOM(const float val);

protected:
	cFuzzySet* m_Set;
	friend class cFuzzyOperatorVery;
	friend class cFuzzyOperatorFairly;

};
#endif
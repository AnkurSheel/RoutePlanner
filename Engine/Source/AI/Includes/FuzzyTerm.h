// ***************************************************************
//  FuzzyTerm   version:  1.0   Ankur Sheel  date: 04/05/2009
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2009 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef FUZZYTERM_H
#define FUZZYTERM_H

class cFuzzySet;

class cFuzzyTerm
{
public:
	virtual ~cFuzzyTerm();
	virtual cFuzzyTerm* Clone() = 0;
	virtual float GetDOM() = 0;
	virtual void ClearDOM() = 0;
	virtual void ORwithDOM(const float val) = 0;
};
#endif

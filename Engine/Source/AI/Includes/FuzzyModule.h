// ***************************************************************
//  FuzzyModule   version:  1.0   Ankur Sheel  date: 04/05/2009
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2009 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef FUZZYMODULE_H
#define FUZZYMODULE_H

class cFuzzyTerm;
class cFuzzyVariable;
class cFuzzyRule;

#include <map>
#include <vector>
#include "AIDefines.h"

class cFuzzyModule
{
protected:
	struct compstr
	{
		bool operator () (const Base::cString & str1, const Base::cString & str2) const
		{
			return str1.CompareInsensitive(str2);	
		}
	};

	typedef std::map<const char * const, cFuzzyVariable*, compstr> VarMap;

public:
	enum DeFuzzifyMethod
	{
		Max_average
		,Centroid
	};
public:
	AI_API cFuzzyModule();
	AI_API virtual ~cFuzzyModule();
	AI_API cFuzzyVariable* CreateFLV(const Base::cString & varName);
	AI_API void AddRule(cFuzzyTerm* antecedent, cFuzzyTerm* consequent);
	AI_API float DeFuzzify(const Base::cString & key, const DeFuzzifyMethod method);
	AI_API void Fuzzify(const Base::cString & nameOfFLV, const float val);

protected:
	void SetConfidencesofConsequentsToZero();

private:
	int m_iNumSamples;
	VarMap m_Variables;
	std::vector<cFuzzyRule* > m_Rules;
};
#endif

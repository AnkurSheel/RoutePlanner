// ne Entertainment, Ltd.
// http://www.neGames.com
// Copyright (c) 2007.  All Rights Reserved
//
// FuzzyRule: Ankur Sheel

#ifndef FUZZYRULE_H
#define FUZZYRULE_H

class cFuzzyTerm;

class cFuzzyRule
{
public:
	cFuzzyRule();
	virtual ~cFuzzyRule();
	cFuzzyRule(cFuzzyTerm* ante, cFuzzyTerm* conse);
	void SetConfidenceOfConsequenceToZero();
	void Calculate();

protected:
	cFuzzyTerm* m_pAntecedent;
	cFuzzyTerm* m_pConsequence;
	cFuzzyRule(const cFuzzyRule& instance);
	cFuzzyRule& operator=(const cFuzzyRule& instance);
};
#endif
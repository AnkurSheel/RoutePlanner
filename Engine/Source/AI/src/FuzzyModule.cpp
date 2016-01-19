// ***************************************************************
//  FuzzyModule   version:  1.0   Ankur Sheel  date: 04/05/2009
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2009 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "FuzzyModule.h"
#include "FuzzyVariable.h"
#include "FuzzyRule.h"
#include "AIDefines.h"

using namespace Base;
//----------------------------------------------------------------------------
// Construction and Destruction
//----------------------------------------------------------------------------
cFuzzyModule::cFuzzyModule()
	: m_iNumSamples(0)
{
	//m_iNumSamples = 15;

}
//----------------------------------------------------------------------------

cFuzzyModule::~cFuzzyModule()
{
	//free variable memory
	for(auto curVar = m_Variables.begin(); curVar != m_Variables.end(); curVar++)
	{
		SafeDelete(&(curVar->second));
	}

	//free rules
	for(auto curRule = m_Rules.begin(); curRule != m_Rules.end();curRule++)
	{
		SafeDelete(&(*curRule));
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Sets confidence of consequents to zero
//----------------------------------------------------------------------------
void cFuzzyModule::SetConfidencesofConsequentsToZero()
{
	for(auto curRule = m_Rules.begin(); curRule !=m_Rules.end(); curRule++)
	{
		(*curRule)->SetConfidenceOfConsequenceToZero();
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// creates a empty fuzzy variable and returns a reference to its Construction
// and Destruction
//----------------------------------------------------------------------------
cFuzzyVariable* cFuzzyModule::CreateFLV(const cString & varName)
{
	m_Variables.insert(std::make_pair(varName.GetData(), DEBUG_NEW cFuzzyVariable()));

	return m_Variables[varName.GetData()];
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// adds a rule to the module
//----------------------------------------------------------------------------
void cFuzzyModule::AddRule(cFuzzyTerm* antecedent, cFuzzyTerm* consequent)
{
	cFuzzyRule* p = DEBUG_NEW cFuzzyRule(antecedent, consequent);
	m_Rules.push_back(p);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// returns a crisp value
//----------------------------------------------------------------------------
float cFuzzyModule::DeFuzzify(const cString & key, const DeFuzzifyMethod method)
{
	_ASSERT((m_Variables.find(key.GetData()) != m_Variables.end()));

	SetConfidencesofConsequentsToZero();

	//process the rules
	for(auto curRule = m_Rules.begin(); curRule != m_Rules.end(); curRule++)
	{
		(*curRule)->Calculate();
	}

	switch(method)
	{
	case Max_average:
		return(m_Variables[key.GetData()]->DeFuzzifyMaxAv());
		break;

	case Centroid:
		return(m_Variables[key.GetData()]->DeFuzzifyCentroid(m_iNumSamples));
		break;

	}
	return 0;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// this method calls the Fuzzify method of the variable with the same name as 
// the key
//----------------------------------------------------------------------------
void cFuzzyModule::Fuzzify(const cString & nameOfFLV, const float val)
{
	_ASSERT((m_Variables.find(nameOfFLV.GetData()) != m_Variables.end()));
	m_Variables[nameOfFLV.GetData()]->Fuzzify(val);
}
//----------------------------------------------------------------------------
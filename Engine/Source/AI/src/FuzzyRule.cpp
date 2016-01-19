// ***************************************************************
//  FuzzyRule   version:  1.0   Ankur Sheel  date: 04/05/2009
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2009 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "FuzzyRule.h"
#include "AIDefines.h"
#include "FuzzyTerm.h"

using namespace Base;
//----------------------------------------------------------------------------
// Construction and Destruction
//----------------------------------------------------------------------------
cFuzzyRule::cFuzzyRule()
: m_pAntecedent(NULL)
, m_pConsequence(NULL)
{
}
//----------------------------------------------------------------------------

cFuzzyRule::~cFuzzyRule()
{
	SafeDelete(&m_pAntecedent);
	SafeDelete(&m_pConsequence);
}
//----------------------------------------------------------------------------

cFuzzyRule::cFuzzyRule(cFuzzyTerm* ante, cFuzzyTerm* conse)
: m_pAntecedent(ante->Clone())
, m_pConsequence(conse->Clone())
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Sets the DOM of the consequence to 0
//----------------------------------------------------------------------------
void cFuzzyRule::SetConfidenceOfConsequenceToZero()
{
	m_pConsequence->ClearDOM();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Updates the DOM of the consequent with the DOM of the Antecedent
//----------------------------------------------------------------------------
void cFuzzyRule::Calculate()
{
	m_pConsequence->ORwithDOM(m_pAntecedent->GetDOM());
}
//----------------------------------------------------------------------------
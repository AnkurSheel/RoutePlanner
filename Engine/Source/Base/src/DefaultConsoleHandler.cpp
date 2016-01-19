#include "stdafx.h"
#include "DefaultConsoleHandler.h"
#include "SpAssertContext.h"
#include <iostream>

using namespace Base;
using namespace std;

//  ********************************************************************************************************************
AssertAction::AssertAction cDefaultConsoleHandler::VDisplayMessageAndGetAction(const ISpAssertContext * const pContext)
{
	cString strChooseMsg;

	if (pContext != NULL)
	{
		strChooseMsg = "Assertion Failed : [" + pContext->VGetExpression();
		strChooseMsg += "] in\n file: " + pContext->VGetFileName();
		strChooseMsg += "\nline: " + pContext->VGetLineNumber();
		if(!pContext->VGetCustomMessage().IsEmpty())
		{
			strChooseMsg += "\nExpression " + pContext->VGetCustomMessage();
		}
		strChooseMsg += "\nValues:\n";

		for(auto iter = pContext->VGetVariablesArray().begin(); iter != pContext->VGetVariablesArray().end(); ++iter)
		{
			strChooseMsg += "\n" + iter->m_VariableName + " = " + iter->m_VariableValue;
		}
	}
	strChooseMsg += "\n\nChoose option: ";
	strChooseMsg += "(M)ore details, ";
	strChooseMsg += "(I)gnore, Ignore (F)orever, Ignore A(L)l, (D)ebug, (A)bort\n";

	cout << strChooseMsg << std::endl;
	bool bContinue = true;
	while (bContinue) 
	{ 
		bContinue = false;
		char ch = cin.get();
		switch (ch) 
		{
		case 'm': case 'M':
			// details
			bContinue = true;
			break;

		case 'i': case 'I':
			return AssertAction::Ignore;

		case 'f': case 'F':
			return AssertAction::IgnoreForever;

		case 'l': case 'L':
			return AssertAction::IgnoreAll;

		case 'd': case 'D':
			return AssertAction::Break;
			break;

		case 'a': case 'A':
			return AssertAction::Abort;
			break;

		default:
			bContinue = true;
			break;
		};

		if ( !isspace( ch) && bContinue)
		// ignore spaces
		cout << strChooseMsg << std::endl;
	};
	return AssertAction::None;
}

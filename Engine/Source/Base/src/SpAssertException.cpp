#include "stdafx.h"
#include "SpAssertException.h"
#include "SpAssertContext.hxx"

using namespace Base;

//  ********************************************************************************************************************
cSpAssertException::cSpAssertException(const ISpAssertContext * const pContext) : m_pContext(pContext)
{

}

//  ********************************************************************************************************************
cSpAssertException::~cSpAssertException()
{

}

//  ********************************************************************************************************************
const char * cSpAssertException::what() const
{
	cString strChooseMsg;
	if (m_pContext != NULL)
	{
		strChooseMsg = "Exception [ " + m_pContext->VGetExpression();
		strChooseMsg += "] \nin : \nfile: " + m_pContext->VGetFileName();
		strChooseMsg += cStringUtilities::MakeFormatted(" : line: %d\n", m_pContext->VGetLineNumber());
		strChooseMsg += "function " + m_pContext->VGetFunctionName() + "\n";
		if(!m_pContext->VGetCustomMessage().IsEmpty())
		{
			strChooseMsg += "Message : " + m_pContext->VGetCustomMessage();
		}
		if (m_pContext->VGetVariablesArray().size() > 0)
		{
			strChooseMsg += "\nValues:\n";

			for(auto iter = m_pContext->VGetVariablesArray().begin(); iter != m_pContext->VGetVariablesArray().end(); ++iter)
			{
				strChooseMsg += iter->m_VariableName + " = " + iter->m_VariableValue + "\n";
			}
		}
	}
	return strChooseMsg.GetData();
}

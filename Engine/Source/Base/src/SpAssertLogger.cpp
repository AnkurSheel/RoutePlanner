#include "stdafx.h"
#include "SpAssertLogger.h"
#include "SpAssertContext.hxx"
#include "FileIO.hxx"
#include "SpAssertFwd.h"

using namespace Base;
using namespace std;

//  ********************************************************************************************************************
cSpAssertLogger::cSpAssertLogger()
: m_pFile(NULL)
{

}

//  ********************************************************************************************************************
cSpAssertLogger::~cSpAssertLogger()
{
	SafeDelete(&m_pFile);
}

//  ********************************************************************************************************************
void cSpAssertLogger::VInitialize()
{
	m_pFile = IFileIO::CreateFileIO();
	m_pFile->VOpenFile("assert.log", ios_base::out);
}

//  ********************************************************************************************************************
void cSpAssertLogger::VLog(const ISpAssertContext * const pContext)
{
	if (pContext != NULL && m_pFile != NULL)
	{
		cString strChooseMsg;
		strChooseMsg = GetAssertLevelAsString(pContext->VGetDebugLevel());
		strChooseMsg += " [ " + pContext->VGetExpression();
		strChooseMsg += "] \nin : \nfile: " + pContext->VGetFileName();
		strChooseMsg += cStringUtilities::MakeFormatted(" : line: %d\n", pContext->VGetLineNumber());
		strChooseMsg += "function " + pContext->VGetFunctionName() + "\n";
		if(!pContext->VGetCustomMessage().IsEmpty())
		{
			strChooseMsg += "Message : " + pContext->VGetCustomMessage();
		}
		if (pContext->VGetVariablesArray().size() > 0)
		{
			strChooseMsg += "\nValues:\n";

			for(auto iter = pContext->VGetVariablesArray().begin(); iter != pContext->VGetVariablesArray().end(); ++iter)
			{
				strChooseMsg += iter->m_VariableName + " = " + iter->m_VariableValue + "\n";
			}
		}
		strChooseMsg += "\n";
		m_pFile->VWriteLine(strChooseMsg);
		m_pFile->VFlush();
	}
}

//  ********************************************************************************************************************
cString cSpAssertLogger::GetAssertLevelAsString(const int level)
{
	switch (level)
	{
	case AssertLevels::LEVEL_WARNING:
		return "Warning";

	case AssertLevels::LEVEL_DEBUG:
		return "Assertion failed";

	case AssertLevels::LEVEL_ERROR:
		return "Assertion failed (Error)";

	case AssertLevels::LEVEL_FATAL:
		return "Assertion failed (FATAL)";

	default: 
		return cStringUtilities::MakeFormatted("Assertion failed (level = %d)", level);
	};
}

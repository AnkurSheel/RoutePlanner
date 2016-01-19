#include "stdafx.h"
#include "Logger.h"
#include <time.h>
#include "XMLFileIO.hxx"
#include "SystemChecker.hxx"
#include "FileIO.hxx"
#include "SpAssertContext.hxx"

using namespace Utilities;
using namespace Base;
using namespace std;

int cLogger::m_iCurrentId = 1;

//  *******************************************************************************************************************
cLogger::cLogger()
: m_pTextLogFile(NULL)
, m_hStdOut(NULL) 
, m_pXmlLogFile(NULL)
, m_PriorityLevel(1)
{
}

//  *******************************************************************************************************************
cLogger::~cLogger()
{
	Close();
}

//  *******************************************************************************************************************
void cLogger::VInitialize()
{
	m_pTextLogFile = IFileIO::CreateFileIO();
	if(!(m_pTextLogFile->VOpenFile("log.txt", ios_base::out)))
	{
		SafeDelete(&m_pTextLogFile);
	}
}

//  *******************************************************************************************************************
void cLogger::VSetLogOptions(const bool bShowConsole, const bool bLogToText,
const bool bLogToXML, const unsigned int uiLevel)
{
	m_PriorityLevel = uiLevel;

	if(bShowConsole)
	{
		m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if(m_hStdOut == NULL && AllocConsole() != 0)
		{
			SetConsoleTitle("Logger");
			m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			FILE *fp;
			freopen_s(&fp, "CONOUT$", "w", stdout);
		}
	}

	if(!bLogToText && m_pTextLogFile)
	{
		SafeDelete(&m_pTextLogFile);
	}

	if(bLogToXML)
	{
		m_pXmlLogFile = IXMLFileIO::CreateXMLFile();
		m_pXmlLogFile->VInitializeForSave("RunTimeLog", "BasicXSLT.xsl");
		m_pXmlLogFile->VAddElement("RunTimeLog", "LogHeader", "", "");
		m_pXmlLogFile->VAddElement("RunTimeLog", "LogEvents", "", "");
		CreateHeader();
	}
}

//  *******************************************************************************************************************
void cLogger::CreateHeader()
{
	m_pXmlLogFile->VAddElement("LogHeader", "OutputLevel", "", cStringUtilities::MakeFormatted("Level %d", m_PriorityLevel));
	m_pXmlLogFile->VAddElement("LogHeader", "OutputLevel", "", cStringUtilities::MakeFormatted("%d", m_PriorityLevel));
	m_pXmlLogFile->VAddElement("LogHeader", "Session", "", "");
	m_pXmlLogFile->VAddElement("Session", "Configuration", "", "");
	m_pXmlLogFile->VAddElement("Configuration", "Memory", "", "");
	m_pXmlLogFile->VAddElement("Memory", "AvailablePhysical", "", cStringUtilities::MakeFormatted("%d", ISystemChecker::Instance()->VGetAvailablePhysicalMemory()));

	m_pXmlLogFile->VAddElement("Memory", "TotalPhysical", "", cStringUtilities::MakeFormatted("%d", ISystemChecker::Instance()->VGetTotalPhysicalMemory()));

	m_pXmlLogFile->VAddElement("Memory", "AvailableVirtual", "", cStringUtilities::MakeFormatted("%d", ISystemChecker::Instance()->VGetAvailableVirtualMemory()));

	m_pXmlLogFile->VAddElement("Memory", "TotalVirtual", "", cStringUtilities::MakeFormatted("%d", ISystemChecker::Instance()->VGetTotalVirtualMemory()));

	m_pXmlLogFile->VAddElement("Memory", "AvailableHardDiskSpace", "", cStringUtilities::MakeFormatted("%d", ISystemChecker::Instance()->VGetAvailableHardDiskSpace()));

	m_pXmlLogFile->VAddElement("Memory", "TotalHardDiskSpace", "", cStringUtilities::MakeFormatted("%d", ISystemChecker::Instance()->VGetTotalHardDiskSpace()));

	m_pXmlLogFile->VAddElement("Configuration", "Processor", "", "");
	m_pXmlLogFile->VAddElement("Processor", "ClockSpeed", "", cStringUtilities::MakeFormatted("%d", ISystemChecker::Instance()->VGetCPUSpeed()));

	m_pXmlLogFile->VAddElement("Session", "Started", "", "");

	time_t currentTime;
	time(&currentTime);
	m_pXmlLogFile->VAddElement("Started", "Time", "", cStringUtilities::CalendarTimeToString(currentTime));
}

//  *******************************************************************************************************************
void cLogger::Close()
{
	if(m_pXmlLogFile)
	{
		m_pXmlLogFile->VSave("log.xml");
	}
	if (m_pTextLogFile)
	{
		m_pTextLogFile->VCloseFile();
	}
	SafeDelete(&m_pTextLogFile);
	SafeDelete(&m_pXmlLogFile);
}

////  *******************************************************************************************************************
//void cLogger::VWriteLogEntry(const LogType eLogEntryType,
//const unsigned int uiPriorityLevel, const Base::cString & strSourceFile,
//const Base::cString & strFunction, const int iSourceLine,
//const Base::cString & strMessage)
//{
//	if(uiPriorityLevel > m_PriorityLevel)
//	return;
//
//	Log(eLogEntryType, strSourceFile, strMessage, iSourceLine, strMessage);
//	if(!m_pXmlLogFile)
//	return;
//
//	cString strEvent = m_pXmlLogFile->VAddElement("LogEvents", "LogEvent", cStringUtilities::MakeFormatted("%d", m_iCurrentId), "");
//
//	m_pXmlLogFile->VAddElement(strEvent, "Type", "", LogTypeToString(eLogEntryType));
//
//	time_t currentTime;
//	time(&currentTime );
//
//	m_pXmlLogFile->VAddElement(strEvent, "TimeIndex", "", cStringUtilities::CalendarTimeToString(currentTime));
//
//	m_pXmlLogFile->VAddElement(strEvent, "File", "", strSourceFile);
//	m_pXmlLogFile->VAddElement(strEvent, "Function", "", strFunction);
//
//	m_pXmlLogFile->VAddElement(strEvent, "LineNumber", "", cStringUtilities::MakeFormatted("%d", iSourceLine));
//	m_pXmlLogFile->VAddElement(strEvent, "Message", "", strMessage);
//	m_iCurrentId++;
//}

//  ********************************************************************************************************************
void cLogger::VLog(const ISpAssertContext * const pContext)
{
	if (pContext != NULL && m_pTextLogFile != NULL)
	{
		if (pContext->VGetPriority() > m_PriorityLevel)
		{
			return;
		}

		cString strChooseMsg;

		time_t currentTime;
		time(&currentTime);

		strChooseMsg = cStringUtilities::CalendarTimeToString(currentTime); 
		
		strChooseMsg = GetAssertLevelAsString(pContext->VGetDebugLevel());
		strChooseMsg += " : [ " + pContext->VGetExpression();
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
		m_pTextLogFile->VWriteLine(strChooseMsg);
		m_pTextLogFile->VFlush();

		if(m_hStdOut)
		{
			SetConsoleTextColor(pContext->VGetDebugLevel());
			cout << strChooseMsg;
		}

		::OutputDebugString(strChooseMsg.GetData());
	}
}

//  *******************************************************************************************************************
void cLogger::SetConsoleTextColor(const int logEntryType)
{
	switch(logEntryType)
	{
	case LogType::LEVEL_DEBUG: 
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
		break;
	case LogType::LEVEL_ERROR:
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_RED|FOREGROUND_INTENSITY);
		break;
	case LogType::LEVEL_WARNING: 
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_RED| FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		break;
	case LogType::LEVEL_INFO:
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		break;
	case LogType::EVENT: 
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_BLUE| FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		break;
	case LogType::GAME_MESSAGE: 
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_BLUE| FOREGROUND_INTENSITY);
		break;
	default:
		//set color to white
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		break;
	}
}

//  ********************************************************************************************************************
cString cLogger::GetAssertLevelAsString(int logLevel)
{
	switch (logLevel)
	{
	case LogType::LEVEL_INFO:
		return "Info";

	case LogType::LEVEL_WARNING:
		return "Warning";

	case LogType::LEVEL_DEBUG:
		return "Assertion failed";

	case LogType::LEVEL_ERROR:
		return "Assertion failed (Error)";

	case LogType::LEVEL_FATAL:
		return "Assertion failed (FATAL)";

	case LogType::EVENT: 
		return "Event";

	case LogType::GAME_MESSAGE: 
		return "Game Message";

	default: 
		return cStringUtilities::MakeFormatted("Assertion failed (level = %d)", logLevel);
	}
}

//  ********************************************************************************************************************
shared_ptr<ILogger> ILogger::CreateLogger()
{
	return shared_ptr<ILogger>(DEBUG_NEW cLogger());
}

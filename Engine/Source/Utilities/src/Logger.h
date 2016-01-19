//  *******************************************************************************************************************
//  Logger   version:  1.0   Ankur Sheel  date: 2011/01/04
//  *******************************************************************************************************************
//  2011/01/04 : based on http://archive.gamedev.net/reference/programming/features/xmltech/default.asp 
//  *******************************************************************************************************************
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "Logger.hxx"

namespace Base
{
	class cString;
	class IFileIO;
	class ISpAssertContext;
}

namespace Utilities
{
	class IXMLFileIO;
}

namespace Utilities
{
	///////////////////////////////////////////////////////////////////////////
	/// @brief Implementation of the Logger
	///
	/// 
	///////////////////////////////////////////////////////////////////////////
	class cLogger
	: public ILogger
	, public Base::cNonCopyable
	{
		public :
		~cLogger();

	private:
		cLogger();
		void VInitialize();
		void VSetLogOptions(const bool bShowConsole, const bool bLogToText,
		const bool bLogToXML, const unsigned int uiPriorityLevel);
		void VLog(const Base::ISpAssertContext * const pContext);
		void CreateHeader();
		void Close();
		void SetConsoleTextColor(const int logEntryType);
		Base::cString GetAssertLevelAsString(int logLevel);

	private:
		Base::IFileIO*	m_pTextLogFile;
		HANDLE			m_hStdOut;
		IXMLFileIO	*	m_pXmlLogFile;
		int	m_PriorityLevel;

		static int		m_iCurrentId;

	private:
		friend static std::tr1::shared_ptr<ILogger> ILogger::CreateLogger();
	};
}
#endif  // __LOGGER_H__


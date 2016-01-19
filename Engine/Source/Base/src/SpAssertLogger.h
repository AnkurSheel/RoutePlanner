//  *******************************************************************************************************************
//  SpAssertLogger   version:  1.0   Ankur Sheel  date: 2014/11/03
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __SPASSERTLOGGER_H__
#define __SPASSERTLOGGER_H__

#include "SpAssertLogger.hxx"

namespace Base
{
	class IFileIO;
	class ISpAssertContext;
}

namespace Base
{
	class cSpAssertLogger
	: public ISpAssertLogger
	{
	public:
		cSpAssertLogger();
		~cSpAssertLogger();

	private:
		void VInitialize();
		void VLog(const ISpAssertContext * const pContext);
		cString GetAssertLevelAsString(const int level);

	private:
		IFileIO * m_pFile;
	};
}
#endif  // __SPASSERTLOGGER_H__

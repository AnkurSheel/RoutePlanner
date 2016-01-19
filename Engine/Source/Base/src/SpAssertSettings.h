//  *******************************************************************************************************************
//  SpAssertSettings   version:  1.0   Ankur Sheel  date: 2014/10/16
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __SPASSERTSETTINGS_H__
#define __SPASSERTSETTINGS_H__

#include "SpAssertContext.h"
#include "SpAssertSettings.hxx"

namespace Base
{
	class cSpAssertHandler;
}

namespace Base
{
	class cSpAssertSettings 
	: public ISpAssertSettings
	{
		typedef std::map< int, cSpAssertHandlerStrongPtr> AssertHandlerMap;
		typedef std::set<cSpAssertContext, std::less<cSpAssertContext> > ContextSet;

	public:
		~cSpAssertSettings();

		bool VGetIgnoreAll() const { return m_bIgnoreAll; }
		void VSetIgnoreAll(bool ignoreAll) { m_bIgnoreAll = ignoreAll; }
		cSpAssertHandlerStrongPtr VGetHandler(int level) const;
		void VSetHandler(int level, cSpAssertHandlerStrongPtr handler);
		ISpAssertLoggerStrongPtr VGetLogger() const { return m_pLogger; }
		void VSetLogger(ISpAssertLoggerStrongPtr pLogger) { m_pLogger = pLogger; }
		void VAddToIgnoreList(const ISpAssertContext * const pContext);
		bool VIsIgnored(const ISpAssertContext * const pContext) const;

	private:
		cSpAssertSettings();
		void SetDefaultLogger();

	private:
		AssertHandlerMap m_handlers;
		ContextSet m_IgnoredAsserts;
		ISpAssertLoggerStrongPtr m_pLogger;
		bool m_bIgnoreAll;

		friend void ISpAssertSettings::CreateAsService();
	};
}
#endif  // __SPASSERTSETTINGS_H__

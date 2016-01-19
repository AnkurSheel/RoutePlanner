//  *******************************************************************************************************************
//  SpAssertSettings   version:  1.0   Ankur Sheel  date: 2014/10/23
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __SPASSERTSETTINGS_HXX__
#define __SPASSERTSETTINGS_HXX__

#include "BaseDefines.h"
#include "SpAssertFwd.h"

namespace Base
{
	class ISpAssertLogger;
  class cAssertHandlerFactory;
}

namespace Base
{
	class ISpAssertSettings
	{
	public:
		virtual ~ISpAssertSettings() {}
		virtual bool VGetIgnoreAll() const = 0;
		virtual void VSetIgnoreAll(bool ignoreAll) = 0;
		virtual void VSetHandler(int level, cSpAssertHandlerStrongPtr handler) = 0;
		virtual void VSetLogger(ISpAssertLoggerStrongPtr logger) = 0;
		virtual void VAddToIgnoreList(const ISpAssertContext * const pContext) = 0;
		virtual bool VIsIgnored(const ISpAssertContext * const pContext) const = 0;
		virtual cSpAssertHandlerStrongPtr VGetHandler(int level) const = 0;
		virtual ISpAssertLoggerStrongPtr VGetLogger() const = 0;
		BASE_API static void CreateAsService();
	};
} 
#endif  // __SPASSERTSETTINGS_HXX__


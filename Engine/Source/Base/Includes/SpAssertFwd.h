//  *******************************************************************************************************************
//  SpAssertFwd   version:  1.0   Ankur Sheel  date: 2014/10/15
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __SPASSERTFWD_H__
#define __SPASSERTFWD_H__

#include <memory>

namespace Base
{
	class cSpAssertHandler;
	class ISpAssertLogger;
	class cAssertHandlerFactory;

	typedef std::shared_ptr<cSpAssertHandler> cSpAssertHandlerStrongPtr;
	typedef std::shared_ptr<ISpAssertLogger> ISpAssertLoggerStrongPtr;

	struct AssertLevels
	{
		enum 
		{
			LEVEL_INFO = 100, // information for logger
			LEVEL_WARNING = 200, // it's just a warning, the program can continue without user intervention
			LEVEL_DEBUG = 500, // it's the default, the usual assert
			LEVEL_ERROR = 700, // an error
			LEVEL_FATAL = 1000 // it's fatal, it's most likely the program/system got unstable
		};
	};

	namespace AssertAction 
	{
		enum AssertAction
		{
			None,
			Abort,
			Break,
			Ignore,
			IgnoreForever,
			IgnoreForeverPersistent,
			IgnoreAll,
			Throw
		};
	}
}

#endif  // __SPASSERTFWD_H__

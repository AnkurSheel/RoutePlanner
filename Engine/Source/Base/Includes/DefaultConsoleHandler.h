//  *******************************************************************************************************************
//  DefaultConsoleHandler   version:  1.0   Ankur Sheel  date: 2014/10/15
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __DEFAULTCONSOLEHANDLER_H__
#define __DEFAULTCONSOLEHANDLER_H__

#include "SpAssertHandler.h"

namespace Base
{
	class cDefaultConsoleHandler : public cSpAssertHandler
	{
		AssertAction::AssertAction VDisplayMessageAndGetAction(const ISpAssertContext * const pContext);
	};
}
#endif  // __DEFAULTCONSOLEHANDLER_H__

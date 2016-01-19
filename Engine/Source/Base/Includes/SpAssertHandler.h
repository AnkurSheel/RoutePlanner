#ifndef __SPASSERTHANDLER_H__
#define __SPASSERTHANDLER_H__

#include "SpAssertFwd.h"

namespace Base
{
	class ISpAssertContext;
	class ISpAssertSettings;
}

namespace Base
{
	class cSpAssertHandler
	{
	public:
		BASE_API cSpAssertHandler();
		BASE_API virtual ~cSpAssertHandler();
		virtual void VHandleAssert(const ISpAssertContext * const pContext);

	protected:
		virtual AssertAction::AssertAction VDisplayMessageAndGetAction(const ISpAssertContext * const pContext) { return AssertAction::None; }

	};
}

#endif  // __SPASSERTHANDLER_H__


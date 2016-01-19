#include "stdafx.h"
#include <SpAssertHandler.h>
#include "SpAssertFwd.h"
#include "SpAssertSettings.hxx"

using namespace Base;

//  ********************************************************************************************************************
cSpAssertHandler::cSpAssertHandler()
{

}

//  ********************************************************************************************************************
cSpAssertHandler::~cSpAssertHandler()
{

}

//  ********************************************************************************************************************
void cSpAssertHandler::VHandleAssert(const ISpAssertContext * const pContext)
{
	AssertAction::AssertAction action = VDisplayMessageAndGetAction(pContext);
	const shared_ptr<ISpAssertSettings> pSettings = MakeStrongPtr<ISpAssertSettings>(cServiceLocator::GetInstance()->GetService<ISpAssertSettings>());

	switch(action)
	{
	case AssertAction::Abort:
		abort();
		break;

	case AssertAction::Break:
		BREAK_HERE;
		break;

	case AssertAction::IgnoreForever:
		//persistence().ignore_assert( context, ignore_forever_persistent);
		break;

	case AssertAction::IgnoreAll:
		if (pSettings!= NULL)
		{
			pSettings->VSetIgnoreAll(true);
		}
		break;

	case AssertAction::IgnoreForeverPersistent:
		break;

	case AssertAction::Throw:
		break;

	case AssertAction::None:
	case AssertAction::Ignore:
	default:
		// no need to do anything here
		break;

	}
}

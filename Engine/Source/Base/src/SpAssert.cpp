#include "stdafx.h"
#include "SpAssert.h"
#include "SpAssertHandler.h"
#include "SpAssertSettings.hxx"
#include "SpAssertContext.h"
#include "SpAssertLogger.hxx"
#include "SpAssertException.h"

using namespace Base;
using namespace std;

#undef SMART_ASSERT_A
#undef SMART_ASSERT_B
#undef SMART_ASSERT_OP

//  ********************************************************************************************************************
cSpAssert::cSpAssert(int level, const cString & expr, const bool onlyLog)
: SMART_ASSERT_A( *this)
, SMART_ASSERT_B( *this)
, m_pContext(NULL)
, m_bOnlyLog(onlyLog)
{
	const shared_ptr<ISpAssertSettings> pSettings = MakeStrongPtr<ISpAssertSettings>(cServiceLocator::GetInstance()->GetService<ISpAssertSettings>());
	if (pSettings == NULL || !pSettings->VGetIgnoreAll())
	{
		m_pContext = ISpAssertContext::Create();
		m_pContext->VSetExpression(expr);
		m_pContext->VSetDebugLevel(level);
	}
}

//  ********************************************************************************************************************
cSpAssert::cSpAssert(const cSpAssert & other)
: SMART_ASSERT_A( *this)
, SMART_ASSERT_B( *this)
, m_pContext(other.m_pContext)
, m_bOnlyLog(other.m_bOnlyLog)
{

}

//  ********************************************************************************************************************
cSpAssert::~cSpAssert()
{
	Handle();
	SafeDelete(&m_pContext);
}

//  ********************************************************************************************************************
void cSpAssert::Handle() const
{
	bool handled = false;
	const shared_ptr<ISpAssertSettings> pSettings = MakeStrongPtr<ISpAssertSettings>(cServiceLocator::GetInstance()->GetService<ISpAssertSettings>());
	if (pSettings != NULL)
	{
		ISpAssertLoggerStrongPtr pLogger = pSettings->VGetLogger();
		if(pLogger != NULL)
		{
			pLogger->VLog(m_pContext);
		}

		if (m_bOnlyLog || pSettings->VGetIgnoreAll() || pSettings->VIsIgnored(m_pContext))
		{
			handled = true;
		}
		else
		{
			cSpAssertHandlerStrongPtr pHandler = pSettings->VGetHandler(m_pContext->VGetDebugLevel());
			if(pHandler != NULL)
			{
				pHandler->VHandleAssert(m_pContext);
				handled = true;
			}
		}
	}
	if (!handled)
	{
		DefaultHandle();
	}
}

//  ********************************************************************************************************************
cSpAssert cSpAssert::Make(int level, const cString & expr, const bool onlyLog)
{
	return cSpAssert(level, expr, onlyLog);
}

//  ********************************************************************************************************************
cSpAssert & cSpAssert::AddContext(const cString & key, const cString & value)
{
	if (m_pContext != NULL)
	{
		m_pContext->VAddContextValue(key, value);
	}
	return *this;
}

//  ********************************************************************************************************************
cSpAssert & cSpAssert::SetCustomMessage(const cString & message)
{
	if(m_pContext != NULL)
	{
		m_pContext->VSetCustomMessage(message);
	}
	return *this;
}

//  ********************************************************************************************************************
void cSpAssert::DefaultHandle() const
{
	if (m_pContext->VGetDebugLevel() >= AssertLevels::LEVEL_FATAL)
	{
		PostQuitMessage(0);
	}
	else if (m_pContext->VGetDebugLevel() >= AssertLevels::LEVEL_ERROR)
	{
		throw cSpAssertException(m_pContext);
	}
	//else if (m_pContext->VGetDebugLevel() >= AssertLevels::LEVEL_DEBUG)
	//{
	//	BREAK_HERE;
	//}
	//else do nothing for lesser levels
}

//void cAssert::AskUserOnAssertWin() 
//{
//  ostringstream_type out;
//  dump_assert_context_summary( context, out);
//  ostringstream_type out_detail;
//  dump_assert_context_detail( context, out_detail);
//
//  string_type title = Private::get_typeof_level( context.get_level() );
//  Private::show_dlg_result nRet =
//    Private::show_assert_dialog( context.get_level(),
//    title.c_str(), out.str().c_str(), out_detail.str().c_str() );
//  switch ( nRet) {
//  default:
//  case Private::show_failed:
//    // FIXME (nice to have) - if cannot create dialog, show a msg box.
//    break;
//
//  case Private::ignore_now:
//    persistence().ignore_assert( context, ignore_now);
//    break;
//
//  case Private::ignore_forever:
//    persistence().ignore_assert( context, ignore_forever_persistent);
//    break;
//
//  case Private::ignore_all:
//    persistence().ignore_assert( context, ignore_all_persistent);
//    break;
//
//  case Private::do_debug:
//    break_into_debugger();
//    break;
//
//  case Private::do_abort:
//    abort();
//    break;
//
//  case Private::already_shown:
//    // another assertion dialog is shown at this time;
//    // we're not showing two dialogs at the same time.
//    // ...ignore.
//    break;
//  };
//}

#include "stdafx.h"
#include "SpAssertSettings.h"
#include "DefaultConsoleHandler.h"
#include "SpAssertLogger.h"

using namespace Base;
using namespace std;

//  ********************************************************************************************************************
cSpAssertSettings::cSpAssertSettings()
: m_bIgnoreAll(false)
, m_pLogger(NULL)
{
	SetDefaultLogger();
}

//  ********************************************************************************************************************
cSpAssertSettings::~cSpAssertSettings()
{
	m_handlers.clear();
}

//  ********************************************************************************************************************
cSpAssertHandlerStrongPtr cSpAssertSettings::VGetHandler(int level) const
{
	auto findIt = m_handlers.find(level);
	if (findIt != m_handlers.end())
	{
		return findIt->second;
	}
	return NULL;
}

//  ********************************************************************************************************************
void cSpAssertSettings::VSetHandler(int level, cSpAssertHandlerStrongPtr handler)
{
	auto findIt = m_handlers.find(level);
	if (findIt != m_handlers.end())
	{
		m_handlers[level].reset();
	}

	m_handlers[level] = handler;
}

//  ********************************************************************************************************************
void cSpAssertSettings::VAddToIgnoreList(const ISpAssertContext * const pContext)
{
	m_IgnoredAsserts.insert(*(static_cast<const cSpAssertContext * const>(pContext)));
}

//  ********************************************************************************************************************
bool cSpAssertSettings::VIsIgnored(const ISpAssertContext * const pContext) const
{
	return m_IgnoredAsserts.find(*(static_cast<const cSpAssertContext *>(pContext))) != m_IgnoredAsserts.end();
}

//  ********************************************************************************************************************
void cSpAssertSettings::SetDefaultLogger()
{
	m_pLogger = shared_ptr<ISpAssertLogger>(new cSpAssertLogger());
	m_pLogger->VInitialize();
}

//  ********************************************************************************************************************
void ISpAssertSettings::CreateAsService()
{
	cServiceLocator::GetInstance()->Register<ISpAssertSettings>(shared_ptr<ISpAssertSettings>(DEBUG_NEW cSpAssertSettings()));
}

//  *******************************************************************************************************************
#include "stdafx.h"
#include "Process.h"

using namespace Utilities;

//  *******************************************************************************************************************
cProcess::cProcess()
: m_bKill(false)
, m_bActive(true)
, m_uProcessFlags(0)
, m_bPaused(false)
, m_bInitialUpdate(true)
{
}

//  *******************************************************************************************************************
cProcess::~cProcess()
{
}
		
//  *******************************************************************************************************************
void cProcess::SetAttached(const bool bAttached)
{
	if(bAttached)
	{
		m_uProcessFlags |= PROCESS_FLAG_ATTACHED;
	}
	else
	{
		m_uProcessFlags &= ~PROCESS_FLAG_ATTACHED;
	}
}

//  *******************************************************************************************************************
void cProcess::VInitialize()
{
	m_bInitialUpdate = false;
}

//  *******************************************************************************************************************
void cProcess::VUpdate(const float DeltaTime)
{
	if(m_bInitialUpdate) 
	{ 
		VInitialize(); 
		m_bInitialUpdate = false; 
	}
}

//  *******************************************************************************************************************
void cProcess::VKill()
{
	m_bKill = true;
}

//  *******************************************************************************************************************
bool cProcess::IsDead() const
{
	return m_bKill;
}

//  *******************************************************************************************************************
bool cProcess::IsActive() const
{
	return m_bActive;
}

//  *******************************************************************************************************************
void cProcess::VSetActive(const bool bActive)
{
	m_bActive = bActive;
}

//  *******************************************************************************************************************
bool cProcess::VIsPaused() const
{
	return m_bPaused;
}

//  *******************************************************************************************************************
bool cProcess::IsInitialized() const
{
	return !m_bInitialUpdate;
}

//  *******************************************************************************************************************
shared_ptr<cProcess> const cProcess::GetNext() const
{
	return m_pNext;
}

//  *******************************************************************************************************************
void cProcess::SetNext(shared_ptr<cProcess> pNext)
{
	m_pNext = pNext;
}

//  *******************************************************************************************************************
void cProcess::VSetPaused(const bool Paused)
{
	m_bPaused = Paused;
}

//  *******************************************************************************************************************
bool cProcess::IsAttached() const
{
	if(m_uProcessFlags & PROCESS_FLAG_ATTACHED) 
		return true;

	return false;
}

#include "stdafx.h"
#include "Timer.h"

using namespace Utilities;

//  *******************************************************************************************************************
cTimer::cTimer()
: m_iCurrentTime(0)
, m_iLastUpdateTime(0)
, m_iLastFPSUpdateTime(0)
, m_iNumFrames(0)
, m_iTotalsFrames(0)
, m_fFPS(0.0f)
, m_fRunningTime(0.0f)
, m_fDeltaTime(0.0f)
, m_bTimerStopped(true)
{
	// Check how many times per second the system counter fires
	if(!QueryPerformanceFrequency( (LARGE_INTEGER *)&m_iTicksPerSecond ))
	{
		SP_ASSERT_FATAL(false).SetCustomMessage("No support for the high performance counter");
	}

	// update every half second
	m_iFPSUpdateInterval = m_iTicksPerSecond >> 1;
}

//  *******************************************************************************************************************
cTimer::~cTimer()
{
}

//  *******************************************************************************************************************
cTimer * cTimer::Create()
{
	return DEBUG_NEW cTimer();
}

//  *******************************************************************************************************************
void cTimer::VStartTimer()
{
	if (m_bTimerStopped )
	{
		// Get the current value of the high-resolution performance counter.
		QueryPerformanceCounter( (LARGE_INTEGER *)&m_iLastUpdateTime );
		m_bTimerStopped = false;
	}
}

//  *******************************************************************************************************************
void cTimer::VStopTimer()
{
	if (!m_bTimerStopped )
	{
		INT64 iStopTime = 0;

		// Get the current value of the high-resolution performance counter.
		QueryPerformanceCounter( (LARGE_INTEGER *)&iStopTime );

		m_fRunningTime += (float)(iStopTime - m_iLastUpdateTime) / (float)m_iTicksPerSecond;
		m_bTimerStopped = true;
	}
}

//  *******************************************************************************************************************
void cTimer::VOnUpdate()
{
	if (!m_bTimerStopped )
	{
		// Get the current value of the high-resolution performance counter.
		QueryPerformanceCounter( (LARGE_INTEGER *)&m_iCurrentTime );

		m_fDeltaTime = (float)(m_iCurrentTime - m_iLastUpdateTime) / (float)m_iTicksPerSecond;
		m_fRunningTime += m_fDeltaTime;

		m_iNumFrames++;
		m_iTotalsFrames++;

		if ( m_iCurrentTime - m_iLastFPSUpdateTime >= m_iFPSUpdateInterval )
		{
			// Calculate FPS
			float fCurrentTime = (float)m_iCurrentTime / (float)m_iTicksPerSecond;
			float fLastTime = (float)m_iLastFPSUpdateTime / (float)m_iTicksPerSecond;
			m_fFPS = (float)m_iNumFrames / (fCurrentTime - fLastTime);

			m_iLastFPSUpdateTime = m_iCurrentTime;
			m_iNumFrames = 0;
		}
		m_iLastUpdateTime = m_iCurrentTime;
	}
}

//  *******************************************************************************************************************
void cTimer::VReset()
{
	m_iCurrentTime = 0;
	m_iLastUpdateTime = 0;
	m_iLastFPSUpdateTime = 0;
	m_iNumFrames = 0;
	m_iTotalsFrames = 0;
	m_fFPS = 0.0f;
	m_fRunningTime = 0.0f;
	m_fDeltaTime = 0.0f;
	m_bTimerStopped = true;
}

//  *******************************************************************************************************************
ITimer * ITimer::CreateTimer()
{
	return cTimer::Create();
}

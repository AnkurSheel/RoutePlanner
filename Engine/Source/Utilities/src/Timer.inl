// ***************************************************************
// returns if the timer has stopped
// ***************************************************************
inline bool cTimer::VIsStopped() const
{
	return m_bTimerStopped;
}

// ***************************************************************
// returns the FPS
// ***************************************************************
inline float cTimer::VGetFPS() const
{
	return m_fFPS;
}

// ***************************************************************
// returns the running time
// ***************************************************************
inline float cTimer::VGetRunningTime() const
{
	return m_fRunningTime;
}

// ***************************************************************
inline TICK cTimer::VGetRunningTicks() const
{
	return m_iTotalsFrames;
}

// ***************************************************************
// returns the elapsed time
// ***************************************************************
inline float cTimer::VGetDeltaTime() const
{
	if (m_bTimerStopped)
	{
		return 0.0f ;
	}
	return m_fDeltaTime;
}

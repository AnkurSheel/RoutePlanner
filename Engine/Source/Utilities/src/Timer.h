// ***************************************************************
//  Timer   version:  1.0   Ankur Sheel  date: 05/01/2008
//  -------------------------------------------------------------
//
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************
#ifndef Timer_h__
#define Timer_h__

#include "Timer.hxx"

namespace Utilities
{
	/********************************************//**
	 * @brief Class Declaration for creating a timer
	 ***********************************************/
		 class cTimer
		: public ITimer
		, public Base::cNonCopyable
	{
	public:
		/********************************************//**
		 * @return A Pointer to the the cTimer object
		 *
		 * Create and Returns an object of this class
		 ***********************************************/
		static cTimer * Create();

	private:
		cTimer();
		~cTimer();
		
		void VStartTimer();
		void VStopTimer();
		void VOnUpdate();
		bool VIsStopped() const;
		float VGetFPS() const;
		float VGetRunningTime() const;
		float VGetDeltaTime() const;
		TICK VGetRunningTicks() const;
		void VReset();

	private:
		INT64		m_iTicksPerSecond;      /*!< The number of times the system counter fires in 1 second*/
		INT64		m_iCurrentTime;         /*!< The time at this instant */
		INT64		m_iLastUpdateTime;      /*!< The time at which the timer was last updated */
		INT64		m_iLastFPSUpdateTime;   /*!< The time at which the FPS was last calculated */
		INT64		m_iFPSUpdateInterval;   /*!< The time interval between calls to update the FPS */
		UINT		m_iNumFrames;           /*!< The numbers of frames that have been rendered since last FPS Calculation*/
		UINT		m_iTotalsFrames;        /*!< The total number of frames been rendered since this timer has been running*/
		float		m_fRunningTime;         /*!< The total time this timer has been running */
		float		m_fDeltaTime;           /*!< The time that has elapsed between 2 frames */
		float		m_fFPS;                 /*!< The FPS */
		bool		m_bTimerStopped;        /*!< True if the timer is stopped*/
	};

#include "Timer.inl"
}
#endif // Timer_h__

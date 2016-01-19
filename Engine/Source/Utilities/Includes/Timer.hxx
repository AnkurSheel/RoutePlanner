// ***************************************************************
//  Timer   version:  1.0   Ankur Sheel  date: 2011/02/15
//  -------------------------------------------------------------
//
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************
#ifndef Timer_hxx__
#define Timer_hxx__

#include "UtilitiesDefines.h"

namespace Utilities
{
    /********************************************//**
 * @brief Interface for the Timer Class
 *
 ***********************************************/
	class ITimer
	{
	public:
		virtual ~ITimer(){}
		/********************************************//**
		 *
		 * Starts the timer
		 ***********************************************/
		UTILITIES_API virtual void VStartTimer() = 0;
		/********************************************//**
		 *
		 * Stops the timer
		 ***********************************************/
		UTILITIES_API virtual void VStopTimer() = 0;
		/********************************************//**
		 *
		 * Updates the timer. Calculates the time elapsed since the last
		 * update call. Updates the FPS and total running time
		 ***********************************************/
		UTILITIES_API virtual void VOnUpdate() = 0;
		/********************************************//**
		 * @return True if the timer has stopped.
		 *
		 * Check whether the timer is stopped or running
		 ***********************************************/
		UTILITIES_API virtual bool VIsStopped() const = 0;
		/********************************************//**
		 * @return The FPS.
		 *
		 * Get the FPS
		 ***********************************************/
		UTILITIES_API virtual float VGetFPS() const = 0;
		/********************************************//**
		 * @return The running time.
		 *
		 * Get the running time
		 ***********************************************/
		UTILITIES_API virtual float VGetRunningTime() const = 0;
		/********************************************//**
		 * @return The no. of frames that have elapsed
		 *
		 * Get the ticks that have elapsed
		 ***********************************************/
		UTILITIES_API virtual TICK VGetRunningTicks() const = 0;
		/********************************************//**
		 * @return The elapsed time.
		 *
		 * Gets the elapsed time between frames
		 ***********************************************/
		UTILITIES_API virtual float VGetDeltaTime() const = 0;
		UTILITIES_API virtual void VReset() = 0;
		/********************************************//**
		 * @return Returns a pointer to the timer
		 *
		 * Creates and returns a pointer to an object of this class
		 ***********************************************/
		UTILITIES_API static ITimer * CreateTimer();
	};
}
#endif // Timer_hxx__

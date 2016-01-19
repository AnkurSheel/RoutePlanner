// *****************************************************************************
//  Audio   version:  1.0   Ankur Sheel  date: 2013/01/03
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Audio_hxx__
#define Audio_hxx__

#include "SoundDefines.h"

namespace Sound
{
	class IAudioBuffer;
	class ISoundResHandle;
}

namespace Sound
{
	class IAudio
	{
	public:
		virtual ~IAudio(){}
		virtual bool VInitialize(const HWND & hwnd) = 0;
		virtual IAudioBuffer * VInitializeAudioBuffer(shared_ptr<ISoundResHandle> pSoundResource) = 0;
		virtual void VReleaseAudioBuffer(IAudioBuffer * pAudioBuffer) = 0;
		/********************************************//**
		 * @return Returns a pointer to the singleton object
		 *
		 * Creates and returns a pointer to a singleton object of this interface
		 ***********************************************/
		SOUND_API static IAudio * GetInstance();
		/********************************************//**
		 *
		 * Deletes the singleton object
		 ***********************************************/
		SOUND_API static void Destroy();

	};
}
#endif // Audio_hxx__
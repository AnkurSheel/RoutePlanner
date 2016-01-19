//  *******************************************************************************************************************
//  DirectSoundAudioBuffer   version:  1.0   Ankur Sheel  date: 2014/12/05
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __DIRECTSOUNDAUDIOBUFFER_H__
#define __DIRECTSOUNDAUDIOBUFFER_H__

#include <dsound.h>
#include "AudioBuffer.h"

namespace Sound
{	
	class ISoundResHandle;
}

namespace Sound
{
	class cDirectSoundAudioBuffer
		: public cAudioBuffer
	{
	public:
		cDirectSoundAudioBuffer(LPDIRECTSOUNDBUFFER pSound, shared_ptr<ISoundResHandle> pResource);

	private:
		bool VPlay();
		bool VStop();
		bool VResume();
		bool VSetPaused(const bool Paused);
		bool VPause();
		bool VIsPlaying();
		bool VRestore();
		void VSetVolume(unsigned int uiVolume);
		float VGetProgress();
		LPDIRECTSOUNDBUFFER GetSoundBuffer();
		bool RestoreBuffer();
		bool FillBufferWithSound();

	private:
		LPDIRECTSOUNDBUFFER		m_pSample;
	};
}
#endif  // __DIRECTSOUNDAUDIOBUFFER_H__

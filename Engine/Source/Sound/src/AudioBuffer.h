// *****************************************************************************
//  AudioBuffer   version:  1.0   Ankur Sheel  date: 2013/01/03
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef AudioBuffer_h__
#define AudioBuffer_h__

#include "AudioBuffer.hxx"

namespace Sound
{
	class ISoundResHandle;
}

namespace Sound
{
	class cAudioBuffer
		: public IAudioBuffer
	{
	public:
		~cAudioBuffer();

	protected:
		cAudioBuffer(shared_ptr<ISoundResHandle> pResource);

	protected:
		shared_ptr<ISoundResHandle>		m_pResource;
		bool							m_bIsPaused;
		unsigned int					m_uiVolume;
	};
}
#endif // AudioBuffer_h__

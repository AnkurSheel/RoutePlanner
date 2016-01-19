// *****************************************************************************
//  SoundResource   version:  1.0   Ankur Sheel  date: 2012/12/29
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************

#include "SoundResource.hxx"

namespace Sound
{
	class cSoundResHandle
		: public ISoundResHandle
	{
	public:
		cSoundResHandle(Utilities::cResource & resource, unsigned char * pBuffer,
			unsigned int uiSize, Utilities::IResCache * pResCache);
		~cSoundResHandle();
		bool VInitialize();
		int VGetPCMBufferSize() const;
		WAVEFORMATEX const * GetFormat() const;
		char const * VGetPCMBuffer() const;

	private:
		bool ParseWave(const char * const pWavStream, const unsigned int uiBufferLength);
		bool ParseOgg(const char * const pOggStream, const unsigned int uiBufferLength);

	private:
		bool					m_bInitialized;		/*!< True if the sound has been initialized. */
		char *					m_pPCMBuffer;		/*!< The destination PCM buffer of the sound. */
		int						m_iPCMBufferSize;	/*!< The length of the PCM buffer. */
		WAVEFORMATEX			m_WaveFormatEx;		/*!< Description of the PCM format. */
		int						m_iLengthMS;		/*!< Length of the sound in milliseconds. */
		const Base::cString		m_strSoundFileName;	/*!< The name of the file resource. */
	};
}
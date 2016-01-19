//  *******************************************************************************************************************
//  SoundProcess   version:  1.0   Ankur Sheel  date: 2013/01/08
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#include "stdafx.h"
#include "SoundProcess.h"
#include "Audio.hxx"
#include "SoundResource.h"
#include "AudioBuffer.hxx"
#include "ResourceManager.hxx"

using namespace Sound;
using namespace Base;
using namespace Utilities;

const cHashedString cSoundProcess::m_Type = cHashedString("soundprocess");

//  *******************************************************************************************************************
cSoundProcess::cSoundProcess(const Base::cString & strType, 
							 shared_ptr<ISoundResHandle> pSoundResource,
							 const int iVolume, const bool bLooping)
: m_pSoundHandle(pSoundResource)
, m_iVolume(iVolume)
, m_bLooping(bLooping)
{

}

//  *******************************************************************************************************************
cSoundProcess::~cSoundProcess()
{
	if (m_pAudioBuffer)
	{
		IAudio::GetInstance()->VReleaseAudioBuffer(m_pAudioBuffer.get());
	}
}
//  *******************************************************************************************************************
void cSoundProcess::VInitialize()
{
	cProcess::VInitialize();
	if (m_pSoundHandle == NULL)
	{
		return;
	}
	m_pSoundHandle->VInitialize();
	IAudioBuffer * pAudioBuffer = IAudio::GetInstance()->VInitializeAudioBuffer(m_pSoundHandle);
	if (pAudioBuffer == NULL)
	{
		VKill();
		return;
	}
	m_pAudioBuffer.reset(pAudioBuffer);
	m_pAudioBuffer->VSetVolume(m_iVolume);
	Play();
}

//  *******************************************************************************************************************
void cSoundProcess::VUpdate(const float DeltaTime)
{
	cProcess::VUpdate(DeltaTime);
	if (!IsPlaying())
	{
		if(m_bLooping)
		{
			Play();
		}
		else
		{
			VKill();
		}
	}
}

//  *******************************************************************************************************************
void cSoundProcess::VKill()
{
	if (IsPlaying())
	{
		Stop();
	}
	cProcess::VKill();
}

//  *******************************************************************************************************************
void cSoundProcess::VSetVolume(const int iVolume)
{
	m_iVolume = iVolume;
	if (m_pAudioBuffer == NULL)
	{
		return;
	}
	m_pAudioBuffer->VSetVolume(m_iVolume);
}

//  *******************************************************************************************************************
void cSoundProcess::Play()
{
	if (m_pAudioBuffer == NULL)
	{
		return;
	}
	m_pAudioBuffer->VPlay();
}

//  *******************************************************************************************************************
void cSoundProcess::Stop()
{
	if (m_pAudioBuffer)
	{
		m_pAudioBuffer->VStop();
	}
}

//  *******************************************************************************************************************
bool cSoundProcess::IsPlaying() 
{
	if (m_pSoundHandle == NULL || m_pAudioBuffer == NULL)
	{
		return false;
	}
	return m_pAudioBuffer->VIsPlaying();
}

//  *******************************************************************************************************************
void cSoundProcess::VSetPaused(const bool Paused)
{
	if (m_pAudioBuffer)
	{
		m_pAudioBuffer->VSetPaused(Paused);
	}
	cProcess::VSetPaused(Paused);
}

//  *******************************************************************************************************************
void cSoundProcess::VSetActive(const bool bActive)
{
	if(m_bActive != bActive)
	{
		cProcess::VSetActive(bActive);
		if (m_pAudioBuffer)
		{
			if(m_bActive)
			{
				m_pAudioBuffer->VResume();
			}
			else
			{
				m_pAudioBuffer->VPause();
			}
		}
	}
}

//  *******************************************************************************************************************
shared_ptr<ISoundProcess> ISoundProcess::CreateSoundProcess(const cString & strType,
															const cString & strSoundFile,
															const int iVolume,
															const bool bLooping)
{
	shared_ptr<cSoundResource> pResource(DEBUG_NEW cSoundResource(strSoundFile));
	shared_ptr<ISoundResHandle> pHandle = static_pointer_cast<ISoundResHandle>(IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource));
	return shared_ptr<ISoundProcess>(DEBUG_NEW cSoundProcess(strType, pHandle, iVolume, bLooping));
}
#include "stdafx.h"
#include "DirectSoundAudio.h"
#include <DxErr.h>
#include "SoundResource.h"
#include "AudioBuffer.hxx"
#include "DirectSoundAudioBuffer.h"

#pragma comment(lib, "Dsound.lib")
#pragma comment(lib, "dxerr.lib")

using namespace Sound;
using namespace Utilities;
using namespace Base;

//  *******************************************************************************************************************
cDirectSoundAudio::cDirectSoundAudio()
: m_pDS(NULL)
{

}

//  *******************************************************************************************************************
cDirectSoundAudio::~cDirectSoundAudio()
{

}

//  *******************************************************************************************************************
bool cDirectSoundAudio::VInitialize(const HWND & hwnd)
{
	if(m_bInitialized)
	{
		return true;
	}

	m_bInitialized = false;
	HRESULT result;

	result = DirectSoundCreate8(NULL, &m_pDS, NULL);
	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(result)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create direct sound");
		return false;
	}

	result = m_pDS->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(result)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not set direct sound cooperative level");
		return false;
	}
	
	result = SetPrimaryBufferFormat(8, 44100, 16);
	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(result)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not set primary buffer format");
		return false;
	}

	m_bInitialized = true;
	m_ActiveSoundList.clear();

	return true;
}

//  *******************************************************************************************************************
bool cDirectSoundAudio::SetPrimaryBufferFormat(const unsigned short usPrimaryChannels, const unsigned long ulPrimaryFreq,
	const unsigned short usPrimaryBitRate)
{
	if(m_pDS == NULL)
	{
		return false;
	}

	DSBUFFERDESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DSBUFFERDESC));
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.lpwfxFormat = NULL;

	HRESULT result;
	LPDIRECTSOUNDBUFFER pDSBuffer;
	result = m_pDS->CreateSoundBuffer(&bufferDesc, &pDSBuffer, NULL);
	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(result)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create sound buffer");
		return false;
	}

	WAVEFORMATEX wfx;
	ZeroMemory(&wfx, sizeof(WAVEFORMATEX));
	wfx.wFormatTag = static_cast<unsigned short>(WAVE_FORMAT_PCM);
	wfx.nChannels = usPrimaryChannels;
	wfx.nSamplesPerSec = ulPrimaryFreq;
	wfx.wBitsPerSample = usPrimaryBitRate;
	wfx.nBlockAlign = usPrimaryBitRate / 8 * wfx.nChannels;
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

	result = pDSBuffer->SetFormat(&wfx);
	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(result)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not set format for sound buffer");
		return false;
	}

	SafeRelease(&pDSBuffer);
	return true;
}

//  *******************************************************************************************************************
void cDirectSoundAudio::VCleanup()
{
	cAudio::VCleanup();
	SafeRelease(&m_pDS);
	m_bInitialized = false;
}

//  *******************************************************************************************************************
IAudioBuffer * cDirectSoundAudio::VInitializeAudioBuffer(shared_ptr<ISoundResHandle> pSoundResource)
{
	if(m_pDS == NULL)
	{
		return NULL;
	}

	DSBUFFERDESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DSBUFFERDESC));
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = pSoundResource->VGetPCMBufferSize();
	bufferDesc.guid3DAlgorithm = GUID_NULL;
	shared_ptr<cSoundResHandle> pHandle = dynamic_pointer_cast<cSoundResHandle>(pSoundResource);
	bufferDesc.lpwfxFormat = const_cast<WAVEFORMATEX *>(pHandle->GetFormat());

	HRESULT result;
	LPDIRECTSOUNDBUFFER pDSBuffer;
	
	result = m_pDS->CreateSoundBuffer(&bufferDesc, &pDSBuffer, NULL);
	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(result)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create sound buffer");
		return NULL;
	}

	IAudioBuffer * pAudioBuffer = static_cast<IAudioBuffer *>(DEBUG_NEW cDirectSoundAudioBuffer(pDSBuffer, pSoundResource));
	m_ActiveSoundList.push_front(pAudioBuffer);
	return pAudioBuffer;
}

//  *******************************************************************************************************************
void cDirectSoundAudio::VReleaseAudioBuffer(IAudioBuffer * pAudioBuffer)
{
	pAudioBuffer->VStop();
	m_ActiveSoundList.remove(pAudioBuffer);
}

//  *******************************************************************************************************************
IAudio * cAudio::Create()
{
	return DEBUG_NEW cDirectSoundAudio();
}

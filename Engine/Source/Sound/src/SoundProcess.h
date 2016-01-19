//  *******************************************************************************************************************
//  SoundProcess   version:  1.0   Ankur Sheel  date: 2013/01/08
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef SoundProcess_h__
#define SoundProcess_h__

#include "SoundProcess.hxx"

namespace Sound
{
	class cSoundResHandle;
	class IAudioBuffer;
}
namespace Sound
{
	class cSoundProcess
		: public ISoundProcess
	{
	public:
		cSoundProcess(const Base::cString & strType, shared_ptr<ISoundResHandle> pSoundResource, const int iVolume,
			const bool bLooping);
		~cSoundProcess();
		void VInitialize();
		void VUpdate(const float DeltaTime);
		void VKill();
		void VSetPaused(const bool Paused);
		void VSetActive(const bool bActive);
		void VSetVolume(const int iVolume);
		void Play();
		void Stop();
		bool IsPlaying();
		const Base::cHashedString & VGetType() const { return m_Type; }

	private:
		static const Base::cHashedString	m_Type;

	private:
		shared_ptr<ISoundResHandle>		m_pSoundHandle;
		shared_ptr<IAudioBuffer>		m_pAudioBuffer;
		int								m_iVolume;
		bool							m_bLooping;
	};
}
#endif // SoundProcess_h__
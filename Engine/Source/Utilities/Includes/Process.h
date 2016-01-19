//  *******************************************************************************************************************
//  Process   version:  1.0   Ankur Sheel  date: 2013/01/08
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#ifndef Process_h__
#define Process_h__

#include "UtilitiesDefines.h"

namespace Utilities
{
	static const int PROCESS_FLAG_ATTACHED		= 0x00000001;

	class cProcess
		: public Base::cNonCopyable
	{
	public:
		UTILITIES_API cProcess();
		UTILITIES_API virtual ~cProcess();

		UTILITIES_API virtual void VInitialize();
		UTILITIES_API virtual void VUpdate(const float deltaTime);
		UTILITIES_API virtual void VKill();
		UTILITIES_API virtual void VSetPaused(const bool Paused);
		UTILITIES_API virtual void VSetActive(const bool bActive);
		virtual const Base::cHashedString & VGetType() const = 0;

		bool IsDead() const;
		bool IsActive() const;
		bool VIsPaused() const;
		bool IsAttached() const;
		void SetAttached(const bool bAttached);
		bool IsInitialized() const;
		shared_ptr<cProcess> const GetNext() const;
		void SetNext(shared_ptr<cProcess> pNext);

	protected:
		bool					m_bKill;
		bool					m_bActive;
		bool					m_bPaused;
		bool					m_bInitialUpdate;
		shared_ptr<cProcess>	m_pNext;
	
	private:
		unsigned int				m_uProcessFlags;

	private:
		friend class cProcessManager;
	};
}
#endif // Process_h__
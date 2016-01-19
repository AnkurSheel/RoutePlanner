//  *******************************************************************************************************************
//  State   version:  1.0   Ankur Sheel  date: 05/23/2008
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#ifndef State_h__
#define State_h__

#include "AIDefines.h"

namespace AI
{
	struct Telegram;
	class cStateImpl;
}

namespace AI
{
	template <class entity_type>
	class cState 
		: public Base::cNonCopyable
	{
	public:
		cState();
		virtual ~cState(){};
		virtual void VOnEnter(entity_type *);
		virtual void VOnUpdate(const TICK currentTick, const float deltaTime) = 0;
		virtual void VOnExit() = 0;
		virtual bool VOnMessage(const AI::Telegram & msg) = 0;
		virtual void VOnPause();
		virtual void VOnResume();
		Base::cString GetName() const;
		bool IsPaused() const;
	
	protected:
		bool	m_IsPaused;
		entity_type *	m_pOwner;
	};

#include "State.inl"

}
#endif // State_h__

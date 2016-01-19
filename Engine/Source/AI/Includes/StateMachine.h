//  *******************************************************************************************************************
//  StateMachine   version:  1.0   Ankur Sheel  date: 05/23/2008
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#ifndef StateMachine_h__
#define StateMachine_h__

namespace AI
{
	struct Telegram;
}

#include "State.h"

namespace AI
{
	template <class entity_type>
	class cStateMachine
		: public Base::cNonCopyable
	{
	public:
		cStateMachine(entity_type * pOwner);
		virtual ~cStateMachine();
		void SetCurrentState(cState<entity_type> * pState);
		void Update(const TICK currentTick, const float deltaTime);
		cState<entity_type>* GetCurrentState();
		bool IsInState(const cState<entity_type> & state);
		bool HandleMessage(const Telegram & msg);
		void RequestChangeState(cState<entity_type> * pNewState);
		void RequestPushState(cState<entity_type> * pNewState);
		void RequestPopState();

	private:
		void ChangeState();
		void PushState();
		void PopState();

	protected:
		entity_type *	m_pOwner;
		cState<entity_type> *	m_pCurrentState;
		cState<entity_type> *	m_pNextState;
		std::deque<cState<entity_type> *>	m_PushedStates;
	
	private:
		bool	m_RequestedStateChange;
		bool	m_RequestedPushState;
		bool	m_RequestedPopState;
	};

#include "Statemachine.inl"
}
#endif // StateMachine_h__
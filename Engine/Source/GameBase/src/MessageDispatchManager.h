//  *******************************************************************************************************************
//  MessageDispatchManager   version:  1.0   Ankur Sheel  date: 2012/07/27
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef MESSAGEDISPATCHMANAGER_H__
#define MESSAGEDISPATCHMANAGER_H__

#include "MessageDispatchManager.hxx"

namespace AI
{
	struct Telegram;
}

namespace Utilities
{
	class  ITimer;
}

namespace GameBase
{
	class IBaseEntity;
	class IEntityManager;
}

namespace GameBase
{
	class cMessageDispatchManager
		: public IMessageDispatchManager
		, public Base::cNonCopyable
	{
	public:
		~cMessageDispatchManager();
		void VDispatchMessage(const double delay, const int senderID, const int recieverID, const unsigned msgId, shared_ptr<void> pExtraInfo) OVERRIDE;
		void VOnUpdate() OVERRIDE;

	private:
		cMessageDispatchManager();
		void Discharge(GameBase::IBaseEntity * const pReceiver, const AI::Telegram& msg);
		void DispatchDelayedMessage();

	private: 
		Utilities::ITimer* m_pTimer;
		weak_ptr<IEntityManager> m_pEntityManager;
		std::set<AI::Telegram> m_PriorityQueue;

	private:
		friend void IMessageDispatchManager::CreateAsService();
	};
}
#endif // MESSAGEDISPATCHMANAGER_H__

#include "stdafx.h"
#include "MessageDispatchManager.h"
#include "Timer.hxx"
#include "EntityManager.hxx"
#include "Telegram.h"
#include "BaseEntity.h"

using namespace Utilities;
using namespace AI;
using namespace Base;
using namespace GameBase;

//  *******************************************************************************************************************
cMessageDispatchManager::cMessageDispatchManager()
{
	m_pTimer = ITimer::CreateTimer();
	m_pTimer->VStartTimer();
	m_pEntityManager = cServiceLocator::GetInstance()->GetService<IEntityManager>();
}

//  *******************************************************************************************************************
cMessageDispatchManager::~cMessageDispatchManager()
{
	SafeDelete(&m_pTimer);
	m_pEntityManager.reset();
}

//  *******************************************************************************************************************
void cMessageDispatchManager::VDispatchMessage(const double delay, const int senderID, const int recieverID,
	const unsigned msgId, shared_ptr<void> pExtraInfo)
{
	shared_ptr<IEntityManager> pEntityManager = MakeStrongPtr<IEntityManager>(m_pEntityManager);
	if (pEntityManager != NULL)
	{
		return;
	}

	IBaseEntity	* pReciever = pEntityManager->VGetEntityFromID(recieverID);
	Telegram telegram(senderID, recieverID, msgId, 0.0, pExtraInfo);
	if (delay <= 0.0)
	{
		SP_LOG(2, "Sending msg immediately")(msgId)(pEntityManager->VGetEntityNameFromID(senderID))(pEntityManager->VGetEntityNameFromID(recieverID));
		Discharge(pReciever, telegram);
	}
	else
	{
		SP_LOG(2, "Sending msg immediately")(msgId)(delay)(pEntityManager->VGetEntityNameFromID(senderID))(pEntityManager->VGetEntityNameFromID(recieverID));
		double dCurrentTime = m_pTimer->VGetRunningTime();
		telegram.m_DispatchTime = dCurrentTime + delay;
		m_PriorityQueue.insert(telegram);
	}
}

//  *******************************************************************************************************************
void cMessageDispatchManager::VOnUpdate()
{
	m_pTimer->VOnUpdate();
	DispatchDelayedMessage();
}

//  *******************************************************************************************************************
void cMessageDispatchManager::DispatchDelayedMessage()
{
	shared_ptr<IEntityManager> pEntityManager = MakeStrongPtr<IEntityManager>(m_pEntityManager);
	if (pEntityManager == NULL)
	{
		return;
	}
	double currentTime = m_pTimer->VGetRunningTime();
	while (!m_PriorityQueue.empty() 
	&& m_PriorityQueue.begin()->m_DispatchTime < currentTime
	&& m_PriorityQueue.begin()->m_DispatchTime > 0)
	{
		Telegram telegram = *m_PriorityQueue.begin();
		IBaseEntity * pReciever = pEntityManager->VGetEntityFromID(telegram.m_ReceiverID);
		Discharge(pReciever, telegram);
		m_PriorityQueue.erase(m_PriorityQueue.begin());
	}
}

//  *******************************************************************************************************************
void cMessageDispatchManager::Discharge(IBaseEntity * const pReceiver, const AI::Telegram& msg)
{
	if(pReceiver->VOnHandleMessage(msg))
	{
		if (!m_pEntityManager.expired())
		{
			SP_LOG(2, "Message Handled")(msg.m_MsgID)(MakeStrongPtr(m_pEntityManager)->VGetEntityName(pReceiver));
		}
	}
	else
	{
		if (!m_pEntityManager.expired())
		{
			SP_LOG(2, "Message Not Handled")(msg.m_MsgID)(MakeStrongPtr(m_pEntityManager)->VGetEntityName(pReceiver));
		}
	}
}

//  *******************************************************************************************************************
void IMessageDispatchManager::CreateAsService()
{
	cServiceLocator::GetInstance()->Register<IMessageDispatchManager>(shared_ptr<IMessageDispatchManager>(DEBUG_NEW cMessageDispatchManager()));
}

#include "stdafx.h"
#include "EventManager.h"
#include "EventFactory.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

//  *******************************************************************************************************************
cEventManager::cEventManager()
	: m_activeQueue(0)
{
}

//  *******************************************************************************************************************
cEventManager::~cEventManager()
{
}

//  *******************************************************************************************************************
void cEventManager::VInitializeEventFactory(shared_ptr<cEventFactory> pEventFactory)
{
	if(m_pEventFactory == NULL && pEventFactory != NULL)
	{
		m_pEventFactory = pEventFactory;
		m_pEventFactory->VRegisterEvents();
	}
}

//  *******************************************************************************************************************
void cEventManager::VAddListener(const EventListenerCallBackFn & fnListener, const EventType & eventType)
{
	SP_LOG_CUSTOM(LogType::EVENT, 2, "Attempting to add listener for event ")(eventType.GetString());

	EventListenerList & eventListeners = m_eventListeners[eventType.GetHash()];

	for (auto it = eventListeners.begin(); it != eventListeners.end(); it++)
	{
		if (fnListener.target_type() == (*it).target_type())
		{
			SP_LOG_CUSTOM(LogType::LEVEL_DEBUG, 2, "Attempting to double-register a listener for event")(eventType.GetString());
			return;
		}
	}

	eventListeners.push_back(fnListener);
	SP_LOG_CUSTOM(LogType::EVENT, 2, "Successfully added delegate")(eventType.GetString());
}

//  *******************************************************************************************************************
void cEventManager::VRemoveListener(const EventListenerCallBackFn & fnListener, const EventType & eventType)
{
	bool success = false;
	SP_LOG_CUSTOM(LogType::EVENT, 2, "Attempting to remove delegate function")(eventType.GetString());

	auto findIt = m_eventListeners.find(eventType.GetHash());
	if (findIt != m_eventListeners.end())
	{
		EventListenerList & listeners = findIt->second;
		for (auto it = listeners.begin(); it != listeners.end(); it++)
		{
			if (fnListener.target_type() == (*it).target_type())
			{
				listeners.erase(it);
				SP_LOG_CUSTOM(LogType::EVENT, 2, "Successfully removed delegate")(eventType.GetString());
				return;
			}
		}
	}
	SP_ASSERT_DEBUG(success)(eventType.GetString()).SetCustomMessage("Could not remove listener");
}

//  *******************************************************************************************************************
void cEventManager::VTriggerEvent(const IEventDataPtr & pEvent)
{
	auto findIt = m_eventListeners.find(pEvent->VGetEventID());
	if (findIt != m_eventListeners.end())
	{
		const EventListenerList& eventListenerList = findIt->second;
		for (auto it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
		{
			EventListenerCallBackFn listener = (*it);
			listener(pEvent);
		}
	}
}

//  *******************************************************************************************************************
void cEventManager::VQueueEvent(const IEventDataPtr & pEvent)
{
	SP_ASSERT_DEBUG(pEvent != NULL)(pEvent->VGetEventName()).SetCustomMessage("Invalid event");

	if (!pEvent)
	{
		return;
	}

	auto findIt = m_eventListeners.find(pEvent->VGetEventID());
	if (findIt != m_eventListeners.end())
	{
		m_queues[m_activeQueue].push_back(pEvent);
	}
	else
	{
		SP_LOG_CUSTOM(LogType::EVENT, 2, "Skipping event since there are no delegates registered to receive it")(pEvent->VGetEventName());
	}
}

//  *******************************************************************************************************************
void cEventManager::VAbortEvent(const EventType & eventType, const bool allEVents)
{
	auto findIt = m_eventListeners.find(eventType.GetHash());

	if (findIt != m_eventListeners.end())
	{
		EventQueue& eventQueue = m_queues[m_activeQueue];
		auto it = eventQueue.begin();
		while (it != eventQueue.end())
		{
			// Removing an item from the queue will invalidate the iterator, so have it point to the next member.  All
			// work inside this loop will be done using thisIt.
			auto thisIt = it;
			++it;

			if ((*thisIt)->VGetEventID() == eventType.GetHash())
			{
				eventQueue.erase(thisIt);
				if (!allEVents)
					break;
			}
		}
	}
}

//  *******************************************************************************************************************
void cEventManager::VUpdate()
{
	// swap active queues and clear the new queue after the swap
	int queueToProcess = m_activeQueue;
	m_activeQueue = (m_activeQueue + 1) % 2;
	m_queues[m_activeQueue].clear();

	// Process the queue
	while (!m_queues[queueToProcess].empty())
	{
		// pop the front of the queue
		IEventDataPtr pEvent = m_queues[queueToProcess].front();
		m_queues[queueToProcess].pop_front();
		SP_LOG_CUSTOM(LogType::EVENT, 3 , "Processing Event")(pEvent->VGetEventName());

		// find all the delegate functions registered for this event
		auto findIt = m_eventListeners.find(pEvent->VGetEventID());
		if (findIt != m_eventListeners.end())
		{
			const EventListenerList& eventListeners = findIt->second;

			// call each listener
			for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it)
			{
				EventListenerCallBackFn listener = (*it);
				listener(pEvent);
			}
		}
	}
}

//  *******************************************************************************************************************
void IEventManager::CreateAsService()
{
	cServiceLocator::GetInstance()->Register<IEventManager>(shared_ptr<IEventManager>(DEBUG_NEW cEventManager()));
}

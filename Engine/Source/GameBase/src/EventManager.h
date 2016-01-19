// *****************************************************************************
//  EventManager version:  1.0   Ankur Sheel  date: 2013/07/25
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef EventManager_h__
#define EventManager_h__

#include "EventManager.hxx"

namespace GameBase
{
	class cEventFactory;
}

namespace GameBase
{
	class cEventManager
		: public IEventManager
		, public Base::cNonCopyable
	{
	private:
		typedef std::list<EventListenerCallBackFn> EventListenerList; 
		typedef std::map<unsigned long, EventListenerList> EventListenerMap;
		typedef std::list<IEventDataPtr> EventQueue;

	public:
		~cEventManager();

	private:
		cEventManager();
		void VInitializeEventFactory(shared_ptr<cEventFactory> pEventFactory) OVERRIDE;
		void VAddListener(const EventListenerCallBackFn & fnListener, const EventType & eventType) OVERRIDE;
		void VRemoveListener(const EventListenerCallBackFn & fnListener, const EventType & eventType) OVERRIDE;
		void VTriggerEvent(const IEventDataPtr& pEvent) OVERRIDE;
		void VQueueEvent(const IEventDataPtr& pEvent) OVERRIDE;
		void VAbortEvent(const EventType& type, const bool allEVents) OVERRIDE;
		void VUpdate() OVERRIDE;

	private:
		int m_activeQueue;  /// index of actively processing queue; events enque to the opposing queue
		EventListenerMap m_eventListeners; /// Stores the list of listeners to be called for each event
		EventQueue m_queues[2]; /// the active and inactive queues
		shared_ptr<cEventFactory> m_pEventFactory;

	private:
		friend void IEventManager::CreateAsService();
	};
}
#endif // EventManager_h__
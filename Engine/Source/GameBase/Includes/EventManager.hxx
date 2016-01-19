// *****************************************************************************
//  EventManager version:  1.0   Ankur Sheel  date: 2013/07/25
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef EventManager_hxx__
#define EventManager_hxx__

#include "GameBaseDefines.h"
#include "EventData.hxx"

namespace GameBase
{
	class cEventFactory;
}

namespace GameBase
{
	typedef shared_ptr<IEventData> IEventDataPtr;
	typedef function<void (IEventDataPtr)> EventListenerCallBackFn;

	class IEventManager
	{
	public:
		virtual ~IEventManager(){}
		virtual void VInitializeEventFactory(shared_ptr<cEventFactory> pEventFactory) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Matches a delegate function with an event type, so that whenever the
		/// the event is triggered, the delegate will be called
		///
		/// @param[in] fnListener The delegate function
		/// @param[in] eventType The type of event
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VAddListener(const EventListenerCallBackFn & fnListener,
			const EventType & eventType) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Removes the delegate function associated with an event type
		///
		/// @param[in] fnListener The delegate function
		/// @param[in] eventType The type of event
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VRemoveListener(const EventListenerCallBackFn & fnListener,
			const EventType & eventType) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Immediately fires an event
		///
		/// @param[in] pEventData The event that has to be fired
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VTriggerEvent(const IEventDataPtr & pEvent) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Puts an event into the queue to be fired later
		///
		/// @param[in] pEvent The event that has to be queued
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VQueueEvent(const IEventDataPtr & pEvent) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Removes an event from the queue 
		///
		/// @param[in] eventType The event that has to be removed
		/// @param[in] allEVents If True, then all events of that type are 
		/// cleared from the input queue
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VAbortEvent(const EventType & eventType, const bool allEVents) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Processes the events in the queue
		///
		/// 
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VUpdate() = 0;
		////////////////////////////////////////////////////////////////////////
		/// Registers the EventManager as a service
		///
		///
		////////////////////////////////////////////////////////////////////////
		GAMEBASE_API static void CreateAsService();
	};
}
#endif // EventManager_hxx__
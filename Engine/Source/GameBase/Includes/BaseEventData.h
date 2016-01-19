// *****************************************************************************
//  BaseEventData version:  1.0   Ankur Sheel  date: 2013/07/25
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef BaseEventData_h__
#define BaseEventData_h__

#include "EventData.hxx"
#include "nonCopyable.h"

namespace GameBase
{
	class cBaseEventData
		: public IEventData
	{
	public:
		cBaseEventData(){};
		virtual ~cBaseEventData(){};
		unsigned long VGetEventID() const { return VGetHashedID(); }
		virtual Base::cString VGetEventName() const { return VGetName(); }
		virtual unsigned long VGetHashedID() const = 0;
		virtual Base::cString VGetName() const = 0;
	};
}
#endif //BaseEventData_h__
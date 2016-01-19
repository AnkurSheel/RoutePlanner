// *****************************************************************************
//  EventFactory   version:  1.0   Ankur Sheel  date: 2013/05/15
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "StdAfx.h"
#include "EventFactory.h"
#include "EventData.hxx"
#include "EntityMovedEventData.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

cEventFactory * cEventFactory::m_pInstance = NULL;

// *****************************************************************************
cEventFactory::cEventFactory()
{
	if(m_pInstance == NULL)
		m_pInstance = this;
}

// *****************************************************************************
cEventFactory::~cEventFactory()
{
}

// *****************************************************************************
void cEventFactory::VRegisterEvents()
{
	m_RegisteredEvents.Register<cEntityMovedEventData>(cEntityMovedEventData::m_Name.GetHash());
}

// *****************************************************************************
IEventData * cEventFactory::CreateEvent(const EventType & Type)
{
	IEventData * pEvent = m_RegisteredEvents.Create(Type.GetHash());
	return pEvent;
}

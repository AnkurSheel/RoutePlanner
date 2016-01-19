#include "stdafx.h"
#include "EntityMovedEventData.h"

using namespace GameBase;
using namespace Base;

cHashedString	cEntityMovedEventData::m_Name = cHashedString("evententitymoved");

// *****************************************************************************
cEntityMovedEventData::cEntityMovedEventData()
	: m_ActorID(0)
{
}

// *****************************************************************************
cEntityMovedEventData::cEntityMovedEventData(const cVector3 & position,
	const int actorID)
	: m_ActorID(actorID)
	, m_Position(position)
{
}

// *****************************************************************************
cEntityMovedEventData::~cEntityMovedEventData()
{
}


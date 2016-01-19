#include "stdafx.h"
#include "EntityScaledEventData.h"

using namespace GameBase;
using namespace Base;

cHashedString	cEntityScaledEventData::m_Name = cHashedString("evententityscaled");

// *****************************************************************************
cEntityScaledEventData::cEntityScaledEventData()
	: m_ActorID(0)
{
}

// *****************************************************************************
cEntityScaledEventData::cEntityScaledEventData(const cVector3 & size,
	const int actorID)
	: m_ActorID(actorID)
	, m_Size(size)
{
}

// *****************************************************************************
cEntityScaledEventData::~cEntityScaledEventData()
{
}


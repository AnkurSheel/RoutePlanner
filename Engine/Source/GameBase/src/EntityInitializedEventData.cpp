#include "stdafx.h"
#include "EntityInitializedEventData.h"

using namespace GameBase;
using namespace Base;

cHashedString	cEntityInitializedEventData::m_Name = cHashedString("evententityinitialized");

//  *******************************************************************************************************************
cEntityInitializedEventData::cEntityInitializedEventData()
	: m_ActorID(0)
	, m_ReInitializing(false)
{
}

//  *******************************************************************************************************************
cEntityInitializedEventData::cEntityInitializedEventData(const cVector3 & position,	const cVector3 & rotation, 
	const cVector3 & size, const bool ReInitializing, const int actorID)
	: m_ActorID(actorID)
	, m_Position(position)
	, m_Rotation(rotation)
	, m_Size(size)
	, m_ReInitializing(ReInitializing)
{
}

//  *******************************************************************************************************************
cEntityInitializedEventData::~cEntityInitializedEventData()
{
}
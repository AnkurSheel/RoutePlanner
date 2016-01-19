//  *******************************************************************************************************************
//  EntityFactory   version:  1.0   Ankur Sheel  date: 2013/05/06
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#include "StdAfx.h"
#include "EntityFactory.h"
#include "BaseEntity.h"
#include "Config.h"
#include "ComponentFactory.h"

using namespace GameBase;
using namespace Utilities;

cEntityFactory * cEntityFactory::m_pInstance = NULL;

//  *******************************************************************************************************************
cEntityFactory::cEntityFactory()
{
	if(m_pInstance == NULL)
	m_pInstance = this;
}

//  *******************************************************************************************************************
cEntityFactory::~cEntityFactory()
{
}

//  ********************************************************************************************************************
IBaseEntity * cEntityFactory::VCreateEntity(const Base::cHashedString & Type)
{
	cBaseEntity * pEntity = dynamic_cast<cBaseEntity *>(m_RegisteredEntities.Create(Type.GetHash()));
	SP_ASSERT_ERROR(pEntity != NULL)(Type.GetString()).SetCustomMessage("Entity not Registered");
	if(pEntity != NULL)
	{
		const cEntityDef * const pEntityDef = cConfig::GetEntityDef(Type);
		if(pEntityDef != NULL)
		{
			for (auto Iter = pEntityDef->m_Components.begin(); Iter != pEntityDef->m_Components.end(); Iter++)
			{
				IBaseComponent * pComponent = cComponentFactory::Instance()->GetDuplicateComponent(Iter->second);
				if(pComponent != NULL)
				{
					pEntity->AddComponent(pComponent);
				}
			}
		}
	}

	return pEntity;
}

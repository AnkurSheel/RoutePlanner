//  *******************************************************************************************************************
//  RenderSystem version:  1.0   Ankur Sheel  date: 2013/04/02
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "RenderSystem.h"
#include "EntityManager.hxx"
#include "SpriteComponent.h"
#include "Camera.hxx"
#include "ModelComponent.h"
#include "EventManager.hxx"
#include "EntityMovedEventData.h"
#include "EntityScaledEventData.h"

using namespace GameBase;
using namespace Utilities;
using namespace Graphics;
using namespace Base;

const cHashedString cRenderSystem::m_Type = cHashedString("rendersystem");

//  *******************************************************************************************************************
cRenderSystem::cRenderSystem()
{
	VInitialize();
}

//  *******************************************************************************************************************
cRenderSystem::~cRenderSystem()
{
	shared_ptr<IEventManager> pEventManager = MakeStrongPtr(cServiceLocator::GetInstance()->GetService<IEventManager>());
	if (pEventManager != NULL)
	{
		EventListenerCallBackFn listener = bind(&cRenderSystem::ActorMovedListener, this, _1);
		pEventManager->VRemoveListener(listener, cEntityMovedEventData::m_Name);

		listener = bind(&cRenderSystem::ActorScaledListener, this, _1);
		pEventManager->VRemoveListener(listener, cEntityScaledEventData::m_Name);
	}
}

void cRenderSystem::VInitialize()
{
	cProcess::VInitialize();
	m_pEntityManager = cServiceLocator::GetInstance()->GetService<IEntityManager>();

	shared_ptr<IEventManager> pEventManager = MakeStrongPtr(cServiceLocator::GetInstance()->GetService<IEventManager>());
	if (pEventManager != NULL)
	{
		EventListenerCallBackFn listener = bind(&cRenderSystem::ActorMovedListener, this, _1);
		pEventManager->VAddListener(listener, cEntityMovedEventData::m_Name);

		listener = bind(&cRenderSystem::ActorScaledListener, this, _1);
		pEventManager->VAddListener(listener, cEntityScaledEventData::m_Name);
	}
}

//  *******************************************************************************************************************
void cRenderSystem::Render(const ICamera * const pCamera)
{
	shared_ptr<IEntityManager> pEntityManager = MakeStrongPtr(m_pEntityManager);
	if (pEntityManager == NULL)
	{
		return;
	}

	IEntityManager::EntityList entityList;
	pEntityManager->VGetEntitiesWithComponent(cModelComponent::GetName(), entityList);
	IEntityManager::EntityList::iterator enityIter;
	for(enityIter = entityList.begin(); enityIter != entityList.end(); ++enityIter)
	{
		IBaseEntity * pEntity = *enityIter;
		IRenderableComponent * pRenderableComponent = CastToRenderableComponent(pEntity);
		pRenderableComponent->VRender(pCamera);
	}

	entityList.clear();

	pEntityManager->VGetEntitiesWithComponent(cSpriteComponent::GetName(), entityList);
	for(enityIter = entityList.begin(); enityIter != entityList.end(); ++enityIter)
	{
		IBaseEntity * pEntity = *enityIter;
		IRenderableComponent * pRenderableComponent = CastToRenderableComponent(pEntity);
		pRenderableComponent->VRender(pCamera);
	}
}

//  *******************************************************************************************************************
void cRenderSystem::ActorMovedListener(IEventDataPtr pEventData)
{
	shared_ptr<IEntityManager> pEntityManager = MakeStrongPtr(m_pEntityManager);
	if (pEntityManager == NULL)
	{
		return;
	}

	shared_ptr<cEntityMovedEventData> pCastEventData = static_pointer_cast<cEntityMovedEventData>(pEventData);

	int id = pCastEventData->GetActorID();
	cVector3 position = pCastEventData->GetPosition();
	
	IBaseEntity * pEntity = pEntityManager->VGetEntityFromID(id);
	if(pEntity != NULL)
	{
		IRenderableComponent * pRenderableComponent = CastToRenderableComponent(pEntity);

		if(pRenderableComponent == NULL)
		{
			pRenderableComponent = dynamic_cast<IRenderableComponent*>(pEntityManager->VGetComponent(pEntity, cSpriteComponent::GetName()));
		}

		if(pRenderableComponent != NULL)
		{
			pRenderableComponent->VSetPosition(position);
		}
	}
}

//  *******************************************************************************************************************
void cRenderSystem::ActorScaledListener(IEventDataPtr pEventData)
{
	shared_ptr<IEntityManager> pEntityManager = MakeStrongPtr(m_pEntityManager);
	if (pEntityManager == NULL)
	{
		return;
	}
	shared_ptr<cEntityScaledEventData> pCastEventData = static_pointer_cast<cEntityScaledEventData>(pEventData);

	int id = pCastEventData->GetActorID();
	cVector3 size = pCastEventData->GetSize();
	
	IBaseEntity * pEntity = pEntityManager->VGetEntityFromID(id);
	if(pEntity != NULL)
	{
		IRenderableComponent * pRenderableComponent = CastToRenderableComponent(pEntity);
		if(pRenderableComponent != NULL)
		{
			pRenderableComponent->VSetSize(size);
		}
	}
}

//  *******************************************************************************************************************
IRenderableComponent* const cRenderSystem::CastToRenderableComponent(const IBaseEntity * const pEntity)
{
	shared_ptr<IEntityManager> pEntityManager = MakeStrongPtr(m_pEntityManager);

	if (pEntityManager == NULL)
	{
		return NULL;
	}

	return (dynamic_cast<IRenderableComponent*>(pEntityManager->VGetComponent(pEntity, cSpriteComponent::GetName())));
}

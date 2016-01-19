#include "stdafx.h"
#include "PhysicsSystem.h"
#include "EntityManager.hxx"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "physics.hxx"
#include "EventManager.hxx"
#include "EntityInitializedEventData.h"
#include "EntityScaledEventData.h"
#include "BaseEntity.hxx"

using namespace GameBase;
using namespace Utilities;
using namespace Base;
using namespace Physics;

const cHashedString cPhysicsSystem::m_Type = cHashedString("physicssystem");

//  *******************************************************************************************************************
cPhysicsSystem::cPhysicsSystem()
{
	VInitialize();
}

//  *******************************************************************************************************************
cPhysicsSystem::~cPhysicsSystem()
{
	m_pPhysics.reset();
	m_pEntityManager.reset();

	shared_ptr<IEventManager> pEventManager = MakeStrongPtr(cServiceLocator::GetInstance()->GetService<IEventManager>());
	if (pEventManager != NULL)
	{
		EventListenerCallBackFn listener = bind(&cPhysicsSystem::ActorInitializedListener, this, _1);
		pEventManager->VRemoveListener(listener, cEntityInitializedEventData::m_Name);

		listener = bind(&cPhysicsSystem::ActorScaledListener, this, _1);
		pEventManager->VRemoveListener(listener, cEntityScaledEventData::m_Name);
	}
}

//  *******************************************************************************************************************
void cPhysicsSystem::VInitialize()
{
	cProcess::VInitialize();

	shared_ptr<IEventManager> pEventManager = MakeStrongPtr(cServiceLocator::GetInstance()->GetService<IEventManager>());
	if (pEventManager != NULL)
	{
		EventListenerCallBackFn listener = bind(&cPhysicsSystem::ActorInitializedListener, this, _1);
		pEventManager->VAddListener(listener, cEntityInitializedEventData::m_Name);

		listener = bind(&cPhysicsSystem::ActorScaledListener, this, _1);
		pEventManager->VAddListener(listener, cEntityScaledEventData::m_Name);
	}

	m_pEntityManager = cServiceLocator::GetInstance()->GetService<IEntityManager>();

	m_pPhysics = (MakeStrongPtr<IPhysics>(cServiceLocator::GetInstance()->GetService<IPhysics>()));
	if(m_pPhysics != NULL)
	{
		m_pPhysics->VInitialize("Physics");
	}
}

//  *******************************************************************************************************************
void cPhysicsSystem::VUpdate(const float deltaTime)
{
	cProcess::VUpdate(deltaTime);

	shared_ptr<IEntityManager> pEntityManager = MakeStrongPtr(m_pEntityManager);
	if (pEntityManager == NULL)
	{
		return;
	}

	IEntityManager::EntityList entityList;
	pEntityManager->VGetEntitiesWithComponent(cPhysicsComponent::GetName(), entityList);
	for(auto enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cPhysicsComponent* pPhysicsComponent = CastToPhysicsComponent(pEntity);
		if (pPhysicsComponent != NULL)
		{
			pPhysicsComponent->Update((int)(deltaTime * 10000));
		}
	}
	
	if(m_pPhysics != NULL)
	{
		m_pPhysics->VUpdate(deltaTime);
	}
	
	for(auto enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cTransformComponent * pTransformComponent = dynamic_cast<cTransformComponent*>(pEntityManager->VGetComponent(pEntity, cTransformComponent::GetName()));
		cPhysicsComponent * pPhysicsComponent = CastToPhysicsComponent(pEntity);
		if (pTransformComponent != NULL && pPhysicsComponent != NULL)
		{
			pTransformComponent->SetPosition(pPhysicsComponent->GetPosition());
		}
	}

	CollisionPairs triggerpairs;
	if(m_pPhysics != NULL)
	{
		triggerpairs = m_pPhysics->VGetTriggerPairs();
	}

	for(auto Iter = triggerpairs.begin(); Iter != triggerpairs.end(); Iter++)
	{
		const CollisionPair pair = *Iter;
		IBaseEntity * pEntity = pEntityManager->VGetEntityFromID(pair.first);
		IBaseEntity * pTrigger = pEntityManager->VGetEntityFromID(pair.second);
		if(pEntity != NULL && pTrigger != NULL)
		{
			pEntity->VOnEnteredTrigger(pTrigger);
		}
	}

	CollisionPairs collisionpairs;
	if(m_pPhysics != NULL)
	{
		collisionpairs = m_pPhysics->VGetCollisionPairs();
	}

	for(auto Iter = collisionpairs.begin(); Iter != collisionpairs.end(); Iter++)
	{
		const CollisionPair pair = *Iter;
		IBaseEntity * pEntity1 = pEntityManager->VGetEntityFromID(pair.first);
		IBaseEntity * pEntity2 = pEntityManager->VGetEntityFromID(pair.second);
		if(pEntity1 != NULL && pEntity2 != NULL)
		{
			pEntity1->VOnCollided(pEntity2);
			pEntity2->VOnCollided(pEntity1);
		}
	}
}

//  *******************************************************************************************************************
void cPhysicsSystem::ActorInitializedListener(IEventDataPtr pEventData)
{
	shared_ptr<IEntityManager> pEntityManager = MakeStrongPtr(m_pEntityManager);
	if (pEntityManager == NULL)
	{
		return;
	}

	shared_ptr<cEntityInitializedEventData> pCastEventData = static_pointer_cast<cEntityInitializedEventData>(pEventData);

	int id = pCastEventData->GetActorID();

	IBaseEntity * pEntity = pEntityManager->VGetEntityFromID(id);

	cPhysicsComponent * pPhysicsComponent = CastToPhysicsComponent(pEntity);

	if(pPhysicsComponent != NULL)
	{
		if(pCastEventData->IsReInitializing())
		{
			pPhysicsComponent->ReInitialize(pCastEventData->GetPosition(), pCastEventData->GetRotation(), pCastEventData->GetSize());
		}
		else
		{
			pPhysicsComponent->Initialize(pCastEventData->GetPosition(), pCastEventData->GetRotation(), pCastEventData->GetSize());
		}
	}
}

//  *******************************************************************************************************************
void cPhysicsSystem::ActorScaledListener(IEventDataPtr pEventData)
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
		cPhysicsComponent * pPhysicsComponent = CastToPhysicsComponent(pEntity);
		if(pPhysicsComponent != NULL)
		{
			pPhysicsComponent->OnSizeUpdated();
		}
	}
}

//  *******************************************************************************************************************
cPhysicsComponent* const GameBase::cPhysicsSystem::CastToPhysicsComponent(const IBaseEntity * const pEntity)
{
	shared_ptr<IEntityManager> pEntityManager = MakeStrongPtr(m_pEntityManager);
	if (pEntityManager == NULL)
	{
		return NULL;
	}

	return (dynamic_cast<cPhysicsComponent*>(pEntityManager->VGetComponent(pEntity, cPhysicsComponent::GetName())));
}

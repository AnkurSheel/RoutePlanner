//  *******************************************************************************************************************
//  PhysicsComponent version:  1.0   Ankur Sheel  date: 2013/05/17
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#include "stdafx.h"
#include "PhysicsComponent.h"
#include "XMLNode.hxx"
#include "optional.h"
#include "RigidBody.hxx"
#include "Physics.hxx"
#include "BaseEntity.hxx"
#include "EntityManager.hxx"
#include "SpriteComponent.h"
#include "EntityMovedEventData.h"
#include "EntityScaledEventData.h"
#include "EventManager.hxx"

using namespace GameBase;
using namespace Base;
using namespace Utilities;
using namespace Physics;

cHashedString	cPhysicsComponent::m_Name = cHashedString("physicscomponent");

//  *******************************************************************************************************************
cPhysicsComponent::cPhysicsComponent()
	: m_pRigidBody(NULL)
	, m_Force(0.0f)
	, m_ApplyForce(false)
	, m_Initialized(false)
{
}

//  *******************************************************************************************************************
cPhysicsComponent::~cPhysicsComponent()
{
	VCleanup();
}

//  *******************************************************************************************************************
void cPhysicsComponent::VInitialize(const IXMLNode * const pXMLNode)
{
	if(pXMLNode == NULL)
	{
		return;
	}
	m_pDef = shared_ptr<Physics::stRigidBodyDef>(DEBUG_NEW stRigidBodyDef());

	m_pDef->m_TopSpeed = pXMLNode->VGetChildValueAsFloat("TopSpeed", 0.0f);
	m_pDef->m_ApplyGravity = pXMLNode->VGetChildValueAsBool("ApplyGravity", false);
	m_pDef->m_LinearDamping = pXMLNode->VGetChildValueAsFloat("LinearDamping", 1.0f);
	m_pDef->m_Mass = pXMLNode->VGetChildValueAsFloat("Mass",0.0f);
	m_pDef->m_Kinematic = pXMLNode->VGetChildValueAsBool("Kinematic", false);
	m_pDef->m_Material = pXMLNode->VGetChildValue("Material");
	m_pDef->m_IsTrigger = pXMLNode->VGetChildValueAsBool("IsTrigger", false);

	m_Force = pXMLNode->VGetChildValueAsFloat("Force", 0.0f);

	cString value = pXMLNode->VGetChildValue("Shape");
	if(!value.IsEmpty())
	{
		m_pDef->m_Shape = cHashedString(cStringUtilities::GetInLowerCase(value));
	}
}

//  *******************************************************************************************************************
void cPhysicsComponent::VOnAttached(IBaseEntity * const pOwner)
{
	cBaseComponent::VOnAttached(pOwner);
	if(m_pDef != NULL)
	{
		CalculateBounds(m_pDef->m_MinBound, m_pDef->m_MaxBound);
	}
	const shared_ptr<IPhysics> pPhysics = (MakeStrongPtr<IPhysics>(cServiceLocator::GetInstance()->GetService<IPhysics>()));
	if(pPhysics != NULL)
	{
		m_pRigidBody = pPhysics->VAddRigidBody(m_pOwner->VGetEntityID(), m_pDef);	
	}
}

//  *******************************************************************************************************************
shared_ptr<IXMLNode> cPhysicsComponent::VGenerateXml() const 
{
	shared_ptr<IXMLNode> pXmlNode = IXMLNode::Create("PhysicsComponent");

	pXmlNode->VAddElement("ApplyGravity", m_pDef->m_ApplyGravity ? "true" : "false");
	pXmlNode->VAddElement("Shape", m_pDef->m_Shape.GetString());
	pXmlNode->VAddElement("TopSpeed", cStringUtilities::MakeFormatted("%f", m_pDef->m_TopSpeed));
	pXmlNode->VAddElement("Force", cStringUtilities::MakeFormatted("%f", m_Force));
	pXmlNode->VAddElement("Mass", cStringUtilities::MakeFormatted("%f", m_pDef->m_Mass));
	pXmlNode->VAddElement("LinearDamping", cStringUtilities::MakeFormatted("%f", m_pDef->m_LinearDamping));
	pXmlNode->VAddElement("Material", m_pDef->m_Material);
	pXmlNode->VAddElement("Kinematic", m_pDef->m_Kinematic ? "true" : "false");
	pXmlNode->VAddElement("IsTrigger", m_pDef->m_IsTrigger ? "true" : "false");
	return pXmlNode;
}

//  *******************************************************************************************************************
void cPhysicsComponent::VCleanup()
{
	if(m_pOwner != NULL)
	{
		const shared_ptr<IPhysics> pPhysics = (MakeStrongPtr<IPhysics>(cServiceLocator::GetInstance()->GetService<IPhysics>()));
		if(pPhysics != NULL)
		{
			pPhysics->VRemoveRigidBody(m_pOwner->VGetEntityID());
		}
	}
}

//  *******************************************************************************************************************
void cPhysicsComponent::Initialize(const cVector3 & position, const cVector3 & rotation, const cVector3 & size)
{
	if(!m_Initialized && m_pRigidBody != NULL)
	{
		m_Initialized = true;
		ReInitialize(position, rotation, size);

		const shared_ptr<IPhysics> pPhysics = (MakeStrongPtr<IPhysics>(cServiceLocator::GetInstance()->GetService<IPhysics>()));
		if(pPhysics != NULL)
		{
			pPhysics->VOnRigidBodyAdded(m_pRigidBody->VGetID());
		}
	}
}

//  *******************************************************************************************************************
void cPhysicsComponent::ReInitialize(const cVector3 & position, const cVector3 & rotation, const cVector3 & size)
{
	m_pRigidBody->VInitialize(position);

	shared_ptr<IEventManager> pEventManager = MakeStrongPtr(cServiceLocator::GetInstance()->GetService<IEventManager>());
	if (pEventManager != NULL)
	{
		shared_ptr<cEntityMovedEventData> pMovedEvent(DEBUG_NEW cEntityMovedEventData(position, m_pOwner->VGetEntityID()));
		pEventManager->VTriggerEvent(pMovedEvent);

		shared_ptr<cEntityScaledEventData> pScaledEvent(DEBUG_NEW cEntityScaledEventData(size, m_pOwner->VGetEntityID()));
		pEventManager->VTriggerEvent(pScaledEvent);
	}
}
//  *******************************************************************************************************************
void cPhysicsComponent::ApplyForce(const cVector3 & Direction)
{
	m_ApplyForce = true;
	m_Direction = Direction;
	//m_pPhysicsComponent->m_CurrentAcceleration = m_pTransFormComponent->m_LookAt * m_pPhysicsComponent->m_Acceleration;
}

//  *******************************************************************************************************************
void cPhysicsComponent::Update(const int deltaTime)
{
	if(m_ApplyForce)
	{
		m_ApplyForce = false;
		if(m_pRigidBody != NULL && m_Initialized)
		{
			float force = m_Force * (float)deltaTime / 10000.0f;
			m_pRigidBody->VApplyForce(m_Direction, force);
		}
	}
}

//  *******************************************************************************************************************
cVector3 cPhysicsComponent::GetPosition() const
{
	if(m_pRigidBody != NULL)
	{
		return m_pRigidBody->VGetRenderPosition();
	}

	return cVector3::Zero;
}

//  *******************************************************************************************************************
void cPhysicsComponent::CalculateBounds(cVector3 & minBound, cVector3 & maxBound)
{
	if(m_pDef != NULL)
	{
		if(m_pDef->m_Shape == cHashedString("rectangle"))
		{
			shared_ptr<IEntityManager> pEntityManager = (MakeStrongPtr<IEntityManager>(cServiceLocator::GetInstance()->GetService<IEntityManager>()));
			if (pEntityManager != NULL)
			{
				IRenderableComponent * pRenderableComponent = dynamic_cast<IRenderableComponent*>(pEntityManager->VGetComponent(m_pOwner, cSpriteComponent::GetName()));
				if(pRenderableComponent != NULL)
				{
					pRenderableComponent->VGetBounds(minBound, maxBound);
				}
			}
		}
	}
}

//  *******************************************************************************************************************
void cPhysicsComponent::OnSizeUpdated()
{
	cVector3 minBound;
	cVector3 maxBound;

	CalculateBounds(minBound, maxBound);
	if(m_pRigidBody != NULL)
	{
		m_pRigidBody->VUpdateCollisionShape(minBound, maxBound);
	}
}

//  *******************************************************************************************************************
void cPhysicsComponent::SetAsTrigger(bool isTrigger)
{
	if(m_pRigidBody != NULL)
	{
		m_pRigidBody->VSetAsTrigger(isTrigger);
	}
}

//  *******************************************************************************************************************
void cPhysicsComponent::GetBounds(cVector3 & minBound, cVector3 & maxBound)
{
	if (m_pRigidBody != NULL)
	{
		m_pRigidBody->VGetBounds(minBound, maxBound);
	}
}

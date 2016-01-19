#include "stdafx.h"
#include "CollisionInfo.h"
#include "RigidBody.h"
#include "Shape.hxx"
#include "RectangleShape.h"
#include "Vector2.h"

using namespace Physics;
using namespace Base;

//  *******************************************************************************************************************
cCollisionInfo::cCollisionInfo(cRigidBody * const pBodyA, cRigidBody * const pBodyB)
	: m_pBodyA(pBodyA)
	, m_pBodyB(pBodyB)
	, m_Distance(0.0f)
	, m_Collided(false)
{
}

//  *******************************************************************************************************************
cCollisionInfo::~cCollisionInfo()
{
}

//  *******************************************************************************************************************
cCollisionInfo::cCollisionInfo(const cCollisionInfo & other)
	: m_pBodyA(other.m_pBodyA)
	, m_pBodyB(other.m_pBodyB)
	, m_Normal(other.m_Normal)
	, m_Distance(other.m_Distance)
	, m_Collided(other.m_Collided)
{
}

//  *******************************************************************************************************************
void cCollisionInfo::Solve()
{
	if(isZero(m_pBodyA->GetInverseMass() + m_pBodyB->GetInverseMass()))
	{
		InfiniteMassCorrection();
		return;
	}

	if(m_pBodyA->GetCollisionShape()->VGetName() == cRectangleShape::m_Name
		&& m_pBodyB->GetCollisionShape()->VGetName() == cRectangleShape::m_Name)
	{
		cVector3 centerDelta = m_pBodyA->GetCollisionShape()->VGetCenter() -  m_pBodyB->GetCollisionShape()->VGetCenter();
		cVector3 overlap = centerDelta;
		overlap.AbsTo();

		cVector3 halfExtentSum = m_pBodyA->GetCollisionShape()->VGetHalfExtents() + m_pBodyB->GetCollisionShape()->VGetHalfExtents();
		overlap = halfExtentSum - overlap;

		m_Collided = overlap.x > 0 && overlap.y > 0;
		if(m_Collided)
		{
			cVector2 smallestOverlap = cVector2(overlap.x, overlap.y);
			smallestOverlap = smallestOverlap.MinorAxis();

			cVector3 smallestOverlap3 = cVector3(smallestOverlap.x, smallestOverlap.y, 0.0f);
			m_Normal = (centerDelta * smallestOverlap3).MajorAxis();
			m_Distance = (overlap * m_Normal).Length();
		}
	}
}

//  *******************************************************************************************************************
void cCollisionInfo::ApplyImpulse()
{
	if(m_pBodyA->VIsTrigger() == true || m_pBodyB->VIsTrigger() == true)
	{
		return;
	}

	// Calculate relative velocity
	cVector3 rv = m_pBodyA->GetLinearVelocity() - m_pBodyB->GetLinearVelocity();

	float velAlongNormal = rv.Dot(m_Normal);

	// Do not resolve if velocities are separating
	if(velAlongNormal > 0)
		return;

	// Calculate restitution
	float e = min(m_pBodyA->GetRestitution(), m_pBodyB->GetRestitution());

	// Calculate impulse scalar
	float j = -(1 + e) * velAlongNormal;
	j /= m_pBodyA->GetInverseMass() + m_pBodyB->GetInverseMass();

	// Apply impulse
	cVector3 impulse = j * m_Normal;
	m_pBodyA->ApplyImpulse(impulse);
	m_pBodyB->ApplyImpulse(impulse.GetReverse());
}

//  *******************************************************************************************************************
void cCollisionInfo::ApplyPositionCorrection()
{
	if(m_pBodyA->VIsTrigger() || m_pBodyB->VIsTrigger())
	{
		return;
	}

	const float slop = 0.05f; // Penetration allowance
	const float percent = 0.8f; // Penetration percentage to correct
	if(isZero(m_Distance - slop))
	{
		return;
	}
	cVector3 correction = (m_Distance / (m_pBodyA->GetInverseMass() + m_pBodyB->GetInverseMass())) * m_Normal * percent;
	m_pBodyA->ApplyPositionCorrection(correction);
	m_pBodyB->ApplyPositionCorrection(correction.GetReverse());
}

//  *******************************************************************************************************************
void cCollisionInfo::InfiniteMassCorrection()
{
	m_pBodyA->SetLinearVelocity(cVector3::Zero);
	m_pBodyB->SetLinearVelocity(cVector3::Zero);
}
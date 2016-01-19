//  *******************************************************************************************************************
//  RigidBody version:  1.0   Ankur Sheel  date: 2013/05/23
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef RigidBody_h
#define RigidBody_h

#include "RigidBody.hxx"
#include "vector3.h"

namespace Physics
{
	class IShape;
	class cQTNode;
}

namespace Physics
{
	class cRigidBody
		: public IRigidBody
	{
	public:
		cRigidBody();
		~cRigidBody();
		cRigidBody(const cRigidBody & other);
		cRigidBody & operator =(const cRigidBody & other);

		bool VIsTrigger() const { return m_IsTrigger; }
		int VGetID() const { return m_ID; }

		void OnCreated(shared_ptr<const stRigidBodyDef> pDef, const int ID);
		cQTNode * const GetNode() const { return m_pNode; }
		bool Sync(const float alpha);
		void IntegrateForces(const float timestep);
		void IntegrateVelocity(const float timestep);
		void ApplyGravity(const float timeStep);
		void SetNode(cQTNode * const pNode) { m_pNode = pNode; }
		IShape * GetCollisionShape() const { return m_pCollisionShape; }
		bool IsInitialized() const { return m_Initialized; }
		bool IsKinematic() const { return m_Kinematic; }
		float GetInverseMass() const { return m_InverseMass; }
		float GetRestitution() const { return m_MaterialData.restitution; }
		Base::cVector3 GetLinearVelocity() const { return m_LinearVelocity; }
		void SetLinearVelocity(const Base::cVector3 & velocity) { m_LinearVelocity = velocity; }
		void ApplyImpulse(const Base::cVector3 & impulse);
		void ApplyPositionCorrection(const Base::cVector3 & correction);

	private:
		void VInitialize(const Base::cVector3 & position) OVERRIDE;
		void VApplyForce(const Base::cVector3 & Direction, const float Newtons) OVERRIDE;
		void VUpdateCollisionShape(const Base::cVector3 & minBound, const Base::cVector3 & maxBound) OVERRIDE;
		void VGetBounds(Base::cVector3& minBound, Base::cVector3 & maxBound) OVERRIDE;
		void OnMoved();

		void VSetAsTrigger(bool isTrigger) OVERRIDE { m_IsTrigger = isTrigger; }
		Base::cVector3 VGetRenderPosition() const OVERRIDE { return m_RenderPosition; }

	private:
		Base::cVector3	m_LinearVelocity;
		Base::cVector3	m_Position;
		Base::cVector3	m_PreviousPosition;
		Base::cVector3	m_RenderPosition;
		Base::cVector3	m_Force;
		IShape *		m_pCollisionShape;
		cQTNode *		m_pNode;
		float			m_InverseMass;
		float			m_LinearDamping;
		float			m_TopSpeed;
		int				m_ID;
		bool			m_ApplyGravity;
		bool			m_Initialized;
		bool			m_Kinematic;
		bool			m_IsTrigger;
		stMaterialData	m_MaterialData;
	};
}
#endif //RigidBody_hxx
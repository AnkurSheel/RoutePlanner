//  *******************************************************************************************************************
//  RigidBody version:  1.0   Ankur Sheel  date: 2013/05/23
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#ifndef RigidBody_hxx
#define RigidBody_hxx

#include "PhysicsDefines.h"
#include "vector3.h"

namespace Physics
{
	struct stMaterialData
	{
		float	restitution;
		float	friction;

		stMaterialData()
			: restitution(1.0f)
			, friction(0.0f)
		{
		}
	};

	struct	stRigidBodyDef
	{
		float				m_Mass;
		float				m_LinearDamping;
		float				m_TopSpeed;
		Base::cVector3		m_MinBound;
		Base::cVector3		m_MaxBound;
		Base::cHashedString	m_Shape; 
		Base::cString		m_Material;
		bool				m_ApplyGravity;
		bool				m_Kinematic;
		bool				m_IsTrigger;

		stRigidBodyDef()
			: m_Mass(0.0f)
			, m_LinearDamping(1.0f)
			, m_ApplyGravity(false)
			, m_TopSpeed(0.0f)
			, m_Shape("none")
			, m_Material("normal")
			, m_Kinematic(false)
			, m_IsTrigger(false)
		{
		}
	};

	class IRigidBody
	{
	public:
		virtual ~IRigidBody() {}
		virtual void VInitialize(const Base::cVector3 & position) = 0;
		virtual void VApplyForce(const Base::cVector3 & direction, const float newtons) = 0;
		virtual void VUpdateCollisionShape(const Base::cVector3 & minBound, const Base::cVector3 & maxBound) = 0;
		virtual Base::cVector3 VGetRenderPosition() const = 0;
		virtual int VGetID() const = 0;
		virtual void VSetAsTrigger(bool isTrigger) = 0;
		virtual bool VIsTrigger() const = 0;
		virtual void VGetBounds(Base::cVector3 & minBound, Base::cVector3 & maxBound) = 0;
		static IRigidBody * Create(shared_ptr<const stRigidBodyDef> pDef, const int ID);
	};
}
#endif //RigidBody_hxx
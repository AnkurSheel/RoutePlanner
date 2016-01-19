//  *******************************************************************************************************************
//  PhysicsComponent version:  1.0   Ankur Sheel  date: 2013/05/17
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef PhysicsComponent_h__
#define PhysicsComponent_h__

#include "GameBaseDefines.h"
#include "BaseComponent.h"
#include "vector3.h"

namespace Base
{
	template<class BaseType, class SubType> 
	BaseType * GenericObjectCreationFunction();
}

namespace Physics
{
	class IRigidBody;
	struct stRigidBodyDef;
}

namespace GameBase
{
	class cPhysicsComponent
		: public cBaseComponent
	{
	public:
		void VInitialize(const Utilities::IXMLNode * const pXMLNode) OVERRIDE;
		void VOnAttached(IBaseEntity * const pOwner) OVERRIDE;
		void VCleanup() OVERRIDE;
		shared_ptr<Utilities::IXMLNode> VGenerateXml() const OVERRIDE;

		GAMEBASE_API static Base::cHashedString	GetName()  {return m_Name; }
		void Initialize(const Base::cVector3 & position, const Base::cVector3 & rotation, const Base::cVector3 & size);
		void ReInitialize(const Base::cVector3 & position, const Base::cVector3 & rotation, const Base::cVector3 & size);
		bool GetInitialized() const { return m_Initialized; }
		Base::cVector3 GetPosition() const;
		GAMEBASE_API void ApplyForce(const Base::cVector3 & Direction);
		void Update(const int deltaTime);
		void OnSizeUpdated();
		GAMEBASE_API void SetAsTrigger(bool isTrigger);
		GAMEBASE_API void GetBounds(Base::cVector3 & minBound, Base::cVector3 & maxBound);

	private:
		cPhysicsComponent();
		~cPhysicsComponent();
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
		void CalculateBounds(Base::cVector3 & minBound, Base::cVector3 & maxBound);

	private:
		Physics::IRigidBody *				m_pRigidBody;
		shared_ptr<Physics::stRigidBodyDef>	m_pDef;
		Base::cVector3						m_Direction;
		float								m_Force;
		bool								m_Initialized;
		bool								m_ApplyForce;
		static Base::cHashedString			m_Name;	///< The component name

	private:
		template<class BaseType, class SubType> 
		friend BaseType * Base::GenericObjectCreationFunction();

	};
}
#endif // PhysicsComponent_h__

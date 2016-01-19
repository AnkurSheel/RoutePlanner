//  *******************************************************************************************************************
//  PhysicsSystem version:  1.0   Ankur Sheel  date: 2013/05/16
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef PhysicsSystem_h__
#define PhysicsSystem_h__

#include "GameBaseDefines.h"
#include "Process.h"

namespace Physics
{
	class IPhysics;
}

namespace GameBase
{
	class IEventData;
	typedef shared_ptr<IEventData> IEventDataPtr;
	class IEntityManager;
	class cPhysicsComponent;
	class IBaseEntity;
}

namespace GameBase
{
	class cPhysicsSystem
		: public Utilities::cProcess
	{
	public:
		GAMEBASE_API cPhysicsSystem();
		GAMEBASE_API ~cPhysicsSystem();
		void VInitialize() OVERRIDE;
		void VUpdate(const float deltaTime) OVERRIDE;

		const Base::cHashedString & VGetType() const OVERRIDE { return m_Type; }

	public:
		GAMEBASE_API static const Base::cHashedString m_Type;

	private:
		void ActorInitializedListener(IEventDataPtr pEventData);
		void ActorScaledListener(IEventDataPtr pEventData);
		cPhysicsComponent * const CastToPhysicsComponent(const IBaseEntity * const pEntity);

	private:
		shared_ptr<Physics::IPhysics> m_pPhysics;
		weak_ptr<IEntityManager> m_pEntityManager;
	};
}
#endif // PhysicsSystem_h__

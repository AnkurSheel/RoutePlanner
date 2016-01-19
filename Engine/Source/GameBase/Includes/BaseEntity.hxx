//  *******************************************************************************************************************
//  BaseEntity   version:  1.0   Ankur Sheel  date: 2012/07/31
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef BaseEntity_hxx__
#define BaseEntity_hxx__

#include "GameBaseDefines.h"

namespace AI
{
	struct Telegram;
}

namespace GameBase
{
	class IBaseComponent;
}

namespace GameBase
{
	class IBaseEntity
	{
	public:
		typedef std::list<IBaseComponent *> ComponentList;

	public:
		virtual ~IBaseEntity(){}
		virtual void VInitialize() = 0;
		virtual void VOnUpdate(const float deltaTime) = 0;
		virtual void VOnRestart() = 0;
		virtual void VCleanup() = 0;
		virtual bool VOnHandleMessage(const AI::Telegram & telegram) = 0;
		virtual void VHandleInput(const float inDeltaTime) = 0;
		virtual Base::cHashedString VGetEntityType() const = 0;
		virtual unsigned long VGetHashedID() const = 0;
		virtual int VGetEntityID() const = 0;
		virtual void VOnCollided(IBaseEntity * const pEntityCollider) = 0;
		virtual void VOnEnteredTrigger(IBaseEntity * const pTrigger) = 0;
		virtual Base::cString VToXml() = 0;
	};
}
#endif // BaseEntity_hxx__
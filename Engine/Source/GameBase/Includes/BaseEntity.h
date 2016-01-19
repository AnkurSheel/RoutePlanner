//  *******************************************************************************************************************
//  BaseEntity   version:  1.0   Ankur Sheel  date: 2012/07/30
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef BaseEntity_h__
#define BaseEntity_h__

#include "BaseEntity.hxx"
#include "GameBaseDefines.h"

namespace GameBase
{
	class IBaseComponent;
	class cComponentDef;
	class cTransformComponent;
}

namespace GameBase
{
	typedef std::map<unsigned long, IBaseComponent *> ComponentMap;
	class cEntityDef
		: public Base::cNonCopyable
	{
	public:
		GAMEBASE_API cEntityDef();
		GAMEBASE_API virtual ~cEntityDef();

	public:
		bool			m_IsCollidable;
		Base::cString	m_Type;
		ComponentMap	m_Components;

	private:
		void Cleanup();
	};

	class cBaseEntity
		: public IBaseEntity
	{
	public:
		GAMEBASE_API cBaseEntity();
		GAMEBASE_API cBaseEntity(const int ID);
		GAMEBASE_API virtual ~cBaseEntity();
		GAMEBASE_API void VInitialize() OVERRIDE;
		GAMEBASE_API void VOnCollided(IBaseEntity * const pEntityCollider) OVERRIDE {}
		GAMEBASE_API void VOnEnteredTrigger(IBaseEntity * const pTrigger) OVERRIDE {}
		GAMEBASE_API void VOnRestart() OVERRIDE;
		GAMEBASE_API void VCleanup() OVERRIDE;
		GAMEBASE_API bool VOnHandleMessage(const AI::Telegram & telegram) OVERRIDE;
		GAMEBASE_API void VHandleInput(const float inDeltaTime) OVERRIDE;
		GAMEBASE_API Base::cString VToXml();

		GAMEBASE_API void VOnInitialized();
		GAMEBASE_API void AddComponent(IBaseComponent * pComponent);
		GAMEBASE_API void RemoveComponent(const unsigned long ComponentID);
		GAMEBASE_API void GetAllComponents(ComponentList & components) const;
		GAMEBASE_API IBaseComponent * GetComponent(const Base::cHashedString & ComponentName) const;
		GAMEBASE_API IBaseComponent * GetComponent(const unsigned long ComponentID) const;

		GAMEBASE_API virtual void VSetActive(const bool Active) { m_Active = Active; }
		GAMEBASE_API bool IsActive() const { return m_Active; };
		GAMEBASE_API int VGetEntityID() const  OVERRIDE{ return m_ID; } 

	private:
		void SetEntityID(const int ID);

	protected:
		cTransformComponent * m_pTransFormComponent;

	private:
		int	m_ID;
		bool	m_Active;
		ComponentMap	m_Components;
		static int	m_sNextValidID;
	};
}
#endif // BaseEntity_h__
// *****************************************************************************
//  EnityManager   version:  1.0   Ankur Sheel  date: 2012/07/27
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************

#ifndef EntityManager_h__
#define EntityManager_h__

#include "EntityManager.hxx"

namespace GameBase
{
	class IBaseEntity;
	class IBaseComponent;
}

namespace GameBase
{
	class cEntityManager
		: public IEntityManager
		, public Base::cNonCopyable
	{
	public:
		~cEntityManager();

	private:
		typedef std::map<unsigned long, EntityList> EntityComponentMap;

	private:
		void VInitializeEntityFactory(shared_ptr<cEntityFactory> pEntityFactory) OVERRIDE;
		void VInitializeComponentFactory(shared_ptr<cComponentFactory> pComponentFactory) OVERRIDE;
		void VAddEntity(IBaseEntity * const pNewEntity) OVERRIDE;
		IBaseEntity * const VAddEntity(const Base::cString & Type) OVERRIDE;
		void VDeleteEntity(IBaseEntity * const pNewEntity) OVERRIDE;
		void VAddComponent(IBaseEntity * const pEntity, IBaseComponent * pComponent) OVERRIDE;
		void VRemoveComponent(IBaseEntity * const pEntity,	const unsigned long ComponentID) OVERRIDE;
		IBaseEntity * const VGetFirstEntityWithComponent(const Base::cHashedString & Component) OVERRIDE;
		void VGetEntitiesWithComponent(const Base::cHashedString & Component, EntityList & entities) OVERRIDE;
		IBaseEntity * const VGetEntityFromID(const int iID) const OVERRIDE;
		Base::cString VGetEntityNameFromID(const int iID) const OVERRIDE;
		Base::cString VGetEntityName(const IBaseEntity * const pEntity) const OVERRIDE;
		IBaseEntity * const VGetEntityOfType(const Base::cHashedString & Type) OVERRIDE;
		IBaseComponent * VGetComponent(const IBaseEntity * const , const Base::cHashedString & ComponentName) const OVERRIDE;
		int VGetEntityID(const IBaseEntity * const pEntity) const OVERRIDE;
		void VUpdate(const float deltaTime) OVERRIDE;
		void VDeleteAllEntities() OVERRIDE;

		int VGetNumberOfEntities() const OVERRIDE { return m_EntityMap.size(); }
		const EntityMap& VGetEntityMap() const OVERRIDE { return m_EntityMap; } 

		void InitializeEntity(IBaseEntity * const pEntity);
		void RemoveDeletedEntities();
		void Cleanup();

		cEntityManager();

	private:
		EntityMap m_EntityMap;
		EntityComponentMap m_ComponentMap;
		shared_ptr<cEntityFactory> m_pEntityFactory;
		shared_ptr<cComponentFactory> m_pComponentFactory;
		EntityList m_DeletedEntities;

	private:
		friend void IEntityManager::CreateAsService();
	};
}
#endif // EnityManager_h__

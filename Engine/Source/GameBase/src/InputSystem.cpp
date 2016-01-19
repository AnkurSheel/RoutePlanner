//  *******************************************************************************************************************
//  InputSystem version:  1.0   Ankur Sheel  date: 2013/05/16
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "InputSystem.h"
#include "EntityManager.hxx"
#include "KeyboardHandlerComponent.h"

using namespace Base;
using namespace GameBase;
using namespace Utilities;
using namespace Graphics;

const cHashedString cInputSystem::m_Type = cHashedString("inputsystem");

//  *******************************************************************************************************************
cInputSystem::cInputSystem()
{
}

//  *******************************************************************************************************************
cInputSystem::~cInputSystem()
{

}

//  *******************************************************************************************************************
void cInputSystem::VUpdate(const float deltaTime)
{
	cProcess::VUpdate(deltaTime);

	shared_ptr<IEntityManager> pEntityManager = (MakeStrongPtr<IEntityManager>(cServiceLocator::GetInstance()->GetService<IEntityManager>()));
	if (pEntityManager != NULL)
	{
		IEntityManager::EntityList entityList;
		pEntityManager->VGetEntitiesWithComponent(cKeyboardHandlerComponent::GetName(), entityList);
		for(auto enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
		{
			IBaseEntity * pEntity = *enityIter;
			cKeyboardHandlerComponent * pKeyboardHandler = dynamic_cast<cKeyboardHandlerComponent*>(pEntityManager->VGetComponent(pEntity, cKeyboardHandlerComponent::GetName()));
			if(pKeyboardHandler != NULL)
			{
				pKeyboardHandler->Update(deltaTime);
			}
		}
	}
}

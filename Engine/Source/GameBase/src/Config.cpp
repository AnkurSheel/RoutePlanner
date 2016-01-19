//  *******************************************************************************************************************
//  Config   version:  1.0   Ankur Sheel  date: 2013/05/06
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#include "StdAfx.h"
#include "Config.h"
#include "XMLNode.hxx"
#include "GameDirectories.h"
#include "ResCache.hxx"
#include "ResourceManager.hxx"
#include "BaseEntity.h"
#include "BaseComponent.hxx"
#include "ComponentFactory.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

cConfig * cConfig::m_pInstance = NULL;

//  *******************************************************************************************************************
cConfig::cConfig()
{
	if(m_pInstance == NULL)
		m_pInstance = this;
}

//  *******************************************************************************************************************
cConfig::~cConfig()
{
	Cleanup();
}

//  *******************************************************************************************************************
void cConfig::VInitialize(const cString & FileName)
{
	IResource * pResource = IResource::CreateResource(cGameDirectories::GetDesignDirectory() + FileName + ".xml");
	shared_ptr<IResHandle> pXMLFile = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);

	SafeDelete(&pResource);
	if(pXMLFile != NULL)
	{
		m_pRoot = shared_ptr<IXMLNode>(IXMLNode::Parse(pXMLFile->GetBuffer(), pXMLFile->GetSize()));
	}
	SP_ASSERT_ERROR(m_pRoot != NULL).SetCustomMessage("Could not find " + FileName + ".xml");

	cString EntitiesFileName = m_pRoot->VGetChildValue("EntitiesFile");
	SP_ASSERT_ERROR(!EntitiesFileName.IsEmpty(), 1, "Missing element: EntitiesFile");
	if(!EntitiesFileName.IsEmpty())
	{
		LoadEntities(EntitiesFileName);
	}
}

//  *******************************************************************************************************************
const cEntityDef * const cConfig::GetEntityDef(const Base::cHashedString & EntityType)
{
	if(m_pInstance != NULL)
	{
		return m_pInstance->m_EntityDefs[EntityType.GetHash()];
	}
	return NULL;
}

//  *******************************************************************************************************************
void cConfig::LoadEntities(const cString & EntitiesFileName)
{
	IResource * pResource = IResource::CreateResource(cGameDirectories::GetDesignDirectory() + EntitiesFileName + ".xml");
	shared_ptr<IResHandle> pXMLFile = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);
	shared_ptr<IXMLNode> pRoot;
	SafeDelete(&pResource);
	if(pXMLFile != NULL)
	{
		pRoot = shared_ptr<IXMLNode>(IXMLNode::Parse(pXMLFile->GetBuffer(), pXMLFile->GetSize()));
	}
	SP_ASSERT_ERROR(m_pRoot != NULL).SetCustomMessage("Could not find " + EntitiesFileName + ".xml");

	IXMLNode::XMLNodeList List;
	pRoot->VGetChildren(List);
	for (auto Iter = List.begin(); Iter != List.end(); Iter++)
	{
		IXMLNode * pEntityDefNode = (*Iter).get();
		SP_LOG(2, "Element Loaded")(pEntityDefNode->VGetName());
		cEntityDef * pEntityDef = DEBUG_NEW cEntityDef();
		m_EntityDefs[cHashedString::CalculateChecksum(cStringUtilities::GetInLowerCase(pEntityDefNode->VGetName()))] = pEntityDef;

		IXMLNode::XMLNodeList List;
		pEntityDefNode->VGetChildren(List);
		for (auto Iter = List.begin(); Iter != List.end(); Iter++)
		{
			IXMLNode * pComponentDefNode = (*Iter).get();
			SP_LOG(2, "Adding Component")(pComponentDefNode->VGetName() );

			IBaseComponent * pComponent = cComponentFactory::Instance()->CreateComponent(cHashedString(cStringUtilities::GetInLowerCase(pComponentDefNode->VGetName())));
			SP_ASSERT_DEBUG(pComponent != NULL)(pComponentDefNode->VGetName()).SetCustomMessage("Component not Registered");
			if(pComponent != NULL)
			{
				pComponent->VInitialize(pComponentDefNode);
				pEntityDef->m_Components[pComponent->VGetID()] = pComponent;
			}
		}
	}
}

//  *******************************************************************************************************************
void cConfig::Cleanup()
{
	auto iter = m_EntityDefs.begin();
	while(iter != m_EntityDefs.end())
	{
		cEntityDef * pEntityDef = const_cast<cEntityDef *>(iter->second);
		iter++;
		SafeDelete(&pEntityDef);
	}
	m_EntityDefs.clear();
}

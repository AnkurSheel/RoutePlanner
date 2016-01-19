//  *******************************************************************************************************************
//  UiManager   version:  1.0   Ankur Sheel  date: 2014/02/20
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#include "stdafx.h"
#include "UiManager.h"
#include "UiControlFactory.h"
#include "BaseControl.hxx"
#include "GameDirectories.h"
#include "ResCache.hxx"
#include "ResourceManager.hxx"
#include "XMLNode.hxx"

using namespace Utilities;
using namespace Base;
using namespace Graphics;

//  *******************************************************************************************************************
cUiManager::cUiManager()
{
	Initialize();
}

//  *******************************************************************************************************************
cUiManager::~cUiManager()
{
	cUiControlFactory::Destroy();
}

//  *******************************************************************************************************************
void cUiManager::Initialize()
{
	cUiControlFactory::Instance()->VRegisterUiControls();
}

//  *******************************************************************************************************************
const shared_ptr<IBaseControl> cUiManager::VCreateUI(const Base::cString & fileName)
{
	shared_ptr<IBaseControl> pUi = NULL;

	SP_ASSERT_ERROR(!fileName.IsEmpty()).SetCustomMessage("FileName is empty");

	IResource * pResource = IResource::CreateResource(cGameDirectories::GetUiDirectory() + fileName +  ".xml");
	shared_ptr<IResHandle> pXMLFile = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);
	SafeDelete(&pResource);

	shared_ptr<IXMLNode> pRoot;
	if(pXMLFile != NULL)
	{
		pRoot = shared_ptr<IXMLNode>(IXMLNode::Parse(pXMLFile->GetBuffer(), pXMLFile->GetSize()));
	}

	SP_ASSERT_ERROR(pRoot != NULL).SetCustomMessage("Could not find " + fileName + " .xml");

	pUi = shared_ptr<IBaseControl>(cUiControlFactory::Instance()->CreateUiControl(cHashedString("windowcontrol")));
	pUi->VInitialize(pRoot);

	shared_ptr<IXMLNode> pControls = pRoot->VGetChild("Controls");

	IXMLNode::XMLNodeList List;
	pControls->VGetChildren(List);
	cString type;
	for (auto Iter = List.begin(); Iter != List.end(); Iter++)
	{
		shared_ptr<IXMLNode> pControlDefNode = *Iter;
		type = pControlDefNode->VGetName();
		SP_LOG(2, "Element Name")(type);

		shared_ptr<IBaseControl> pControl(cUiControlFactory::Instance()->CreateUiControl(cHashedString(cStringUtilities::GetInLowerCase(type))));

		SP_ASSERT(pControl != NULL).SetCustomMessage("Ui Control " + type + " Not Created");
		if (pControl != NULL)
		{
			pControl->VInitialize(pControlDefNode);
			pUi->VAddChildControl(pControl);
		}
	}
	return pUi;
}

//  *******************************************************************************************************************
void IUiManager::CreateAsService()
{
	cServiceLocator::GetInstance()->Register<IUiManager>(shared_ptr<IUiManager>(DEBUG_NEW cUiManager()));
}

// *****************************************************************************
//  ModelComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "ModelComponent.h"
#include "Model.hxx"
#include "TransformComponent.h"
#include "XMLNode.hxx"

using namespace Graphics;
using namespace GameBase;
using namespace Base;
using namespace Utilities;

Base::cHashedString	cModelComponent::m_Name = cHashedString("modelcomponent");

// *****************************************************************************
cModelComponent::cModelComponent()
	: m_pModel(NULL)
{
}

cModelComponent::~cModelComponent()
{
	VCleanup();
}

// *****************************************************************************
void cModelComponent::VInitialize(const IXMLNode * const pXMLNode)
{
	if(pXMLNode == NULL)
	{
		return;
	}

	cString ModelName = pXMLNode->VGetChildValue("Name");
	SP_ASSERT(!ModelName.IsEmpty()).SetCustomMessage("Element Name in Model Component cannot be empty");
	if (!ModelName.IsEmpty())
	{
		m_pModel = IModel::CreateModel(ModelName);
	}
}
// *****************************************************************************
void cModelComponent::VCleanup()
{
	SafeDelete(&m_pModel);
}

// *****************************************************************************
void cModelComponent::VSetPosition(const cVector3 & position)
{
	if(m_pModel != NULL)
	{
		//m_pModel->VRecalculateWorldMatrix(vPosition, vRotation, vSize);
	}
}

// *****************************************************************************
void cModelComponent::VSetRotation(const cVector3 & rotation)
{
}

// *****************************************************************************
void cModelComponent::VSetSize(const cVector3 & size)
{
	if(m_pModel != NULL)
	{
		//m_pModel->VRecalculateWorldMatrix(vPosition, vRotation, vSize);
	}
}

// *****************************************************************************
void cModelComponent::VRender(const ICamera * const pCamera)
{
	if(m_pModel != NULL)
	{
		m_pModel->VRender(pCamera);
	}
}
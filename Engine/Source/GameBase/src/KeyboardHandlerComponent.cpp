// *****************************************************************************
//  KeyboardHandlerComponent version:  1.0   Ankur Sheel  date: 2013/05/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "stdafx.h"
#include "KeyboardHandlerComponent.h"
#include "BaseEntity.hxx"
#include "XMLNode.hxx"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

Base::cHashedString	cKeyboardHandlerComponent::m_Name = cHashedString("keyboardhandlercomponent");

// *****************************************************************************
cKeyboardHandlerComponent::cKeyboardHandlerComponent()
{
}

// *****************************************************************************
cKeyboardHandlerComponent::~cKeyboardHandlerComponent()
{
}

// *****************************************************************************
void cKeyboardHandlerComponent::VInitialize(const IXMLNode * const pXMLNode)
{
}

// *****************************************************************************
void cKeyboardHandlerComponent::VCleanup()
{
}

// *****************************************************************************
void cKeyboardHandlerComponent::Update(const float deltaTime)
{
	m_pOwner->VHandleInput(deltaTime);
}

//  *******************************************************************************************************************
shared_ptr<IXMLNode> cKeyboardHandlerComponent::VGenerateXml() const 
{
	shared_ptr<IXMLNode> pXmlNode = IXMLNode::Create("KeyboardHandlerComponent");

	return pXmlNode;
}

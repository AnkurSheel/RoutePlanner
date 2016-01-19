//  *******************************************************************************************************************
//  ButtonControl   version:  1.0   Ankur Sheel  date: 2011/11/23
//  *******************************************************************************************************************
//	purpose 
//  *******************************************************************************************************************
#include "stdafx.h"
#include "ButtonControl.h"
#include "TextureManager.hxx"
#include "DxBase.hxx"
#include "Font.hxx"
#include "Sprite.hxx"
#include "GameDirectories.h"
#include "XMLNode.hxx"
#include "UiControlFactory.h"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

cHashedString cButtonControl::m_Name = cHashedString("buttoncontrol");

//  *******************************************************************************************************************
cButtonControl::cButtonControl()
: m_Pressed(false)
{

}

//  *******************************************************************************************************************
cButtonControl::cButtonControl(const cButtonControl & other)
	: cBaseControl(other)
	, m_pDefaultTexture(other.m_pDefaultTexture)
	, m_pPressedTexture(other.m_pPressedTexture)
	, m_Pressed(false)
	, m_pLabel(other.m_pLabel->VDuplicate())
{
	
}

//  *******************************************************************************************************************
cButtonControl::~cButtonControl()
{
}

//  *******************************************************************************************************************
void cButtonControl::VInitialize(const shared_ptr<IXMLNode const> pXMLNode) 
{
	if(pXMLNode == NULL)
	{
		return;
	}
	
	cString defaultImage = pXMLNode->VGetChildValue("DefaultImage");
	if(!defaultImage.IsEmpty() && m_pDefaultTexture == NULL)
	{
		m_pDefaultTexture = ITextureManager::GetInstance()->VGetTexture(cGameDirectories::GetSpriteDirectory() + defaultImage);
	}

	cString pressedImage = pXMLNode->VGetChildValue("PressedImage");
	if(!pressedImage.IsEmpty() && m_pPressedTexture == NULL)
	{
		m_pPressedTexture = ITextureManager::GetInstance()->VGetTexture(cGameDirectories::GetSpriteDirectory() + pressedImage);
	}

	if (m_pDefaultTexture)
	{
		m_pBGSprite = ISprite::CreateSprite();
		m_pBGSprite->VInitialize(m_pDefaultTexture);
	}

	shared_ptr<IXMLNode> pLabelControl = pXMLNode->VGetChild("LabelControl");
	if(pLabelControl != NULL)
	{
		m_pLabel = shared_ptr<IBaseControl>(cUiControlFactory::Instance()->CreateUiControl(cHashedString("labelcontrol")));
		m_pLabel->VInitialize(pLabelControl);
	}
	
	cBaseControl::VInitialize(pXMLNode);

	bool autoSize = pXMLNode->VGetChildValueAsBool("AutoSize", false);
	if(autoSize == true)
	{
		VSetSize(cVector2(m_pLabel->VGetWidth(), m_pLabel->VGetHeight()));
	}
}

//  *******************************************************************************************************************
shared_ptr<IBaseControl> cButtonControl::VDuplicate()
{
	return std::shared_ptr<IBaseControl>(DEBUG_NEW cButtonControl(*this));
}

//  *****************************************************************************************************************************
void cButtonControl::VRender(const ICamera * const pCamera)
{
	if(m_bVisible)
	{
		cBaseControl::VRender(pCamera);
		if (m_pLabel)
		{
			m_pLabel->VRender(pCamera);
		}
	}
}

//  *******************************************************************************************************************
bool cButtonControl::VOnLeftMouseButtonUp( const int X, const int Y )
{
	if(m_bIsLeftMouseDown)
	{
		SP_LOG(3, "cButtonControl :Button Released");
		m_Pressed = false;
		if(m_pDefaultTexture)
		{
			m_pBGSprite->VSetTexture(m_pDefaultTexture);
		}
		if (UIEventCallBackFn * pFn = GetCallbackFromMap(UIEVENTTYPE::BUTTONRELEASED))
		{
			stUIEventCallbackParam param;
			(*pFn)(param);
		}
		return cBaseControl::VOnLeftMouseButtonUp(X, Y);
	}
	return false;
}

//  *******************************************************************************************************************
bool cButtonControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	SP_LOG(3, "cButtonControl: Button Pressed");
	m_Pressed = true;
	if (m_pPressedTexture)
	{
		m_pBGSprite->VSetTexture(m_pPressedTexture);
	}
	if (UIEventCallBackFn * pFn = GetCallbackFromMap(UIEVENTTYPE::BUTTONPRESSED))
	{
		stUIEventCallbackParam param;
		(*pFn)(param);
	}
	return cBaseControl::VOnLeftMouseButtonDown(X, Y);
}

//  *****************************************************************************************************************************
void cButtonControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	if (m_pLabel)
	{
		float fcenterX = m_vControlAbsolutePosition.x + VGetWidth()/2.0f - m_pLabel->VGetWidth()/2.0f;
		float fcenterY = m_vControlAbsolutePosition.y + VGetHeight()/2.0f- m_pLabel->VGetHeight()/2.0f;
		m_pLabel->VSetPosition(cVector2(fcenterX, fcenterY));
	}
}

//  *********************************************************************************************************************************
void cButtonControl::VSetText(const Base::cString & strText)
{
	if(m_pLabel)
	{
		m_pLabel->VSetText(strText);
		VSetAbsolutePosition();
	}
}
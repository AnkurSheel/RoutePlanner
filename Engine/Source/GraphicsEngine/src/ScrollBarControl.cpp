#include "stdafx.h"
#include "ScrollBarControl.h"
#include "ButtonControl.h"
#include "Sprite.hxx"
#include "Structures.h"
#include "XMLNode.hxx"
#include "UiControlFactory.h"

using namespace Base;
using namespace Graphics;
using namespace Utilities;

//  *******************************************************************************************************************
cScrollBarControl::cScrollBarControl()
: m_MinPos(0)
, m_MaxPos(0)
, m_ThumbPos(0)
, m_NoOfIncrements(0)
, m_DragMode(false)
, m_pBtnThumb(NULL)
, m_pBtnDecrementArrow(NULL)
, m_pBtnIncrementArrow(NULL)
{

}

//  *******************************************************************************************************************
cScrollBarControl::~cScrollBarControl()
{
	VCleanup();
}

//  *******************************************************************************************************************
void cScrollBarControl::VInitialize(const shared_ptr<IXMLNode const> pXMLNode) 
{
	if(pXMLNode == NULL)
	{
		return;
	}

	m_MinPos = pXMLNode->VGetChildValueAsInt("MinValue", 0);
	m_MaxPos = pXMLNode->VGetChildValueAsInt("MaxValue", 0);
	m_ThumbPos = pXMLNode->VGetChildValueAsInt("InitialThumbPosition", 0) - m_MinPos;
	m_NoOfIncrements = m_MaxPos - m_MinPos;

	shared_ptr<IXMLNode> pButtonControl = pXMLNode->VGetChild("ThumbButton");
	if(pButtonControl != NULL)
	{
		m_pBtnThumb = shared_ptr<IBaseControl>(cUiControlFactory::Instance()->CreateUiControl(cHashedString("buttoncontrol")));
		m_pBtnThumb->VInitialize(pButtonControl);
	}

	pButtonControl.reset();
	pButtonControl = pXMLNode->VGetChild("DecrementButton");
	if(pButtonControl != NULL)
	{
		m_pBtnDecrementArrow = shared_ptr<IBaseControl>(cUiControlFactory::Instance()->CreateUiControl(cHashedString("buttoncontrol")));
		m_pBtnDecrementArrow->VInitialize(pButtonControl);
	}

	pButtonControl.reset();
	pButtonControl = pXMLNode->VGetChild("IncrementButton");
	if(pButtonControl != NULL)
	{
		m_pBtnIncrementArrow = shared_ptr<IBaseControl>(cUiControlFactory::Instance()->CreateUiControl(cHashedString("buttoncontrol")));
		m_pBtnIncrementArrow->VInitialize(pButtonControl);
	}

	cBaseControl::VInitialize(pXMLNode);

	m_callbackIncrementArrowPressed = bind(&cScrollBarControl::IncrementArrowPressed, this, _1);
	m_pBtnIncrementArrow->VRegisterCallBack(UIEVENTTYPE::BUTTONRELEASED, m_callbackIncrementArrowPressed);
	
	m_callbackDecrementArrowPressed = bind(&cScrollBarControl::DecrementArrowPressed, this, _1);
	m_pBtnDecrementArrow->VRegisterCallBack(UIEVENTTYPE::BUTTONRELEASED, m_callbackDecrementArrowPressed);

	m_callbackThumbPressed = bind(&cScrollBarControl::ThumbPressed, this, _1);
	m_pBtnThumb->VRegisterCallBack(UIEVENTTYPE::BUTTONPRESSED, m_callbackThumbPressed);

	m_callbackThumbReleased = bind(&cScrollBarControl::ThumbReleased, this, _1);
	m_pBtnThumb->VRegisterCallBack(UIEVENTTYPE::BUTTONRELEASED, m_callbackThumbReleased);
}

//  *******************************************************************************************************************
void cScrollBarControl::VRender(const ICamera * const pCamera)
{
	if(m_bVisible)
	{
		cBaseControl::VRender(pCamera);
	
		if (m_pBtnThumb)
		{
			m_pBtnThumb->VRender(pCamera);
		}
		if (m_pBtnDecrementArrow)
		{
			m_pBtnDecrementArrow->VRender(pCamera);
		}
		if (m_pBtnIncrementArrow)
		{
			m_pBtnIncrementArrow->VRender(pCamera);
		}
	}
}

//  *******************************************************************************************************************
bool cScrollBarControl::VOnLeftMouseButtonUp( const int X, const int Y )
{
	AppMsg msg;
	msg.m_uMsg = WM_LBUTTONUP;
	msg.m_lParam = MAKELONG(X, Y);

	if(m_pBtnIncrementArrow && m_pBtnIncrementArrow->VPostMsg(msg))
	{
		return true;
	}
	else if(m_pBtnDecrementArrow && m_pBtnDecrementArrow->VPostMsg(msg))
	{
		return true;
	}
	else if(m_pBtnThumb && m_pBtnThumb->VPostMsg(msg))
	{
		return true;
	}
	return cBaseControl::VOnLeftMouseButtonUp(X, Y);
}

//  *******************************************************************************************************************
bool cScrollBarControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	AppMsg msg;
	msg.m_uMsg = WM_LBUTTONDOWN;
	msg.m_lParam = MAKELONG(X, Y);

	if(m_pBtnIncrementArrow && m_pBtnIncrementArrow->VPostMsg(msg))
	{
		return true;
	}
	if(m_pBtnDecrementArrow && m_pBtnDecrementArrow->VPostMsg(msg))
	{
		return true;
	}
	if(m_pBtnThumb && m_pBtnThumb->VPostMsg(msg))
	{
		return true;
	}

	return cBaseControl::VOnLeftMouseButtonDown(X, Y);
}

//  *******************************************************************************************************************
void cScrollBarControl::VSetThumbPosition(const int iNewPosition)
{
	m_ThumbPos = iNewPosition;
	if (m_ThumbPos < 0)
	{
		m_ThumbPos = 0;
	}
	else if (m_ThumbPos > m_NoOfIncrements)
	{
		m_ThumbPos = m_NoOfIncrements;
	}
	if (UIEventCallBackFn * pFn = GetCallbackFromMap(UIEVENTTYPE::SCROLLBARCHANGED))
	{
		stUIEventCallbackParam param;
		param.iThumbPos = m_ThumbPos;
		(*pFn)(param);
	}
}

//  *******************************************************************************************************************
void cScrollBarControl::VCleanup()
{
	cBaseControl::VCleanup();
	
	m_pBtnDecrementArrow.reset();
	m_pBtnIncrementArrow.reset();
	m_pBtnThumb.reset();
}

//  *******************************************************************************************************************
void cScrollBarControl::IncrementArrowPressed(const stUIEventCallbackParam & params)
{
	VSetThumbPosition(m_ThumbPos + 1);
}

//  *******************************************************************************************************************
void cScrollBarControl::DecrementArrowPressed(const stUIEventCallbackParam & params)
{
	VSetThumbPosition(m_ThumbPos - 1);
}

//  *******************************************************************************************************************
void cScrollBarControl::ThumbPressed(const stUIEventCallbackParam & params)
{
	SP_LOG(3, "Drag Mode set");
	m_DragMode = true;
}

//  *******************************************************************************************************************
void cScrollBarControl::ThumbReleased(const stUIEventCallbackParam & params)
{
	SP_LOG(3, "Drag Mode unset");
	m_DragMode = false;
}

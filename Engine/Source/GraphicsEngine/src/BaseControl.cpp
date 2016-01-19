//  *******************************************************************************************************************
//  BaseControl   version:  1.0   Ankur Sheel  date: 2011/07/21
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "BaseControl.h"
#include "Sprite.hxx"
#include "Structures.h"
#include "GraphicUtils.h"
#include "XMLNode.hxx"
#include "Vector2.h"

using namespace Graphics;
using namespace Utilities;
using namespace Base;
using namespace std;

//  *******************************************************************************************************************
cBaseControl::cBaseControl()
	: m_bVisible(true)
	, m_pBGSprite(NULL)
	, m_pParentControl(NULL) 
	, m_vPosition(cVector2(-1.0f, -1.0f))
	, m_bFocus(false)
	, m_pFocusControl(NULL)
	, m_bIsLeftMouseDown(false)
	, m_bAllowMovingControls(false)
	, m_ConstrainInParent(true)
{

}

//  *******************************************************************************************************************
cBaseControl::cBaseControl(const cBaseControl & other)
	: m_bVisible(other.m_bVisible)
	, m_bFocus(false)
	, m_bAllowMovingControls(other.m_bAllowMovingControls)
	, m_bIsLeftMouseDown(false)
	, m_pFocusControl(other.m_pFocusControl)
	, m_pParentControl(other.m_pParentControl)
	, m_iMouseDownXPos(other.m_iMouseDownXPos)
	, m_iMouseDownYPos(other.m_iMouseDownYPos)
	, m_strControlName(other.m_strControlName)
	, m_ConstrainInParent(other.m_ConstrainInParent)
	, m_pBGSprite(NULL)
{
	if(other.m_pBGSprite != NULL)
	{
		m_pBGSprite = ISprite::CreateSprite();
		m_pBGSprite->VInitialize(other.m_pBGSprite->VGetTexture());
	}

	VSetPosition(other.m_vPosition);
	VSetSize(other.m_vSize);

	for(auto iter = other.m_pChildControl.begin(); iter != other.m_pChildControl.end(); iter++)
	{
		shared_ptr<IBaseControl> pTest = (*iter);
		shared_ptr<IBaseControl> pControl = pTest->VDuplicate();
		VAddChildControl(pControl);
	}
}

//  *******************************************************************************************************************
cBaseControl::~cBaseControl()
{
	VCleanup();
}

//  *******************************************************************************************************************
void cBaseControl::VInitialize(const shared_ptr<IXMLNode const> pXMLNode)
{
	if(pXMLNode == NULL)
	{
		return;
	}

	VSetControlName(pXMLNode->VGetChildValue("Name"));

	cString bgImageFileName = pXMLNode->VGetChildValue("BackGroundImage");
	if(!bgImageFileName.IsEmpty())
	{
		m_pBGSprite = ISprite::CreateSprite();
		m_pBGSprite->VInitialize(bgImageFileName);
	}

	m_ConstrainInParent = pXMLNode->VGetChildValueAsBool("ConstrainInParent", true);

	cVector2 size = pXMLNode->VGetChildValueAsVector2("ScaleInPixels", cVector2(8.0f, 8.0f));
	VSetSize(size);

	cVector2 position = pXMLNode->VGetChildValueAsVector2("Position", cVector2::Zero);
	VSetPosition(position);

	bool visible = pXMLNode->VGetChildValueAsBool("Visible", true);
	VSetVisible(visible);
}

//  *******************************************************************************************************************
void cBaseControl::Initialize(const cBaseControlDef & def)
{
	VSetControlName(def.strControlName);
	VSetPosition(def.vPosition);
	VSetSize(def.vSize);
}

//  *******************************************************************************************************************
bool cBaseControl::VPostMsg( const AppMsg & msg )
{
	if(!m_bVisible)
	{
		return false;
	}

	switch(msg.m_uMsg)
	{
	case WM_LBUTTONDOWN:
		if(IsCursorIntersect(LOWORD(msg.m_lParam), HIWORD(msg.m_lParam)))
		{
			if(!PostToAll(msg))
			{
				VOnLeftMouseButtonDown(LOWORD(msg.m_lParam), HIWORD(msg.m_lParam));
				if (AllowMovingControl() && m_pParentControl)
				{
					m_pParentControl->VMoveToFront(this);
				}
				SetFocusControl(this);
			}
			return true;
		}
		break;

	case WM_LBUTTONUP:
		if(!PostToAll(msg))
		{
			if (m_pFocusControl)
			{
				return m_pFocusControl->VOnLeftMouseButtonUp(LOWORD(msg.m_lParam), HIWORD(msg.m_lParam));
			}
		}
		break;

	case WM_MOUSEMOVE:
		if(!PostToAll(msg))
		{
			if (m_pFocusControl)
			{
				return m_pFocusControl->VOnMouseMove(LOWORD(msg.m_lParam), HIWORD(msg.m_lParam));
			}
		}
		break;

	case WM_KEYUP:
		if(!PostToAll(msg))
		{
			if(m_pFocusControl)
			{
				return m_pFocusControl->VOnKeyUp(msg.m_wParam);
			}
		}
		break;

	case WM_KEYDOWN:
		if(!PostToAll(msg))
		{
			if(m_pFocusControl)
			{
				return m_pFocusControl->VOnKeyDown(msg.m_wParam);
			}
		}
		break;

	case WM_CHAR:
		if(!PostToAll(msg))
		{
			if(m_pFocusControl)
			{
				return m_pFocusControl->VOnCharPress(msg.m_wParam);
			}
		}
		break;
	}
	return false;
}

//  *******************************************************************************************************************
void cBaseControl::VAddChildControl(shared_ptr<IBaseControl> pChildControl)
{
	shared_ptr<cBaseControl> pControl = static_pointer_cast<cBaseControl>(pChildControl);
	if (pControl)
	{
		pControl->SetParentControl(this);
		pControl->VSetAbsolutePosition();
		m_pChildControl.push_back(pControl);
	}
}

//  *******************************************************************************************************************
void cBaseControl::VRemoveAllChildren()
{
	if (m_bFocus)
	{
		m_pFocusControl = this;
	}
	for(auto iter = m_pChildControl.begin(); iter != m_pChildControl.end(); ++iter)
	{
		(*iter)->VUnRegisterAllCallBacks();
	}
	m_pChildControl.clear();
}

//  *******************************************************************************************************************
void cBaseControl::VRemoveChildControl(const cString & strControlName)
{
	ControlList::iterator iter;
	unsigned long checksum = cHashedString::CalculateChecksum(cStringUtilities::GetInLowerCase(strControlName));
	for(iter = m_pChildControl.begin(); iter != m_pChildControl.end(); ++iter)
	{
		if((*iter).get()->m_strControlName.GetHash() == checksum)
		{
			break;
		}
	}
	SP_ASSERT(iter != m_pChildControl.end())(strControlName).SetCustomMessage("Could not find Child control in Base Control");

	if(iter != m_pChildControl.end())
	{
		if ((*iter).get()->m_bFocus)
		{
			m_pFocusControl = this;
		}
		m_pChildControl.erase(iter);
	}
}

//  *******************************************************************************************************************
const shared_ptr<Graphics::IBaseControl> cBaseControl::VFindChildControl(const cString & strControlName)
{
	ControlList::const_iterator iter;
	unsigned long checksum = cHashedString::CalculateChecksum(cStringUtilities::GetInLowerCase(strControlName));
	for(iter = m_pChildControl.begin(); iter != m_pChildControl.end(); ++iter)
	{
		if((*iter).get()->m_strControlName.GetHash() == checksum)
		{
			break;
		}
	}
	SP_ASSERT(iter != m_pChildControl.end())(strControlName).SetCustomMessage("Could not find Child control in Base Control");
	if(iter == m_pChildControl.end())
	{
		return NULL;
	}
	else
	{
		return (*iter);
	}
}

//  *******************************************************************************************************************
void cBaseControl::VSetPosition( const cVector2 & vPosition )
{
	if(m_vPosition != vPosition)
	{
		m_vPosition = vPosition;
		VSetAbsolutePosition();
	}
}

//  *******************************************************************************************************************
const cVector2 cBaseControl::VGetSize() const
{
	return m_vSize;
}

//  *******************************************************************************************************************
void cBaseControl::VSetSize( const cVector2 & vSize)
{
	if (m_vSize != vSize)
	{
		m_vSize = vSize;

		if(m_pBGSprite)
		{
			m_pBGSprite->VSetSize(m_vSize);
		}
	}
}

//  *******************************************************************************************************************
void cBaseControl::VRegisterCallBack(const UIEVENTTYPE::ENUM eventType, UIEventCallBackFn fnCallback)
{
	m_CallbackMap.insert(std::make_pair(eventType, fnCallback));
}

//  *******************************************************************************************************************
void cBaseControl::VUnregisterCallBack(const UIEVENTTYPE::ENUM eventType)
{
	m_CallbackMap.erase(eventType);
}

//  *******************************************************************************************************************
void cBaseControl::VUnRegisterAllCallBacks()
{
	m_CallbackMap.clear();
}

//  *******************************************************************************************************************
void cBaseControl::VMoveToFront(const IBaseControl * const pControl )
{
	auto iter = GetChildControlIterator(pControl);
	if(iter != m_pChildControl.end() && iter != m_pChildControl.begin())
	{
		m_pChildControl.splice(m_pChildControl.begin(), m_pChildControl, iter);
	}
}

//  *******************************************************************************************************************
void cBaseControl::VSetText(const Base::cString & strText)
{
	SP_ASSERT(false).SetCustomMessage("This function should be implemented in a child class.");
}

//  *******************************************************************************************************************
bool cBaseControl::VOnLeftMouseButtonUp( const int X, const int Y )
{
	if(AllowMovingControl() && m_bIsLeftMouseDown)
	{
		SP_LOG(2, cStringUtilities::MakeFormatted("New Position - X : %f , Y : %f", m_vPosition.x, m_vPosition.y ));
	}

	m_bIsLeftMouseDown = false;
	return true;
}

//  *******************************************************************************************************************
bool cBaseControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	m_iMouseDownXPos = X - static_cast<int>(m_vControlAbsolutePosition.x);
	m_iMouseDownYPos = Y - static_cast<int>(m_vControlAbsolutePosition.y);
	m_bIsLeftMouseDown = true;
	return true;
}

//  *******************************************************************************************************************
void cBaseControl::VRender(const ICamera * const pCamera)
{
	if (!m_bVisible)
	{
		return;
	}

	if(m_pBGSprite)
	{
		m_pBGSprite->VRender(pCamera);
	}

	for(auto iter = m_pChildControl.rbegin(); iter != m_pChildControl.rend(); iter++)
	{
		(*iter)->VRender(pCamera);
	}
}

//  *******************************************************************************************************************
bool cBaseControl::VOnKeyDown(const unsigned int iCharID)
{
	if (UIEventCallBackFn * pFn = GetCallbackFromMap(UIEVENTTYPE::KEYDOWN))
	{
		stUIEventCallbackParam param;
		param.uiCharId = iCharID;
		(*pFn)(param);
	}
	return false;
}

//  *******************************************************************************************************************
bool cBaseControl::VOnKeyUp(const unsigned int iCharID)
{
	return false;
}

//  *******************************************************************************************************************
bool cBaseControl::VOnCharPress(const unsigned int iCharID)
{
	return false;
}

//  *******************************************************************************************************************
bool cBaseControl::VOnMouseMove( const int X, const int Y )
{
	if (AllowMovingControl() && m_bIsLeftMouseDown)
	{
		float x = m_vPosition.x + (X - (int)m_vControlAbsolutePosition.x) - m_iMouseDownXPos;
		float y = m_vPosition.y + (Y - (int)m_vControlAbsolutePosition.y) - m_iMouseDownYPos;
		if(m_ConstrainInParent)
		{
			ConstrainChildControl(x, y);
		}
		VSetPosition(cVector2(x, y));
		return true;
	}
	return false;
}

//  *******************************************************************************************************************
void cBaseControl::VSetAbsolutePosition()
{
	if(m_ConstrainInParent)
	{
		ConstrainChildControl(m_vPosition.x, m_vPosition.y);
	}
	m_vControlAbsolutePosition = m_vPosition;
	if (m_pParentControl)
	{
		m_vControlAbsolutePosition += m_pParentControl->m_vControlAbsolutePosition;
	}
	if (m_pBGSprite)
	{
		m_pBGSprite->VSetPosition(m_vControlAbsolutePosition);
	}

	for(auto iter = m_pChildControl.begin(); iter != m_pChildControl.end(); iter++)
	{
		(*iter)->VSetAbsolutePosition();
	}
}

//  *******************************************************************************************************************
void cBaseControl::VOnFocusChanged() 
{

}

//  *******************************************************************************************************************
void cBaseControl::VSetVisible( bool bIsVisible )
{
	m_bVisible = bIsVisible;
}

//  *******************************************************************************************************************
void cBaseControl::VCleanup()
{
	m_CallbackMap.clear();
	VRemoveAllChildren();
	SafeDelete(&m_pBGSprite);
}

//  *******************************************************************************************************************
float cBaseControl::VGetHeight() const
{
	return m_vSize.y;
}

//  *******************************************************************************************************************
float cBaseControl::VGetWidth() const
{
	return m_vSize.x;
}

//  *******************************************************************************************************************
cString cBaseControl::VGetControlName() const
{
	return m_strControlName.GetString();
}

//  *******************************************************************************************************************
void cBaseControl::VSetControlName(const cString & inControlName)
{
	m_strControlName = cHashedString(cStringUtilities::GetInLowerCase(inControlName));
}

//  *******************************************************************************************************************
bool cBaseControl::IsCursorIntersect( const float fX, const float fY )
{
	if((fX >= m_vControlAbsolutePosition.x) 
		&& (fX <= m_vControlAbsolutePosition.x + VGetWidth())
		&& (fY >= m_vControlAbsolutePosition.y)
		&& (fY <= m_vControlAbsolutePosition.y + VGetHeight()))
	{
		return true;
	}
	return false;
}

//  *******************************************************************************************************************
bool cBaseControl::PostToAll( const AppMsg & msg )
{
	for(auto iter = m_pChildControl.begin(); iter != m_pChildControl.end(); iter++)
	{
		if((*iter)->VPostMsg(msg))
		{
			return true;
		}
	}
	return false;
}

//  *******************************************************************************************************************
void cBaseControl::SetFocusControl( const cBaseControl * const pControl )
{
	if (!m_bFocus || m_pFocusControl != pControl)
	{
		if (m_pParentControl)
		{
			m_pParentControl->SetFocusControl(pControl);
		}
		else
		{
			if(m_pFocusControl)
			{
				m_pFocusControl->SetFocus(false);
			}
			m_pFocusControl = const_cast<cBaseControl *>(pControl);
		}
		SetFocus(true);
	}
}
//  *******************************************************************************************************************
void cBaseControl::SetFocus(const bool bFocus)
{
	m_bFocus = bFocus;
	VOnFocusChanged();
}

//  *******************************************************************************************************************
void cBaseControl::ConstrainChildControl(float & fX, float & fY)
{
	// constrain child control in parent control
	if (m_pParentControl)
	{
		if (fX < 0)
		{
			fX = 0; 
		}
		if ((fX + m_vSize.x) > m_pParentControl->VGetWidth())
		{
			fX = m_pParentControl->VGetWidth() - m_vSize.x; 
		}
		if (fY < 0)
		{
			fY = 0; 
		}
		if ((fY + m_vSize.y) > m_pParentControl->VGetHeight())
		{
			fY = m_pParentControl->VGetHeight() - m_vSize.y; 
		}
	}
}

//  *******************************************************************************************************************
void cBaseControl::SetParentControl( cBaseControl * pParentControl )
{
	m_pParentControl = pParentControl;
}

//  *******************************************************************************************************************
bool cBaseControl::AllowMovingControl()
{
	if (m_pParentControl)
	{
		return m_pParentControl->AllowMovingControl();
	}
	return m_bAllowMovingControls;
}

//  *******************************************************************************************************************
cBaseControl::ControlList::const_iterator cBaseControl::GetChildControlIterator(const IBaseControl * const pChildControl)
{
	ControlList::const_iterator iter;
	for(iter = m_pChildControl.begin(); iter != m_pChildControl.end(); ++iter)
	{
		if((*iter).get() == pChildControl)
		{
			break;
		}
	}
	if(iter == m_pChildControl.end())
	{
		SP_LOG_CUSTOM(AssertLevels::LEVEL_ERROR, 2, "Could not find Child control in Base Control");
	}
	return iter;
}

//  *******************************************************************************************************************
UIEventCallBackFn * cBaseControl::GetCallbackFromMap(const UIEVENTTYPE::ENUM eventType)
{
	auto iter = m_CallbackMap.find(eventType);
	if(iter != m_CallbackMap.end())
	{
		return &(iter->second);
	}
	return NULL;
}
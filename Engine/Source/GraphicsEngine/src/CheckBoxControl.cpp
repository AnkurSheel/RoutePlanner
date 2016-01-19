#include "stdafx.h"
#include "CheckBoxControl.h"
#include "Structures.h"
#include "XMLNode.hxx"
#include "UiControlFactory.h"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

cHashedString cCheckBoxControl::m_Name = cHashedString("checkboxcontrol");

//  *******************************************************************************************************************
cCheckBoxControl::cCheckBoxControl()
: m_Checked(false)
{

}

//  *******************************************************************************************************************
cCheckBoxControl::~cCheckBoxControl()
{
	VCleanup();
}		

//  *******************************************************************************************************************
void cCheckBoxControl::VInitialize(const shared_ptr<IXMLNode const> pXMLNode) 
{
	if(pXMLNode == NULL)
	{
		return;
	}

	cBaseControl::VInitialize(pXMLNode);

	float spaceCaption = pXMLNode->VGetChildValueAsFloat("SpaceCaption", 0.0f);
	m_Checked = pXMLNode->VGetChildValueAsBool("Checked", false);

	float width = spaceCaption;
	float height = 8.0f;

	shared_ptr<IXMLNode> pButtonControl = pXMLNode->VGetChild("TickBox");
	if(pButtonControl != NULL)
	{
		m_pTickBox = shared_ptr<IBaseControl>(cUiControlFactory::Instance()->CreateUiControl(cHashedString("buttoncontrol")));
		m_pTickBox->VInitialize(pButtonControl);
		width += m_pTickBox->VGetWidth();
		height = max(height, m_pTickBox->VGetHeight());
	}

	shared_ptr<IBaseControl>pLabel = NULL;
	shared_ptr<IXMLNode> pLabelControl = pXMLNode->VGetChild("LabelControl");
	if(pLabelControl != NULL)
	{
		pLabel = shared_ptr<IBaseControl>(cUiControlFactory::Instance()->CreateUiControl(cHashedString("labelcontrol")));
		pLabel->VInitialize(pLabelControl);
		VAddChildControl(pLabel);
		width += pLabel->VGetWidth();
		height = max(height, pLabel->VGetHeight());
	}

	VSetSize(cVector2(width, height));

	float fX = spaceCaption;
	if(m_pTickBox != NULL)
	{
		fX += m_pTickBox->VGetWidth();
		if (m_Checked)
		{
			m_pTickBox->VOnLeftMouseButtonDown(0, 0);
		}
		else
		{
			m_pTickBox->VOnLeftMouseButtonUp(0, 0);
		}
	}

	float fY = VGetHeight()/2.0f;
	if(pLabel != NULL)
	{
		fY += pLabel->VGetHeight()/2.0f;
		pLabel->VSetPosition(cVector2(fX, fY));
	}
}

//  *******************************************************************************************************************
shared_ptr<IBaseControl> cCheckBoxControl::VDuplicate()
{
	return std::shared_ptr<IBaseControl>(DEBUG_NEW cCheckBoxControl(*this));
}

//  *****************************************************************************************************************************
void cCheckBoxControl::VRender(const ICamera * const pCamera)
{
	if(m_bVisible)
	{
		cBaseControl::VRender(pCamera);
		if (m_pTickBox)
		{
			m_pTickBox->VRender(pCamera);
		}
	}
}

//  *******************************************************************************************************************
bool cCheckBoxControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	AppMsg msg;
	msg.m_uMsg = WM_LBUTTONDOWN;
	msg.m_lParam = MAKELONG(X, Y);

	if(m_pTickBox && m_pTickBox->VPostMsg(msg))
	{
		if (m_Checked)
		{
			m_pTickBox->VOnLeftMouseButtonUp(X, Y);
			m_Checked = false;
		}
		else
		{
			m_pTickBox->VOnLeftMouseButtonDown(X, Y);
			m_Checked = true;
		}
		if (UIEventCallBackFn * pFn = GetCallbackFromMap(UIEVENTTYPE::BUTTONPRESSED))
		{
			stUIEventCallbackParam param;
			param.bChecked = m_Checked;
			(*pFn)(param);
		}
	}
	return cBaseControl::VOnLeftMouseButtonDown(X, Y);
}

//  *******************************************************************************************************************
void cCheckBoxControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	if (m_pTickBox)
	{
		m_pTickBox->VSetPosition(m_vControlAbsolutePosition);
	}
}

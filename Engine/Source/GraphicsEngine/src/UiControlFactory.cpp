//  *******************************************************************************************************************
//  UiControlFactory   version:  1.0   Ankur Sheel  date: 2013/05/15
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#include "StdAfx.h"
#include "UiControlFactory.h"
#include "WindowControl.h"
#include "LabelControl.h"
#include "ButtonControl.h"
#include "CheckboxControl.h"
#include "HScrollBar.h"
#include "VScrollBar.h"
#include "TextBoxControl.h"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

cUiControlFactory * cUiControlFactory::m_pInstance = NULL;

//  *******************************************************************************************************************
cUiControlFactory::cUiControlFactory()
{
	
}

//  *******************************************************************************************************************
cUiControlFactory::~cUiControlFactory()
{
}

//  *******************************************************************************************************************
void cUiControlFactory::VRegisterUiControls()
{
	m_RegisteredControls.Register<cWindowControl>(cWindowControl::GetName().GetHash());
	m_RegisteredControls.Register<cLabelControl>(cLabelControl::GetName().GetHash());
	m_RegisteredControls.Register<cButtonControl>(cButtonControl::GetName().GetHash());
	m_RegisteredControls.Register<cCheckBoxControl>(cCheckBoxControl::GetName().GetHash());
	m_RegisteredControls.Register<cHScrollBar>(cHScrollBar::GetName().GetHash());
	m_RegisteredControls.Register<cVScrollBar>(cVScrollBar::GetName().GetHash());
	m_RegisteredControls.Register<cTextBoxControl>(cTextBoxControl::GetName().GetHash());
}

//  *******************************************************************************************************************
IBaseControl * cUiControlFactory::CreateUiControl(const cHashedString & Type)
{
	IBaseControl * pControl= m_RegisteredControls.Create(Type.GetHash());
	return pControl;
}

//  *******************************************************************************************************************
cUiControlFactory * cUiControlFactory::Instance() 
{ 
	if(m_pInstance == NULL)
		m_pInstance = DEBUG_NEW cUiControlFactory();
	return m_pInstance; 
}

//  *******************************************************************************************************************
void cUiControlFactory::Destroy() 
{
	SafeDelete(&m_pInstance);
}
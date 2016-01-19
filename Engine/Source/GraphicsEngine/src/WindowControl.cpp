//  *******************************************************************************************************************
//  WindowControl   version:  1.0   Ankur Sheel  date: 2011/11/21
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "WindowControl.h"
#include "Sprite.hxx"
#include "DxBase.hxx"
#include "XMLNode.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;
using namespace std;

cHashedString cWindowControl::m_Name = cHashedString("windowcontrol");

//  *******************************************************************************************************************
cWindowControl::cWindowControl()
	: m_eWindowType(cWindowControlDef::WT_DESKTOP)
{
	
}

//  *******************************************************************************************************************
cWindowControl::~cWindowControl()
{
}

void cWindowControl::VInitialize(const shared_ptr<Utilities::IXMLNode const> pXMLNode) 
{
	if(pXMLNode == NULL)
	{
		return;
	}
	
	m_eWindowType = cWindowControlDef::WT_STANDARD;

	cBaseControl::VInitialize(pXMLNode);
}

//  *******************************************************************************************************************
shared_ptr<IBaseControl> cWindowControl::VDuplicate()
{
	return std::shared_ptr<IBaseControl>(DEBUG_NEW cWindowControl(*this));
}

//  *******************************************************************************************************************
void cWindowControl::Initialize(const cWindowControlDef & def)
{
	m_bAllowMovingControls = def.bAllowMovingControls;
	m_eWindowType = def.wType;
	if(m_eWindowType != cWindowControlDef::WT_DESKTOP && !def.strBGImageFile.IsEmpty())
	{
		m_pBGSprite = ISprite::CreateSprite();
		m_pBGSprite->VInitialize(def.strBGImageFile);
	}
	cBaseControl::Initialize(def);
}

//  *******************************************************************************************************************
bool cWindowControl::VOnLeftMouseButtonUp( const int X, const int Y )
{
	if (m_eWindowType != cWindowControlDef::WT_DESKTOP)
	{
		return	cBaseControl::VOnLeftMouseButtonUp(X, Y);
	}
	return false;
}

//  *******************************************************************************************************************
bool cWindowControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	if (m_eWindowType != cWindowControlDef::WT_DESKTOP)
	{
		return cBaseControl::VOnLeftMouseButtonDown(X, Y);
	}
	return false;
}

//  *******************************************************************************************************************
bool cWindowControl::VOnMouseMove( const int X, const int Y )
{
	if (m_eWindowType != cWindowControlDef::WT_DESKTOP)
	{
		return cBaseControl::VOnMouseMove(X, Y);
	}
	return false;
}

//  *******************************************************************************************************************
void cWindowControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	if (m_pBGSprite)
	{
		m_pBGSprite->VSetPosition(m_vControlAbsolutePosition);
	}
}

//  *******************************************************************************************************************
IBaseControl * IBaseControl::CreateWindowControl(const cWindowControlDef & def)
{
	cWindowControl * pControl = DEBUG_NEW cWindowControl();
	pControl->Initialize(def);
	
	return pControl;
}
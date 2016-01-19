//  *******************************************************************************************************************
//  LabelControl   version:  1.0   Ankur Sheel  date: 2011/11/22
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#include "stdafx.h"
#include "LabelControl.h"
#include "Sentence.hxx"
#include "Sprite.hxx"
#include "XMLNode.hxx"

using namespace Base;
using namespace Utilities;
using namespace Graphics;

cHashedString cLabelControl::m_Name = cHashedString("labelcontrol");

//  *******************************************************************************************************************
cLabelControl::cLabelControl()
: m_pSentence(NULL)
{
}

//  *******************************************************************************************************************
cLabelControl::cLabelControl(const cLabelControl & other)
	: cBaseControl(other)
	, m_pSentence(NULL)
	, m_TextColor(other.m_TextColor)
	, m_FontName(other.m_FontName)
{
	if(other.m_pSentence != NULL)
	{
		m_pSentence = ISentence::CreateSentence();
		m_pSentence->VInitialize(m_FontName, other.m_pSentence->VGetText(), m_TextColor);
		m_pSentence->VSetHeight(other.m_pSentence->VGetHeight());
	}
}

//  *******************************************************************************************************************
cLabelControl::~cLabelControl()
{
	VCleanup();
}

//  *******************************************************************************************************************
void cLabelControl::VInitialize(const shared_ptr<IXMLNode const> pXMLNode) 
{
	if(pXMLNode == NULL)
	{
		return;
	}

	cBaseControl::VInitialize(pXMLNode);

	m_FontName = pXMLNode->VGetChildValue("Font");
	if(!m_FontName.IsEmpty())
	{
		cString text = pXMLNode->VGetChildValue("Text");
		float height = pXMLNode->VGetChildValueAsFloat("Height", 8.0f);

		m_TextColor = pXMLNode->VGetChildValueAsColor("TextColor", cColor::BLACK);

		m_pSentence = ISentence::CreateSentence();
		m_pSentence->VInitialize(m_FontName, text, m_TextColor);
		m_pSentence->VSetHeight(height);
	}

	bool autoSize = pXMLNode->VGetChildValueAsBool("AutoSize", false);
	
	if(m_pSentence != NULL && autoSize == true)
	{
		VSetSize(cVector2(m_pSentence->VGetWidth(), m_pSentence->VGetHeight()));
	}
}

//  *******************************************************************************************************************
shared_ptr<IBaseControl> cLabelControl::VDuplicate()
{
	return std::shared_ptr<IBaseControl>(DEBUG_NEW cLabelControl(*this));
}

//  *******************************************************************************************************************
void cLabelControl::Initialize(const cLabelControlDef & def)
{
	if(!def.strFont.IsEmpty())
	{
		m_pSentence = ISentence::CreateSentence();
		m_pSentence->VInitialize(def.strFont, def.strText, def.textColor);
		m_pSentence->VSetHeight(def.fTextHeight);
	}
	if(!def.strBGImageFile.IsEmpty())
	{
		m_pBGSprite = ISprite::CreateSprite();
		m_pBGSprite->VInitialize(def.strBGImageFile);
	}

	cBaseControl::Initialize(def);
	if(def.bAutoSize && m_pSentence != NULL)
	{
		VSetSize(cVector2(m_pSentence->VGetWidth(), m_pSentence->VGetHeight()));
	}
}

//  *******************************************************************************************************************
void cLabelControl::VRender(const ICamera * const pCamera)
{
	if(m_bVisible)
	{
		cBaseControl::VRender(pCamera);
		if (m_pSentence)
		{
			m_pSentence->VRender(pCamera);
		}
	}
}

//  *****************************************************************************************************************************
void cLabelControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	if(m_pSentence)
	{
		m_pSentence->VSetPosition(m_vControlAbsolutePosition);	
	}
}

//  *****************************************************************************************************************************
void cLabelControl::VSetText(const Base::cString & strText)
{
	if(m_pSentence != NULL)
	{
		m_pSentence->VSetText(strText);
		VSetSize(cVector2(m_pSentence->VGetWidth(strText), m_pSentence->VGetHeight()));
	}
}

//  *****************************************************************************************************************************
void cLabelControl::VCleanup()
{
	SafeDelete(&m_pSentence);
	cBaseControl::VCleanup();
}

//  *****************************************************************************************************************************
IBaseControl * IBaseControl::CreateLabelControl(const cLabelControlDef & def)
{
	cLabelControl * pControl = DEBUG_NEW cLabelControl();
	pControl->Initialize(def);
	return pControl;
}
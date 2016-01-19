//  *******************************************************************************************************************
//  TextBoxControl   version:  1.0   Ankur Sheel  date: 2011/12/01
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#include "stdafx.h"
#include "TextBoxControl.h"
#include "Sentence.hxx"
#include "DxBase.hxx"
#include "Structures.h"
#include "Sprite.hxx"
#include "Timer.hxx"
#include "XMLNode.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

cHashedString cTextBoxControl::m_Name = cHashedString("textboxcontrol");

//  *******************************************************************************************************************
cTextBoxControl::cTextBoxControl()
	: m_CaretPosInTextBox(0.0f)
	, m_pCaretSprite(NULL)
	, m_LastCaretUpdateTime(0.0f)
	, m_CaretUpdateTime(0.0f)
	, m_CaretPosInText(0)
	, m_TextBoxFull(false)
	, m_IsCaretVisible(false)
{

}

//  *******************************************************************************************************************
cTextBoxControl::~cTextBoxControl()
{
	VCleanup();
}

//  *******************************************************************************************************************
void cTextBoxControl::VInitialize(const shared_ptr<IXMLNode const> pXMLNode) 
{
	if(pXMLNode == NULL)
	{
		return;
	}	

	cString font = pXMLNode->VGetChildValue("Font");
	if(!font.IsEmpty())
	{
		cString text = pXMLNode->VGetChildValue("Text");
		float height = pXMLNode->VGetChildValueAsFloat("Height", 8.0f);

		cColor textColor = pXMLNode->VGetChildValueAsColor("TextColor", cColor::BLACK);

		m_pSentence = ISentence::CreateSentence();
		m_pSentence->VInitialize(font, text, textColor);
		m_pSentence->VSetHeight(height);

		cString CaretImageFileName = pXMLNode->VGetChildValue("CaretImage");
		if(!CaretImageFileName.IsEmpty())
		{
			m_pCaretSprite = ISprite::CreateSprite();
			m_pCaretSprite->VInitialize(CaretImageFileName);
			float caretWidth = pXMLNode->VGetChildValueAsFloat("CaretWidth", 8.0f);
			m_pCaretSprite->VSetSize(cVector2(static_cast<float>(caretWidth), height));	
		}

		m_CaretUpdateTime = pXMLNode->VGetChildValueAsFloat("CaretUpdateTime", 0.5f);
		m_pTimer = ITimer::CreateTimer();
	}
	cBaseControl::VInitialize(pXMLNode);
}

//  *******************************************************************************************************************
shared_ptr<IBaseControl> cTextBoxControl::VDuplicate()
{
	return std::shared_ptr<IBaseControl>(DEBUG_NEW cTextBoxControl(*this));
}

//  *******************************************************************************************************************
void cTextBoxControl::VRender(const ICamera * const pCamera )
{
	if(!m_bVisible)
	{
		return;
	}

	cBaseControl::VRender(pCamera);
	if (m_pSentence)
	{
		m_pSentence->VRender(pCamera);
	}
	m_pTimer->VOnUpdate();	
	m_LastCaretUpdateTime += m_pTimer->VGetDeltaTime();

	if (m_LastCaretUpdateTime >= m_CaretUpdateTime)
	{
		m_LastCaretUpdateTime = 0.0f;
		m_IsCaretVisible = !m_IsCaretVisible;
	}

	if(m_bFocus)
	{
		if(m_IsCaretVisible)
		{
			if (m_pCaretSprite)
			{
				m_pCaretSprite->VRender(pCamera);
			}
		}
	}
}

//  *******************************************************************************************************************
bool cTextBoxControl::VOnCharPress(const unsigned int CharID)
{
	cBaseControl::VOnCharPress(CharID);

	switch (CharID)
	{
	case VK_BACK:
		RemoveText(1);
		return true;

	case VK_ESCAPE:
		SetFocusControl(NULL);
		return true;

	default:
		InsertText((char *)&CharID);
		return true;
	}
	return false;
}


//  *******************************************************************************************************************
bool cTextBoxControl::VOnKeyDown(const unsigned int CharID)
{
	cBaseControl::VOnKeyDown(CharID);

	switch (CharID)
	{
	case VK_DELETE:
		if(SetCaratPosition(m_CaretPosInText + 1))
		{
			RemoveText(1);
		}
		return true;

	case VK_LEFT:
		SetCaratPosition(m_CaretPosInText - 1);
		return true;

	case VK_RIGHT:
		SetCaratPosition(m_CaretPosInText + 1);
		return true;
	}
	return false;
}

//  *********************************************************************************************************************************
void cTextBoxControl::VSetText(const Base::cString & Text)
{
	if(m_pSentence != NULL)
	{
		m_pSentence->VSetText(Text);
	}
}

//  *******************************************************************************************************************
void cTextBoxControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	if(m_pSentence)
	{
		m_pSentence->VSetPosition(m_vControlAbsolutePosition);	
	}
	SetCaratAbsolutePosition();
}

//  *****************************************************************************************************************************
void cTextBoxControl::VOnFocusChanged()
{
	if (m_bFocus)
	{
		m_pTimer->VStartTimer();
		m_IsCaretVisible = true;
		m_LastCaretUpdateTime = 0.0f;
	}
	else
	{
		m_pTimer->VStopTimer();	
		m_IsCaretVisible = false;
		if (UIEventCallBackFn * pFn = GetCallbackFromMap(UIEVENTTYPE::FOCUSLOST))
		{
			stUIEventCallbackParam param;
			param.strText = m_pSentence->VGetText();
			(*pFn)(param);
		}
	}
}

//  *****************************************************************************************************************************
void cTextBoxControl::VCleanup()
{
	cBaseControl::VCleanup();
	SafeDelete(&m_pSentence);
	SafeDelete(&m_pTimer);
	SafeDelete(&m_pCaretSprite);
}

//  *******************************************************************************************************************
bool cTextBoxControl::InsertText( const Base::cString & Text )
{
	if(!m_TextBoxFull && (GetStringWidth() + GetStringWidth(Text)) <= m_vSize.x)
	{
		cString existingText = m_pSentence->VGetText();
		existingText.Insert(m_CaretPosInText, Text);
		SetText(existingText);
		SetCaratPosition(m_CaretPosInText + Text.GetLength());
		return true;
	}
	m_TextBoxFull = true;
	return false;
}

//  *******************************************************************************************************************
void cTextBoxControl::RemoveText(const unsigned int Quantity)
{
	if(SetCaratPosition(m_CaretPosInText - Quantity))
	{
		cString text = m_pSentence->VGetText();
		text.Remove(m_CaretPosInText, Quantity);
		SetText(text);
		m_TextBoxFull = false;
	}
}

//  *******************************************************************************************************************
float cTextBoxControl::GetStringWidth()
{
	if (m_pSentence)
	{
		return m_pSentence->VGetWidth();
	}
	return 0;
}

//  *******************************************************************************************************************
float cTextBoxControl::GetStringWidth( const Base::cString & Text )
{
	if (m_pSentence)
	{
		return m_pSentence->VGetWidth(Text);
	}
	return 0;
}

//  *******************************************************************************************************************
void cTextBoxControl::SetText( const Base::cString & Text )
{
	if (m_pSentence)
	{
		m_pSentence->VSetText(Text);
	}
}

//  *******************************************************************************************************************
bool cTextBoxControl::SetCaratPosition(const unsigned int Pos )
{
	cString text = m_pSentence->VGetText();
	if (Pos <= text.GetLength())
	{
		cString subStr = text.GetSubString(0, Pos - 1);
		m_CaretPosInTextBox = GetStringWidth(subStr);
		m_CaretPosInText = Pos;
		SetCaratAbsolutePosition();
		return true;
	}
	return false;
}

//  *******************************************************************************************************************
void cTextBoxControl::SetCaratAbsolutePosition()
{
	if (m_pCaretSprite)
	{
		cVector2 vec = m_vControlAbsolutePosition;
		vec.x += m_CaretPosInTextBox;
		m_pCaretSprite->VSetPosition(vec);
	}
}
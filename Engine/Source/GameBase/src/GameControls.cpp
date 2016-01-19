// ********************************************************************************************************************
//  GameControls   version:  1.0   Ankur Sheel  date: 2013/03/19
// ********************************************************************************************************************
// 
// ********************************************************************************************************************
#include "stdafx.h"
#include "GameControls.h"
#include "XMLFileio.hxx"
#include "GameDirectories.h"

using namespace Base;
using namespace GameBase;
using namespace Utilities;

// ********************************************************************************************************************
cGameControls::cGameControls(const cString & inFileName)
	: m_KeysFile(cGameDirectories::GetMediaDirectory() + inFileName + ".dat")
{
}

// ********************************************************************************************************************
cGameControls::~cGameControls()
{
	m_KeyMap.clear();
}

// ********************************************************************************************************************
void cGameControls::SetKey(const int inKeyIndex, const unsigned int inKey)
{
	unsigned int uiPrevKey = m_KeyMap[inKeyIndex].m_KeyCode;

	// assign the new key
	m_KeyMap[inKeyIndex].m_KeyCode = inKey;

	// If any other action already had the key, reassign it to prevent unwanted behavior because of clashes
	for(auto iter = m_KeyMap.begin(); iter != m_KeyMap.end(); iter++)
	{
		if(iter->second.m_KeyCode == inKey && iter->first != inKeyIndex)
		{
			iter->second.m_KeyCode = uiPrevKey;
		}
	}
}

// ********************************************************************************************************************
cString cGameControls::GetKeyName(const unsigned int inKey) const
{
	int scanCode = MapVirtualKey(inKey, MAPVK_VK_TO_VSC);

	switch (inKey)
	{
		// arrow keys
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
	case VK_DOWN:
		// page up and page down 
	case VK_PRIOR:
	case VK_NEXT:

	case VK_HOME: 
	case VK_END: 
	case VK_INSERT:
	case VK_DELETE: 
	case VK_DIVIDE: 
	case VK_NUMLOCK:
		{
			scanCode |= 0x100; //set extended bit
			break;
		}
	}
	char keyName[50];
	GetKeyNameText(scanCode << 16,  keyName, sizeof(keyName));
	return keyName;
}

// ********************************************************************************************************************
void cGameControls::Save()
{
	IXMLFileIO * pXml = IXMLFileIO::CreateXMLFile();

	pXml->VInitializeForSave("Keys", "");
	cString strElementName;
	for(auto iter = m_KeyMap.begin(); iter != m_KeyMap.end(); iter++)
	{
		strElementName = pXml->VAddElement("Keys", "Key", cStringUtilities::MakeFormatted("%d",iter->first), "");
		pXml->VAddAttribute(strElementName, "name", iter->second.m_DisplayName);
		pXml->VAddAttribute(strElementName, "code", static_cast<int>(iter->second.m_KeyCode));
	}
	pXml->VSave(m_KeysFile);
	SafeDelete(&pXml);
}

// ********************************************************************************************************************
void cGameControls::Load()
{
	DWORD attr = GetFileAttributes(m_KeysFile.GetData());
	if (attr == INVALID_FILE_ATTRIBUTES)
	{
		VSetDefaults();
		Save();
	}
	else
	{
		IXMLFileIO	* pXml = IXMLFileIO::CreateXMLFile();
		pXml->VLoad(m_KeysFile);
		m_KeyMap.clear();
		std::vector<cString> vKeyIDs;
		pXml->VGetAllChildrenNames("Keys", vKeyIDs);

		stGameControl gameControl;
		for(auto iter = vKeyIDs.begin(); iter != vKeyIDs.end(); iter++)
		{
			cString strKeyID = (*iter);
			int iKeyIndex = pXml->VGetNodeAttributeAsInt(strKeyID, "id");
			gameControl.m_DisplayName = pXml->VGetNodeAttribute(strKeyID, "name");
			gameControl.m_KeyCode = pXml->VGetNodeAttributeAsInt(strKeyID, "code");

			m_KeyMap.insert(std::make_pair(iKeyIndex, gameControl));
		}
		SafeDelete(&pXml);
	}
}
//  *******************************************************************************************************************
unsigned int GameBase::cGameControls::GetKeyCode(const unsigned int index) const
{
	return m_KeyMap.at(index).m_KeyCode;
}

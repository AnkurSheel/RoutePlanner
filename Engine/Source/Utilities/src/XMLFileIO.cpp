#include "stdafx.h"
#include "XMLFileIO.h"
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace Base;
using namespace Utilities;

//  *******************************************************************************************************************
cXMLFileIO::cXMLFileIO()
	: m_pDoc(NULL)
{
}

//  *******************************************************************************************************************
cXMLFileIO::~cXMLFileIO()
{
	SafeDelete(&m_pDoc);
	m_ElementMap.clear();
}

//  *******************************************************************************************************************
void cXMLFileIO::VInitializeForSave(const cString & strRootName, const cString & strStyleSheetPath)
{
	SafeDelete(&m_pDoc);
	m_pDoc = DEBUG_NEW XMLDocument();

	m_pDoc->InsertEndChild(m_pDoc->NewDeclaration(NULL));

	if (!strStyleSheetPath.IsEmpty())
	{
		cString str = "xml-stylesheet type=\"text/xsl\" href=\"" + strStyleSheetPath + "\"";
		m_pDoc->InsertEndChild(m_pDoc->NewDeclaration(str.GetData()));
	}
	XMLElement * pRoot = m_pDoc->NewElement(strRootName.GetData());  
	m_pDoc->InsertEndChild(pRoot);

	m_ElementMap.insert(std::make_pair(strRootName.GetData(), pRoot));
}

//  *******************************************************************************************************************
void cXMLFileIO::VLoad(const cString & strFilePath, cString & strRootName)
{
	VLoad(strFilePath);
	strRootName = m_pDoc->RootElement()->Value();
}

//  *******************************************************************************************************************
void cXMLFileIO::VLoad(const cString & strFilePath)
{
	SP_LOG(3, "loading XML file ")(strFilePath);
	SafeDelete(&m_pDoc);
	m_pDoc = DEBUG_NEW XMLDocument();
	int error = m_pDoc->LoadFile(strFilePath.GetData());
	SP_ASSERT_ERROR(error == XML_NO_ERROR)(strFilePath).SetCustomMessage("Could not load XML file");

	XMLElement * pRoot = m_pDoc->FirstChildElement();
	m_ElementMap.insert(std::make_pair(pRoot->Name(), pRoot));

	AddChildElements(pRoot);
}

//  *******************************************************************************************************************
void cXMLFileIO::VParse(const cString & strXML, const unsigned int size)
{
	SP_LOG(3, "Parsing XML file ");
	SafeDelete(&m_pDoc);
	m_pDoc = DEBUG_NEW XMLDocument();
	int error = m_pDoc->Parse(strXML.GetData(), size);
	SP_ASSERT_ERROR(error == XML_NO_ERROR)(m_pDoc->GetErrorStr1())(m_pDoc->GetErrorStr2()).SetCustomMessage("Could not parse XML file");

	XMLElement * pRoot = m_pDoc->FirstChildElement();
	m_ElementMap.insert(std::make_pair(pRoot->Name(), pRoot));

	AddChildElements(pRoot);
}

//  *******************************************************************************************************************
void cXMLFileIO::VSave(const cString & strFilePath)
{
	m_pDoc->SaveFile(strFilePath.GetData());
}

//  *******************************************************************************************************************
cString cXMLFileIO::VAddElement(const cString & strParentName, const cString & strElementName,
	const cString & strElementAttribID, const cString & strElementValue)
{
	XMLElement * pElement = m_pDoc->NewElement(strElementName.GetData());
	if (!strElementAttribID.IsEmpty())
	{
		pElement->SetAttribute("id", strElementAttribID.GetData());
	}

	if (!strElementValue.IsEmpty())
	{
		XMLText * pText = m_pDoc->NewText(strElementValue.GetData());
		pElement->InsertEndChild(pText);
	}

	auto curr = m_ElementMap.find(strParentName);
	XMLElement * pParentElement = const_cast<XMLElement*> (curr->second);
	pParentElement->LinkEndChild(pElement);

	cString strID;
	GetUniqueNameForMap(pElement, strID);
	m_ElementMap.insert(std::make_pair(strID, pElement));
	return strID;
}

//  *******************************************************************************************************************
void cXMLFileIO::VAddAttribute(const cString & strElementName, const cString & strAttributeName,
	const cString & strAttributeValue)
{
	auto curr = m_ElementMap.find(strElementName);
	const_cast<XMLElement*> (curr->second)->SetAttribute(strAttributeName.GetData(), strAttributeValue.GetData());
}

//  *******************************************************************************************************************
void cXMLFileIO::VAddAttribute(const cString & strElementName, const cString & strAttributeName, const int iAttributeValue)
{
	auto curr = m_ElementMap.find(strElementName);
	const_cast<XMLElement*> (curr->second)->SetAttribute(strAttributeName.GetData(), iAttributeValue);
}

//  *******************************************************************************************************************
void cXMLFileIO::VAddAttribute(const cString & strElementName, const cString & strAttributeName, const bool bAttributeValue)
{
	auto curr = m_ElementMap.find(strElementName);
	const_cast<XMLElement*> (curr->second)->SetAttribute(strAttributeName.GetData(), bAttributeValue);
}

//  *******************************************************************************************************************
void cXMLFileIO::VAddComment(const cString & strParentElementID, const cString & strComment)
{
	auto curr = m_ElementMap.find(strParentElementID);
	XMLElement * pElement = const_cast<XMLElement*> (curr->second);
	pElement->InsertEndChild(m_pDoc->NewComment(strComment.GetData()));
}

//  *******************************************************************************************************************
void cXMLFileIO::VGetAllChildrenNames(const cString & strParentID, std::vector<cString> & vElements)
{
	auto curr = m_ElementMap.find(strParentID);
	const XMLElement * pParentElement = curr->second;
	const XMLElement *pElement = pParentElement->FirstChildElement();

	cString strId;
	while(pElement)
	{
		GetUniqueNameForMap(pElement, strId);
		vElements.push_back(strId);
		pElement = pElement->NextSiblingElement();
	}
}

//  *******************************************************************************************************************
cString cXMLFileIO::VGetNodeValue(const cString & strElementID)
{
	auto curr = m_ElementMap.find(strElementID);
	if (curr == m_ElementMap.end())
	{
		SP_ASSERT_WARNING(false)(strElementID).SetCustomMessage("Could not find element");
		return "";
	}
	XMLElement * pElem = const_cast<XMLElement*> (curr->second);
	return(pElem->GetText());
}

//  *******************************************************************************************************************
cString cXMLFileIO::VGetNodeAttribute(const cString & strElementID, const cString & strAttributeName)
{
	auto curr = m_ElementMap.find(strElementID);
	SP_ASSERT_WARNING(curr != m_ElementMap.end())(strAttributeName)(strElementID).SetCustomMessage("Could not find attribute");
	if (curr != m_ElementMap.end())
	{
		return (curr->second->Attribute(strAttributeName.GetData()));
	}
	return "";
}

//  *******************************************************************************************************************
int cXMLFileIO::VGetNodeAttributeAsInt(const cString & strElementID, const cString & strAttributeName)
{
	cString strAttributeValue = VGetNodeAttribute(strElementID, strAttributeName);
	tOptional<int> val = strAttributeValue.ToInt();
	SP_ASSERT_WARNING(val.IsValid())(strAttributeName)(strElementID).SetCustomMessage("Error in getting attribute as int");
	if(val.IsInvalid())
	{
		return 0;
	}
	return val.GetValue();
}

//  *******************************************************************************************************************
bool cXMLFileIO::VGetNodeAttributeAsBool(const cString & strElementID, const cString & strAttributeName)
{
	cString strAttributeValue = VGetNodeAttribute(strElementID, strAttributeName);
	tOptional<bool> val = strAttributeValue.ToBool();
	SP_ASSERT_WARNING(val.IsValid())(strAttributeName)(strElementID).SetCustomMessage("Error in getting attribute as bool");
	if(val.IsInvalid())
	{
		return false;
	}
	return val.GetValue();
}

//  *******************************************************************************************************************
cString cXMLFileIO::GetNodeName(const cString & strParent, const int iIndex)
{
	XMLElement *pElem;

	auto curr = m_ElementMap.find(strParent);
	XMLElement *pParent =const_cast<XMLElement*> (curr->second);
	pElem = pParent->FirstChildElement();
	for(int i=0;i<iIndex;i++)
	{
		pElem = pElem->NextSiblingElement();
	}
	return(pElem->Value());
}

//  *******************************************************************************************************************
void cXMLFileIO::AddChildElements(XMLElement * const pParent)
{
	XMLElement * pElement = pParent->FirstChildElement();
	if(pElement == NULL)
	{
		return;
	}

	cString strName;
	while(pElement)
	{
		strName = cString(pElement->Value()) + pElement->Attribute("id");

		auto itr = m_ElementMap.insert(std::make_pair(strName, pElement));
		SP_ASSERT_WARNING(itr != m_ElementMap.end())(strName).SetCustomMessage("Duplicate element name");

		AddChildElements(pElement);
		pElement = pElement->NextSiblingElement();
	}
}

//  *******************************************************************************************************************
void cXMLFileIO::GetUniqueNameForMap(const XMLElement * const pElement, cString & strName)
{
	strName = cString(pElement->Value()) + pElement->Attribute("id");
}

//  *******************************************************************************************************************
IXMLFileIO * IXMLFileIO::CreateXMLFile()
{
	cXMLFileIO* pXMLFile= DEBUG_NEW cXMLFileIO();
	return pXMLFile;
}

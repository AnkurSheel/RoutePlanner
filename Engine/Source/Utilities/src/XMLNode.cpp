//  *******************************************************************************************************************
//  XMLNode   version:  1.0   Ankur Sheel  date: 2013/05/02
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#include "stdafx.h"
#include "XMLNode.h"
#include "tinyxml2.h"
#include "vector2.h"
#include "vector3.h"
#include "Color.h"

using namespace tinyxml2;
using namespace Base;
using namespace Utilities;

//  *******************************************************************************************************************
cXMLNode::cXMLNode()
	: m_pDoc(NULL)
	, m_pElement(NULL)
{
}

//  *******************************************************************************************************************
cXMLNode::~cXMLNode()
{
	m_ChildNodes.clear();
	m_pElement = NULL;
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> cXMLNode::InitializeForSave(const cString & RootName, const cString & StyleSheetPath)
{
	const shared_ptr<cXMLNode> pNode(DEBUG_NEW cXMLNode());
	pNode->m_pDoc = shared_ptr<XMLDocument>(DEBUG_NEW XMLDocument());

	pNode->m_pDoc->InsertEndChild(pNode->m_pDoc->NewDeclaration(NULL));

	if (!StyleSheetPath.IsEmpty())
	{
		cString str = "xml-stylesheet type=\"text/xsl\" href=\"" + StyleSheetPath + "\"";
		pNode->m_pDoc->InsertEndChild(pNode->m_pDoc->NewDeclaration(str.GetData()));
	}
	pNode->m_pElement = pNode->m_pDoc->NewElement(RootName.GetData());  
	pNode->m_pDoc->InsertEndChild(pNode->m_pElement);

	return pNode;
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> cXMLNode::Load(const cString & FilePath)
{
	SP_LOG(3, "Loading XML file")(FilePath);
	const shared_ptr<cXMLNode> pNode(DEBUG_NEW cXMLNode());

	pNode->m_pDoc = shared_ptr<XMLDocument>(DEBUG_NEW XMLDocument());
	int error = pNode->m_pDoc->LoadFile(FilePath.GetData());
	SP_ASSERT_ERROR(error == XML_NO_ERROR)(FilePath).SetCustomMessage("Could not load XML file");

	pNode->m_pElement = pNode->m_pDoc->FirstChildElement();

	pNode->AddChildElements();
	return pNode;
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> cXMLNode::Parse(const cString & XML, const unsigned int Size)
{
	SP_LOG(3, "Parsing XML file ");
	const shared_ptr<cXMLNode> pNode(DEBUG_NEW cXMLNode());

	pNode->m_pDoc = shared_ptr<XMLDocument>(DEBUG_NEW XMLDocument());
	int error = pNode->m_pDoc->Parse(XML.GetData(), Size);
	SP_ASSERT_ERROR(error == XML_NO_ERROR)(pNode->m_pDoc->GetErrorStr1())(pNode->m_pDoc->GetErrorStr2()).SetCustomMessage("Could not parse XML file");

	pNode->m_pElement = pNode->m_pDoc->FirstChildElement();

	pNode->AddChildElements();
	return pNode;
}

//  *******************************************************************************************************************
void cXMLNode::VSave(const cString & FilePath)
{
	m_pDoc->SaveFile(FilePath.GetData());
}

//  *******************************************************************************************************************
const weak_ptr<IXMLNode> cXMLNode::VAddElement(const cString & ElementName, const cString & ElementValue)
{
	const shared_ptr<cXMLNode> pNode(DEBUG_NEW cXMLNode());
	pNode->m_pElement = m_pDoc->NewElement(ElementName.GetData());
	pNode->m_pDoc = m_pDoc;

	if (!ElementValue.IsEmpty())
	{
		XMLText * pText = m_pDoc->NewText(ElementValue.GetData());
		pNode->m_pElement->InsertEndChild(pText);
	}

	m_pElement->LinkEndChild(pNode->m_pElement);
	m_ChildNodes.push_back(pNode);
	return pNode;
}

//  *******************************************************************************************************************
void cXMLNode::VAddChild(shared_ptr<IXMLNode> pNode)
{
	shared_ptr<cXMLNode> pXmlNode = dynamic_pointer_cast<cXMLNode>(pNode);
	if (pXmlNode != NULL)
	{
		DeepClone(shared_from_this(), pXmlNode);
	}
}

//  *******************************************************************************************************************
cVector3 cXMLNode::VGetChildValueAsVector3(const cString & Name, const cVector3 & DefaultValue) const
{
	shared_ptr<IXMLNode> pNode(VGetChild(Name));
	if(pNode != NULL)
	{
		cVector3 val;
		val.x = pNode->VGetNodeAttributeAsFloat("x", DefaultValue.x);
		val.y = pNode->VGetNodeAttributeAsFloat("y", DefaultValue.y);
		val.z = pNode->VGetNodeAttributeAsFloat("z", DefaultValue.z);
		return val;
	}
	return DefaultValue;
}

//  *******************************************************************************************************************
void cXMLNode::VAddComment(const cString & Comment)
{
	m_pElement->InsertEndChild(m_pDoc->NewComment(Comment.GetData()));
}

//  *******************************************************************************************************************
void cXMLNode::VAddAttribute(const cString & AttributeName, const cString & AttributeValue)
{
	m_pElement->SetAttribute(AttributeName.GetData(), AttributeValue.GetData());
}

//  *******************************************************************************************************************
void cXMLNode::VAddAttribute(const cString & AttributeName, const int AttributeValue)
{
	m_pElement->SetAttribute(AttributeName.GetData(), AttributeValue);
}

//  *******************************************************************************************************************
void cXMLNode::VAddAttribute(const cString & AttributeName, const bool AttributeValue)
{
	m_pElement->SetAttribute(AttributeName.GetData(), AttributeValue);
}

//  *******************************************************************************************************************
cString cXMLNode::VGetName() const
{
	return m_pElement->Name();
}

//  *******************************************************************************************************************
cString cXMLNode::VGetNodeValue() const
{
	return (m_pElement->GetText());
}

//  *******************************************************************************************************************
cString cXMLNode::VGetNodeAttribute(const cString & AttributeName) const
{
	return m_pElement->Attribute(AttributeName.GetData());
}

//  *******************************************************************************************************************
tOptional<int> cXMLNode::VGetNodeAttributeAsInt(const cString & AttributeName) const
{
	cString AttributeValue = VGetNodeAttribute(AttributeName);
	tOptional<int> val = AttributeValue.ToInt();
	SP_ASSERT_WARNING(val.IsValid())(AttributeName)(m_pElement->Name()).SetCustomMessage("Error in getting attribute as int");
	return val;
}

//  *******************************************************************************************************************
int cXMLNode::VGetNodeAttributeAsInt(const cString & AttributeName, const int defaultValue) const
{
	cString AttributeValue = VGetNodeAttribute(AttributeName);
	tOptional<int> val = AttributeValue.ToInt();
	if(val.IsInvalid())
	{
		return defaultValue;
	}
	return val.GetValue();
}

//  *******************************************************************************************************************
tOptional<bool> cXMLNode::VGetNodeAttributeAsBool(const cString & AttributeName) const
{
	cString AttributeValue = VGetNodeAttribute(AttributeName);
	tOptional<bool> val = AttributeValue.ToBool();
	SP_ASSERT_WARNING(val.IsValid())(AttributeName)(m_pElement->Name()).SetCustomMessage("Error in getting attribute as bool");
	return val;
}

//  *******************************************************************************************************************
bool cXMLNode::VGetNodeAttributeAsBool(const cString & AttributeName, const bool defaultValue) const
{
	cString AttributeValue = VGetNodeAttribute(AttributeName);
	tOptional<bool> val = AttributeValue.ToBool();
	if(val.IsInvalid())
	{
		return defaultValue;
	}
	return val.GetValue();
}

//  *******************************************************************************************************************
tOptional<float> cXMLNode::VGetNodeAttributeAsFloat(const cString & AttributeName) const
{
	cString AttributeValue = VGetNodeAttribute(AttributeName);
	tOptional<float> val = AttributeValue.ToFloat();
	SP_ASSERT_WARNING(val.IsValid())(AttributeName)(m_pElement->Name()).SetCustomMessage("Error in getting attribute as float");
	return val;
}

//  *******************************************************************************************************************
float cXMLNode::VGetNodeAttributeAsFloat(const cString & AttributeName, const float DefaultValue) const
{
	cString AttributeValue = VGetNodeAttribute(AttributeName);
	tOptional<float> val = AttributeValue.ToFloat();
	if(val.IsInvalid())
	{
		return DefaultValue;
	}
	return val.GetValue();
}

//  *******************************************************************************************************************
void cXMLNode::VGetChildren(XMLNodeList & ChildrenList) const
{
	ChildrenList = m_ChildNodes;
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> cXMLNode::VGetChild(const cString & Name) const
{
	shared_ptr<IXMLNode> pNode;
	for(auto Iter = m_ChildNodes.begin(); Iter != m_ChildNodes.end(); Iter++)
	{
		pNode = (*Iter);
		if(Name.CompareInsensitive(pNode->VGetName()) == 0)
		{
			return pNode;
		}
	}
	return NULL;
}

//  *******************************************************************************************************************
cString cXMLNode::VGetChildValue(const cString & Name) const
{
	cString value;
	shared_ptr<IXMLNode> pNode(VGetChild(Name));
	if(pNode != NULL)
	{
		value = pNode->VGetNodeValue();
	}
	return value;
}

//  *******************************************************************************************************************
tOptional<int> cXMLNode::VGetChildValueAsInt(const cString & Name) const
{
	cString Value = VGetChildValue(Name);
	tOptional<int> val = Value.ToInt();
	SP_ASSERT_WARNING(val.IsValid())(Name)(m_pElement->Name()).SetCustomMessage("Error in getting value as int");
	return val;
}

//  *******************************************************************************************************************
int cXMLNode::VGetChildValueAsInt(const cString & Name, const int DefaultValue) const
{
	cString Value = VGetChildValue(Name);
	tOptional<int> val = VGetChildValueAsInt(Name);
	if(val.IsInvalid())
	{
		return DefaultValue;
	}
	return val.GetValue();
}

//  *******************************************************************************************************************
tOptional<float> cXMLNode::VGetChildValueAsFloat(const cString & Name) const 
{
	cString Value = VGetChildValue(Name);
	tOptional<float> val = Value.ToFloat();
	SP_ASSERT_WARNING(val.IsValid())(Name)(m_pElement->Name()).SetCustomMessage("Error in getting value as float");
	return val;
}

//  *******************************************************************************************************************
float cXMLNode::VGetChildValueAsFloat(const cString & Name, const float DefaultValue) const
{
	tOptional<float> val = VGetChildValueAsFloat(Name);
	if(val.IsInvalid())
	{
		return DefaultValue;
	}
	return val.GetValue();
}

//  *******************************************************************************************************************
tOptional<bool> cXMLNode::VGetChildValueAsBool(const cString & Name) const
{
	cString Value = VGetChildValue(Name);
	tOptional<bool> val = Value.ToBool();
	SP_ASSERT_WARNING(val.IsValid())(Name)(m_pElement->Name()).SetCustomMessage("Error in getting value as bool");
	return val;
}

//  *******************************************************************************************************************
bool cXMLNode::VGetChildValueAsBool(const cString & Name, const bool DefaultValue) const
{
	tOptional<bool> val = VGetChildValueAsBool(Name);
	if(val.IsInvalid())
	{
		return DefaultValue;
	}
	return val.GetValue();
}

//  *******************************************************************************************************************
cVector2 cXMLNode::VGetChildValueAsVector2(const cString & Name, const cVector2 & DefaultValue) const
{
	shared_ptr<IXMLNode> pNode(VGetChild(Name));
	if(pNode != NULL)
	{
		cVector2 val;
		val.x = pNode->VGetNodeAttributeAsFloat("x", DefaultValue.x);
		val.y = pNode->VGetNodeAttributeAsFloat("y", DefaultValue.y);
		return val;
	}
	return DefaultValue;
}

//  *******************************************************************************************************************
Base::cColor cXMLNode::VGetChildValueAsColor(const Base::cString & Name, const Base::cColor & DefaultValue) const
{
	shared_ptr<IXMLNode> pNode(VGetChild(Name));
	if(pNode != NULL)
	{
		cColor val;
		val.m_Red = pNode->VGetNodeAttributeAsInt("r", 0);
		val.m_Blue = pNode->VGetNodeAttributeAsInt("b", 0);
		val.m_Green = pNode->VGetNodeAttributeAsInt("g", 0);
		val.m_Alpha = pNode->VGetNodeAttributeAsInt("a", 255);
		return val;
	}
	return DefaultValue;
}

//  *******************************************************************************************************************
cString cXMLNode::VToString() const
{
	XMLPrinter printer;
	m_pDoc->Accept(&printer);

	return printer.CStr();
}

//  *******************************************************************************************************************
void cXMLNode::AddChildElements()
{
	XMLElement * pElement = m_pElement->FirstChildElement();

	while(pElement)
	{
		const shared_ptr<cXMLNode> pNode(DEBUG_NEW cXMLNode());
		pNode->m_pElement = pElement;

		m_ChildNodes.push_back(pNode);	
		pNode->AddChildElements();
		pElement = pElement->NextSiblingElement();
	}
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> IXMLNode::InitializeForSave(const cString & RootName, const cString & StyleSheetPath)
{
	return cXMLNode::InitializeForSave(RootName, StyleSheetPath);
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> IXMLNode::Load(const cString & FilePath)
{
	return cXMLNode::Load(FilePath);
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> IXMLNode::Parse(const cString & XML, const unsigned int Size)
{
	return cXMLNode::Parse(XML, Size);
}

//  *******************************************************************************************************************
const shared_ptr<IXMLNode> IXMLNode::Create(const Base::cString & RootName)
{
	const shared_ptr<cXMLNode> pNode(DEBUG_NEW cXMLNode());
	pNode->m_pDoc = shared_ptr<XMLDocument>(DEBUG_NEW XMLDocument());

	pNode->m_pElement = pNode->m_pDoc->NewElement(RootName.GetData());  
	pNode->m_pDoc->InsertEndChild(pNode->m_pElement);

	return pNode;
}

//  *******************************************************************************************************************
void cXMLNode::DeepClone(const shared_ptr<IXMLNode> pDestination, const shared_ptr<IXMLNode> pSource)
{
	const shared_ptr<cXMLNode> pCopy(DEBUG_NEW cXMLNode());
	pCopy->m_pDoc = m_pDoc;

	const shared_ptr<cXMLNode> pDestinationNode = dynamic_pointer_cast<cXMLNode>(pDestination);
	const shared_ptr<cXMLNode> pSourceNode = dynamic_pointer_cast<cXMLNode>(pSource);

	pCopy->m_pElement = dynamic_cast<XMLElement*>(pSourceNode->m_pElement->ShallowClone(m_pDoc.get()));
	if (pSourceNode->m_ChildNodes.size() > 0)
	{
		for (auto iter = pSourceNode->m_ChildNodes.begin(); iter != pSourceNode->m_ChildNodes.end(); iter++)
		{
			DeepClone(pCopy, dynamic_pointer_cast<cXMLNode>(*iter));
		}
	}
	else
	{
		XMLNode * pChildNode = pSourceNode->m_pElement->FirstChild();

		while(pChildNode)
		{
			XMLNode * pCopiedChildNode = pChildNode->ShallowClone(pCopy->m_pDoc.get());
			pCopy->m_pElement->LinkEndChild(pCopiedChildNode);
			pChildNode = pChildNode->NextSiblingElement();
		}
	}
	pDestinationNode->m_pElement->LinkEndChild(pCopy->m_pElement);
	pDestinationNode->m_ChildNodes.push_back(pCopy);
}

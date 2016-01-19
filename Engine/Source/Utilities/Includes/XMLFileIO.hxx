// *****************************************************************************
//  XMLFileIO   version:  1.0   Ankur Sheel  date: 2011/02/01
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef XMLFileIO_hxx__
#define XMLFileIO_hxx__

namespace Base
{
	class cString;
}

namespace Utilities
{
	class IXMLFileIO
	{
	public:
		virtual ~IXMLFileIO(){};
		/********************************************//**
		 * @param[in] strRootName The name of the root element
		 * @param[in] strStyleSheetPath The stylesheet associated with this xml. Can be NULL
		 *
		 * Creates the header XML and adds the root element
		 ***********************************************/
		virtual void VInitializeForSave(const Base::cString & strRootName,
			const Base::cString & strStyleSheetPath) = 0;
		/********************************************//**
		 * @param[in] strFilePath The path for the XML file to be save
		 *
		 * Saves the XML file
		 ***********************************************/
		virtual void VSave(const Base::cString & strFilePath) = 0;
		/********************************************//**
		 * @param[in] strFilePath The path for the XML file to be loaded
		 *
		 * Loads the XML file
		 ***********************************************/
		virtual void VLoad(const Base::cString & strFilePath) = 0;
		/********************************************//**
		 * @param[in] strFilePath The path for the XML file to be loaded
		 * @param[out] strRootName the name of the root in the xml
		 *
		 * Loads the XML file
		 ***********************************************/
		virtual void VLoad(const Base::cString & strFilePath, Base::cString & strRootName) = 0;
		/********************************************//**
		 * @param[in] strXML The xml string
		 * @param[in] size the size of the the string
		 *
		 * Parses an XML file from a character string
		 ***********************************************/
		virtual void VParse(const Base::cString & strXML, const unsigned int size) = 0;
		/********************************************//**
		 * @param[in] strParentElementID The ID of the parent element
		 * @param[in] strComment The comment text
		 *
		 * Adds a comment under the parent specified by the strParentElementName
		 ***********************************************/
		virtual void VAddComment(const Base::cString & strParentElementID,
			const Base::cString & strComment) = 0;
		/********************************************//**
		 * @param[in] strParentName The parent of the element
		 * @param[in] strElementAttribID The unique ID associated with the element. Will be added as an attribute
		 * @param[in] strElementName The name of the element
		 * @param[in] strElementValue The value associated with the element
		 * @return Returns the name with which this element can be accessed
		 *
		 * Adds a element under the parent specified by the strParentElementName
		 ***********************************************/
		virtual Base::cString VAddElement(const Base::cString & strParentName, 
			const Base::cString & strElementName, const Base::cString & strElementAttribID,
			const Base::cString & strElementValue) = 0;
		/********************************************//**
		 * @param[in] strElementName The name of the element
		 * @param[in] strAttributeName The attribute name
		 * @param[in] strAttributeValue The value of the attribute
		 *
		 * Adds a attribute for the element specified by the strElementName
		 ***********************************************/
		virtual void VAddAttribute(const Base::cString & strElementName,
			const Base::cString & strAttributeName, 
			const Base::cString & strAttributeValue) = 0;
		/********************************************//**
		 * @param[in] strElementName The name of the element
		 * @param[in] strAttributeName The attribute name
		 * @param[in] iAttributeValue The integer value of the attribute
		 *
		 * Adds a attribute for the element specified by the strElementName
		 ***********************************************/
		virtual void VAddAttribute(const Base::cString & strElementName,
			const Base::cString & strAttributeName, const int iAttributeValue) = 0;
		/********************************************//**
		 * @param[in] strElementName The name of the element
		 * @param[in] strAttributeName The attribute name
		 * @param[in] bAttributeValue The boolean value of the attribute
		 *
		 * Adds a attribute for the element specified by the strElementName
		 ***********************************************/
		virtual void VAddAttribute(const Base::cString & strElementName,
			const Base::cString & strAttributeName, const bool bAttributeValue) = 0;
		/********************************************//**
		 * @param[in] strElementID The unique ID of the element
		 * @param[in] strAttributeName The attribute name
		 * @return The value of the attribute
		 *
		 * Given an attribute name for an element with unique name strElementID,
		 * this functions stores the value for the attribute of that name,
		 * in strElementValue
		 ***********************************************/
		virtual Base::cString VGetNodeAttribute(const Base::cString & strElementID,
			const Base::cString & strAttributeName) = 0;
		/********************************************//**
		 * @param[in] strElementID The unique id of the element
		 * @return The value associated with the element
		 *
		 * Given an element with unique name strElementID, this functions 
		 * returns the value associated with it
		 ***********************************************/
		virtual Base::cString VGetNodeValue(const Base::cString & strElementID) = 0;
		/********************************************//**
		 * @param[in] strElementID The unique ID of the element
		 * @param[in] strAttributeName The attribute name
		 * @return The integer value of the attribute 
		 *
		 * Given an attribute name for an element with unique name strElementID,
		 * this functions converts the value for the attribute of that name into an
		 * int and returns it
		 ***********************************************/
		virtual int VGetNodeAttributeAsInt(const Base::cString & strElementID,
			const Base::cString & strAttributeName) = 0;
		/********************************************//**
		 * @param[in] strElementID The unique ID of the element
		 * @param[in] strAttributeName The attribute name
		 * @return The bool value of the attribute 
		 *
		 * Given an attribute name for an element with unique name strElementID,
		 * this functions converts the value for the attribute of that name into an,
		 * bool and returns it
		 ***********************************************/
		virtual bool VGetNodeAttributeAsBool(const Base::cString & strElementID,
			const Base::cString & strAttributeName) = 0;
		/********************************************//**
		 * @param[in] strParentID The unique id of the parent element
		 * @param[out] vElements The vector in which all the child elements unique names are stored 
		 *
		 * For a element with unique name strParentID, gets the unique names for
		 * all its children and stores it in vElements
		 ***********************************************/
		virtual void VGetAllChildrenNames(const Base::cString & strParentID,
			std::vector<Base::cString> & vElements ) = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		UTILITIES_API static IXMLFileIO * CreateXMLFile();
	};
}
#endif // XMLFileIO_h__

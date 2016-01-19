//  *******************************************************************************************************************
//  XMLNode   version:  1.0   Ankur Sheel  date: 2013/05/02
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#ifndef XMLNode_h__
#define XMLNode_h__

#include "XMLNode.hxx"

namespace tinyxml2
{
	class XMLElement;
	class XMLDocument;
}

namespace Base
{
	template<class T>
	class tOptional;
}

namespace Utilities
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief XML parser Implementation
	/// 
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class cXMLNode
		: public IXMLNode
		, public Base::cNonCopyable
		, public std::enable_shared_from_this<cXMLNode>
	{
	public:
		~cXMLNode();
		static const shared_ptr<IXMLNode> InitializeForSave(const Base::cString & RootName,	const Base::cString & StyleSheetPath);
		static const shared_ptr<IXMLNode> Load(const Base::cString & FilePath);
		static const shared_ptr<IXMLNode> Parse(const Base::cString & XML,	const unsigned int Size);

	private:
		cXMLNode();
		void VSave(const Base::cString & FilePath);
		const weak_ptr<IXMLNode> VAddElement(const Base::cString & ElementName, const Base::cString & ElementValue) OVERRIDE;
		void VAddChild(shared_ptr<IXMLNode> pNode) OVERRIDE;
		void VAddComment(const Base::cString & Comment) OVERRIDE;
		void VAddAttribute(const Base::cString & AttributeName, const Base::cString & AttributeValue) OVERRIDE;
		void VAddAttribute(const Base::cString & AttributeName, const int AttributeValue) OVERRIDE;
		void VAddAttribute(const Base::cString & AttributeName, const bool AttributeValue) OVERRIDE;
		Base::cString VGetName() const OVERRIDE;
		Base::cString VGetNodeValue() const OVERRIDE;
		Base::cString VGetNodeAttribute(const Base::cString & AttributeName) const OVERRIDE;
		Base::tOptional<int> VGetNodeAttributeAsInt(const Base::cString & AttributeName) const OVERRIDE;
		int VGetNodeAttributeAsInt(const Base::cString & AttributeName, const int defaultValue) const OVERRIDE;
		Base::tOptional<bool> VGetNodeAttributeAsBool(const Base::cString & AttributeName) const OVERRIDE;
		bool VGetNodeAttributeAsBool(const Base::cString & AttributeName, const bool defaultValue) const OVERRIDE;
		Base::tOptional<float> VGetNodeAttributeAsFloat(const Base::cString & AttributeName) const OVERRIDE;
		float VGetNodeAttributeAsFloat(const Base::cString & AttributeName, const float DefaultValue) const OVERRIDE;
		void VGetChildren(XMLNodeList & ChildrenList) const OVERRIDE;
		const shared_ptr<IXMLNode> VGetChild(const Base::cString & Name) const OVERRIDE;
		Base::cString VGetChildValue(const Base::cString & Name) const OVERRIDE;
		Base::tOptional<int> VGetChildValueAsInt(const Base::cString & Name) const OVERRIDE;
		int VGetChildValueAsInt(const Base::cString & Name, const int DefaultValue) const OVERRIDE;
		Base::tOptional<float> VGetChildValueAsFloat(const Base::cString & Name) const OVERRIDE;
		float VGetChildValueAsFloat(const Base::cString & Name, const float DefaultValue) const OVERRIDE;
		Base::tOptional<bool> VGetChildValueAsBool(const Base::cString & Name) const OVERRIDE;
		bool VGetChildValueAsBool(const Base::cString & Name, const bool DefaultValue) const OVERRIDE;
		Base::cVector3 VGetChildValueAsVector3(const Base::cString & Name, const Base::cVector3 & DefaultValue) const OVERRIDE;
		Base::cVector2 VGetChildValueAsVector2(const Base::cString & Name, const Base::cVector2 & DefaultValue) const OVERRIDE;
		Base::cColor VGetChildValueAsColor(const Base::cString & Name, const Base::cColor & DefaultValue) const OVERRIDE;
		Base::cString VToString() const OVERRIDE;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Adds all the child elements for the parent element to the child list
		/// 
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void AddChildElements();
		void DeepClone(const shared_ptr<IXMLNode> pDestination, const shared_ptr<IXMLNode> pSource);

	private:
		shared_ptr<tinyxml2::XMLDocument>	m_pDoc;	///< Pointer to the tinyxml2 Document. Will be NULL except for the root element.
		XMLNodeList	m_ChildNodes;	///< The list of the child elements.
		tinyxml2::XMLElement *	m_pElement;	///< The tinyxml2 element.

	private:
		friend shared_ptr<IXMLNode> IXMLNode::Create(const Base::cString & RootName);
	};
}
#endif // XMLNode_h__
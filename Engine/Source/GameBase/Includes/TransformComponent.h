// *****************************************************************************
//  TransformComponent version:  1.0   Ankur Sheel  date: 2013/04/10
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef TransformComponent_h__
#define TransformComponent_h__

#include "GameBaseDefines.h"
#include "BaseComponent.h"
#include "Vector3.h"

namespace Base
{
	template<class BaseType, class SubType> 
	BaseType * GenericObjectCreationFunction();
}

namespace Utilities
{
	class IXMLNode;
}

namespace GameBase
{
	class cTransformComponent
		: public cBaseComponent
	{
	public:
		void VInitialize(const Utilities::IXMLNode * const pXMLNode) OVERRIDE;
		void VCleanup()  OVERRIDE;
		shared_ptr<Utilities::IXMLNode> VGenerateXml() const OVERRIDE;

		static Base::cHashedString	GetName()  {return m_Name; }
		Base::cVector3 GetPosition() const { return m_Position; }
		GAMEBASE_API void SetPosition(const Base::cVector3 & position);
		Base::cVector3 GetSize() const { return m_Size; }
		GAMEBASE_API void SetSize(const Base::cVector3 & size);
		Base::cVector3 GetRotation() const { return m_Rotation; }
		GAMEBASE_API void SetRotation(const Base::cVector3 & rotation);
		Base::cVector3 GetLookAt() const { return m_LookAt; }

	private:
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
		cTransformComponent();
		~cTransformComponent();

	private:
		GAMEBASE_API static Base::cHashedString	m_Name;	///< The component name
		Base::cVector3	m_Position;	///< The position of the game element.
		Base::cVector3	m_Rotation;	///< The rotation of the game element.
		Base::cVector3	m_Size;		///< The size of the game element.
		Base::cVector3	m_LookAt;

	private:
		template<class BaseType, class SubType> 
		friend BaseType * Base::GenericObjectCreationFunction();
	};
}
#endif // TransformComponent_h__

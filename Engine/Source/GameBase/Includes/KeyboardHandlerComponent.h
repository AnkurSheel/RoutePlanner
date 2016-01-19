// *****************************************************************************
//  KeyboardHandlerComponent version:  1.0   Ankur Sheel  date: 2013/05/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef KeyboardHandlerComponent_h__
#define KeyboardHandlerComponent_h__

#include "GameBaseDefines.h"
#include "BaseComponent.h"

namespace Base
{
	template<class BaseType, class SubType> 
	BaseType * GenericObjectCreationFunction();
}

namespace GameBase
{
	class cKeyboardHandlerComponent
		: public cBaseComponent
	{
	public:
		GAMEBASE_API void VInitialize(const Utilities::IXMLNode * const pXMLNode) OVERRIDE;
		GAMEBASE_API void VCleanup() OVERRIDE;
		shared_ptr<Utilities::IXMLNode> VGenerateXml() const OVERRIDE;
		GAMEBASE_API static Base::cHashedString	GetName()  {return m_Name; }
		void Update(const float deltaTime);

	private:
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
		cKeyboardHandlerComponent();
		~cKeyboardHandlerComponent();

	private:
		static Base::cHashedString	m_Name;	///< The component name

	private:
		template<class BaseType, class SubType> 
		friend BaseType * Base::GenericObjectCreationFunction();

	};
}
#endif // KeyboardHandlerComponent_h__

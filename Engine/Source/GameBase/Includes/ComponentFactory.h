// *****************************************************************************
//  ComponentFactory   version:  1.0   Ankur Sheel  date: 2013/05/15
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef ComponentFactory_h__
#define ComponentFactory_h__

#include "GameBaseDefines.h"
#include "GenericObjectCreation.h"

namespace GameBase
{
	class IBaseComponent;
}

namespace GameBase
{
	class cComponentFactory
	{
	public:
		GAMEBASE_API cComponentFactory();
		GAMEBASE_API ~cComponentFactory();
		GAMEBASE_API void VRegisterComponents();
		IBaseComponent * CreateComponent(const Base::cHashedString & Type);
		GAMEBASE_API IBaseComponent * GetDuplicateComponent(const IBaseComponent * const pComponent);
		static cComponentFactory * Instance() { return m_pInstance; }

	private:
		Base::GenericObjectFactory<IBaseComponent, unsigned long>	m_RegisteredComponents;
		GAMEBASE_API static cComponentFactory *				m_pInstance;
	};
}
#endif // ComponentFactory_h__

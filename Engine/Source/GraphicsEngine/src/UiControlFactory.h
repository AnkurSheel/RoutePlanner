//  *******************************************************************************************************************
//  UiControlFactory   version:  1.0   Ankur Sheel  date: 2013/05/15
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#ifndef UiControlFactory_h__
#define UiControlFactory_h__

#include "GenericObjectCreation.h"

namespace Graphics
{
	class IBaseControl;
}

namespace Graphics
{
	class cUiControlFactory
	{
	public:
		~cUiControlFactory();
		void VRegisterUiControls();
		IBaseControl * CreateUiControl(const Base::cHashedString & Type);
		static cUiControlFactory * Instance();
		static void Destroy();

	private:
		cUiControlFactory();

	private:
		Base::GenericObjectFactory<IBaseControl, unsigned long>	m_RegisteredControls;
		static cUiControlFactory *	m_pInstance;
	};
}
#endif // UiControlFactory_h__

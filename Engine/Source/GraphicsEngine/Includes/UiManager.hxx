//  *******************************************************************************************************************
//  UiManager   version:  1.0   Ankur Sheel  date: 2014/02/20
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#ifndef UiManager_hxx__
#define UiManager_hxx__

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class cUiControlFactory;
	class IBaseControl;
}

namespace Graphics
{
	class IUiManager
	{
	public:
		virtual ~IUiManager(){}
		virtual const shared_ptr<IBaseControl> VCreateUI(const Base::cString& fileName) = 0;
		GRAPHIC_API static void CreateAsService();
	};
}

#endif // UiManager_hxx__
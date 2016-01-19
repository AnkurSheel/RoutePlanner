// ********************************************************************************************************************
//  BaseApp   version:  1.0   Ankur Sheel  date: 04/30/2008
// ********************************************************************************************************************
// 
// ********************************************************************************************************************
#ifndef BaseApp_hxx__
#define BaseApp_hxx__

#include "GameBaseDefines.h"

namespace Base
{
	struct AppMsg;
}

namespace Utilities
{
	class IParamLoader;
	class IProcessManager;
}

namespace GameBase
{
	class cGameControls;
}

namespace GameBase
{
	class IBaseApp
	{
	public:
		virtual ~IBaseApp(){}
		virtual void VOnInitialization(const HINSTANCE & hInstance, const int nCmdShow, const Base::cString & OptionsFile) = 0;
		virtual bool VOnMsgProc(const Base::AppMsg & msg) = 0;
		virtual void VRun() = 0;
		virtual float VGetFPS() const = 0;
		virtual Utilities::IParamLoader * VGetParamLoader() const = 0;
		virtual Utilities::IProcessManager * VGetProcessManager() const = 0;
		virtual cGameControls * VGetGameControls() const = 0;
		virtual Base::cString VGetName() const = 0;
		
		GAMEBASE_API static const IBaseApp * const GetInstance();
	};
}
#endif // BaseApp_hxx__
// ********************************************************************************************************************
//  BaseApp   version:  1.0   Ankur Sheel  date: 2011/10/19
// ********************************************************************************************************************
// 
// ********************************************************************************************************************
#ifndef BaseApp_h__
#define BaseApp_h__

#include "BaseApp.hxx"
#include "BaseEntity.h"

namespace Utilities
{
	class ITimer;
	class IParamLoader;
	class IProcessManager;
	class ILogger;
}

namespace GameBase
{
	class cHumanView;
	class cHighScoreTable;
	class cGameControls;
	class cConfig;
}

namespace GameBase
{
	class cBaseApp 
	: public IBaseApp
	{
	public:
		GAMEBASE_API virtual ~cBaseApp();
		GAMEBASE_API virtual cHumanView * const VGetHumanView() const { return m_pHumanView; }
		GAMEBASE_API Utilities::IProcessManager * VGetProcessManager() const {return m_pProcessManager; }
		GAMEBASE_API float GetRunningTime() const;
		GAMEBASE_API cGameControls * VGetGameControls() const { return m_pGameControls; }
		GAMEBASE_API virtual void VOnInitialization(const HINSTANCE & inhInstance, const int inCmdShow, const Base::cString & inOptionsFile);
		GAMEBASE_API virtual void VRender(TICK inCurrentTick, float inElapsedTime);
		GAMEBASE_API virtual void VOnUpdate();

		TICK GetRunningTicks() const;
		void RegisterServices();

	protected:
		GAMEBASE_API cBaseApp(const Base::cString & Name);
		GAMEBASE_API virtual void VCreateHumanView();
		GAMEBASE_API virtual void VCreateEntityFactory() = 0;
		GAMEBASE_API virtual void VCreateComponentFactory();
		GAMEBASE_API virtual void VCreateEventFactory();
		GAMEBASE_API virtual HWND VInitializeApplicationWindow(const HINSTANCE & hInstance, const int cmdShow);
		GAMEBASE_API virtual bool VInitializeGraphics(const HWND & hwnd);
		GAMEBASE_API virtual void VInitializeGameOptions();
		GAMEBASE_API virtual void VRun();
		GAMEBASE_API virtual bool VOnMsgProc(const Base::AppMsg & msg);
		GAMEBASE_API virtual void VCleanup();

	private:
		GAMEBASE_API Utilities::IParamLoader * VGetParamLoader() const { return m_pParamLoader; }
		GAMEBASE_API float VGetFPS() const;
		Base::cString VGetName() const { return m_Title; }

		bool MeetsMinimumSystemRequirements();
		void SetLoggerOptions(const shared_ptr<Utilities::ILogger> pLogger);
		void OnInitializationError();
		bool InitializeResourceManager(const Base::cString & assetsPath, const Base::cString& resourceFile);

	protected:
		Utilities::ITimer *	m_pGameTimer;
		cHumanView *	m_pHumanView;
		Utilities::IParamLoader *	m_pParamLoader;
		cHighScoreTable *	m_pHighScoreTable;
		cGameControls *	m_pGameControls;
		Utilities::IProcessManager *	m_pProcessManager;
		cConfig*	m_pConfig;
		Base::cString	m_Title;
		bool	m_Quitting;
		bool	m_IsEditorRunning;
		static IBaseApp *	m_spInstance;

	private:
		friend static const IBaseApp * const IBaseApp::GetInstance();
	};
}

#endif // BaseApp_h__
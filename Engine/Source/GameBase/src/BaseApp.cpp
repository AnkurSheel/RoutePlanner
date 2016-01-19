#include "stdafx.h"
#include "BaseApp.h"
#include "MainWindow.hxx"
#include "Timer.hxx"
#include "HumanView.h"
#include "ParamLoaders.hxx"
#include "Optional.h"
#include "SystemChecker.hxx"
#include "EntityManager.hxx"
#include "MessageDispatchManager.hxx"
#include "ResourceManager.hxx"
#include "GraphicsClass.hxx"
#include "ProcessManager.hxx"
#include "GameDirectories.h"
#include "GameOptions.h"
#include "EventManager.hxx"
#include "GameControls.h"
#include "Color.h"
#include "ComponentFactory.h"
#include "EventFactory.h"
#include "SpAssertSettings.hxx"
#include "Logger.hxx"
#include "Physics.hxx"
#include "Config.h"
#include "TweenManager.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;
using namespace Graphics;
using namespace Physics;
using namespace std;
using namespace std::tr1;

IBaseApp * cBaseApp::m_spInstance = NULL;

// ********************************************************************************************************************
cBaseApp::cBaseApp(const cString & Name)
	: m_pGameTimer(NULL)
	, m_pHumanView(NULL)
	, m_pParamLoader(NULL)
	, m_pHighScoreTable(NULL)
	, m_pGameControls(NULL)
	, m_Quitting(false)
	, m_pProcessManager(NULL)
	, m_pConfig(NULL)
	, m_IsEditorRunning(false)
{
	// make sure our memory leak checker is working
#if _DEBUG
	int * p = DEBUG_NEW int();
#endif

	if (m_spInstance == NULL)
	{
		m_spInstance = this;
	}
}

//  ********************************************************************************************************************
cBaseApp::~cBaseApp()
{
	VCleanup();
}

// ********************************************************************************************************************
void cBaseApp::VOnInitialization(const HINSTANCE & inhInstance, const int inCmdShow, const cString & inOptionsFile)
{
	RegisterServices();

	shared_ptr<ILogger> pLogger(ILogger::CreateLogger());
	pLogger->VInitialize();
	const shared_ptr<ISpAssertSettings> pAssertSettings = MakeStrongPtr<ISpAssertSettings>(cServiceLocator::GetInstance()->GetService<ISpAssertSettings>());
	if (pAssertSettings != NULL)
	{
		pAssertSettings->VSetLogger(pLogger);
	}

	SP_ASSERT(m_pParamLoader == NULL).SetCustomMessage("Param Loader should be NULL");
	if(m_pParamLoader == NULL)
	{
		m_pParamLoader = IParamLoader::CreateParamLoader();
		m_pParamLoader->VLoadParametersFromFile(inOptionsFile);
	}

	m_Title = m_pParamLoader->VGetParameterValueAsString("-title", "Game");

	if(!MeetsMinimumSystemRequirements())
	{
		OnInitializationError();
		return;
	}

	SetLoggerOptions(pLogger);

	// initialize resource manager
	cString assetsPath = m_pParamLoader->VGetParameterValueAsString("-AssetsPath", "");
	cString resourceFile = m_pParamLoader->VGetParameterValueAsString("-ResourceFile", "");

	if(!InitializeResourceManager(assetsPath, resourceFile))
	{
		OnInitializationError();
		return;
	}

	cGameDirectories::Initialize(assetsPath + resourceFile);
	VInitializeGameOptions();

	VCreateEntityFactory();
	VCreateComponentFactory();
	VCreateEventFactory();
	VCreateHumanView();

	HWND hwnd = VInitializeApplicationWindow(inhInstance, inCmdShow);
	if (hwnd == NULL)
	{
		OnInitializationError();
		return;
	}

	if(!VInitializeGraphics(hwnd))
	{
		OnInitializationError();
		return;
	}

	m_pProcessManager = IProcessManager::CreateProcessManager();
	m_pHumanView->VOnCreateDevice(this);
	//IAudio::GetInstance()->VInitialize(hWnd);
}

void cBaseApp::VCreateHumanView()
{
	m_pHumanView = DEBUG_NEW cHumanView();
}

// ********************************************************************************************************************
void cBaseApp::VRun()
{
	MSG Msg ;

	m_pGameTimer = ITimer::CreateTimer();
	m_pGameTimer->VStartTimer();

	PeekMessage(&Msg, NULL, 0, 0, PM_NOREMOVE) ;
	// run till completed
	while (Msg.message!=WM_QUIT)
	{
		// is there a message to process?
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			// dispatch the message
			TranslateMessage(&Msg) ;
			DispatchMessage(&Msg) ;
		}
		else
		{
			//No message to process?
			// Then do your game stuff here
			VOnUpdate();
			VRender(m_pGameTimer->VGetRunningTicks(), m_pGameTimer->VGetDeltaTime());
		}
	}
}

// ********************************************************************************************************************
void cBaseApp::VOnUpdate()
{
	if(m_Quitting)
	{
		return;
	}
	if (m_pGameTimer != NULL)
	{
		m_pGameTimer->VOnUpdate();
	}
	shared_ptr<IMessageDispatchManager> pMessageDispatcher = MakeStrongPtr(cServiceLocator::GetInstance()->GetService<IMessageDispatchManager>());
	if (pMessageDispatcher != NULL)
	{
		pMessageDispatcher->VOnUpdate();
	}

	float deltaTime = 0.0f;
	if(m_pGameTimer != NULL)
	{
		deltaTime = m_pGameTimer->VGetDeltaTime();
	}
	if(m_pProcessManager)
	{
		m_pProcessManager->VUpdateProcesses(deltaTime);
	}

	shared_ptr<IEventManager> pEventManager = MakeStrongPtr(cServiceLocator::GetInstance()->GetService<IEventManager>());
	if (pEventManager != NULL)
	{
		pEventManager->VUpdate();
	}
}

// ********************************************************************************************************************
void cBaseApp::VCleanup()
{
	SafeDelete(&m_pGameTimer);
	SafeDelete(&m_pParamLoader);
	SafeDelete(&m_pProcessManager);
	SafeDelete(&m_pHumanView);
	SafeDelete(&m_pGameControls);
	SafeDelete(&m_pConfig);

	IGraphicsClass::Destroy();
	IResourceManager::Destroy();
	IMainWindow::Destroy();
	cServiceLocator::Destroy();
}

// ********************************************************************************************************************
float cBaseApp::GetRunningTime() const
{
	if(m_pGameTimer)
	{
		return m_pGameTimer->VGetRunningTime();
	}

	return 0.f;
}

// ********************************************************************************************************************
TICK cBaseApp::GetRunningTicks() const
{
	if(m_pGameTimer != NULL)
	{
		return m_pGameTimer->VGetRunningTicks();
	}

	return 0;
}

// ********************************************************************************************************************
// Display the FPS
// ********************************************************************************************************************
float cBaseApp::VGetFPS() const
{
	if(m_pGameTimer != NULL)
	{
		return m_pGameTimer->VGetFPS();
	}
	return 0.0f;
}

// ********************************************************************************************************************
bool cBaseApp::VOnMsgProc( const Base::AppMsg & msg )
{
	if(m_Quitting)
	{
		return false;
	}
	return m_pHumanView->VOnMsgProc(msg);
}

// ********************************************************************************************************************
void cBaseApp::VRender(TICK tickCurrent, float fElapsedTime)
{
	if(m_Quitting)
	{
		return;
	}
	m_pHumanView->VOnRender(tickCurrent, fElapsedTime);
}

//  ********************************************************************************************************************
bool cBaseApp::MeetsMinimumSystemRequirements()
{
	SP_ASSERT(m_pParamLoader != NULL).SetCustomMessage("Parameter Loader does not exist");
	bool minRequirementsSatified = true;

	bool multipleInstances = (m_pParamLoader != NULL && m_pParamLoader->VGetParameterValueAsBool("-multipleinstances", false));
	if (multipleInstances)
	{
		minRequirementsSatified = ISystemChecker::Instance()->VIsOnlyInstance(m_Title);
	}

	/*minRequirementsSatified = ISystemChecker::Instance()->VCheckMemory(32, 64)
		&& ISystemChecker::Instance()->VCheckHardDiskSpace(6)
		&& ISystemChecker::Instance()->VCheckCPUSpeed(266);*/
	ISystemChecker::Instance()->VCheckMemory(32, 64);
	ISystemChecker::Instance()->VCheckHardDiskSpace(6);
	ISystemChecker::Instance()->VCheckCPUSpeed(266);

	ISystemChecker::Destroy();
	return minRequirementsSatified;
}

//  ********************************************************************************************************************
void cBaseApp::SetLoggerOptions(const shared_ptr<ILogger> pLogger)
{
	SP_ASSERT(m_pParamLoader != NULL).SetCustomMessage("Parameter Loader does not exist");

	bool showConsoleLog = m_pParamLoader != NULL && m_pParamLoader->VGetParameterValueAsBool("-showconsolelog", false);
	bool logToText = m_pParamLoader != NULL && m_pParamLoader->VGetParameterValueAsBool("-logtotext", true);
	bool logToXML = m_pParamLoader != NULL && m_pParamLoader->VGetParameterValueAsBool("-logtoxml", false);
	unsigned int priorityLevel = m_pParamLoader == NULL ? 1 : m_pParamLoader->VGetParameterValueAsInt("-loglevel", 1);

	pLogger->VSetLogOptions(showConsoleLog, logToText, logToXML, priorityLevel);
}

//  ********************************************************************************************************************
void cBaseApp::OnInitializationError()
{
	PostQuitMessage(0);
	m_Quitting = true;
}

//  ********************************************************************************************************************
bool cBaseApp::InitializeResourceManager(const cString & assetsPath, const cString& resourceFile)
{
	SP_ASSERT_FATAL(m_pParamLoader != NULL).SetCustomMessage("Parameter Loader does not exist");

	bool useDevelopmentDirectory = m_IsEditorRunning || m_pParamLoader->VGetParameterValueAsBool("-UseDevelopmentDirectory", false);
	IResourceManager::GetInstance()->VInitialize(30, assetsPath, resourceFile, useDevelopmentDirectory);
	return true;
}

//  ********************************************************************************************************************
void cBaseApp::VInitializeGameOptions()
{
	SP_ASSERT_FATAL(m_pParamLoader != NULL).SetCustomMessage("Parameter Loader does not exist");
	cGameOptions::InitializeGameOptions(cGameDirectories::GetMediaDirectory() + "PlayerOptions.xml");

#if _DEBUG
	cGameOptions::GameOptions().bFullScreen = m_pParamLoader->VGetParameterValueAsBool("-fullscreen", cGameOptions::GameOptions().bFullScreen);
	cGameOptions::GameOptions().iWidth = m_pParamLoader->VGetParameterValueAsInt("-WindowWidth", cGameOptions::GameOptions().iWidth);
	cGameOptions::GameOptions().iHeight = m_pParamLoader->VGetParameterValueAsInt("-WindowHeight", cGameOptions::GameOptions().iHeight);
#endif
}

//  ********************************************************************************************************************
HWND cBaseApp::VInitializeApplicationWindow(const HINSTANCE & hInstance, const int cmdShow)
{
	SP_ASSERT_FATAL(m_pParamLoader != NULL).SetCustomMessage("Parameter Loader does not exist");
	return IMainWindow::GetInstance()->VOnInitialization(hInstance, cmdShow, this);
}

//  ********************************************************************************************************************
bool cBaseApp::VInitializeGraphics(const HWND & hwnd)
{
	SP_ASSERT_FATAL(m_pParamLoader != NULL).SetCustomMessage("Parameter Loader does not exist");

	vector<int> vBGColor;
	m_pParamLoader->VGetParameterValueAsIntList("-BackGroundColor", vBGColor);
	cColor bgColor = cColor::BLACK;
	if(!vBGColor.empty() && vBGColor.size() == 4)
	{
		bgColor = cColor(vBGColor[0], vBGColor[1], vBGColor[2], vBGColor[3]);
	}
	bool vSyncEnabled = m_pParamLoader->VGetParameterValueAsBool("-VSyncEnabled", false);
	float screenFar = m_pParamLoader->VGetParameterValueAsFloat("-ScreenFar", 1000.0f);
	float screenNear = m_pParamLoader->VGetParameterValueAsFloat("-ScreenNear", 0.1f);

	bool success = IGraphicsClass::GetInstance()->VInitialize(hwnd, bgColor,
		cGameOptions::GameOptions().bFullScreen, vSyncEnabled,
		cGameOptions::GameOptions().iWidth, 
		cGameOptions::GameOptions().iHeight, screenFar, screenNear);

	return success;
}

//  ********************************************************************************************************************
void cBaseApp::VCreateComponentFactory()
{
	shared_ptr<IEntityManager> pEntityManager = (MakeStrongPtr<IEntityManager>(cServiceLocator::GetInstance()->GetService<IEntityManager>()));
	if (pEntityManager != NULL)
	{
		pEntityManager->VInitializeComponentFactory(shared_ptr<cComponentFactory>(DEBUG_NEW cComponentFactory()));
	}
}

//  ********************************************************************************************************************
void cBaseApp::VCreateEventFactory()
{
	shared_ptr<IEventManager> pEventManager = MakeStrongPtr(cServiceLocator::GetInstance()->GetService<IEventManager>());
	if (pEventManager != NULL)
	{
		pEventManager->VInitializeEventFactory(shared_ptr<cEventFactory>(DEBUG_NEW cEventFactory()));
	}
}

//  *******************************************************************************************************************
void cBaseApp::RegisterServices()
{
	ISpAssertSettings::CreateAsService();
	IPhysics::CreateAsService();
	IEntityManager::CreateAsService();
	IEventManager::CreateAsService();
	cTweenManager::CreateAsService();
}

//  *******************************************************************************************************************
const IBaseApp * const IBaseApp::GetInstance()
{
	return cBaseApp::m_spInstance;
}

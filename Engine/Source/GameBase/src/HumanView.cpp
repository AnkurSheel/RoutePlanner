#include "stdafx.h"
#include "HumanView.h"
#include "GraphicsClass.hxx"
#include "BaseApp.hxx"
#include "BaseControl.hxx"
#include "MainWindow.hxx"
#include "Camera.hxx"
#include "ParamLoaders.hxx"
#include "Audio.hxx"
#include "SoundProcess.hxx"
#include "GameOptions.h"
#include "GameDirectories.h"
#include "ProcessManager.hxx"
#include "KeyboardController.hxx"

using namespace Utilities;
using namespace Graphics;
using namespace Base;
using namespace GameBase;
using namespace Sound;

//  *******************************************************************************************************************
cHumanView::cHumanView()
	: m_bRunFullSpeed(true)
	, m_pAppWindowControl(NULL) 
	, m_pCamera(NULL)
	, m_bDisplayFPS(false)
	, m_hashSFXChannel("SFXChannelProcess")
	, m_hashMusicChannel("MusicChannelProcess")
{

}

//  *******************************************************************************************************************
cHumanView::~cHumanView()
{
	VOnDestroyDevice();
}

//  *******************************************************************************************************************
void cHumanView::VOnCreateDevice(IBaseApp* pBaseApp)
{
	m_pGame = pBaseApp;
	if(m_pGame->VGetParamLoader() != NULL)
	{
		m_bDisplayFPS = m_pGame->VGetParamLoader()->VGetParameterValueAsBool("-DisplayFPS", false);
	}
	cWindowControlDef def;
	def.wType = cWindowControlDef::WT_DESKTOP;
	def.strControlName = "App";
	def.vSize = cVector2(static_cast<float>(cGameOptions::GameOptions().iWidth), static_cast<float>(cGameOptions::GameOptions().iHeight));
	if(m_pGame->VGetParamLoader() != NULL)
	{
		def.bAllowMovingControls = m_pGame->VGetParamLoader()->VGetParameterValueAsBool("-AllowMovingControls", false);
	}
	m_pAppWindowControl = IBaseControl::CreateWindowControl(def);
	m_pCamera = ICamera::CreateCamera();

	// 	m_pCursorSprite = ISprite::CreateSprite();
	// 	m_pCursorSprite->Init(IDXBase::GetInstance()->VGetDevice(), 
	// 		"cursor.png");
	// 	m_pCursorSprite->SetSize((float)iClientWidth/30, (float)iClientHeight/30);
	// 	m_pCursorSprite->SetFlags(D3DXSPRITE_ALPHABLEND);
	cLabelControlDef fpsLabelDef;
	fpsLabelDef.strControlName = "FPSLabel";
	fpsLabelDef.strFont= "arial"; 
	fpsLabelDef.textColor = cColor::WHITE;
	fpsLabelDef.fTextHeight = 30;
	fpsLabelDef.vPosition = cVector2(static_cast<float>(cGameOptions::GameOptions().iWidth/2- 75), 0.0f);
	fpsLabelDef.bAutoSize = false;
	fpsLabelDef.vSize = cVector2(150, 30);
	CreateFPSLabel(fpsLabelDef);
}

//  *******************************************************************************************************************
void cHumanView::VOnUpdate(const TICK tickCurrent, const float fElapsedTime)
{
	if (m_pCamera)
	{
		m_pCamera->VUpdate();
	}
}

//  *******************************************************************************************************************
void cHumanView::VOnRender(const TICK tickCurrent, const float fElapsedTime)
{
	HRESULT hr;
	hr = OnBeginRender(tickCurrent);
	if(SUCCEEDED(hr))
	{
		VRenderPrivate();
		OnEndRender(hr);
	}
}

//  *******************************************************************************************************************
void cHumanView::VOnDestroyDevice()
{
	SafeDelete(&m_pAppWindowControl);
	SafeDelete(&m_pCamera);
	IAudio::Destroy();
	IKeyboardController::Destroy();
}

//  *******************************************************************************************************************
bool cHumanView::VOnMsgProc( const Base::AppMsg & msg )
{
	bool bHandled = false;
	switch(msg.m_uMsg)
	{
	case WM_CHAR:
		if (m_pAppWindowControl)
		{
			bHandled = m_pAppWindowControl->VPostMsg(msg);
		}
		//if(!bHandled)
		//{
		//	switch (msg.m_wParam)
		//	{ 
		//	case VK_SPACE:
		//		IMainWindow::GetInstance()->VToggleFullScreen();
		//		Log_Write_L3(ILogger::LT_DEBUG, "Toggled FullScreen");
		//	}
		//}
		break;
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_KEYUP:
	case WM_KEYDOWN:
		if (m_pAppWindowControl)
		{
			bHandled = m_pAppWindowControl->VPostMsg(msg);
		}
		if (msg.m_wParam == VK_F2 && !IKeyboardController::Instance()->VIsKeyLocked(VK_F2) )
		{
			// lock the F2 key
			IKeyboardController::Instance()->VLockKey(VK_F2);
			m_bDisplayFPS = !m_bDisplayFPS;
			if(m_pFpsLabel)
			{
				m_pFpsLabel->VSetVisible(m_bDisplayFPS);
			}
		}
		break;
	}
	return bHandled;
}

//  *******************************************************************************************************************
IGameView::GAMEVIEWTYPE cHumanView::VGetType()
{
	return GV_HUMAN;
}

//  *******************************************************************************************************************
GameViewId cHumanView::VGetId() const
{
	return -1;
}

//  *******************************************************************************************************************
void cHumanView::VOnAttach(GameViewId id)
{
	m_idView = id;
}

const ICamera * const cHumanView::GetCamera() const
{
	return m_pCamera;
}

//  *******************************************************************************************************************
HRESULT cHumanView::OnBeginRender(TICK tickCurrent)
{
	m_tickCurrent = tickCurrent; 
	HRESULT hr = S_OK;
	IGraphicsClass::GetInstance()->VBeginRender();
	return hr;
}

//  *******************************************************************************************************************
void cHumanView::VRenderPrivate()
{
	if (m_pAppWindowControl)
	{
		m_pAppWindowControl->VRender(m_pCamera);
	}

	// 		if (m_pCursorSprite->IsVisible())
	// 		{
	// 			m_pCursorSprite->SetPosition(D3DXVECTOR3((float)m_pInput->GetX(), (float)m_pInput->GetY(), 0.0f));
	// 			m_pCursorSprite->OnRender(IDXBase::GetInstance()->VGetDevice());
	// 		}
	if (m_bDisplayFPS && m_pFpsLabel && m_pGame)
	{
		m_pFpsLabel->VSetText(cStringUtilities::MakeFormatted("%0.2f", m_pGame->VGetFPS()));
	}
}

//  *******************************************************************************************************************
void cHumanView::OnEndRender(const HRESULT hr)
{
	m_tickLastDraw = m_tickCurrent; 
	IGraphicsClass::GetInstance()->VEndRender();
}

//  *******************************************************************************************************************
void cHumanView::SetCursorVisible( bool bVisible )
{
	// 	if (m_pCursorSprite)
	// 	{
	// 		m_pCursorSprite->SetVisible(bVisible);
	// 	}
}

//  *******************************************************************************************************************
void cHumanView::PlaySFX(const cString & strSoundFile)
{
	if(cGameOptions::GameOptions().bPlaySfx)
	{
		shared_ptr<ISoundProcess> pSFXChannelProcess(ISoundProcess::CreateSoundProcess(m_hashSFXChannel.GetString(),
			cGameDirectories::GetSoundSFXDirectory() + strSoundFile, cGameOptions::GameOptions().iSFXVolume, false));
		m_pGame->VGetProcessManager()->VAttachProcess(pSFXChannelProcess);
	}
}

//  *******************************************************************************************************************
void cHumanView::PlayMusic(const cString & strMusicFile, const bool bLooping)
{
	shared_ptr<ISoundProcess> pMusicChannelProcess = ISoundProcess::CreateSoundProcess(m_hashMusicChannel.GetString(),
		cGameDirectories::GetSoundMusicDirectory() + strMusicFile, cGameOptions::GameOptions().iMusicVolume, bLooping);
	m_pGame->VGetProcessManager()->VAttachProcess(pMusicChannelProcess);
	m_pGame->VGetProcessManager()->VSetProcessesActive(m_hashMusicChannel, cGameOptions::GameOptions().bPlayMusic);
}

//  *******************************************************************************************************************
void cHumanView::SetMusicVolume()
{
	ProcessList pProcessList;
	m_pGame->VGetProcessManager()->VGetProcesses(m_hashMusicChannel, pProcessList);
	for (auto curProcess = pProcessList.begin(); curProcess != pProcessList.end(); curProcess++)
	{
		shared_ptr<ISoundProcess> p = dynamic_pointer_cast<ISoundProcess>(*curProcess);
		p->VSetVolume(cGameOptions::GameOptions().iMusicVolume);
	}
}

//  *******************************************************************************************************************
void cHumanView::SetSFXVolume()
{
	ProcessList pProcessList;
	m_pGame->VGetProcessManager()->VGetProcesses(m_hashSFXChannel, pProcessList);
	for (auto curProcess = pProcessList.begin(); curProcess != pProcessList.end(); curProcess++)
	{
		shared_ptr<ISoundProcess> p = dynamic_pointer_cast<ISoundProcess>(*curProcess);
		p->VSetVolume(cGameOptions::GameOptions().iSFXVolume);
	}
}

//  *******************************************************************************************************************
void cHumanView::MusicCheckBoxPressed(const stUIEventCallbackParam & params)
{
	cGameOptions::GameOptions().bPlayMusic = params.bChecked;
	m_pGame->VGetProcessManager()->VSetProcessesActive(m_hashMusicChannel, cGameOptions::GameOptions().bPlayMusic);
}

//  *******************************************************************************************************************
void cHumanView::SfxCheckBoxPressed(const stUIEventCallbackParam & params)
{
	cGameOptions::GameOptions().bPlaySfx = params.bChecked;
	m_pGame->VGetProcessManager()->VSetProcessesActive(m_hashSFXChannel, cGameOptions::GameOptions().bPlaySfx);
}

//  *******************************************************************************************************************
void cHumanView::FullScreenCheckBoxPressed(const stUIEventCallbackParam & params)
{
	cGameOptions::GameOptions().bFullScreen = !(cGameOptions::GameOptions().bFullScreen);
	IGraphicsClass::GetInstance()->VSetFullScreenMode(cGameOptions::GameOptions().bFullScreen);
}

//  *******************************************************************************************************************
void cHumanView::CreateFPSLabel(const cLabelControlDef & def)
{
	m_pFpsLabel = shared_ptr<IBaseControl>(IBaseControl::CreateLabelControl(def));
	m_pAppWindowControl->VAddChildControl(m_pFpsLabel);
}

//  *******************************************************************************************************************
//  MainWindow   version:  1.0   Ankur Sheel  date: 04/28/2008
//  -------------------------------------------------------------------------------------------------------------------
//
//  -------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
//  *******************************************************************************************************************
//
//  *******************************************************************************************************************
#include "stdafx.h"
#include "MainWindow.h"
#include "GraphicsClass.hxx"
#include "BaseApp.hxx"
#include "Structures.h"
#include "GameOptions.h"
#include "optional.h"

using namespace Utilities;
using namespace Base;
using namespace GameBase;
using namespace Graphics;

static IMainWindow * s_pWindow = NULL;

//  *******************************************************************************************************************
cMainWindow::cMainWindow()
: m_Hwnd(NULL)
, m_hInstance(NULL)
, m_pGame(NULL)
, m_kdwWindowedStyle(WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION)
{
}

//  *******************************************************************************************************************
cMainWindow::~cMainWindow()
{
}

//  *******************************************************************************************************************
HWND cMainWindow::VOnInitialization(const HINSTANCE & hInstance, const int & nCmdShow, IBaseApp * const pGame)
{
	m_hInstance = hInstance;
	m_pGame = pGame;

	RegisterWin();

	cString strGameTitle = "GameTitle";

	if (m_pGame != NULL)
	{
		strGameTitle = m_pGame->VGetName();
	}

	if(!CreateMyWindow(nCmdShow, strGameTitle))
	{
		return NULL;
	}

	//Bring the window into the foreground and activates the window
	SetForegroundWindow(m_Hwnd);

	//Set the keyboard focus
	SetFocus(m_Hwnd);

	return m_Hwnd;
}

//  *******************************************************************************************************************
void cMainWindow::VOnWindowResized(const int iNewWidth, const int iNewHeight)
{
	tOptional<bool> bFullScreen = IGraphicsClass::GetInstance()->VOnWindowResized(iNewWidth, iNewHeight);
	if(bFullScreen.IsValid())
	{
		cGameOptions::GameOptions().bFullScreen = bFullScreen.GetValue();
	}
	if(!cGameOptions::GameOptions().bFullScreen)
	{
		int x = (GetSystemMetrics(SM_CXSCREEN) - cGameOptions::GameOptions().iWidth) / 2;
		int y = (GetSystemMetrics(SM_CYSCREEN) - cGameOptions::GameOptions().iHeight) / 2;

		SetWindowPos(m_Hwnd, HWND_NOTOPMOST, x, y, 
			m_windowRect.right - m_windowRect.left,
			m_windowRect.bottom - m_windowRect.top, 0);
	}
}

//  *******************************************************************************************************************
void cMainWindow::RegisterWin()
{
	WNDCLASSEX	wc;

	wc.cbSize = sizeof(WNDCLASSEX) ;
	wc.style = 0 ;
	wc.lpfnWndProc = (WNDPROC)cMainWindow::StaticWndProc ;
	wc.cbClsExtra = 0 ;
	wc.cbWndExtra = 0 ;
	wc.hInstance = m_hInstance ;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO) ;
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW) ;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL ;
	wc.lpszClassName = "Window" ;
	if(!RegisterClassEx(&wc))
	{
		SP_ASSERT_FATAL(false).SetCustomMessage("Window Registration Failed");
		abort();
	}
}

//  *******************************************************************************************************************
bool cMainWindow::CreateMyWindow(const int &nCmdShow, const cString & lpWindowTitle)
{
	CalculateWindowRect();

	int x = (GetSystemMetrics(SM_CXSCREEN) - cGameOptions::GameOptions().iWidth)  / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - cGameOptions::GameOptions().iHeight) / 2;
	int width = m_windowRect.right - m_windowRect.left;
	int height = m_windowRect.bottom - m_windowRect.top;

	m_Hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		"Window",
		lpWindowTitle.GetData(),
		m_kdwWindowedStyle,
		x,
		y,
		width,
		height,
		NULL,
		NULL,
		m_hInstance,
		this) ; // pass "this" so that staticwndproc can access the non static data

	SP_ASSERT_ERROR(m_Hwnd != NULL).SetCustomMessage("Window Creation Failed");

	ShowWindow(m_Hwnd, nCmdShow) ;
	return true;
}

//  *******************************************************************************************************************
LRESULT CALLBACK cMainWindow::StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if ( msg == WM_CREATE )
	{
		// store the this pointer which is passed when we create the window in lparam
		// lpCreateParams contains the value of the lpParam parameter specified in the function call.
		SetWindowLongPtr( hwnd, GWLP_USERDATA, (LONG)((CREATESTRUCT *)lParam)->lpCreateParams );
	}

	// get the this pointer for this class using GWLP_USERDATA
	cMainWindow *targetApp = reinterpret_cast<cMainWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if ( targetApp )
	{
		// let our window handle the msg
		return targetApp->WndProc( hwnd, msg, wParam, lParam );
	}

	return DefWindowProc( hwnd, msg, wParam, lParam );
}

//  *******************************************************************************************************************
LRESULT CALLBACK cMainWindow::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch(uMsg)
	{
	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps);
		EndPaint (hwnd, &ps);
		return 0 ;

	case WM_CLOSE:
		OnWindowDestroyed();
		return 0 ;

	case WM_DESTROY:
		OnWindowDestroyed();
		return 0 ;

	case WM_SIZE:
		VOnWindowResized(LOWORD(lParam), HIWORD(lParam));
		return 0;

	case WM_ACTIVATE:
		{
			if (LOWORD(wParam) == WA_ACTIVE)
			{
				if(cGameOptions::GameOptions().bFullScreen)
				{
					SetDisplayResolution();
				}
				ShowWindow(hwnd, SW_RESTORE);
			}
			else if (LOWORD(wParam) == WA_INACTIVE)
			{
				if(cGameOptions::GameOptions().bFullScreen)
				{
					SetDisplayResolution();
				}
				ShowWindow(hwnd, SW_MINIMIZE);
			}
			return 0;
		}
	case WM_LBUTTONDBLCLK:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:
	case WM_RBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
		Base::AppMsg msg;
		msg.m_hWnd = hwnd;
		msg.m_uMsg = uMsg;
		msg.m_wParam = wParam;
		msg.m_lParam = lParam;

		if (m_pGame)
		{
			m_pGame->VOnMsgProc(msg);
		}
		return 0;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam) ;
	}
}

//  *******************************************************************************************************************
void cMainWindow::OnWindowDestroyed()
{
	// return to the default mode
	ChangeDisplaySettings(NULL, 0);

	// release the graphic object
	ReleaseCapture() ;
	UnregisterClass("Window", m_hInstance);
	PostQuitMessage(0);
}

//  *******************************************************************************************************************
void cMainWindow::SetDisplayResolution()
{
	if (cGameOptions::GameOptions().bFullScreen)
	{
		DEVMODE dmScreenSettings;
		SecureZeroMemory(&dmScreenSettings, sizeof(dmScreenSettings));
		if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmScreenSettings))
		{
			SP_ASSERT_DEBUG(false).SetCustomMessage("Could not get current display Settings");
			return;
		}

		// set the full screen height and width
		dmScreenSettings.dmPelsHeight = (unsigned long)cGameOptions::GameOptions().iHeight;
		dmScreenSettings.dmPelsWidth = (unsigned long)cGameOptions::GameOptions().iWidth;
		dmScreenSettings.dmFields = (DM_PELSWIDTH | DM_PELSHEIGHT);

		// Test if the requested graphics mode could be set.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_TEST) == DISP_CHANGE_SUCCESSFUL)
		{
			// Set the requested graphics mode.
			if(ChangeDisplaySettings(&dmScreenSettings, 0) == DISP_CHANGE_SUCCESSFUL)
			{
				SP_LOG(1, "Resolution set")(cGameOptions::GameOptions().iWidth)(cGameOptions::GameOptions().iHeight);
				return;
			}
		}
		SP_ASSERT_DEBUG(false)(cGameOptions::GameOptions().iWidth)(cGameOptions::GameOptions().iHeight).SetCustomMessage("Could not set Resolution");
	}

	// return to the default mode
	ChangeDisplaySettings(NULL, 0);
}

//  *******************************************************************************************************************
void cMainWindow::CalculateWindowRect()
{
	m_windowRect.left = 0;
	m_windowRect.top = 0;
	m_windowRect.right =  cGameOptions::GameOptions().iWidth;
	m_windowRect.bottom = cGameOptions::GameOptions().iHeight;

	//get the required size of the window rectangle, based on the desired size of the client rectangle
	AdjustWindowRectEx(&m_windowRect, m_kdwWindowedStyle, false, 0);
}

//  *******************************************************************************************************************
void cMainWindow::VCleanup()
{
	DestroyWindow(m_Hwnd);
}

//  *******************************************************************************************************************
IMainWindow * const IMainWindow::GetInstance()
{
	if(s_pWindow == NULL)
		s_pWindow = DEBUG_NEW cMainWindow();
	return s_pWindow;
}

//  *******************************************************************************************************************
void IMainWindow::Destroy()
{
	if(s_pWindow != NULL)
	{
		s_pWindow->VCleanup();
		SP_LOG(2, cStringUtilities::MakeFormatted("Window destroyed"));
	}
	SafeDelete(&s_pWindow);
}

//  *******************************************************************************************************************
//  GraphicsClass   version:  1.0   Ankur Sheel  date: 2012/09/13
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#include "stdafx.h"
#include "GraphicsClass.h"
#include "DxBase.hxx"
#include "ShaderManager.hxx"
#include "TextureManager.hxx"
#include "Camera.hxx"
#include "GraphicUtils.h"
#include "FontManager.hxx"
#include "ObjModelLoader.hxx"
#include "CollisionChecker.hxx"
#include "Optional.h"
#include "UiManager.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

IGraphicsClass * cGraphicsClass::s_pGraphic= NULL;

//  *******************************************************************************************************************
cGraphicsClass::cGraphicsClass()
{

}

//  *******************************************************************************************************************
cGraphicsClass::~cGraphicsClass()
{
	Cleanup();
}

//  *******************************************************************************************************************
bool cGraphicsClass::VInitialize( const HWND & hWnd, const Base::cColor & bkColor, const bool bFullScreen,
	const bool bVsyncEnabled, const int iWidth, const int iHeight, const float fScreenDepth,const float fScreenNear)
{
	IUiManager::CreateAsService();

	SP_ASSERT_FATAL(IDXBase::GetInstance() != NULL);
	if (IDXBase::GetInstance() != NULL)
	{
		return IDXBase::GetInstance()->VInitialize(hWnd, bkColor, bFullScreen, bVsyncEnabled, iWidth, iHeight, fScreenDepth, fScreenNear);
	}
	return false;
}

//  *******************************************************************************************************************
tOptional<bool> cGraphicsClass::VOnWindowResized(const int iNewWidth, const int iNewHeight)
{
	return IDXBase::GetInstance()->VOnWindowResized(iNewWidth, iNewHeight);
}

//  *******************************************************************************************************************
void cGraphicsClass::VSetFullScreenMode(const bool bIsFullScreen)
{
	return IDXBase::GetInstance()->VSetFullScreenMode(bIsFullScreen);
}

//  *******************************************************************************************************************
void cGraphicsClass::Cleanup()
{
	IFontManager::Destroy();
	IShaderManager::Destroy();
	ITextureManager::Destroy();
	IObjModelLoader::Destroy();
	ICollisionChecker::Destroy();
	IGraphicUtils::Destroy();
	IDXBase::Destroy();
}

//  *******************************************************************************************************************
void cGraphicsClass::VBeginRender()
{
	IDXBase::GetInstance()->VBeginRender();
}

//  *******************************************************************************************************************
void cGraphicsClass::VEndRender()
{
	IDXBase::GetInstance()->VEndRender();
}

//  *******************************************************************************************************************
IGraphicsClass * IGraphicsClass::GetInstance()
{
	if(cGraphicsClass::s_pGraphic == NULL)
		cGraphicsClass::s_pGraphic = DEBUG_NEW cGraphicsClass();
	return cGraphicsClass::s_pGraphic ;
}

//  *******************************************************************************************************************
void IGraphicsClass::Destroy()
{
	SafeDelete(&cGraphicsClass::s_pGraphic);
}

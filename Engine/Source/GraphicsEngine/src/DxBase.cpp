#include "stdafx.h"
#include "DxBase.h" 
#include "optional.h"

using namespace Utilities;
using namespace Base;
using namespace Graphics;

IDXBase * cDXBase::s_pDXBase = NULL;

// ********************************************************************************************************************
cDXBase::cDXBase()
	: m_bVsyncEnabled(false)
	, m_pSwapChain(NULL)
	, m_pDevice(NULL)
	, m_pDeviceContext(NULL)
	, m_pRenderTargetView(NULL)
	, m_pDepthStencilBuffer(NULL)
	, m_p3DDepthStencilState(NULL)
	, m_p2DDepthStencilState(NULL)
	, m_pDepthStencilView(NULL)
	, m_pRasterState(NULL)
	, m_iScreenWidth(0)
	, m_iScreenHeight(0)
	, m_pAlphaEnableBlendingState(NULL)
	, m_pAlphaDisableBlendingState(NULL)
{

}

// ********************************************************************************************************************
cDXBase::~cDXBase()
{
	Cleanup();
}

// ********************************************************************************************************************
bool cDXBase::VInitialize( const HWND & hWnd, const Base::cColor & bkColor, const bool bFullScreen,
	const bool bVsyncEnabled, const int iWidth, const int iHeight, const float fScreenDepth, const float fScreenNear)
{
	m_bVsyncEnabled = bVsyncEnabled;
	m_iScreenWidth = iWidth;
	m_iScreenHeight = iHeight;

	bkColor.GetColorComponentsInFloat(m_afBackGroundcolor[0], m_afBackGroundcolor[1], m_afBackGroundcolor[2], m_afBackGroundcolor[3]);

	if(!SetupRenderTargets(iWidth, iHeight, hWnd, bFullScreen))
		return false;

	if(!SetupRasterStates())
		return false;

	if(!CreateBlendStates())
		return false;

	SetupViewPort(0, 0, iWidth, iHeight);

	SetupProjectionMatrix(iWidth, iHeight, fScreenNear, fScreenDepth);
	XMStoreFloat4x4(&m_matWorld, XMMatrixIdentity());

	XMMATRIX matOrtho = XMMatrixOrthographicLH((float)iWidth, (float)iHeight, fScreenNear, fScreenDepth);
	XMStoreFloat4x4(&m_matOrtho, matOrtho);

	VTurnOnAlphaBlending();

	VSetFullScreenMode(bFullScreen, iWidth, iHeight);

	return true;
}

// ********************************************************************************************************************
void cDXBase::VBeginRender()
{
	// Clear the back buffer.
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, m_afBackGroundcolor);

	// Clear the depth buffer.
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

// ********************************************************************************************************************
void cDXBase::VEndRender()
{
	// Present the back buffer to the screen since rendering is complete.
	if(m_bVsyncEnabled)
	{
		// Lock to screen refresh rate.
		m_pSwapChain->Present(1, 0);
	}
	else
	{
		// Present as fast as possible.
		m_pSwapChain->Present(0, 0);
	}

}

// ********************************************************************************************************************
ID3D11Device * cDXBase::VGetDevice() const
{
	return m_pDevice;
}

// ********************************************************************************************************************
ID3D11DeviceContext * cDXBase::VGetDeviceContext() const
{
	return m_pDeviceContext;
}

// ********************************************************************************************************************
const XMFLOAT4X4 & cDXBase::VGetWorldMatrix() const
{
	return m_matWorld;
}

// ********************************************************************************************************************
const XMFLOAT4X4 & cDXBase::VGetProjectionMatrix() const
{
	return m_matProjection;
}

// ********************************************************************************************************************
const XMFLOAT4X4 & cDXBase::VGetOrthoMatrix() const
{
	return m_matOrtho;
}

// ********************************************************************************************************************
int cDXBase::VGetScreenWidth() const
{
	return m_iScreenWidth;
}

// ********************************************************************************************************************
int cDXBase::VGetScreenHeight() const
{
	return m_iScreenHeight;
}

// ********************************************************************************************************************
void cDXBase::VTurnZBufferOn()
{
	m_pDeviceContext->OMSetDepthStencilState(m_p3DDepthStencilState, 1);
}

// ********************************************************************************************************************
void cDXBase::VTurnZBufferOff()
{
	m_pDeviceContext->OMSetDepthStencilState(m_p2DDepthStencilState, 1);
}

// ********************************************************************************************************************
void cDXBase::VTurnOnAlphaBlending()
{
	float blendFactor[4];

	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	// Turn on the alpha blending.
	m_pDeviceContext->OMSetBlendState(m_pAlphaEnableBlendingState, blendFactor, 0xffffffff);
}

// ********************************************************************************************************************
void cDXBase::VTurnOffAlphaBlending()
{
	float blendFactor[4];

	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	// Turn on the alpha blending.
	m_pDeviceContext->OMSetBlendState(m_pAlphaDisableBlendingState, blendFactor, 0xffffffff);
}

// ******************************************************************************************************************************
void cDXBase::VSetFullScreenMode(const bool bIsFullScreen)
{
	VSetFullScreenMode(bIsFullScreen, m_iScreenWidth, m_iScreenHeight);
}

// ******************************************************************************************************************************
void cDXBase::VSetFullScreenMode(const bool bIsFullScreen, const int iNewWidth, const int iNewHeight)
{
	if(iNewWidth == 0 || iNewHeight == 0)
	{
		return;
	}
	if (m_pSwapChain)
	{
		m_pDeviceContext->OMSetRenderTargets(0, 0, 0);

		SafeRelease(&m_pRenderTargetView);
		SafeRelease(&m_pDepthStencilBuffer);
		SafeRelease(&m_pDepthStencilView);

		DXGI_SWAP_CHAIN_DESC scd;
		m_pSwapChain->GetDesc(&scd);
		if(bIsFullScreen)
		{
			m_pSwapChain->ResizeTarget(&scd.BufferDesc);
			m_pSwapChain->SetFullscreenState(true, NULL);
			ZeroMemory(&scd.BufferDesc.RefreshRate, sizeof(scd.BufferDesc.RefreshRate));
			m_pSwapChain->ResizeTarget(&scd.BufferDesc);
		}
		else
		{
			//m_pSwapChain->ResizeTarget(&scd.BufferDesc);
			m_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN , DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
			m_pSwapChain->SetFullscreenState(false, NULL);
		}

		AttachBackBufferToSwapChain();
		CreateDepthStencilBuffer(iNewWidth, iNewHeight);
		CreateDepthStencilView();
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
		SetupViewPort(0, 0, iNewWidth, iNewHeight);
	}
}

// ********************************************************************************************************************
tOptional<bool> cDXBase::VOnWindowResized(const int iNewWidth, const int iNewHeight)
{
	if (m_pSwapChain)
	{
		BOOL bFullScreen;
		m_pSwapChain->GetFullscreenState(&bFullScreen, NULL);
		VSetFullScreenMode(bFullScreen, iNewWidth, iNewHeight);

		return bFullScreen;
	}
	return tOptional<bool>();
}

// ********************************************************************************************************************
bool cDXBase::SetupRenderTargets(const int iWidth, const int iHeight, const HWND & hWnd, const bool bFullScreen)
{
	if(!SetupSwapChain(iWidth, iHeight, hWnd))
		return false;

	if(!CreateDepthStencilBuffer(iWidth, iHeight))
		return false;

	if(!SetupDepthStencilStateFor3D())
		return false;

	if(!SetupDepthStencilStateFor2D())
		return false;

	m_pDeviceContext->OMSetDepthStencilState(m_p3DDepthStencilState, 1);

	if(!CreateDepthStencilView())
		return false;

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);


	IDXGIDevice * pDXGIDevice;
	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);

	IDXGIAdapter * pDXGIAdapter;
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);
	pDXGIDevice->Release();

	IDXGIFactory * pIDXGIFactory;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&pIDXGIFactory);
	pDXGIAdapter->Release();

	pIDXGIFactory->MakeWindowAssociation(hWnd, 0);
	pIDXGIFactory->Release();

	return true;
}

// ********************************************************************************************************************
bool cDXBase::SetupSwapChain(const int iWidth, const int iHeight, const HWND & hWnd)
{
	if(!GetDisplayMode(iWidth, iHeight))
		return false;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 2;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
	swapChainDesc.BufferDesc.Width = iWidth;
	swapChainDesc.BufferDesc.Height = iHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	if(m_bVsyncEnabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = m_DisplayMode.RefreshRate.Numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = m_DisplayMode.RefreshRate.Denominator;
	}
	/*else
	{
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}*/

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	swapChainDesc.Windowed = true;

	unsigned int iCreationFlags = 0;//DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
#ifdef _DEBUG
	//iCreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_SOFTWARE
	};

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT result;
	for( int i = 0; i < 4; ++i)
	{
		result = D3D11CreateDeviceAndSwapChain(NULL, driverTypes[0],
			NULL, iCreationFlags, NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, 
			&m_pSwapChain, &m_pDevice, &featureLevel, &m_pDeviceContext);

		if( SUCCEEDED( result))
			break;
	}
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create the swap chain, Direct3D device, and Direct3D device context");
		return false;
	}

	ID3D11Debug *d3dDebug = nullptr;
	if(SUCCEEDED(m_pDevice->QueryInterface( __uuidof(ID3D11Debug), (void**)&d3dDebug)))
	{
		ID3D11InfoQueue *d3dInfoQueue = nullptr;
		if( SUCCEEDED( d3dDebug->QueryInterface( __uuidof(ID3D11InfoQueue), (void**)&d3dInfoQueue)))
		{
#ifdef _DEBUG
			d3dInfoQueue->SetBreakOnSeverity( D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
			d3dInfoQueue->SetBreakOnSeverity( D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
			D3D11_MESSAGE_ID hide [] =
			{
				D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
				// Add more message IDs here as needed
			};

			D3D11_INFO_QUEUE_FILTER filter;
			memset( &filter, 0, sizeof(filter));
			filter.DenyList.NumIDs = _countof(hide);
			filter.DenyList.pIDList = hide;
			d3dInfoQueue->AddStorageFilterEntries( &filter);
			d3dInfoQueue->Release();
		}
		d3dDebug->Release();
	}

	if(!AttachBackBufferToSwapChain())
		return false;

	return true;
}

// ********************************************************************************************************************
bool cDXBase::SetupDepthStencilStateFor3D()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	HRESULT result = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_p3DDepthStencilState);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create the depth stencil state");
		return false;
	}

	return true;
}

// ********************************************************************************************************************
bool cDXBase::SetupDepthStencilStateFor2D()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	HRESULT result = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_p2DDepthStencilState);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create the depth stencil state for 2D drawing");
		return false;
	}

	return true;
}

// ********************************************************************************************************************
bool cDXBase::CreateDepthStencilView()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	HRESULT result = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create the depth stencil view");
		return false;
	}
	return true;
}

// ********************************************************************************************************************
bool cDXBase::CreateBlendStates()
{
	D3D11_BLEND_DESC blendStateDescription;
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));

	// Create an alpha enabled blend state description.
	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	HRESULT result = m_pDevice->CreateBlendState(&blendStateDescription, &m_pAlphaEnableBlendingState);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create the blend State");
		return false;
	}

	blendStateDescription.RenderTarget[0].BlendEnable = FALSE;

	result = m_pDevice->CreateBlendState(&blendStateDescription,
		&m_pAlphaDisableBlendingState);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create the blend State");
		return false;
	}
	return true;
}

// ********************************************************************************************************************
bool cDXBase::SetupRasterStates()
{
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	HRESULT result = m_pDevice->CreateRasterizerState(&rasterDesc, &m_pRasterState);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create the raster  State");
		return false;
	}

	m_pDeviceContext->RSSetState(m_pRasterState);
	return true;
}

// ********************************************************************************************************************
void cDXBase::SetupViewPort(const int x, const int y, const int width, const int height)
{
	D3D11_VIEWPORT viewport;
	// Setup the viewport for rendering.
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = static_cast<float>(x);
	viewport.TopLeftY = static_cast<float>(y);

	// Create the viewport.
	m_pDeviceContext->RSSetViewports(1, &viewport);
}

// ********************************************************************************************************************
bool cDXBase::GetDisplayMode(const int iWidth, const int iHeight)
{
	HRESULT result;

	IDXGIFactory * pFactory = NULL;
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create IDXGIFactory factory");
		return false;
	}

	IDXGIAdapter * pAdapter = NULL;
	result = pFactory->EnumAdapters(0, &pAdapter);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create an adapter for the video card");
		return false;
	}

	IDXGIOutput* pAdapterOutput = NULL;
	result = pAdapter->EnumOutputs(0, &pAdapterOutput);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not Enumerate the monitor");
		return false;
	}

	unsigned int iNumModes;
	result = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &iNumModes, NULL);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not get the number of modes for the monitor with DXGI_FORMAT_R8G8B8A8_UNORM display format");
		return false;
	}

	DXGI_MODE_DESC * pDisplayModeList = DEBUG_NEW DXGI_MODE_DESC[iNumModes];
	result = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED, &iNumModes, pDisplayModeList);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not get the display modes for this monitor/video card combination.");
		return false;
	}

	// Get the numerator and denominator for the refresh rate
	for(unsigned int i = 0; i < iNumModes; i++)
	{
		if(pDisplayModeList[i].Width == (unsigned int)iWidth)
		{
			if(pDisplayModeList[i].Height == (unsigned int)iHeight)
			{
				m_DisplayMode = pDisplayModeList[i];
				break;
			}
		}
	}

	SafeDelete(&pDisplayModeList);
	SafeRelease(&pAdapterOutput);
	SafeRelease(&pAdapter);
	SafeRelease(&pFactory);

	return true;
}

// ********************************************************************************************************************
bool cDXBase::AttachBackBufferToSwapChain()
{
	ID3D11Texture2D * pbackBufferTexture = NULL;
	bool bSuccess = true;
	HRESULT result = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), 
		(LPVOID*)&pbackBufferTexture);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not get a pointer to the back buffer");
		PostQuitMessage(0);
		bSuccess = false;
	}
	else
	{
		result = m_pDevice->CreateRenderTargetView(pbackBufferTexture, NULL, &m_pRenderTargetView);
		if(FAILED(result))
		{
			SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create a render target view with the back buffer pointer.");
			bSuccess = false;
		}
	}
	SetDebugObjectName(pbackBufferTexture, "BackBufferTexture");
	SafeRelease(&pbackBufferTexture);
	return bSuccess;
}

// ********************************************************************************************************************
bool cDXBase::CreateDepthStencilBuffer( const int iWidth, const int iHeight)
{
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = iWidth;
	depthBufferDesc.Height = iHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	HRESULT result = m_pDevice->CreateTexture2D(&depthBufferDesc, NULL, &m_pDepthStencilBuffer);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create the 2D texture for the depth buffer");
		return false;
	}
	SetDebugObjectName(m_pDepthStencilBuffer, "DepthStencilBuffer");
	return true;
}

// ********************************************************************************************************************
void cDXBase::SetupProjectionMatrix( const int iWidth, const int iHeight, const float fScreenNear, const float fScreenDepth)
{
	float fFieldOfView= (float)Pi / 4.0f;
	float fScreenAspect = (float)iWidth / (float)iHeight;

	// Create the projection matrix for 3D rendering.
	XMMATRIX matProjection = XMMatrixPerspectiveFovLH(fFieldOfView, fScreenAspect, fScreenNear, fScreenDepth);
	XMStoreFloat4x4(&m_matProjection, matProjection);
}

// ********************************************************************************************************************
void cDXBase::DumpDirectXInfo()
{
#ifdef _DEBUG
	if(m_pDevice != NULL)
	{
		ID3D11Debug * pD3dDebug = NULL;
		if(SUCCEEDED(m_pDevice->QueryInterface( __uuidof(ID3D11Debug), (void**)&pD3dDebug)))
		{
			pD3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
			pD3dDebug->Release();
		}
	}
#endif
}

// ********************************************************************************************************************
void cDXBase::Cleanup()
{
	SafeRelease(&m_pRasterState);
	SafeRelease(&m_pDepthStencilView);
	SafeRelease(&m_p3DDepthStencilState);
	SafeRelease(&m_p2DDepthStencilState);
	SafeRelease(&m_pDepthStencilBuffer);
	SafeRelease(&m_pRenderTargetView);
	SafeRelease(&m_pAlphaEnableBlendingState);
	SafeRelease(&m_pAlphaDisableBlendingState);

	// Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
	if(m_pSwapChain != NULL)
	{
		m_pSwapChain->SetFullscreenState(false, NULL);
	}
	SafeRelease(&m_pSwapChain);
	SafeRelease(&m_pDeviceContext);
	DumpDirectXInfo();

	SafeRelease(&m_pDevice);
}

// ********************************************************************************************************************
IDXBase * IDXBase::GetInstance()
{
	if (cDXBase::s_pDXBase == NULL)
		cDXBase::s_pDXBase = DEBUG_NEW cDXBase();
	return cDXBase::s_pDXBase ;
}

// ********************************************************************************************************************
void IDXBase::Destroy()
{
	SafeDelete(&cDXBase::s_pDXBase);
}
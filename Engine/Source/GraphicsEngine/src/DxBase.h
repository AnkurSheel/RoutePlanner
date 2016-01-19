// *****************************************************************************
//  DxBase   version:  1.0   Ankur Sheel  date: 04/29/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef DxBase_h__
#define DxBase_h__

#include "DxBase.hxx"

namespace Graphics
{
	////////////////////////////////////////////////////////////////////////////
    /// @brief Class Declaration for \c IDXBase interface
	///
	///
    ////////////////////////////////////////////////////////////////////////////
	class cDXBase
		: public IDXBase
		, public Base::cNonCopyable
	{
	private:
		cDXBase() ;
		~cDXBase() ;
		bool VInitialize(const HWND & hWnd, const Base::cColor & bkColor,
			const bool bFullScreen, const bool bVsyncEnabled, const int iWidth,
			const int iHeight, const float fScreenDepth, const float fScreenNear);
		void VBeginRender();
		void VEndRender();
		void VTurnZBufferOn();
		void VTurnZBufferOff();
		void VTurnOnAlphaBlending();
		void VTurnOffAlphaBlending();
		void VSetFullScreenMode(const bool bIsFullScreen, const int iNewWidth,
			const int iNewHeight);
		void VSetFullScreenMode(const bool bIsFullScreen);
		ID3D11Device * VGetDevice() const;
		ID3D11DeviceContext * VGetDeviceContext() const;
		const XMFLOAT4X4 & VGetWorldMatrix() const;
		const XMFLOAT4X4 & VGetProjectionMatrix() const;
		const XMFLOAT4X4 & VGetOrthoMatrix() const;
		int VGetScreenWidth() const;
		int VGetScreenHeight() const;
		Base::tOptional<bool> VOnWindowResized(const int iNewWidth, const int iNewHeight);
		////////////////////////////////////////////////////////////////////////
		/// Sets up the device, swap chain, depth buffer, depth stencil state. 
		/// Bind the render target view and the depth stencil buffer to the 
		/// output render pipeline.
		///
		/// @param[in] iWidth The width of the window
		/// @param[in] iHeight The height of the window
		/// @param[in] hWnd A handle to the current window
		/// @param[in] bFullScreen True if the application is full screen.
		/// False if Windowed
		/// @return False if there was an error
        ///
		////////////////////////////////////////////////////////////////////////
		bool SetupRenderTargets(const int iWidth, const int iHeight,
			const HWND & hWnd, const bool bFullScreen);
		////////////////////////////////////////////////////////////////////////
		/// Fills out the swap chain description and creates the device and
		/// swap chain
		///
		/// @param[in] iWidth The width of the window
		/// @param[in] iHeight The height of the window
		/// @param[in] hWnd A handle to the current window
		/// @return False if there was an error
        ///
		////////////////////////////////////////////////////////////////////////
		bool SetupSwapChain(const int iWidth, const int iHeight, const HWND & hWnd);
		////////////////////////////////////////////////////////////////////////
		/// Creates the depth stencil state for 3D.
		///
		/// @return False if there was an error
        ///
		////////////////////////////////////////////////////////////////////////
		bool SetupDepthStencilStateFor3D();
		////////////////////////////////////////////////////////////////////////
		/// Creates the depth stencil state for 2D drawing.
		///
		/// @return False if there was an error
        ///
		////////////////////////////////////////////////////////////////////////
		bool SetupDepthStencilStateFor2D();
		////////////////////////////////////////////////////////////////////////
		/// Creates the blend states
		///
		/// @return False if there was an error
        ///
		////////////////////////////////////////////////////////////////////////
		bool CreateBlendStates();
		////////////////////////////////////////////////////////////////////////
		/// Creates a rasterizer state
		///
		/// @return False if there was an error
        ///
		////////////////////////////////////////////////////////////////////////
		bool SetupRasterStates();
		////////////////////////////////////////////////////////////////////////
		/// Sets up the viewport so that Direct3D can map clip space coordinates
		/// to the render target space
		///
		/// @param[in] x The left corner of the window
		/// @param[in] y The top corner of the window
    /// @param[in] width The width of the window
		/// @param[in] height The height of the window
    ///
		////////////////////////////////////////////////////////////////////////
		void SetupViewPort(const int x, const int y, const int width, const int height);
		////////////////////////////////////////////////////////////////////////
		/// Stores the selected display mode in m_DisplayMode
		///
		/// @param[in] iWidth The width of the window
		/// @param[in] iHeight The height of the window
		/// @return False if there was an error
        ///
		////////////////////////////////////////////////////////////////////////
		bool GetDisplayMode(const int iWidth, const int iHeigh);
		////////////////////////////////////////////////////////////////////////
		/// Gets a pointer to the back buffer and attaches it to the swap chain.
		///
		/// @return False if there was an error
        ///
		////////////////////////////////////////////////////////////////////////
		bool AttachBackBufferToSwapChain();
		////////////////////////////////////////////////////////////////////////
		/// Creates a Depth Buffer.
		///
		/// @param[in] iWidth The width of the window
		/// @param[in] iHeight The height of the window
		/// @return False if there was an error
        ///
		////////////////////////////////////////////////////////////////////////
		bool CreateDepthStencilBuffer( const int iWidth, const int iHeight );
		////////////////////////////////////////////////////////////////////////
		/// Sets the view of the depth stencil buffer so that Direct3D knows
		/// to use the depth buffer as a depth stencil texture
		///
		/// @return False if there was an error
        ///
		////////////////////////////////////////////////////////////////////////
		bool CreateDepthStencilView();
		////////////////////////////////////////////////////////////////////////
		/// Creates the projection matrix to translate the 3D scene into
		/// the 2D viewport space.
		///
		/// @param[in] iWidth Width of the window
		/// @param[in] iHeight Height of the window
		/// @param[in] fScreenDepth Far Depth setting for the 3D environment
		/// @param[in] fScreenNear Near Depth setting for the 3D environment
        ///
		////////////////////////////////////////////////////////////////////////
		void SetupProjectionMatrix(const int iWidth, const int iHeight,
			const float fScreenNear, const float fScreenDepth);
		////////////////////////////////////////////////////////////////////////
		/// Helper function to report information of directx resources that
		/// might be leaking.
		///
        ///
		////////////////////////////////////////////////////////////////////////
		void DumpDirectXInfo();
		////////////////////////////////////////////////////////////////////////
		/// Releases all the pointers
		///
        ///
		////////////////////////////////////////////////////////////////////////
		void Cleanup() ;

	private:
		bool						m_bVsyncEnabled;	///<< True if we want Direct3D to render according to the users monitor refresh rate. False if want it to go as fast as possible.
		IDXGISwapChain *			m_pSwapChain;	///<< The swap chain is the front and back buffer to which the graphics will be drawn.
		ID3D11Device *				m_pDevice;	///<< Pointer to the directX device to create resources
		ID3D11DeviceContext *		m_pDeviceContext;	///<< Pointer to a directX device context which generates rendering commands
		ID3D11RenderTargetView *	m_pRenderTargetView;	///<< The back buffer to be used as the render target
		ID3D11Texture2D *			m_pDepthStencilBuffer;	///<< Depth Buffer used to render polygons in 3D space
		ID3D11DepthStencilState *	m_p3DDepthStencilState;	///<< The depth stencil state allows us to control what type of depth test Direct3D will do for each pixel
		ID3D11DepthStencilState *	m_p2DDepthStencilState;	///<< The depth stencil state for 2D drawing
		ID3D11DepthStencilView *	m_pDepthStencilView;	///<< The depth stencil view for the render target
		ID3D11RasterizerState *		m_pRasterState;	///<< The rasterizer state give us control over how polygons are rendered.
		XMFLOAT4X4					m_matProjection;	///<< The projection matrix is used to translate the 3D scene into a 2D viewport space
		XMFLOAT4X4					m_matWorld;	///<< The world matrix is used to convert the vertices of our objects into vertices in the 3D scene.
		XMFLOAT4X4					m_matOrtho;	///<< The orthographic projection matrix is used for rendering 2D elements on the screen allowing us to skip the 3D rendering
		float						m_afBackGroundcolor[4];	///<< The components for the back
		int							m_iScreenWidth;	///<< Screen width
		int							m_iScreenHeight;	///<< Screen height
		ID3D11BlendState *			m_pAlphaEnableBlendingState;	///<< The blend state with AlphaBlending enabled
		ID3D11BlendState *			m_pAlphaDisableBlendingState;	///<< The blend state with AlphaBlending disbaled
		DXGI_MODE_DESC				m_DisplayMode;	///< The current display mode
		static IDXBase *			s_pDXBase;	///<< static object of this class

		friend static IDXBase * IDXBase::GetInstance();
		friend static void IDXBase::Destroy();
	};
}
#endif // DxBase_h__

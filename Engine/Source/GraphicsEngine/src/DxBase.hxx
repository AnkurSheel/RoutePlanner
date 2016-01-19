// *****************************************************************************
//  DxBase   version:  1.0   Ankur Sheel  date: 2011/02/16
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef DxBase_hxx__
#define DxBase_hxx__

namespace Base
{
	class cColor;
}

namespace Graphics
{
	struct stVertex;
}

namespace Graphics
{
	////////////////////////////////////////////////////////////////////////////
	/// @brief Interface for DirectX.
	///
	/// Singleton class.\n
	/// Usage :
	/// \li Call \c GetInstance() to use this class.
	/// \li Call \c Destroy() when the application quits
	///
	///
	////////////////////////////////////////////////////////////////////////////
	class IDXBase
	{
	public:
		virtual ~IDXBase(){}
		static IDXBase * GetInstance();
		static void Destroy();
		////////////////////////////////////////////////////////////////////////
		/// Initializes the DirectX device and sets it up for use. 
		///
		/// @param[in] hWnd A handle to the current window
		/// @param[in] bkColor The default background color of the window
		/// @param[in] bFullScreen True if the application is full screen.
		/// False if Windowed.
		/// @param[in] bVsyncEnabled True if we want Direct3D to render
		/// according to the users monitor refresh rate. False if we want to 
		/// render as fast as possible.
		/// @param[in] iWidth Width of the window
		/// @param[in] iHeight Height of the window
		/// @param[in] fScreenDepth Far Depth setting for the 3D environment
		/// @param[in] fScreenNear Near Depth setting for the 3D environment.
		/// @return True if Successful. False otherwise.
        ///
		////////////////////////////////////////////////////////////////////////
		virtual bool VInitialize(const HWND & hWnd, 
			const Base::cColor & bkColor, const bool bFullScreen, 
			const bool bVsyncEnabled, const int iWidth, const int iHeight,
			const float fScreenDepth, const float fScreenNear) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Begins the rendering and clears the surface
		///
        ///
		////////////////////////////////////////////////////////////////////////
		virtual void VBeginRender() = 0;
		////////////////////////////////////////////////////////////////////////
		/// Ends the rendering and presents the contents
		///
        ///
		////////////////////////////////////////////////////////////////////////
		virtual void VEndRender() = 0;
		////////////////////////////////////////////////////////////////////////
		/// Turns the Z buffer on for 3D rendering
		///
        ///
		////////////////////////////////////////////////////////////////////////
		virtual void VTurnZBufferOn() = 0;
		////////////////////////////////////////////////////////////////////////
		/// Turns the Z buffer off for 2D rendering
		///
        ///
		////////////////////////////////////////////////////////////////////////
		virtual void VTurnZBufferOff() = 0;
		////////////////////////////////////////////////////////////////////////
		/// Turns Alpha Blending On
		///
        ///
		////////////////////////////////////////////////////////////////////////
		virtual void VTurnOnAlphaBlending() = 0;
		////////////////////////////////////////////////////////////////////////
		/// Turns Alpha Blending Off
		///
        ///
		////////////////////////////////////////////////////////////////////////
		virtual void VTurnOffAlphaBlending() = 0;
		////////////////////////////////////////////////////////////////////////
		/// Returns a pointer to the DirectX11 device
		///
		/// @return The pointer to DX11 device
        ///
		////////////////////////////////////////////////////////////////////////
		virtual ID3D11Device * VGetDevice() const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Returns a pointer to the DirectX11 device context
		///
		/// @return The pointer to DX11 device context
        ///
		////////////////////////////////////////////////////////////////////////
		virtual ID3D11DeviceContext * VGetDeviceContext() const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Returns the world matrix
		///
		/// @return The World Matrix
        ///
		////////////////////////////////////////////////////////////////////////
		virtual const XMFLOAT4X4 & VGetWorldMatrix() const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Returns the projection matrix
		///
		/// @return The projection matrix
        ///
		////////////////////////////////////////////////////////////////////////
		virtual const XMFLOAT4X4 & VGetProjectionMatrix() const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Returns the ortho matrix
		///
		/// @return The ortho matrix
        ///
		////////////////////////////////////////////////////////////////////////
		virtual const XMFLOAT4X4 & VGetOrthoMatrix() const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Returns the screen width
		///
		/// @return The screen width
        ///
		////////////////////////////////////////////////////////////////////////
		virtual int VGetScreenWidth() const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Returns the screen height
		///
		/// @return The screen height
        ///
		////////////////////////////////////////////////////////////////////////
		virtual int VGetScreenHeight() const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Sets the full screen/windowed mode for the DirectX engine
		///
		/// @param[in] iNewWidth The new width of the window
		/// @param[in] iNewHeight The new height of the window
		/// @return True if fullscreen. False otherwise
        ///
		////////////////////////////////////////////////////////////////////////
		virtual void VSetFullScreenMode(const bool bIsFullScreen, const int iNewWidth,
			const int iNewHeight) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Sets the full screen/windowed mode for the DirectX engine
		///
		/// @return True if fullscreen. False otherwise
        ///
		////////////////////////////////////////////////////////////////////////
		virtual void VSetFullScreenMode(const bool bIsFullScreen) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Callback for when the window is resized
		///
		/// @param[in] iNewWidth The new width of the window
		/// @param[in] iNewHeight The new height of the window
		/// @return True if we are in full screen mode. False otherwise
		///
		////////////////////////////////////////////////////////////////////////
		virtual Base::tOptional<bool> VOnWindowResized(const int iNewWidth, const int iNewHeight) = 0;
	};
}
#endif // DxBase_h__
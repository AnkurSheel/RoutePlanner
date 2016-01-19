// *****************************************************************************
//  GraphicsClass   version:  1.0   Ankur Sheel  date: 2012/09/13
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef GraphicsClass_hxx__
#define GraphicsClass_hxx__

#include "GraphicEngineDefines.h"

namespace Base
{
	class cColor;
	class cVector2;
	class cVector3;
}

namespace Graphics
{
	class ICamera;
}

namespace Graphics
{
	////////////////////////////////////////////////////////////////////////////
	/// @brief Interface to encapsulate all the graphics functionality
	/// 
	/// Singleton class.\n
	/// Usage :
	/// \li Call \c GetInstance() to use this class.
	/// \li Call \c VOnDestroy() when the application quits
	/// 
	/// 
	////////////////////////////////////////////////////////////////////////////
	class IGraphicsClass
	{
	public:
		////////////////////////////////////////////////////////////////////////
		/// Creates and returns a pointer to a singleton object of this
		/// interface
		///
		/// @return Returns a pointer to the singleton object
        ///
		////////////////////////////////////////////////////////////////////////
		GRAPHIC_API static IGraphicsClass * GetInstance();
		////////////////////////////////////////////////////////////////////////
		/// Releases the DirectX object and deletes the singleton object
		///
        ///
		////////////////////////////////////////////////////////////////////////
		GRAPHIC_API static void Destroy();
		////////////////////////////////////////////////////////////////////////
		/// Creates the DirectX object and Initializes the DirectX system.
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
		/// @param[in] fScreenNear Near Depth setting for the 3D environment
		/// @return True if Successful. False otherwise
        ///
		////////////////////////////////////////////////////////////////////////
		virtual bool VInitialize(const HWND & hWnd, const Base::cColor & bkColor,
			const bool bFullScreen, const bool bVsyncEnabled, const int iWidth,
			const int iHeight, const float fScreenDepth, const float fScreenNear) = 0;
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
		/// Callback for when the window is resized
		///
		/// @param[in] iNewWidth The new width of the window
		/// @param[in] iNewHeight The new height of the window
		/// @return True if we are in full screen mode. False otherwise
		///
		////////////////////////////////////////////////////////////////////////
		virtual Base::tOptional<bool> VOnWindowResized(const int iNewWidth, const int iNewHeight) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Sets the full screen/windowed mode for the DirectX engine
		///
		/// @param[in] bIsFullScreen True if fullscreen. False otherwise
		///
		////////////////////////////////////////////////////////////////////////
		virtual void VSetFullScreenMode(const bool bIsFullScreen) = 0;
		virtual ~IGraphicsClass(){}
	};
}
#endif // GraphicsClass_hxx__
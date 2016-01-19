// *****************************************************************************
//  GraphicsClass   version:  1.0   Ankur Sheel  date: 2012/09/13
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef GraphicsClass_h__
#define GraphicsClass_h__

#include "GraphicsClass.hxx"

namespace Graphics
{
	class IDXBase;
}

namespace Graphics
{
	////////////////////////////////////////////////////////////////////////////
	/// @brief Class Declaration for \c IGraphicsClass interface
	///
	///
	////////////////////////////////////////////////////////////////////////////
	class cGraphicsClass
		: public IGraphicsClass
		, public Base::cNonCopyable
	{
	private:
		bool VInitialize(const HWND & hWnd, const Base::cColor & bkColor,
			const bool bFullScreen, const bool bVsyncEnabled, const int iWidth,
			const int iHeight, const float fScreenDepth, const float fScreenNear);
		void VBeginRender();
		void VEndRender();
		void VSetFullScreenMode(const bool bIsFullScreen);
		Base::tOptional<bool> VOnWindowResized(const int iNewWidth, const int iNewHeight);
		/********************************************//**
		 *
		 * Releases all the resources
		 ***********************************************/
		void Cleanup();

	private:
		cGraphicsClass();
		~cGraphicsClass();

	private:
		static IGraphicsClass * s_pGraphic;	///< static object of this class

	private:
		friend static IGraphicsClass * IGraphicsClass::GetInstance();
		friend static void IGraphicsClass::Destroy();
	};
}
#endif // GraphicsClass_h__
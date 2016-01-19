//  *******************************************************************************************************************
//  MainWindow   version:  1.0   Ankur Sheel  date: 2011/02/16
//  -------------------------------------------------------------------------------------------------------------------
//  Interface for Main Window
//  -------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef MainWindow_hxx__
#define MainWindow_hxx__

#include "GameBaseDefines.h"

namespace GameBase
{
	class IBaseApp;
}

namespace GameBase
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Interface to Create the Window.
	///
	/// Singleton class.\n
	/// Usage :
	/// \li Call \c GetInstance() to use this class.
	/// \li Call \c Destroy() when the application quits
	///
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class IMainWindow
	{
	public:
		virtual ~IMainWindow() {}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Initializes, Registers and creates the window. Returns a handle to the created window.
		///
		/// @param[in] hInstance A handle to the current instance of the application
		/// @param[in] nCmdShow Controls how the window is to be shown
		/// @param[in] pGame A pointer to the the IBaseApp object
		/// @return Handle to the created window
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual HWND VOnInitialization(const HINSTANCE & hInstance,	const int & nCmdShow, IBaseApp* const pGame) = 0;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Handler for when the window is resized i.e WM_SIZE message is received
		///
		/// @param[in] iNewWidth The new width of the window
		/// @param[in] iNewHeight The new height of the window
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void VOnWindowResized(const int iNewWidth, const int iNewHeight) = 0;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Destroys the Window
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void VCleanup() = 0;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Creates and returns a pointer to a singleton object of this class
		///
		/// @return Returns a pointer to the singleton object
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		GAMEBASE_API static IMainWindow * const GetInstance();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Destroys the window and the singleton object
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		GAMEBASE_API static void Destroy();
	};
}
#endif // MainWindow_hxx__
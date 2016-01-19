//  ***************************************************************************
//  MainWindow   version:  1.0   Ankur Sheel  date: 04/28/2008
//  ----------------------------------------------------------------------------
//  Window for that application
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
//  ****************************************************************************
//
//  ****************************************************************************
#ifndef MainWindow_h__
#define MainWindow_h__

#include "MainWindow.hxx"

namespace GameBase
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Class Declaration for \c IMainWindow interface
	///
	///
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class cMainWindow
		: public IMainWindow
		, public Base::cNonCopyable
	{
	private:
		cMainWindow();
		~cMainWindow();
		HWND VOnInitialization(const HINSTANCE & hInstance, const int& nCmdShow, IBaseApp * const pGame);
		void VOnWindowResized(const int iNewWidth, const int iNewHeight);
		void VCleanup();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Event handler. Routes messages to appropriate instance.
		///
		/// @param[in] hWnd Unique handle to the window.
        /// @param[in] message Incoming message.
        /// @param[in] wParam Parameter of the message (unsigned int).
        /// @param[in] lParam Parameter of the message (long).
        ///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Register the window
		///
		///
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void RegisterWin() ;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Creates the window
		///
		/// @param[in] nCmdShow Controls how the window is to be shown
		/// @param[in] lpWindowTitle Controls how the window is to be shown
		/// @return True if Successful. False Otherwise
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool CreateMyWindow(const int& nCmdShow, const Base::cString& lpWindowTitle);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Window procedure to handle the window messages.
		///
		/// @param[in] hWnd Unique handle to the window.
        /// @param[in] message Incoming message.
        /// @param[in] wParam Parameter of the message (unsigned int).
        /// @param[in] lParam Parameter of the message (long).
        ///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Function called when the application is closed
		///
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void OnWindowDestroyed();
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Sets the settings of the default display device
		/// to the specified graphics mode.
		///
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void SetDisplayResolution();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Calculates and stores the window rectangle when
		/// the app is in windowed mode.
		///
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void CalculateWindowRect();

	private:
		const DWORD	m_kdwWindowedStyle;	///< The style when viewing in windowed mode
		HWND m_Hwnd;	///< Window handle
		HINSTANCE m_hInstance;	///< Application instance
		IBaseApp * m_pGame;	///< Pointer to the App
		RECT m_windowRect;	///< stores the window dimensions in windowed mode

	private:
		friend IMainWindow * const IMainWindow::GetInstance();
	};
}
#endif // MainWindow_h__

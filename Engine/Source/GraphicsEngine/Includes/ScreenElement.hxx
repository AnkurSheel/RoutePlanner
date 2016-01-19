// ***************************************************************
//  ScreenElement   version:  1.0   Ankur Sheel  date: 2011/05/05
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ScreenElement_hxx__
#define ScreenElement_hxx__

#include "GraphicEngineDefines.h"

namespace Base
{
	struct AppMsg;
}

namespace Graphics
{
	class ICamera;
}

namespace Graphics
{
	/********************************************//**
	 * @brief Interface to be used by all 2D elements.
	 *
	 ***********************************************/
	class IScreenElement
	{
	public:
		virtual ~IScreenElement(){};
		/********************************************//**
 		 * @param[in] pCamera The camera which contains the current view matrix
		 *
		 * Draws the control
		 ***********************************************/
		virtual void VRender(const ICamera * const pCamera) = 0;
		/********************************************//**
 		 * @param[in] bIsVisible True if the control should be visible, false otherwise
		 *
		 * Sets the visibility of the 2D element
		 ***********************************************/
		virtual void VSetVisible(bool bIsVisible) = 0;
	};
}
#endif // ScreenElement_hxx__
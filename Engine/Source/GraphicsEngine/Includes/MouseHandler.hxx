// ***************************************************************
//  MouseHandler   version:  1.0   Ankur Sheel  date: 2012/04/20
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef MouseHandler_hxx__
#define MouseHandler_hxx__

namespace Graphics
{
	/********************************************//**
	 * @brief Interface for Handling Mouse Clicks
	 *
	 * Should be implemented by all classes that want to
	 * handle mouse clicks
	 ***********************************************/
	class IMouseHandler
	{
	public:
		virtual ~IMouseHandler(){}
		/********************************************//**
 		 * @param[in] X The X position of the mouse
		 * @param[in] Y The Y position of the mouse
		 *
		 * Event Handler for left button down at (X,Y)
		 ***********************************************/
		virtual bool VOnLeftMouseButtonUp(const int X, const int Y) = 0;
		/********************************************//**
 		 * @param[in] X The X position of the mouse
		 * @param[in] Y The Y position of the mouse
		 *
		 * Event Handler for left button up at (X,Y)
		 ***********************************************/
		virtual bool VOnLeftMouseButtonDown(const int X, const int Y) = 0;
		/********************************************//**
 		 * @param[in] X The X position of the mouse
		 * @param[in] Y The Y position of the mouse
		 *
		 * Event Handler for mouse move
		 ***********************************************/
		virtual bool VOnMouseMove(const int X, const int Y) = 0;
	};
}

#endif // MouseHandler_h__
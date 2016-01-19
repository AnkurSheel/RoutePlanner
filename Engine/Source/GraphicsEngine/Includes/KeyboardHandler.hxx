// ***************************************************************
//  KeyboardHandler   version:  1.0   Ankur Sheel  date: 2012/04/20
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef KeyboardHandler_hxx__
#define KeyboardHandler_hxx__

namespace Graphics
{
	/********************************************//**
	 * @brief Interface for Handling key presses on the keyboard
	 *
	 * Should be implemented by all classes that want to
	 * handle key presses
	 ***********************************************/
	class IKeyboardHandler
	{
	public:
		virtual ~IKeyboardHandler(){}
		/********************************************//**
 		 * @param[int] iCharID The ascii value of the key that is pressed
		 *
		 * Event Handler for key down
		 ***********************************************/
		virtual bool VOnKeyDown(const unsigned int iCharID) = 0;
		/********************************************//**
 		 * @param[int] iCharID The ascii value of the key that is released
		 *
		 * Event Handler for key up
		 ***********************************************/
		virtual bool VOnKeyUp(const unsigned int iCharID) = 0;
		/********************************************//**
 		 * @param[int] iCharID The ascii value of the character key that is pressed
		 *
		 * Event Handler for character key pressed
		 ***********************************************/
		virtual bool VOnCharPress(const unsigned int iCharID) = 0;
	};
}

#endif // KeyboardHandler_h__
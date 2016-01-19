// *****************************************************************************
//  Sentence   version:  1.0   Ankur Sheel  date: 2012/10/10
//  ---------------------------------------------------------------------------
//  
//  ---------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Sentence_hxx__
#define Sentence_hxx__

#include "GraphicEngineDefines.h"

namespace Base
{
	class cString;
	class cColor;
}

namespace Graphics
{
	class ICamera;
	class IMyFont;
}

namespace Graphics
{
	/********************************************//**
	 * @brief Interface to encapsulate all the text 
	 * related functionality
	 ***********************************************/
	class ISentence
	{
	public:
		virtual ~ISentence(){}
		/********************************************//**
 		 * @param[in] strFont The font that will be used to display the text
		 * @param[in] strText The text to be rendered
		 * @param[in] textColor The color of the text
		 *
		 * Puts the text on the video card to prepare it for drawing
		 * by the shader
		 ***********************************************/
		virtual bool VInitialize(const Base::cString & strFont,
			const Base::cString & strText, const Base::cColor & textColor) = 0;
		/********************************************//**
 		 * @param[in] pCamera The camera which contains the current view matrix
		 *
		 * Puts the text on the video card to prepare it for drawing
		 * by the shader
		 ***********************************************/
		virtual void VRender(const ICamera * const pCamera) = 0;
		/********************************************//**
 		 * @param[in] vPosition The new position at which the text should be shown
		 *
		 * Sets the position of the text
		 ***********************************************/
		virtual void VSetPosition(const Base::cVector2 & vPosition) = 0;
		/********************************************//**
 		 * @param[in] strText The text that needs to be displayed
		 *
		 * Sets the text that needs to be shown
		 ***********************************************/
		virtual void VSetText(const Base::cString & strText) = 0;
		/********************************************//**
 		 * @param[in] colorText The text color
		 *
		 * Sets the color of the text
		 ***********************************************/
		virtual void VSetTextColor(const Base::cColor & colorText) = 0;
		/********************************************//**
 		 * @return The width of the sentence
		 *
		 * Gets the width of the sentence
		 ***********************************************/
		virtual float VGetWidth() const = 0;
		/********************************************//**
		 * @param[in] strText The text for which the width is needed
		 * @return The width of the sentence
		 *
		 * Gets the width of the sentence thats has been passed
		 * in strText
		 ***********************************************/
		virtual float VGetWidth(const Base::cString & strText) const = 0;
		/********************************************//**
 		 * @return The text 
		 *
		 * Gets the text of the sentence
		 ***********************************************/
		virtual Base::cString VGetText() const = 0;
		/********************************************//**
 		 * @return The height used by the sentence
		 *
		 * Gets the height of the characters of the sentence
		 ***********************************************/
		virtual float VGetHeight() const = 0;
		/********************************************//**
 		 * @param[in] fTextHeight The new height of the characters in the sentence
		 *
		 * Sets the new height of the characters in the sentence
		 ***********************************************/
		virtual void VSetHeight(const float fTextHeight) = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		GRAPHIC_API static ISentence * CreateSentence();
	};
}
#endif // Sentence_hxx__
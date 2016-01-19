// *****************************************************************************
//  Font   version:  1.0   Ankur Sheel  date: 2011/02/16
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Font_hxx__
#define Font_hxx__

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class IMyFont
	{
	public:
	/********************************************//**
     * @brief Structure to hold the various parameters
	 * defining the character
     ***********************************************/
	struct CharDescriptor
	{
		unsigned short id;			/*!< The character id */
		unsigned short x;			/*!< The left position of the character image in the font texture */
		unsigned short y;			/*!< The top position of the character image in the font texture */
		unsigned short Width;		/*!< TThe width of the character image in the font texture */
		unsigned short Height;		/*!< The height of the character image in the font texture */
		unsigned short XOffset;		/*!< How much the current position should be offset when copying the image from the font texture to the screen */
		unsigned short YOffset;		/*!< How much the current position should be offset when copying the image from the font texture to the screen */
		unsigned short XAdvance;	/*!< How much the current position should be advanced after drawing the character */

		CharDescriptor() 
			: id(0)
			, x(0)
			, y(0)
			, Width(0)
			, Height(0)
			, XOffset(0)
			, YOffset(0)
			, XAdvance(0)
		{
		}
	};

	/********************************************//**
     * @brief Vertex Data description for a character
     ***********************************************/
	struct stVertexData
	{
		CharDescriptor	ch;		/*!< The parameters describing the character */
		float			fTexU;	/*!< The U position of this character in the texture map */
		float			fTexV;	/*!< The V position of this character in the texture map */
		float			fTexU1;	/*!< The U1 position of this character in the texture map */
		float			fTexV1;	/*!< The V1 position of this character in the texture map */

		stVertexData()
			: fTexU(0.0f)
			, fTexV(0.0f)
			, fTexU1(0.0f)
			, fTexV1(0.0f)
		{
		}
	};

	public:
		virtual ~IMyFont(){}
		/********************************************//**
		 * @param[in] strFontDescFilename The file name of the font description file
		 *
		 * Parses the font description file and sets up the character descriptors.
		 * Creates and Initializes the font texture.
		 ***********************************************/
		virtual bool VInitialize(const Base::cString & strFontDescFilename) = 0;
		/********************************************//**
 		 * @param[in] inMatWorld The world matrix
		 * @param[in] inMatView The View Matrix
		 * @param[in] inMatProjection The projection Matrix
		 * @param[in] textColor The color of the text
		 *
		 * Sets the shader parameters and then draws the model
		 * using the HLSL shader
		 ***********************************************/
		virtual void VRender(const XMFLOAT4X4 & inMatWorld, const XMFLOAT4X4 & inMatView,
			const XMFLOAT4X4 & inMatProjection, const Base::cColor & textColor) = 0;
		/********************************************//**
 		 * @param[in] iCharAsciiValue The ascii value of the character
		 * @return The vertex data
		 *
		 * Returns the vertex data for a character with the 
		 * given ascii vakue
		 ***********************************************/
		virtual stVertexData VGetCharVertexData(const int iCharAsciiValue) = 0;
		/********************************************//**
		 * @return The height of the a line using this font
		 *
		 * Returns the height of the a line using this font
		 ***********************************************/
		virtual int VGetFontHeight() const = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		static IMyFont * CreateMyFont();
	} ;
}
#endif // Font_h__

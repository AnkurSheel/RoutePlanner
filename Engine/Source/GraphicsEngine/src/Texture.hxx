// ***************************************************************
//  Texture   version:  1.0   Ankur Sheel  date: 2011/11/23
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Texture_hxx__
#define Texture_hxx__

#include "GraphicEngineDefines.h"

namespace Base
{
	class cString;
}

namespace Graphics
{
	/********************************************//**
	 * @brief Interface to encapsulate the loading, 
	 * unloading, and accessing of a single texture resource
	 *
	 ***********************************************/
	class ITexture
	{
	public:
		virtual ~ITexture(){}
		/********************************************//**
		 * @return A pointer to the texture resource 
		 *
		 * Returns a pointer to the texture resource so that
		 * it can be used for rendering by shaders
		 ***********************************************/
		virtual ID3D11ShaderResourceView * VGetTexture() const = 0;
		/********************************************//**
 		 * param[in] strTexturePath The path of the texture
		 * @return An Object of this class
		 *
		 * Creates an object of this class and returns it
		 ***********************************************/
		static shared_ptr<ITexture> CreateTexture(const Base::cString & strTexturePath);
	};
}

#endif // Texture_hxx__
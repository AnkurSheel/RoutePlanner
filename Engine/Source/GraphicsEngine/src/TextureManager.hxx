// *************************************************************************
//  TextureManager   version:  1.0   Ankur Sheel  date: 2012/10/28
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class ITexture;
}

namespace Graphics
{
	/********************************************//**
	 * @brief Interface for texture manager.
	 *
	 * Use this class to create and assign Textures
	 * 
	 * Singleton class.\n
	 * Usage :
	 * \li Call \c GetInstance() to use this class.
	 * \li Call \c VOnDestroy() when the application quits
	 ***********************************************/
	class ITextureManager
	{
	public:
		virtual ~ITextureManager(){}
		/********************************************//**
 		 * param[in] strTexturePath The path of the texture file
		 * @return Pointer to the texture
		 *
		 * Loads and creates the texture if it has not been created already.
		 * Adds the texture to the texture list
		 * Returns a pointer to the existing texture otherwise
		 ***********************************************/
		virtual shared_ptr<ITexture> VGetTexture(const Base::cString & strTexturePath) = 0;

		static ITextureManager * GetInstance();
		static void Destroy();
	};
}
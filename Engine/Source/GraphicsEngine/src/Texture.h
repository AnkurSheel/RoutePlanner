// ***************************************************************
//  Texture   version:  1.0   Ankur Sheel  date: 2011/07/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#ifndef Texture_h__
#define Texture_h__

#include "Texture.hxx"

namespace Graphics 
{
    /********************************************//**
     * @brief Class Declaration for \c ITexture
     * interface
     ***********************************************/
	class cTexture
		: public ITexture
		, public Base::cNonCopyable
	{
	public:
		cTexture();
		~cTexture();
		/********************************************//**
 		 * @param[in] strTexturePath The path of the texture file
		 * return True if the texture is created. False otherwise
		 *
		 * Loads and creates the texture from the resource cache
		 ***********************************************/
		bool Initialize(const Base::cString & strTexturePath);

	private:
		ID3D11ShaderResourceView * VGetTexture() const;
		/********************************************//**
		 *
		 * Releases all the pointers
		 ***********************************************/
		void Cleanup();
	
	private:
		ID3D11ShaderResourceView *		m_pTexture;	/*!< The texture resource */
	};
}
#endif // Texture_h__

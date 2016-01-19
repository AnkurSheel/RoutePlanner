// *****************************************************************************
//  Shader   version:  1.0   Ankur Sheel  date: 2012/09/15
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Shader_hxx__
#define Shader_hxx__

namespace Graphics
{
	class ITexture;
}

namespace Graphics
{
	/********************************************//**
	 * @brief Interface to invoke the HLSL shaders
	 * for drawing the 3D models
	 ***********************************************/
	class IShader
	{
	public:
		virtual ~IShader(){}
		/********************************************//**
 		 * @param[in] strShaderName The name of the shader. This should be the same as the vertex and pixel shader files without the extension
		 * @return False if there is any error
		 *
		 * Creates the vertex and pixel shader objects. Creates the layout of the vertex
		 * data that will be processed by this shader
		 ***********************************************/
		virtual bool VInitialize(const Base::cString & strShaderName) = 0;
		/********************************************//**
 		 * @param[in] inMatWorld The world matrix
		 * @param[in] inMatView The View Matrix
		 * @param[in] inMatProjection The projection Matrix
		 * @return False if there is any error
		 *
		 * Sets the shader parameters and then draws the model
		 * using the HLSL shader
		 ***********************************************/
		virtual bool VRender(const XMFLOAT4X4 & inMatWorld, const XMFLOAT4X4 & inMatView,
			const XMFLOAT4X4 & inMatProjection) = 0;
		/********************************************//**
 		 * @param[in] pTexture The texture to be used by the shader
		 *
		 * Sets the texture to be used by the shader
		 ***********************************************/
		virtual void VSetTexture(shared_ptr<ITexture> pTexture) = 0;
		/********************************************//**
		 * @return An object to use a color shader
		 *
		 * Returns an object to use a color shader
		 ***********************************************/
		static IShader * const CreateColorShader();
		/********************************************//**
		 * @return An object to use a texture shader
		 *
		 * Returns an object to use a texture shader
		 ***********************************************/
		static IShader * const CreateTextureShader();
		/********************************************//**
		 * @return An object to use a font shader
		 *
		 * Returns an object to use a font shader
		 ***********************************************/
		static IShader * const CreateFontShader();
	};
}
#endif // Shader_hxx__
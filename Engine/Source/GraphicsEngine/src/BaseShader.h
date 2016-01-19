// *****************************************************************************
//  BaseShader   version:  1.0   Ankur Sheel  date: 2012/09/24
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef BaseShader_h__
#define BaseShader_h__

#include "Shader.hxx"

namespace Utilities
{
	class IResHandle;
}

namespace Graphics
{
    /********************************************//**
     * @brief Class Declaration for \c IShader
     * interface. Base class for All Shader classes
     ***********************************************/
	class cBaseShader
		: public IShader
		, public Base::cNonCopyable
	{
		/********************************************//**
		 * @brief Constant buffer to be passed to the shader.
		 ***********************************************/
		struct MatrixBufferType
		{
			XMFLOAT4X4 world;			/*!< The world matrix. */
			XMFLOAT4X4 view;			/*!< The view matrix. */
			XMFLOAT4X4 projection;		/*!< The projection matrix. */
		};

	public:
		void VSetTexture(shared_ptr<ITexture> pTexture);
		bool VRender(const XMFLOAT4X4 & inMatWorld, const XMFLOAT4X4 & inMatView,
			const XMFLOAT4X4 & inMatProjection);

	protected:
		cBaseShader();
		virtual ~cBaseShader();
		bool VInitialize(const Base::cString & strShaderName);
		/********************************************//**
 		 * @param[in] inMatWorld The world matrix
		 * @param[in] inMatView The View Matrix
		 * @param[in] inMatProjection The projection Matrix
		 * @return True if Successful. False Otherwise
		 *
		 * Sets the world, view and projection matrix to be passed to the shader
		 ***********************************************/
		virtual bool VSetShaderParameters( const XMFLOAT4X4 & inMatWorld,
			const XMFLOAT4X4 & inMatView, const XMFLOAT4X4 & inMatProjection);
		/********************************************//**
		  *
		  * Renders the shader
		  ***********************************************/
		virtual void VRenderShader();
		/********************************************//**
		  *
		  * Releases and destroys all the resources 
		  ***********************************************/
		virtual void VCleanup();

	private:
		/********************************************//**
		  * @param[in] shaderHandle Handle to the compiled vertex shader file
		  * @return False if there is any error
		  *
		  * Creates the layout of the vertex data that will be processed by this shader
		  ***********************************************/
		virtual bool VCreateLayout(shared_ptr<Utilities::IResHandle const> shaderHandle) = 0;
		/********************************************//**
		  * @param[in] strShaderName The name of the shader. The extension .vsho will be added automatically
		  * @return False if there is any error
		  *
		  * Creates the vertex shader object and the layout of the vertex
		  * data that will be processed by this shader
		  ***********************************************/
		bool CreateVertexShader(const Base::cString & strShaderName);
		/********************************************//**
		  * @param[in] strShaderName The name of the shader. The extension .sho will be added automatically
		  *
		  * Creates the pixel shader object
		  ***********************************************/
		bool CreatePixelShader(const Base::cString & strShaderName);

	protected:
		ID3D11InputLayout *		m_pLayout;			/*!< The input layout of the vertex shader */
		shared_ptr<ITexture>	m_pTexture;			/*!< The texture to be used by this shader*/

	private:
		ID3D11VertexShader *	m_pVertexShader;	/*!< The vertex shader object */
		ID3D11PixelShader *		m_pPixelShader;		/*!< The pixel shader object */
		ID3D11Buffer *			m_pMatrixBuffer;	/*!< The vertex shader constant buffer to store the matrix data*/
	};
}
#endif // BaseShader_h__

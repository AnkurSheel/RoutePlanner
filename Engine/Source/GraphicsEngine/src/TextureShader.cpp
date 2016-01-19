#include "stdafx.h"
#include "TextureShader.h"
#include "DxBase.hxx"
#include "FileIO.hxx"
#include "Texture.hxx"
#include "ResCache.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

//  *******************************************************************************************************************
cTextureShader::cTextureShader()
: m_pSampleState(NULL)
, m_pPixelBuffer(NULL)
{

}

//  *******************************************************************************************************************
cTextureShader::~cTextureShader()
{
	VCleanup();
}

//  *******************************************************************************************************************
bool cTextureShader::VCreateLayout(shared_ptr<IResHandle const> shaderHandle)
{
	int iNumberOfLayouts = 2;
	D3D11_INPUT_ELEMENT_DESC * pPolygonLayout = DEBUG_NEW D3D11_INPUT_ELEMENT_DESC[iNumberOfLayouts];

	pPolygonLayout[0].SemanticName = "POSITION";
	pPolygonLayout[0].SemanticIndex = 0;
	pPolygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pPolygonLayout[0].InputSlot = 0;
	pPolygonLayout[0].AlignedByteOffset = 0;
	pPolygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pPolygonLayout[0].InstanceDataStepRate = 0;

	pPolygonLayout[1].SemanticName = "TEXCOORD";
	pPolygonLayout[1].SemanticIndex = 0;
	pPolygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	pPolygonLayout[1].InputSlot = 0;
	pPolygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pPolygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pPolygonLayout[1].InstanceDataStepRate = 0;

	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateInputLayout(pPolygonLayout, 
		iNumberOfLayouts, shaderHandle->GetBuffer(), shaderHandle->GetSize(), &m_pLayout);

	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Error creating Input Layout");
		SafeDeleteArray(&pPolygonLayout);
		return false;
	}
	SafeDeleteArray(&pPolygonLayout);
	return true;
}

//  *******************************************************************************************************************
bool cTextureShader::VInitialize(const Base::cString & strShaderName)
{
	if(!cBaseShader::VInitialize(strShaderName))
	{
		return false;
	}
	
	if(!CreateSampleState())
	{
		return false;
	}

	if(!CreatePixelBuffer())
	{
		return false;
	}
	return true;
}

//  *******************************************************************************************************************
bool cTextureShader::VSetShaderParameters(const XMFLOAT4X4 & inMatWorld, const XMFLOAT4X4 & inMatView, const XMFLOAT4X4 & inMatProjection)
{
	if(!cBaseShader::VSetShaderParameters(inMatWorld, inMatView, inMatProjection))
	{
		return false;
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	bool bHasTexture = false;
	if(m_pTexture)
	{
		bHasTexture = true;
		ID3D11ShaderResourceView * pTex = m_pTexture->VGetTexture();
		IDXBase::GetInstance()->VGetDeviceContext()->PSSetShaderResources(0, 1, &pTex);
	}

	// Lock the pixel constant buffer so it can be written to.
	HRESULT result = IDXBase::GetInstance()->VGetDeviceContext()->Map(m_pPixelBuffer,
		0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not lock the pixel Buffer to update with the data");
		return false;
	}

	stPixelBufferData * pPixelData = (stPixelBufferData*)mappedResource.pData;
	// Copy the pixel color into the pixel constant buffer.
	pPixelData->pixelColor = m_DiffuseColor;
	pPixelData->hasTexture = bHasTexture;

	// Unlock the pixel constant buffer.
	IDXBase::GetInstance()->VGetDeviceContext()->Unmap(m_pPixelBuffer, 0);

	// Set the position of the pixel constant buffer in the pixel shader.
	unsigned int iBufferNumber = 0;

	// Now set the pixel constant buffer in the pixel shader with the updated value.
	IDXBase::GetInstance()->VGetDeviceContext()->PSSetConstantBuffers(iBufferNumber, 1, &m_pPixelBuffer);
	return true;
}

//  *******************************************************************************************************************
void cTextureShader::VRenderShader()
{
	cBaseShader::VRenderShader();
	IDXBase::GetInstance()->VGetDeviceContext()->PSSetSamplers(0, 1, &m_pSampleState);

}

//  *******************************************************************************************************************
void cTextureShader::VCleanup()
{
	SafeRelease(&m_pSampleState);
	SafeRelease(&m_pPixelBuffer);
	cBaseShader::VCleanup();
}
//  *****************************************************************************************************************************
bool cTextureShader::CreateSampleState()
{
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory( &samplerDesc, sizeof( samplerDesc ) );
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateSamplerState(&samplerDesc, &m_pSampleState);
	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Error creating sampler state");
		return false;
	}
	return true;
}
//  *****************************************************************************************************************************
bool cTextureShader::CreatePixelBuffer()
{
	D3D11_BUFFER_DESC pixelBufferDesc;
	pixelBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	pixelBufferDesc.ByteWidth = roundUp(sizeof(stPixelBufferData), 16);
	pixelBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	pixelBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pixelBufferDesc.MiscFlags = 0;
	pixelBufferDesc.StructureByteStride = 0;

	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateBuffer(&pixelBufferDesc, NULL, &m_pPixelBuffer);

	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Error creating pixel buffer");
		return false;
	}
	return true;
}

//  *****************************************************************************************************************************
void cTextureShader::SetDiffuseColor(const cColor & colorDiffuse)
{
	float fRed, fBlue, fGreen, fAlpha;
	colorDiffuse.GetColorComponentsInFloat(fRed, fBlue, fGreen, fAlpha);
	m_DiffuseColor = XMFLOAT4(fRed, fBlue, fGreen, fAlpha);
}

//  *******************************************************************************************************************
IShader * const IShader::CreateTextureShader()
{
	IShader * pShader= DEBUG_NEW cTextureShader();
	return pShader;
}
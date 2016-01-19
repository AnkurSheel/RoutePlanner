#include "stdafx.h"
#include "BaseShader.h"
#include "DxBase.hxx"
#include "FileIO.hxx"
#include "Texture.hxx"
#include "GameDirectories.h"
#include "ResCache.hxx"
#include "ResourceManager.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;
using namespace std;

//  *******************************************************************************************************************
cBaseShader::cBaseShader()
: m_pVertexShader(NULL)
, m_pPixelShader(NULL)
, m_pLayout(NULL)
, m_pMatrixBuffer(NULL)
{

}

//  *******************************************************************************************************************
cBaseShader::~cBaseShader()
{
	VCleanup();
}

//  *******************************************************************************************************************
bool cBaseShader::VInitialize(const Base::cString & strShaderName)
{
	if(!CreateVertexShader(strShaderName))
		return false;

	if(!CreatePixelShader(strShaderName))
		return false;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateBuffer(&matrixBufferDesc, 
		NULL, &m_pMatrixBuffer);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Error creating matrix buffer");
		return false;
	}

	return true;
}

//  *******************************************************************************************************************
bool cBaseShader::VRender(const XMFLOAT4X4 & inMatWorld, const XMFLOAT4X4 & inMatView, const XMFLOAT4X4 & inMatProjection)
{	
	if(!VSetShaderParameters(inMatWorld, inMatView, inMatProjection))
	{
		return false;
	}
	VRenderShader();
	return true;
}

//  *****************************************************************************************************************************
void cBaseShader::VSetTexture(shared_ptr<ITexture> pTexture)
{
	m_pTexture = pTexture;
}

//  *******************************************************************************************************************
bool cBaseShader::CreateVertexShader(const Base::cString & strShaderName)
{
	//ID3D10Blob * pVertexShaderBuffer = NULL;

	//if(!CompileShader(strVertexShaderPath, strEntry, strModel, &pVertexShaderBuffer))
	//	return false;

	cString strVertexShaderPath = cGameDirectories::GetShaderDirectory() + strShaderName + ".vsho";
	shared_ptr<IResource> pResource = shared_ptr<IResource>(IResource::CreateResource(strVertexShaderPath));
	shared_ptr<IResHandle> shaderHandle = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);
	if(shaderHandle == NULL)
	{
		return false;
	}
	const void * pData = shaderHandle->GetBuffer();
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateVertexShader(pData, 
		shaderHandle->GetSize(), NULL, &m_pVertexShader);

	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Error creating Vertex Shader");
		return false;
	}
	bool bSuccess = VCreateLayout(shaderHandle);
	return bSuccess;
}

//  *******************************************************************************************************************
bool cBaseShader::CreatePixelShader(const Base::cString & strShaderName)
{
	cString strPixelShaderPath = cGameDirectories::GetShaderDirectory() + strShaderName + ".psho";

	IResource * pResource = IResource::CreateResource(strPixelShaderPath);
	shared_ptr<IResHandle> shaderHandle = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);

	const void * pData = shaderHandle->GetBuffer();
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreatePixelShader(pData, 
		shaderHandle->GetSize(), NULL, &m_pPixelShader);

	SafeDelete(&pResource);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Error creating pixel shader");
		return false;
	}

	return true;
}

//  *******************************************************************************************************************
bool cBaseShader::VSetShaderParameters(const XMFLOAT4X4 & inMatWorld, const XMFLOAT4X4 & inMatView, const XMFLOAT4X4 & inMatProjection)
{
	if(m_pMatrixBuffer == NULL)
	{
		return false;
	}
	XMMATRIX matWorld = XMMatrixTranspose(XMLoadFloat4x4(&inMatWorld));
	XMMATRIX matView = XMMatrixTranspose(XMLoadFloat4x4(&inMatView));
	XMMATRIX matProjection = XMMatrixTranspose(XMLoadFloat4x4(&inMatProjection));

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT result = IDXBase::GetInstance()->VGetDeviceContext()->Map(m_pMatrixBuffer,
	0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		SP_ASSERT_FATAL(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not lock the Matrix Buffer to update with the matrices data");
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	MatrixBufferType * pMatrixData = static_cast<MatrixBufferType *>(mappedResource.pData);

	// Copy the matrices into the constant buffer.
	
	XMStoreFloat4x4(&pMatrixData->world, matWorld);
	XMStoreFloat4x4(&pMatrixData->view, matView);
	XMStoreFloat4x4(&pMatrixData->projection, matProjection);

	// Unlock the constant buffer.
	IDXBase::GetInstance()->VGetDeviceContext()->Unmap(m_pMatrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	unsigned int iBufferNumber = 0;

	IDXBase::GetInstance()->VGetDeviceContext()->VSSetConstantBuffers(iBufferNumber, 1, &m_pMatrixBuffer);

	return true;
}

//  *******************************************************************************************************************
void cBaseShader::VRenderShader()
{
	IDXBase::GetInstance()->VGetDeviceContext()->IASetInputLayout(m_pLayout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	IDXBase::GetInstance()->VGetDeviceContext()->VSSetShader(m_pVertexShader, NULL, 0);
	IDXBase::GetInstance()->VGetDeviceContext()->PSSetShader(m_pPixelShader, NULL, 0);
}

//  *******************************************************************************************************************
void cBaseShader::VCleanup()
{
	SafeRelease(&m_pMatrixBuffer);
	SafeRelease(&m_pLayout);
	SafeRelease(&m_pPixelShader);
	SafeRelease(&m_pVertexShader);
}

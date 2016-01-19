#include "stdafx.h"
#include "Sprite.h"
#include "DxBase.hxx"
#include "Texture.hxx"
#include "TextureShader.h"
#include "vertexstruct.h"
#include "Camera.hxx"
#include "ShaderManager.hxx"
#include "TextureManager.hxx"
#include "GameDirectories.h"

using namespace Utilities;
using namespace Graphics;
using namespace Base;

//  *******************************************************************************************************************
cSprite::cSprite()
	: m_pVertexBuffer(NULL)
	, m_pIndexBuffer(NULL)
	, m_vScale(1.0f, 1.0f)
	, m_bIsDirty(true)
	, m_iIndexCount(0)
	, m_iVertexCount(0)
{
}

//  *******************************************************************************************************************
cSprite::~cSprite()
{
	VCleanup();
}

//  *******************************************************************************************************************
bool cSprite::VInitialize( shared_ptr<ITexture> const pTexture )
{
	m_pTexture = pTexture;
	m_iVertexCount = 4;
	if(!CreateVertexBuffer())
		return false;

	if(!CreateIndexBuffer())
		return false;

	if(!InitializeShader())
		return false;

	m_vPosition = cVector2(-1.0f, -1.0f);

	ID3D11Resource* resource;
	D3D11_TEXTURE2D_DESC desc;
	m_pTexture->VGetTexture()->GetResource(&resource);
	ID3D11Texture2D * texResource = reinterpret_cast<ID3D11Texture2D*>(resource);
	texResource->GetDesc(&desc);

	m_vSize.x = static_cast<float>(desc.Width);
	m_vSize.y = static_cast<float>(desc.Height);
	m_vScaledSize = m_vSize;
	m_bIsDirty = true;
	SetDebugObjectName(texResource, "SpriteTextureResource");
	SafeRelease(&texResource);
	return true;
}

//  *******************************************************************************************************************
bool cSprite::VInitialize( const Base::cString & strTextureFilename )
{
	SP_LOG_CUSTOM(LogType::EVENT, 2, "Loading Sprite : " + strTextureFilename);

	m_pTexture = ITextureManager::GetInstance()->VGetTexture(cGameDirectories::GetSpriteDirectory() + strTextureFilename);

	if (m_pTexture != NULL)
	{
		return VInitialize(m_pTexture);
	}
	return false;
}

//  *******************************************************************************************************************
void cSprite::VRender(const ICamera * const pCamera)
{
	if (!m_pTexture || m_vScaledSize == cVector2::Zero)
	{
		return;
	}
	if (m_bIsDirty)
	{
		RecalculateVertexData(pCamera);
		m_bIsDirty = false;
	}

	unsigned int stride = sizeof(stTexVertex);
	unsigned int offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	IDXBase::GetInstance()->VGetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	IDXBase::GetInstance()->VGetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	IDXBase::GetInstance()->VGetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	IDXBase::GetInstance()->VTurnZBufferOff();
	if (m_pShader)
	{
		XMFLOAT4X4 matView;
		XMStoreFloat4x4(&matView, XMMatrixIdentity());

		m_pShader->VSetTexture(m_pTexture);
		m_pShader->VRender(IDXBase::GetInstance()->VGetWorldMatrix(), matView, IDXBase::GetInstance()->VGetOrthoMatrix());
	}
	IDXBase::GetInstance()->VGetDeviceContext()->DrawIndexed(m_iIndexCount, 0, 0);
}

//  *******************************************************************************************************************
void cSprite::VSetPosition( const Base::cVector2 & vPosition )
{
	if(m_vPosition != vPosition)
	{
		m_vPosition = vPosition;
		m_bIsDirty = true;
	}
}

//  *******************************************************************************************************************
void cSprite::VSetSize( const Base::cVector2 & vSize)
{
	if(m_vScaledSize != vSize)
	{
		SP_ASSERT(vSize.x > 0 && vSize.y > 0)(vSize).SetCustomMessage("Setting sprite size to 0");
		m_vScaledSize = vSize;
		m_vScale.x = m_vScaledSize.x / vSize.x;
		m_vScale.y = m_vScaledSize.y / vSize.y;
		m_bIsDirty = true;
	}
}

//  *******************************************************************************************************************
cVector2 cSprite::VGetScaledSize() const
{
	return m_vScaledSize;
}

//  *******************************************************************************************************************
void cSprite::VSetScale(const Base::cVector2 & vScale)
{
	if(m_vScale != vScale)
	{
		m_vScale = vScale;
		m_vScaledSize = m_vSize * m_vScale;
		m_bIsDirty = true;
	}
}

//  *******************************************************************************************************************
void cSprite::VCleanup()
{
	m_pShader = NULL;
	m_pTexture = NULL;
	SafeRelease(&m_pVertexBuffer);
	SafeRelease(&m_pIndexBuffer);
}

//  *******************************************************************************************************************
bool cSprite::CreateVertexBuffer()
{
	stTexVertex * pVertices = DEBUG_NEW stTexVertex[m_iVertexCount];

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(stTexVertex) * m_iVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory( &vertexData, sizeof(vertexData));
	vertexData.pSysMem = pVertices;

	// Now create the vertex buffer.
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_pVertexBuffer);

	SafeDeleteArray(&pVertices);

	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create Vertex Buffer");
		return false;
	}
	return true;
}

//  *******************************************************************************************************************
bool cSprite::CreateIndexBuffer()
{
	unsigned long aIndices[] = {0,1,2,
		1,3,2};
	m_iIndexCount = 6;
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_iIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = aIndices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_pIndexBuffer);

	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create Index Buffer");
		return false;
	}
	return true;

}

//  *******************************************************************************************************************
bool cSprite::RecalculateVertexData(const ICamera * const pCamera)
{
	//center of the screen is 0,0
	float left = -(float)IDXBase::GetInstance()->VGetScreenWidth()/2.0f + m_vPosition.x;
	float right = left + m_vScaledSize.x;
	float top = (float)IDXBase::GetInstance()->VGetScreenHeight()/2.0f - m_vPosition.y;
	float bottom = top - m_vScaledSize.y;
	cVector2 point(m_vPosition.x/IDXBase::GetInstance()->VGetScreenWidth(), m_vPosition.y/IDXBase::GetInstance()->VGetScreenHeight());
	cVector2 screenSpace = 2 * point;
	screenSpace.x -= 1;
	screenSpace.y -= 1;

	float z = 1.0f;

	// Create the vertex array.
	stTexVertex * pVertices = DEBUG_NEW stTexVertex [4];
	pVertices[0] = stTexVertex(left, bottom, z, 0.0f, 1.0f);
	pVertices[1] = stTexVertex(left, top, z, 0.0f, 0.0f);
	pVertices[2] = stTexVertex(right, bottom, z, 1.0f, 1.0f);
	pVertices[3] = stTexVertex(right, top, z, 1.0f, 0.0f);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT result = IDXBase::GetInstance()->VGetDeviceContext()->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not lock the vertex buffer to update with the vertex data");

		SafeDeleteArray(&pVertices);
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	stTexVertex * verticesPtr = (stTexVertex*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)pVertices, (sizeof(stTexVertex) * 4));

	// Unlock the vertex buffer.
	IDXBase::GetInstance()->VGetDeviceContext()->Unmap(m_pVertexBuffer, 0);

	SafeDeleteArray(&pVertices);
	return true;
}

//  *******************************************************************************************************************
bool cSprite::InitializeShader()
{
	m_pShader = shared_ptr<IShader>(IShader::CreateTextureShader());
	return IShaderManager::GetInstance()->VGetShader(m_pShader, "Texture");
}

//  *******************************************************************************************************************
ISprite * ISprite::CreateSprite()
{
	return DEBUG_NEW cSprite();
}

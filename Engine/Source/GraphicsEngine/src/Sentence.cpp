#include "stdafx.h"
#include "Sentence.h"
#include "DxBase.hxx"
#include "vertexstruct.h"
#include "Font.h"
#include "Camera.hxx"
#include "Optional.h"
#include "FontManager.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

//  *******************************************************************************************************************
cSentence::cSentence()
	: m_pVertexBuffer(NULL)
	, m_pIndexBuffer(NULL)
	, m_TextColor(1.0f, 1.0f, 1.0f, 1.0f)
	, m_iVertexCount(0)
	, m_iIndexCount(0)
	, m_bIsDirty(true)
	, m_fWidth(0.0f)
	, m_fHeight(0.0f)
	, m_fScale(1.0f)
{
}

//  *******************************************************************************************************************
cSentence::~cSentence()
{
	Cleanup();
}

//  *******************************************************************************************************************
bool cSentence::VInitialize(const cString & strFont, const cString & strText, const cColor & textColor)
{
	m_pFont = IFontManager::GetInstance()->VGetFont(strFont);

	m_iVertexCount = MAX_FILENAME_WIDTH * 4;

	if(!CreateVertexBuffer())
		return false;

	if(!CreateIndexBuffer())
		return false;

	m_vPosition = cVector2(-1.0f, -1.0f);
	VSetText(strText);
	VSetTextColor(textColor);
	ReInitializeVertexBuffer(NULL);
	m_fHeight = static_cast<float>(m_pFont->VGetFontHeight());
	m_bIsDirty = true;
	return true;
}

//  *******************************************************************************************************************
void cSentence::VRender(const ICamera * const pCamera)
{
	if(m_strText.IsEmpty())
	{
		return;
	}

	//IDXBase::GetInstance()->VTurnOnAlphaBlending();
	if (m_bIsDirty)
	{
		ReInitializeVertexBuffer(pCamera);
		m_bIsDirty = false;
	}

	unsigned int stride = sizeof(stTexVertex);
	unsigned int offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	IDXBase::GetInstance()->VGetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	IDXBase::GetInstance()->VGetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	IDXBase::GetInstance()->VGetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	IDXBase::GetInstance()->VTurnZBufferOff();

	XMFLOAT4X4 matView;
	XMStoreFloat4x4(&matView, XMMatrixIdentity());

	m_pFont->VRender(IDXBase::GetInstance()->VGetWorldMatrix(),
		matView, IDXBase::GetInstance()->VGetOrthoMatrix(), m_TextColor);
	IDXBase::GetInstance()->VGetDeviceContext()->DrawIndexed(m_iIndexCount, 0, 0);
	//IDXBase::GetInstance()->VTurnOffAlphaBlending();
}

//  *******************************************************************************************************************
void cSentence::VSetPosition(const cVector2 & vPosition)
{
	m_vPosition = vPosition;
	m_bIsDirty = true;
}

//  *******************************************************************************************************************
cString cSentence::VGetText() const
{
	return m_strText;
}

//  *******************************************************************************************************************
void cSentence::VSetText(const cString & strText)
{
	m_strText = strText;
	m_bIsDirty = true;
}

//  *******************************************************************************************************************
void cSentence::VSetTextColor(const cColor & colorText)
{
	m_TextColor = colorText;
}

//  *******************************************************************************************************************
float cSentence::VGetWidth() const
{
	return m_fScale * m_fWidth;
}

//  *******************************************************************************************************************
float cSentence::VGetHeight() const
{
	return m_fScale * m_fHeight;
}

//  *******************************************************************************************************************
float cSentence::VGetWidth(const cString & strText) const
{
	float fWidth = 0.0f;
	int istrLength = strText.GetLength();

	IMyFont::stVertexData vertexData;
	for (int i=0; i<istrLength; i++)
	{
		int val = (int)strText[i];
		vertexData = m_pFont->VGetCharVertexData(val);

		fWidth += vertexData.ch.XAdvance;
	}
	return m_fScale * fWidth;
}

//  *******************************************************************************************************************
void cSentence::VSetHeight(const float fTextHeight)
{
	m_fScale = fTextHeight/m_pFont->VGetFontHeight();
	m_bIsDirty = true;
}

//  *******************************************************************************************************************
bool cSentence::ReInitializeVertexBuffer(const ICamera * const pCamera)
{
	int istrLength = m_strText.GetLength();
	int iPos = 0;
	cVector2 vPos = m_vPosition;

	m_fWidth = 0.0f;
	m_iIndexCount = istrLength * 6;
	m_iVertexCount = istrLength * 4;

	stTexVertex * pVertices = NULL;
	if (pCamera)
	{
		pVertices = DEBUG_NEW stTexVertex[m_iVertexCount];
	}

	tOptional<int> iLineLength = m_strText.FindFirstOfAny("\n", 0);
	if (iLineLength.IsInvalid())
	{
		iLineLength = istrLength;
	}

	while(iPos < istrLength)
	{
		float fWidth = 0.0f;
		InitializesVertexData(pVertices, iLineLength.GetValue(), iPos, vPos, fWidth);
		if (m_fWidth < fWidth)
		{
			m_fWidth = fWidth;
		}
		iPos += iLineLength.GetValue() + 1;
		vPos.y += VGetHeight();
		tOptional<int> iEndPos = m_strText.FindFirstOfAny("\n", iPos);
		if(iEndPos.IsValid())
		{
			iLineLength = iEndPos.GetValue() - iPos;
		}
		else
		{
			iLineLength = istrLength - iPos;
		}
	}

	if (pCamera)
	{
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
		memcpy(verticesPtr, (void*)pVertices, (sizeof(stTexVertex) * m_iVertexCount));

		// Unlock the vertex buffer.
		IDXBase::GetInstance()->VGetDeviceContext()->Unmap(m_pVertexBuffer, 0);
	}

	SafeDeleteArray(&pVertices);
	return true;
}

//  *******************************************************************************************************************
void cSentence::InitializesVertexData(stTexVertex * const pVertices, const int iLineLength, const int iStartPos, 
	const cVector2 & vPos, float & fWidth)
{
	float curX = -(float)IDXBase::GetInstance()->VGetScreenWidth()/2.0f + vPos.x;
	float curY = (float)IDXBase::GetInstance()->VGetScreenHeight()/2.0f - vPos.y;
	float left;
	float right;
	float top;
	float bottom;

	IMyFont::stVertexData vertexData;
	for (int i = 0; i < iLineLength; i++)
	{
		int iTextIndex = i + iStartPos;
		int val = (int)m_strText[iTextIndex];
		vertexData = m_pFont->VGetCharVertexData(val);

		if (pVertices)
		{
			left = curX + m_fScale * vertexData.ch.XOffset;
			right = left + m_fScale * vertexData.ch.Width;
			top = curY + m_fScale * vertexData.ch.YOffset;
			bottom = top - m_fScale * vertexData.ch.Height;

			float z = 1.f;

			// Create the vertex array.
			pVertices[iTextIndex*4] = stTexVertex(left, bottom, z, vertexData.fTexU, vertexData.fTexV1);
			pVertices[iTextIndex*4+1] = stTexVertex(left, top, z, vertexData.fTexU, vertexData.fTexV);
			pVertices[iTextIndex*4+2] = stTexVertex(right, bottom, z, vertexData.fTexU1, vertexData.fTexV1);
			pVertices[iTextIndex*4+3] = stTexVertex(right, top, z, vertexData.fTexU1, vertexData.fTexV);

			curX += m_fScale *  vertexData.ch.XAdvance;
		}
		fWidth += vertexData.ch.XAdvance;
	}
}

//  *******************************************************************************************************************
bool cSentence::CreateVertexBuffer()
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
bool cSentence::CreateIndexBuffer()
{
	m_iIndexCount = MAX_FILENAME_WIDTH * 6;
	unsigned long * pIndices= DEBUG_NEW unsigned long[m_iIndexCount];
	for (int i=0;i<MAX_FILENAME_WIDTH;i=i++)
	{
		pIndices[i*6] = i*4;
		pIndices[i*6+1] = i*4+1;
		pIndices[i*6+2] = i*4+2;
		pIndices[i*6+3] = i*4+1;
		pIndices[i*6+4] = i*4+3;
		pIndices[i*6+5] = i*4+2;
	}

	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_iIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = pIndices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_pIndexBuffer);

	bool bSuccess;
	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create Index Buffer");
		bSuccess = false;
	}
	else
	{
		bSuccess = true;
	}

	SafeDeleteArray(&pIndices);
	return bSuccess;
}

//  *******************************************************************************************************************
void cSentence::Cleanup()
{
	SafeRelease(&m_pVertexBuffer);
	SafeRelease(&m_pIndexBuffer);
}

//  *******************************************************************************************************************
ISentence * ISentence::CreateSentence()
{
	return DEBUG_NEW cSentence();
}

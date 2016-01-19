#include "stdafx.h"
#include "Model.h"
#include "vertexstruct.h"
#include "DxBase.hxx"
#include "TextureShader.h"
#include "Camera.hxx"
#include "Texture.hxx"
#include "ShaderManager.hxx"
#include "TextureManager.hxx"
#include "ObjModelLoader.h"
#include "BoundingBox.hxx"

using namespace Utilities;
using namespace Base;
using namespace Graphics;

//  *******************************************************************************************************************
cModel::cModel()
: m_pVertexBuffer(NULL)
, m_pIndexBuffer(NULL)
, m_iVertexCount(0)
, m_iIndexCount(0)
, m_iVertexSize(0)
, m_fBoundingSphereRadius(0)
, m_pBoundingBox(NULL)
{

}

//  *******************************************************************************************************************
cModel::~cModel()
{
	VCleanup();
}

//  *******************************************************************************************************************
bool cModel::OnInitialization(shared_ptr<const stModelDef> pModeldef)
{
	if(pModeldef == NULL)
	{	
		return false;
	}

	m_iVertexCount = pModeldef->iNumberOfVertices;
	m_iIndexCount = pModeldef->iNumberOfIndices;
	m_iVertexSize = sizeof(stTexVertex);

	if(!CreateVertexBuffer(pModeldef->pVertices))
		return false;

	if(!CreateIndexBuffer(pModeldef->pIndices))
		return false;

	for (unsigned int i=0; i<pModeldef->vSubsetsDef.size(); i++)
	{
		stObjectSubset subset;
		subset.m_iIndexCountInSubset = pModeldef->vSubsetsDef[i].iNumberOfIndicesinSubset;
		subset.m_diffuseColor = pModeldef->vSubsetsDef[i].diffuseColor;
		subset.m_iStartIndexNo = pModeldef->vSubsetsDef[i].iStartIndexNo;
		if(!pModeldef->vSubsetsDef[i].strDiffuseTextureFilename.IsEmpty())
		{
			subset.m_pTexture = ITextureManager::GetInstance()->VGetTexture(pModeldef->vSubsetsDef[i].strDiffuseTextureFilename);
		}
		
		m_vSubsets.push_back(subset);
	}

	m_pBoundingBox = IBoundingBox::CreateBoundingBox(pModeldef->vBoundingBoxMinPos, pModeldef->vBoundingBoxMaxPos);
	/*	float distX = (vMaxAABB.m_dX - m_vAABBMin.m_dX) / 2.0f;
	float distY = (vMaxAABB.m_dY - m_vAABBMin.m_dY) / 2.0f;
	float distZ = (vMaxAABB.m_dZ - m_vAABBMin.m_dZ) / 2.0f;

	m_vBoundingSphereCentre = cVector3(vMaxAABB.m_dX - distX, m_vAABBMax.m_dY - distY, m_vAABBMax.m_dZ - distZ);
	m_fBoundingSphereRadius = (distX * distX + distY * distY + distZ * distZ) / 2.0f;
*/
	shared_ptr<IShader> pShader = shared_ptr<IShader>(IShader::CreateTextureShader());
	bool bSuccess = IShaderManager::GetInstance()->VGetShader(pShader,"Texture");
	m_pShader = dynamic_pointer_cast<cTextureShader>(pShader);

	return bSuccess;
}

//  *******************************************************************************************************************
void cModel::VRender(const ICamera * const pCamera)
{
	unsigned int stride = m_iVertexSize;
	unsigned int offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	IDXBase::GetInstance()->VGetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	IDXBase::GetInstance()->VGetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	IDXBase::GetInstance()->VGetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	IDXBase::GetInstance()->VTurnZBufferOn();

	for (unsigned int i=0; i<m_vSubsets.size(); i++)
	{
		if (m_pShader)
		{
			m_pShader->SetDiffuseColor(m_vSubsets[i].m_diffuseColor);
			m_pShader->VSetTexture(m_vSubsets[i].m_pTexture);
			if(m_pShader->VRender(m_matWorld, pCamera->VGetViewMatrix(), IDXBase::GetInstance()->VGetProjectionMatrix()))
			{
				IDXBase::GetInstance()->VGetDeviceContext()->DrawIndexed(m_vSubsets[i].m_iIndexCountInSubset,
					m_vSubsets[i].m_iStartIndexNo, 0);
			}
		}
	}
}

//  *******************************************************************************************************************
void cModel::VRecalculateWorldMatrix(const cVector3 vPosition, const cVector3 vRotation, const cVector3 vScale)
{
	XMMATRIX matRotation = XMMatrixRotationRollPitchYaw(vRotation.x, vRotation.y, vRotation.z);
	XMMATRIX matScale = XMMatrixScaling(vScale.x, vScale.y, vScale.z);
	XMMATRIX matPosition = XMMatrixTranslation(vPosition.x, vPosition.y, vPosition.z);

	XMMATRIX matWorld = matScale * matRotation * matPosition;
	XMStoreFloat4x4(&m_matWorld, matWorld);

	if(m_pBoundingBox)
		m_pBoundingBox->VTransform(m_matWorld);
}

//  *******************************************************************************************************************
const IAABB * const cModel::VGetAABB() const
{
	if(m_pBoundingBox)
	{
		return m_pBoundingBox->VGetAABB();
	}
	return NULL;
}

//  *******************************************************************************************************************
void cModel::VCleanup()
{
	SafeDelete(&m_pBoundingBox);
	SafeRelease(&m_pVertexBuffer);
	SafeRelease(&m_pIndexBuffer);
	m_vSubsets.clear();
}

//  *******************************************************************************************************************
bool cModel::CreateVertexBuffer( const stTexVertex * const pVertices )
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = m_iVertexSize * m_iVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory( &vertexData, sizeof(vertexData));
	vertexData.pSysMem = pVertices;

	// Now create the vertex buffer.
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_pVertexBuffer);
	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create Vertex Buffer");
		return false;
	}
	return true;
}

//  *******************************************************************************************************************
bool cModel::CreateIndexBuffer(const unsigned long * const pIndices)
{
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
	if(FAILED(result))
	{
		SP_ASSERT_ERROR(false)(DXGetErrorString(result))(DXGetErrorDescription(result)).SetCustomMessage("Could not create Index Buffer");
		return false;
	}
	return true;
}

//  *******************************************************************************************************************
IModel * IModel::CreateModel(const cString & strModelFile)
{
	shared_ptr<stModelDef> pModelDef(IObjModelLoader::GetInstance()->VGetModelDef(strModelFile));
	cModel * pModel = DEBUG_NEW cModel();
	pModel->OnInitialization(pModelDef);
	return pModel;
}

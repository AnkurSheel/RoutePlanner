// *****************************************************************************
//  BoundingBox   version:  1.0   Ankur Sheel  date: 2012/11/24
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "BoundingBox.h"
#include "Vector2.h"
#include "GraphicUtils.h"
#include "AABB.h"

using namespace Graphics;
using namespace Base;

// *****************************************************************************
cBoundingBox::cBoundingBox( const cVector3 & vMinBound, const cVector3 & vMaxBound)
: m_pAABB(NULL)
{
	m_avObjectBounds[0] = cVector3(vMinBound.x, vMinBound.y, vMinBound.z); 
	m_avObjectBounds[1] = cVector3(vMaxBound.x, vMinBound.y, vMinBound.z); 
	m_avObjectBounds[2] = cVector3(vMinBound.x, vMaxBound.y, vMinBound.z); 
	m_avObjectBounds[3] = cVector3(vMaxBound.x, vMaxBound.y, vMinBound.z); 
	m_avObjectBounds[4] = cVector3(vMinBound.x, vMinBound.y, vMaxBound.z); 
	m_avObjectBounds[5] = cVector3(vMaxBound.x, vMinBound.y, vMaxBound.z); 
	m_avObjectBounds[6] = cVector3(vMinBound.x, vMaxBound.y, vMaxBound.z); 
	m_avObjectBounds[7] = cVector3(vMaxBound.x, vMaxBound.y, vMaxBound.z); 

	m_pAABB = DEBUG_NEW cAABB(vMinBound, vMaxBound);
}

// *****************************************************************************
cBoundingBox::~cBoundingBox()
{
	SafeDelete(&m_pAABB);
}

// *********************************************************************************
const IAABB * const cBoundingBox::VGetAABB() const
{
	if(m_pAABB)
	{
		return m_pAABB;
	}
	return NULL;
}

// *****************************************************************************
void cBoundingBox::VTransform(const XMFLOAT4X4 & matWorld)
{
	XMVECTOR worldBounds[8];
	XMVECTOR objectBounds[8];
	XMFLOAT3 temp;

	for( int i = 0; i < 8; i++ )
	{
		temp = XMFLOAT3(m_avObjectBounds[i].x, m_avObjectBounds[i].y, m_avObjectBounds[i].z);
		objectBounds[i] = XMLoadFloat3(&temp);
	
		worldBounds[i] = XMVector3TransformCoord(objectBounds[i], XMLoadFloat4x4(&matWorld));
		XMStoreFloat3(&temp, worldBounds[i]);
		
		m_avOBBBounds[i] = cVector3(temp.x, temp.y, temp.z);
	}

	RecalculateAABBFromOBB();
}

// *****************************************************************************
void cBoundingBox::RecalculateAABBFromOBB()
{
	cVector3 vMin = m_avOBBBounds[0];
	cVector3 vMax = m_avOBBBounds[0];

	for (int i=0; i<8; i++)
	{
		vMin.x = min(vMin.x, m_avOBBBounds[i].x);
		vMin.y = min(vMin.y, m_avOBBBounds[i].y);
		vMin.z = min(vMin.z, m_avOBBBounds[i].z);

		//Get the largest vertex 
		vMax.x = max(vMax.x, m_avOBBBounds[i].x);
		vMax.y = max(vMax.y, m_avOBBBounds[i].y);
		vMax.z = max(vMax.z, m_avOBBBounds[i].z);
	}

	m_pAABB->Calculate(vMin, vMax);
}

// *****************************************************************************
IBoundingBox * IBoundingBox::CreateBoundingBox(const cVector3 & vMinBound,
											   const cVector3 & vMaxBound)
{
	IBoundingBox * pAABB = DEBUG_NEW cBoundingBox(vMinBound, vMaxBound);
	return pAABB;
}
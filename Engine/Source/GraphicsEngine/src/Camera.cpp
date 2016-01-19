// *****************************************************************************
//  Camera   version:  1.0   Ankur Sheel  date: 2012/09/15
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "Camera.h"
#include "GraphicUtils.h"

using namespace Graphics;
using namespace Base;

// *****************************************************************************
cCamera::cCamera()
	: m_bIsDirty(true)
{
}

// *****************************************************************************
cCamera::~cCamera()
{

}

// *****************************************************************************
void cCamera::VUpdate()
{
	if (m_bIsDirty)
	{
		m_bIsDirty = false;
		CalculateViewMatrix();
	}
}

// *****************************************************************************
cVector3 cCamera::VGetPosition() const
{
	return m_vPosition;
}

// *****************************************************************************
void cCamera::VSetPosition( const cVector3 & vPosition )
{
	if (m_vPosition != vPosition)
	{
		m_vPosition = vPosition;
		m_bIsDirty = true;
	}	
}

// *****************************************************************************
void cCamera::VSetRotation( const cVector3 & vRotation )
{
	if (m_vRotation != vRotation)
	{
		m_vRotation = vRotation;
		m_bIsDirty = true;
	}	
}

// *****************************************************************************
const XMFLOAT4X4 & cCamera::VGetViewMatrix() const 
{ 
	return m_matView; 
}

// *****************************************************************************
void cCamera::CalculateViewMatrix()
{
	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	float fPitch = DegtoRad(m_vRotation.x);
	float fYaw   = DegtoRad(m_vRotation.y);
	float fRoll  = DegtoRad(m_vRotation.z);

	XMMATRIX matRotation = XMMatrixRotationRollPitchYaw(fPitch, fYaw, fRoll);

	XMFLOAT3 temp(0.0f, 0.0f, 1.0f);
	XMVECTOR vLookAt = XMLoadFloat3(&temp);

	vLookAt = XMVector3TransformCoord(vLookAt, matRotation);

	temp = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMVECTOR up = XMLoadFloat3(&temp);

	up = XMVector3TransformCoord(up, matRotation);

	temp = XMFLOAT3(m_vPosition.x, m_vPosition.y, m_vPosition.z);
	XMVECTOR vPosition = XMLoadFloat3(&temp);
	vLookAt = vPosition + vLookAt;

	// Finally create the view matrix from the three updated vectors.
	XMMATRIX matView = XMMatrixLookAtLH(vPosition, vLookAt, up);
	XMStoreFloat4x4(&m_matView , matView);
}

// *****************************************************************************
ICamera * ICamera::CreateCamera()
{
	return DEBUG_NEW cCamera();
}
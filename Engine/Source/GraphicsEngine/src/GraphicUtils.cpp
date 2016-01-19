#include "stdafx.h"
#include "GraphicUtils.h"
#include "DxBase.hxx"
#include "Camera.hxx"

using namespace Graphics;
using namespace Base;

IGraphicUtils * cGraphicUtils::s_pGraphicUtils = NULL;

//  *******************************************************************************************************************
cGraphicUtils::cGraphicUtils()
{

}
//  *******************************************************************************************************************
cGraphicUtils::~cGraphicUtils()
{

}

//  *******************************************************************************************************************
cVector3 cGraphicUtils::VScreenToWorldSpace(const cVector2 & vScreenPos, const ICamera * const pCamera)
{
	cVector3 vViewSpace;

	vViewSpace.x = ((2.0f * vScreenPos.x) / IDXBase::GetInstance()->VGetScreenWidth()) - 1.0f;
	vViewSpace.y =  1 - ((2.0f * vScreenPos.y) / IDXBase::GetInstance()->VGetScreenHeight());
	vViewSpace.z = 1.0f;

	XMMATRIX matProjection = XMLoadFloat4x4(&(IDXBase::GetInstance()->VGetProjectionMatrix()));
	vViewSpace.x = vViewSpace.x / matProjection._11;
	vViewSpace.y = vViewSpace.y / matProjection._22;
	vViewSpace.z = vViewSpace.z / matProjection._33;

	// Get the inverse of the view matrix to get the world matrix.
	XMMATRIX matView = XMLoadFloat4x4(&(pCamera->VGetViewMatrix()));
	XMMATRIX matWorld = XMMatrixInverse(&XMMatrixDeterminant(matView), matView);

	cVector3 vOrigin(matWorld._41, matWorld._42, matWorld._43);

	cVector3 direction;
	direction.x = (vViewSpace.x * matWorld._11) + (vViewSpace.y * matWorld._21) + (vViewSpace.z * matWorld._31);
	direction.y = (vViewSpace.x * matWorld._12) + (vViewSpace.y * matWorld._22)	+ (vViewSpace.z * matWorld._32);
	direction.z = (vViewSpace.x * matWorld._13) + (vViewSpace.y * matWorld._23) + (vViewSpace.z * matWorld._33);
	direction.Normalize();

	XMMATRIX matViewProjection = matView * matProjection;

	cVector3 vPlaneNormal(matViewProjection._13, matViewProjection._23, matViewProjection._33);
	vPlaneNormal.Normalize();

	float fIncidentAngle = direction.Dot(vPlaneNormal);
	if (fIncidentAngle != 0)
	{
		float fPlaneDistanceFromOrigin = 0;

		float t = (-(fPlaneDistanceFromOrigin + vOrigin.Dot(vPlaneNormal))) / fIncidentAngle;
		vOrigin = vOrigin + (direction * t);
		return  vOrigin;
	}
	return cVector3::Zero;
}

//  *******************************************************************************************************************
void cGraphicUtils::VGetRayFromScreenPosition(const cVector2 & vScreenPos, const ICamera * const pCamera, stRay& ray)
{
	cVector3 vViewSpace;

	vViewSpace.x = ((2.0f * vScreenPos.x) / IDXBase::GetInstance()->VGetScreenWidth()) - 1.0f;
	vViewSpace.y =  1 - ((2.0f * vScreenPos.y) / IDXBase::GetInstance()->VGetScreenHeight());
	vViewSpace.z = 1.0f;

	XMMATRIX projectionMatrix = XMLoadFloat4x4(&(IDXBase::GetInstance()->VGetProjectionMatrix()));
	vViewSpace.x = vViewSpace.x / projectionMatrix._11;
	vViewSpace.y = vViewSpace.y / projectionMatrix._22;

	// Get the inverse of the view matrix to get the world matrix.
	XMMATRIX viewMatrix = XMLoadFloat4x4(&(pCamera->VGetViewMatrix()));
	XMMATRIX worldMatrix = XMMatrixInverse(&XMMatrixDeterminant(viewMatrix), viewMatrix);

	ray.origin = Vec3TransformCoordinate(ray.origin, worldMatrix);

	ray.direction = Vec3TransformNormal(vViewSpace, worldMatrix);
	ray.direction.Normalize();
}

//  *******************************************************************************************************************
// https://www.winehq.org/pipermail/wine-cvs/2007-October/037549.html
//  *******************************************************************************************************************
cVector3 cGraphicUtils::Vec3TransformNormal(const cVector3& inVector, const XMMATRIX& inMatrix)
{
	cVector3 tranformedVector;
	tranformedVector.x = (inVector.x * inMatrix._11) + (inVector.y * inMatrix._21) + (inVector.z * inMatrix._31);
	tranformedVector.y = (inVector.x * inMatrix._12) + (inVector.y * inMatrix._22) + (inVector.z * inMatrix._32);
	tranformedVector.z = (inVector.x * inMatrix._13) + (inVector.y * inMatrix._23) + (inVector.z * inMatrix._33);
	return tranformedVector;
}

//  *******************************************************************************************************************
// https://www.winehq.org/pipermail/wine-cvs/2007-October/037547.html
//  *******************************************************************************************************************
cVector3 cGraphicUtils::Vec3Transform(const cVector3& inVector, const XMMATRIX& inMatrix)
{
	cVector3 transformedVector;

	transformedVector.x = (inVector.x * inMatrix._11) + (inVector.y * inMatrix._21) + (inVector.z * inMatrix._31) + inMatrix._41;
	transformedVector.y = (inVector.x * inMatrix._12) + (inVector.y * inMatrix._22) + (inVector.z * inMatrix._32) + inMatrix._42;
	transformedVector.z = (inVector.x * inMatrix._13) + (inVector.y * inMatrix._23) + (inVector.z * inMatrix._33) + inMatrix._43;

	return cVector3(transformedVector.x, transformedVector.y, transformedVector.z);
}

//  *******************************************************************************************************************
// https://www.winehq.org/pipermail/wine-cvs/2007-October/037548.html
//  *******************************************************************************************************************
cVector3 cGraphicUtils::Vec3TransformCoordinate(const cVector3& inVector, const XMMATRIX& inMatrix)
{
	cVector3 transformedVector;

	float norm = ((inVector.x * inMatrix._14) + (inVector.y * inMatrix._24) + (inVector.z * inMatrix._34) + inMatrix._44);

	if (!isEqual(norm, 0.0f))
	{
		transformedVector.x = ((inVector.x * inMatrix._11) + (inVector.y * inMatrix._21) + (inVector.z * inMatrix._31) + inMatrix._41) / norm;
		transformedVector.y = ((inVector.x * inMatrix._12) + (inVector.y * inMatrix._22) + (inVector.z * inMatrix._32) + inMatrix._42) / norm;
		transformedVector.z = ((inVector.x * inMatrix._13) + (inVector.y * inMatrix._23) + (inVector.z * inMatrix._33) + inMatrix._43) / norm;
	}
	return transformedVector;
}

//  *******************************************************************************************************************
IGraphicUtils * IGraphicUtils::GetInstance()
{
	if(cGraphicUtils::s_pGraphicUtils == NULL)
		cGraphicUtils::s_pGraphicUtils = DEBUG_NEW cGraphicUtils();
	return cGraphicUtils::s_pGraphicUtils ;
}

//  *******************************************************************************************************************
void IGraphicUtils::Destroy()
{
	SafeDelete(&cGraphicUtils::s_pGraphicUtils);
}

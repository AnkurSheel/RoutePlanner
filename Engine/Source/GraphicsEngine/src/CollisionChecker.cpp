// *****************************************************************************
//  CollisionChecker   version:  1.0   Ankur Sheel  date: 05/14/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "CollisionChecker.h"
#include "AABB.h"

using namespace Graphics;
using namespace Base;

ICollisionChecker * cCollisionChecker::s_pCollisionChecker = NULL;

// *****************************************************************************
cCollisionChecker::cCollisionChecker()
{
}

// *****************************************************************************
cCollisionChecker::~cCollisionChecker()
{
}

// *****************************************************************************
bool cCollisionChecker::VCheckForCollisions(const IAABB * const pAABB1, const IAABB * pAABB2, cContact & contact)
{
	cVector3 vCenterDelta = pAABB1->VGetCenter() - pAABB2->VGetCenter();
	cVector3 vOverlap = vCenterDelta;
	vOverlap.AbsTo();

	cVector3 vHalfExtentSum = pAABB2->VGetHalfExtents() +pAABB1->VGetHalfExtents();
	vOverlap = vHalfExtentSum - vOverlap;

	bool bOverlap = vOverlap.x > 0 && vOverlap.y > 0 && vOverlap.z > 0;
	if(bOverlap)
	{
		cVector3 vSmallestOverlap = vOverlap.MinorAxis();
		cVector3 vPlaneNormal = (vCenterDelta * vSmallestOverlap).MajorAxis();

		//cVector3 vPlaneCenter = (vPlaneNormal * vHalfExtentSum) + pAABB2->VGetCenter();

		//cVector3 vPlaneDelta = pAABB2->VGetCenter() - vPlaneCenter;
		//float dist = vPlaneDelta.Dot(vPlaneNormal);

		contact.vNormal = vPlaneNormal;
		contact.vDistance = vOverlap * vPlaneNormal;
	}
	return bOverlap;
}

//// *****************************************************************************
//// Checks for collisions for 2D objects.
//// returns true if there is a collision
//// *****************************************************************************
//bool cCollisionChecker::CheckFor2DCollisions(const IPolygon * pPolygon1, const IPolygon * pPolygon2)
//{
//	//axis along the poly's edge
//	D3DXVECTOR2 edge;
//
//	// flag mtv as invalid
//	float fLengthSquared = -1.0f; 
//
//	const cPolygon * pPolygonA = static_cast<const cPolygon *>(pPolygon1);
//	const cPolygon * pPolygonB = static_cast<const cPolygon *>(pPolygon2);
//
//	//loop through all the m_pVertices in polygonA
//	for (int i = 0; i < pPolygonA->m_nNoOfVertices; i++)
//	{
//		//Join the last vertex with the first
//		if (i == pPolygonA->m_nNoOfVertices - 1)
//		{
//			edge = Vector2ToD3DXVEC2(pPolygonA->m_pVertices[pPolygonA->m_nNoOfVertices - 1] - pPolygonA->m_pVertices[0]);
//		}
//		//Join the m_pVertices
//		else
//		{
//			edge = Vector2ToD3DXVEC2(pPolygonA->m_pVertices[i + 1] - pPolygonA->m_pVertices[i]);
//		}
//
//		//Get the normal and normalise 
//		D3DXVECTOR2 axis(-edge.y, edge.x);
//		D3DXVec2Normalize(&axis, &axis);
//
//		//Check to see if the polygons overlap along the current axis
//		if (NoOverlap(axis, *pPolygonA, *pPolygonB, fLengthSquared))
//			return false;
//
//		//Do the same for the other m_pVertices in this polygon
//	}
//
//	//Loop through all the m_pVertices in polygonB
//	for (int i = 0; i < pPolygonB->m_nNoOfVertices; i++)
//	{
//		//Join the last vertex with the first 
//		if (i == pPolygonB->m_nNoOfVertices - 1)
//		{
//			edge = Vector2ToD3DXVEC2(pPolygonB->m_pVertices[pPolygonB->m_nNoOfVertices - 1] - pPolygonB->m_pVertices[0]);
//		}
//		//Join the m_pVertices to make the edge
//		else
//		{
//			edge = Vector2ToD3DXVEC2(pPolygonB->m_pVertices[i + 1] - pPolygonB->m_pVertices[i]);
//		}
//
//		//Get the normal and normalise 
//		D3DXVECTOR2 axis(-edge.y, edge.x);
//		D3DXVec2Normalize(&axis, &axis);
//
//		//Check to see if the polygons overlap along the current axis
//		if (NoOverlap(axis, *pPolygonA, *pPolygonB, fLengthSquared))
//			return false;
//	}
//
//	//If no separation axis between the 2 polygons has been found by now, 
//	//THERE IS A COLLISION
//	return true;
//}
//
//bool cCollisionChecker::NoOverlap(const D3DXVECTOR2 &axis, const cPolygon & polygon1, const cPolygon & polygon2, float & fLengthSquared)
//{
//	float poly1Min, poly1Max;
//
//	//Project the other m_pVertices onto the axis by using dot product
//	//Initialise the min/max values with the first value
//	poly1Min  = D3DXVec2Dot(&Vector2ToD3DXVEC2(polygon1.m_pVertices[0]), &axis);
//	poly1Max = D3DXVec2Dot(&Vector2ToD3DXVEC2(polygon1.m_pVertices[0]), &axis);
//
//	//Get the highest and lowest dot products
//	for (int i = 1; i < polygon1.m_nNoOfVertices; i++)
//	{
//		float projection = D3DXVec2Dot(&Vector2ToD3DXVEC2(polygon1.m_pVertices[i]), &axis);
//
//		if (projection < poly1Min)
//		{
//			poly1Min = projection;
//		}
//
//		else if (projection > poly1Max)
//		{
//			poly1Max = projection;
//		}
//	}
//
//	//Now project the other polygon's m_pVertices onto the axis
//	float poly2Min, poly2Max;
//	poly2Min  = D3DXVec2Dot(&Vector2ToD3DXVEC2(polygon2.m_pVertices[0]), &axis);
//	poly2Max = D3DXVec2Dot(&Vector2ToD3DXVEC2(polygon2.m_pVertices[0]), &axis);
//
//	//Project onto the axis and get the min/max values
//	for (int i = 1; i < polygon2.m_nNoOfVertices; i++)
//	{
//		//Project onto the axis
//		float projection = D3DXVec2Dot(&Vector2ToD3DXVEC2(polygon2.m_pVertices[i]), &axis);
//
//		if (projection < poly2Min)
//		{
//			poly2Min = projection;
//		}
//
//		else if (projection > poly2Max)
//		{
//			poly2Max = projection;
//		}
//	}
//
//	float overlap1 = (poly2Max - poly1Min);
//	float overlap2 = (poly2Min - poly1Max);
//
//	// no overlap detected
//	if(overlap1 < 0.0f || overlap2 > 0.0f) return true;
//
//	// find out if we overlap on the 'right' or 'left' of the polygon.
//	float overlap = (overlap1 < -overlap2)? overlap1 : overlap2;
//
//	D3DXVECTOR2 sep = axis * overlap;
//
//	// the mtv vector length squared.
//	float sep_length_squared = D3DXVec2Dot(&sep, &sep);
//
//	// if that vector is smaller than our computed mtv (or the mtv hasn't been computed yet)
//	// use that vector as our current mtv.
//	if(sep_length_squared < fLengthSquared || fLengthSquared < 0.0f)
//	{
//		fLengthSquared = sep_length_squared;
//	}
//	return false;
//}

// *****************************************************************************
void cCollisionChecker::CreateCollisionChecker()
{
	s_pCollisionChecker = DEBUG_NEW cCollisionChecker();
}

// *****************************************************************************
void cCollisionChecker::Destroy()
{
	SafeDelete(&s_pCollisionChecker);
}

// *****************************************************************************
ICollisionChecker * ICollisionChecker::GetInstance()
{
	if(cCollisionChecker::s_pCollisionChecker == NULL)
		cCollisionChecker::CreateCollisionChecker();
	return cCollisionChecker::s_pCollisionChecker;
}

// *****************************************************************************
void ICollisionChecker::Destroy()
{
	cCollisionChecker::Destroy();
}

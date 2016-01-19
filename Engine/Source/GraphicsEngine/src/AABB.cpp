// *******************************************************************************************
//  AABB   version:  1.0   Ankur Sheel  date: 2012/11/25
//  ---------------------------------------------------------------------------------------
//  
//  ---------------------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *******************************************************************************************
// 
// *******************************************************************************************
#include "stdafx.h"
#include "AABB.h"

using namespace Graphics;
using namespace Base;

// *******************************************************************************************
cAABB::cAABB(const cVector3 & vMin, const cVector3 & vMax)
{
	Calculate(vMin, vMax);
}

// *******************************************************************************************
cAABB::~cAABB()
{

}

cAABB::cAABB(const cAABB & other)
{
	m_vCenter = other.m_vCenter;
	m_vHalfExtents = other.m_vHalfExtents;
}

cAABB & cAABB::operator =(const cAABB & other)
{
	m_vCenter = other.m_vCenter;
	m_vHalfExtents = other.m_vHalfExtents;
	return *this;
}

// *******************************************************************************************
void cAABB::VTransalate(const Base::cVector3 & vDeltaPos)
{
	m_vCenter += vDeltaPos;
}

// *******************************************************************************************
void cAABB::Calculate(const cVector3 & vMin, const cVector3 & vMax)
{
	m_vCenter = ((vMin + vMax) * 0.5f);
	m_vHalfExtents = ((vMax - vMin) * 0.5f);
}

// *******************************************************************************************
cVector3 cAABB::VGetCenter() const
{
	return m_vCenter;
}

// *******************************************************************************************
Base::cVector3 cAABB::VGetHalfExtents() const
{
	return m_vHalfExtents;
}

// *******************************************************************************************
shared_ptr<IAABB> const IAABB::DuplicateAABB(const IAABB * const pAABB)
{
	const cAABB * ptr = dynamic_cast<const cAABB *>(pAABB);
	IAABB * dupAABB = DEBUG_NEW cAABB(*ptr);
	return shared_ptr<IAABB>(dupAABB);
}
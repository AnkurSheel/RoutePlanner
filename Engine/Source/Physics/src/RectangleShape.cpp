// *****************************************************************************
//  RectangleShape version:  1.0   Ankur Sheel  date: 2013/06/22
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "RectangleShape.h"

using namespace Physics;
using namespace Base;

Base::cHashedString	cRectangleShape::m_Name = cHashedString("rectangle");

// *****************************************************************************
cRectangleShape::cRectangleShape()
{
}

// *****************************************************************************
cRectangleShape::~cRectangleShape()
{
}

// *****************************************************************************
IShape * cRectangleShape::VDuplicate()
{
	cRectangleShape * pShape = DEBUG_NEW cRectangleShape(*this);
	return pShape;
}

// *****************************************************************************
void cRectangleShape::VInitialize(const cVector3 & minBound, const cVector3 & maxBound)
{
	VUpdateBounds(cVector3::Zero, minBound, maxBound);
}

// *****************************************************************************
void cRectangleShape::VUpdateBounds(const Base::cVector3 & position,
	const cVector3 & minBound, const cVector3 & maxBound)
{
	m_Center = position + ((minBound + maxBound) * 0.5f);
	m_HalfExtents = ((maxBound - minBound) * 0.5f);
}

// *****************************************************************************
IShape * IShape::CreateRectangleShape()
{
	return DEBUG_NEW cRectangleShape();
}

// *****************************************************************************
//  Shape version:  1.0   Ankur Sheel  date: 2013/06/22
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "Shape.h"

using namespace Physics;
using namespace Base;

// *****************************************************************************
cShape::cShape()
{
}

// *****************************************************************************
cShape::~cShape()
{
}

// *****************************************************************************
cShape::cShape(const cShape & other)
: 	m_Center(other.m_Center)
, m_HalfExtents(other.m_HalfExtents)
{
}

// *****************************************************************************
cShape & cShape::operator =(const cShape & other)
{
	m_Center = other.m_Center;
	m_HalfExtents = other.m_HalfExtents;
	return *this;
}

// *****************************************************************************
void cShape::VOnMoved(const cVector3 & deltaPosition)
{
	m_Center += deltaPosition;
}

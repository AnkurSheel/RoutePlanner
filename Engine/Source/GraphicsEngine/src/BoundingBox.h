// *****************************************************************************
//  BoundingBox   version:  1.0   Ankur Sheel  date: 2012/11/24
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef BoundingBox_h__
#define BoundingBox_h__

#include "BoundingBox.hxx"

namespace Graphics
{
	class IAABB;
	class cAABB;
}

namespace Graphics
{
	class cBoundingBox 
		: public IBoundingBox
	{
	public:
		cBoundingBox(const Base::cVector3 & vMinBound, const Base::cVector3 & vMaxBound);
		~cBoundingBox();
		const Graphics::IAABB * const VGetAABB() const;
		void VTransform(const XMFLOAT4X4 & matWorld);
		void RecalculateAABBFromOBB();

	public:
		Base::cVector3	m_avObjectBounds[8];
		Base::cVector3	m_avOBBBounds[8];
		cAABB *			m_pAABB;
	};
}
#endif // BoundingBox_h__
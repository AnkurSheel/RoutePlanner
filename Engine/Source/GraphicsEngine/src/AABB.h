// *************************************************************************
//  AABB   version:  1.0   Ankur Sheel  date: 2012/11/25
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************
#ifndef AABB_h__
#define AABB_h__

#include "AABB.hxx"

namespace Graphics
{
	class cAABB
		: public IAABB
	{
	public:
		cAABB(const Base::cVector3 & vMin, const Base::cVector3 & vMax);
		~cAABB();
		cAABB(const cAABB & other);
		cAABB & operator =(const cAABB & other);
		
		Base::cVector3 VGetCenter() const;
		Base::cVector3 VGetHalfExtents() const;
		void Calculate(const Base::cVector3 & vMin, const Base::cVector3 & vMax);

	private:
		void VTransalate(const Base::cVector3 & vDeltaPos);

	private:
		Base::cVector3	m_vCenter;
		Base::cVector3	m_vHalfExtents;
	};
}
#endif // AABB_h__
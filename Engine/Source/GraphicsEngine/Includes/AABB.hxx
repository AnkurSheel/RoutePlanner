// *****************************************************************************
//  AABB   version:  1.0   Ankur Sheel  date: 2012/12/11
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef AABB_hxx__
#define AABB_hxx__

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class IAABB
	{
	public:
		virtual ~IAABB(){};
		virtual void VTransalate(const Base::cVector3 & vDeltaPos) = 0;
		virtual Base::cVector3 VGetCenter() const = 0; 
		virtual Base::cVector3 VGetHalfExtents() const = 0;

		GRAPHIC_API static shared_ptr<IAABB> const DuplicateAABB(const IAABB * const pAABB);
	};
}
#endif // AABB_hxx__

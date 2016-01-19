// *****************************************************************************
//  CollisionChecker   version:  1.0   Ankur Sheel  date: 05/14/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef CollisionChecker_h__
#define CollisionChecker_h__

#include "CollisionChecker.hxx"


namespace Graphics
{
	class cCollisionChecker 
		: public ICollisionChecker
		, public Base::cNonCopyable
	{
	public:
		static void CreateCollisionChecker();
		static void Destroy();

	private:
		cCollisionChecker();
		~cCollisionChecker();
//		bool CheckFor2DCollisions(const IPolygon * pPolygon1, const IPolygon * pPolygon2);		
		bool VCheckForCollisions(const IAABB * const pAABB1, const IAABB * pAABB2, cContact & contact);
//		bool NoOverlap(const D3DXVECTOR2 & axis, const cPolygon & polygon1, const cPolygon & polygon2, float & fLengthSquared);

	public:
		static ICollisionChecker * s_pCollisionChecker;
	};
}
#endif // CollisionChecker_h__

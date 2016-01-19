// *****************************************************************************
//  CollisionCheck   version:  1.0   Ankur Sheel  date: 05/14/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef CollisionChecker_hxx__
#define CollisionChecker_hxx__

#include "GraphicEngineDefines.h"

namespace Graphics
{
	//class IPolygon;
	class IAABB;
}

namespace Graphics
{
	class cContact
	{
	public:
		Base::cVector3	vNormal;
		Base::cVector3	vDistance;
	};

	class ICollisionChecker
	{
	public:
		virtual ~ICollisionChecker(){}
		//GRAPHIC_API virtual bool CheckFor2DCollisions(const Graphics::IPolygon * polygonA, const Graphics::IPolygon * polygonB) = 0;
		virtual bool VCheckForCollisions(const IAABB * const pAABB1, const IAABB * pAABB2, cContact & contact) = 0;
		GRAPHIC_API static ICollisionChecker * GetInstance();
		GRAPHIC_API static void Destroy();
	};
}
#endif // CollisionChecker_h__
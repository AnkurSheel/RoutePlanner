//  *******************************************************************************************************************
//  GraphicUtils   version:  1.0   Ankur Sheel  date: 2015/01/21
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef GRAPHICUTILS_HXX__
#define GRAPHICUTILS_HXX__

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class ICamera;
}
namespace Base
{
	class cVector3;
	class cVector2;
}

namespace Graphics
{
	struct stRay
	{
		Base::cVector3 origin;
		Base::cVector3 direction;

		float tMin;
		float tMax;

		stRay()
			: tMin(0.0f)
			, tMax(Base::MaxFloat)
		{
		}
	};

	class IGraphicUtils
	{
	public:
		/********************************************//**
		* @return Returns a pointer to the singleton object
		*
		* Creates and returns a pointer to a singleton object of this interface
		***********************************************/
		GRAPHIC_API static IGraphicUtils * GetInstance();
		GRAPHIC_API static void Destroy();
		
		virtual Base::cVector3 VScreenToWorldSpace(const Base::cVector2 & vPos, const ICamera * const pCamera) = 0;
		virtual void VGetRayFromScreenPosition(const Base::cVector2 & vScreenPos, const ICamera * const pCamera, stRay& ray) = 0;
		virtual ~IGraphicUtils(){}
	};
}
#endif // GRAPHICUTILS_HXX__

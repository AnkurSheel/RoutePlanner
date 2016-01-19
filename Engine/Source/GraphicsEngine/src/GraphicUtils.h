//  *******************************************************************************************************************
//  GraphicUtils   version:  1.0   Ankur Sheel  date: 2015/01/21
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef GRAPHICUTILS_H__
#define GRAPHICUTILS_H__

#include "GraphicUtils.hxx"

namespace Base
{
	class cVector2;
	class cVector3;
}

namespace Graphics
{
	class ICamera;
}

namespace Graphics
{
	class cGraphicUtils
		: public IGraphicUtils
		, public Base::cNonCopyable
	{
	private:
		cGraphicUtils();
		~cGraphicUtils();
		Base::cVector3 VScreenToWorldSpace(const Base::cVector2 & vPos, const ICamera * const pCamera) OVERRIDE;
		void VGetRayFromScreenPosition(const Base::cVector2 & vScreenPos, const ICamera * const pCamera, stRay& ray) OVERRIDE;

		Base::cVector3 Vec3TransformNormal(const Base::cVector3& inVector, const XMMATRIX& inMatrix);
		Base::cVector3 Vec3Transform(const Base::cVector3& inVector, const XMMATRIX& inMatrix);
		Base::cVector3 Vec3TransformCoordinate(const Base::cVector3& inVector, const XMMATRIX& inMatrix);

	private:
		static IGraphicUtils* s_pGraphicUtils;		/*!< static object of this class */

	private:
		friend static IGraphicUtils * IGraphicUtils::GetInstance();
		friend static void IGraphicUtils::Destroy();
	};
}
#endif // GRAPHICUTILS_H__

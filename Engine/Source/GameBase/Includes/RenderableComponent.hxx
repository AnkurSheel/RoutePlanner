// *****************************************************************************
//  RenderableComponent   version:  1.0   Ankur Sheel  date: 2013/05/21
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef RenderableComponent_hxx__
#define RenderableComponent_hxx__

#include "GameBaseDefines.h"

namespace Base
{
	class cVector3;
}
namespace Graphics
{
	class ICamera;
}

namespace GameBase
{
	class IRenderableComponent
	{
	public:
		virtual ~IRenderableComponent() {};
		virtual void VSetPosition(const Base::cVector3 & Position) = 0;
		virtual void VSetRotation(const Base::cVector3 & Rotation) = 0;
		virtual void VSetSize(const Base::cVector3 & Size) = 0;
		virtual void VRender(const Graphics::ICamera * const pCamera) = 0;
		virtual void VGetBounds(Base::cVector3 & minBound, Base::cVector3 & maxBounds) = 0;
	};
}
#endif // RenderableComponent_hxx__
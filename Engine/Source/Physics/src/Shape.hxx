// *****************************************************************************
//  Shape version:  1.0   Ankur Sheel  date: 2013/06/07
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef Shape_hxx
#define Shape_hxx

#include "PhysicsDefines.h"

namespace Base
{
	class cVector3;
}

namespace Physics
{
	class IShape
	{
	public:
		virtual ~IShape() {}
		virtual void VInitialize(const Base::cVector3 & minBound,
			const Base::cVector3 & maxBound) = 0;
		virtual Base::cVector3 VGetCenter() const = 0; 
		virtual Base::cVector3 VGetHalfExtents() const = 0;
		virtual Base::cVector3 VGetMinBound() const = 0;
		virtual Base::cVector3 VGetMaxBound() const = 0;
		virtual void VUpdateBounds(const Base::cVector3 & position,
			const Base::cVector3 & minBound, const Base::cVector3 & maxBound) = 0;
		virtual void VOnMoved(const Base::cVector3 & deltaPosition) = 0;
		virtual Base::cHashedString VGetName() = 0;
		virtual IShape * VDuplicate() = 0;
		virtual void VScale(const float scaleFactor) = 0;
		static IShape * CreateRectangleShape();
	};
}
#endif //Shape_hxx
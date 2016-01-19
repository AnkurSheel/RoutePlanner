// *****************************************************************************
//  Shape version:  1.0   Ankur Sheel  date: 2013/06/22
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef Shape_h
#define Shape_h

#include "Shape.hxx"
#include "vector3.h"

namespace Physics
{
	class cShape
		: public IShape
	{
	public:
		cShape();
		virtual ~cShape();
		cShape(const cShape & other);
		cShape & operator =(const cShape & other);
		virtual Base::cHashedString VGetShapeName() = 0;
		Base::cVector3 VGetCenter() const { return m_Center; }
		Base::cVector3 VGetHalfExtents() const { return m_HalfExtents; }
		Base::cVector3 VGetMinBound() const { return m_Center - m_HalfExtents; }
		Base::cVector3 VGetMaxBound() const { return m_Center + m_HalfExtents; }
		void VScale(const float scaleFactor) { m_HalfExtents *= scaleFactor; }

		Base::cHashedString VGetName() { return VGetShapeName(); }
		void VOnMoved(const Base::cVector3 & deltaPosition);

	protected:
		Base::cVector3	m_Center;
		Base::cVector3	m_HalfExtents;
	};
}
#endif //Shape_h
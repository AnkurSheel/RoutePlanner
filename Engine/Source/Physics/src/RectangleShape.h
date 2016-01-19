// *****************************************************************************
//  RectangleShape version:  1.0   Ankur Sheel  date: 2013/06/07
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef RectangleShape_hxx
#define RectangleShape_hxx

#include "Shape.h"

namespace Physics
{
	class cRectangleShape 
		: public cShape
	{
	public:
		cRectangleShape();
		~cRectangleShape();
		void VInitialize(const Base::cVector3 & minBound, const Base::cVector3 & maxBound);
		void VUpdateBounds(const Base::cVector3 & position,
			const Base::cVector3 & minBound, const Base::cVector3 & maxBound);
		IShape * VDuplicate();
		Base::cHashedString	VGetShapeName()  {return m_Name; }

	public:
		static Base::cHashedString			m_Name;	///< The component name
	};
}
#endif //RectangleShape_hxx
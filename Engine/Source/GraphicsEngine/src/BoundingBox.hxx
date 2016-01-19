// *****************************************************************************
//  BoundingBox   version:  1.0   Ankur Sheel  date: 2012/11/24
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef BoundingBox_hxx__
#define BoundingBox_hxx__

namespace Graphics
{
	class IAABB;
}

namespace Graphics
{
	class IBoundingBox
	{
	public:
		virtual ~IBoundingBox() {}
		/********************************************//**
		 * @return The AABB bounding volume of the model
		 *
		 * Returns The AABB bounding volume of the model
		 ***********************************************/
		virtual const Graphics::IAABB * const VGetAABB() const = 0;
		virtual void VTransform(const XMFLOAT4X4 & matWorld) = 0;
		static IBoundingBox * CreateBoundingBox(const Base::cVector3 & vMinBound,
			const Base::cVector3 & vMaxBound);
	};
}
#endif // BoundingBox_hxx__

// *****************************************************************************
//  Camera   version:  1.0   Ankur Sheel  date: 2012/09/15
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Camera_h__
#define Camera_h__
#include "Camera.hxx"

namespace Graphics
{
	/********************************************//**
     * @brief Class Declaration for \c ICamera
     * interface
     ***********************************************/
	class cCamera
		: public ICamera
		, public Base::cNonCopyable
	{
	public:
		cCamera();
	
	private:
		~cCamera();
		void VUpdate();
		Base::cVector3 VGetPosition() const;
		void VSetPosition(const Base::cVector3 & vPosition);
		const XMFLOAT4X4 & VGetViewMatrix() const;
		void VSetRotation(const Base::cVector3 & vRotation);

	private:
		/********************************************//**
		 *
		 * Calculates the view matrix based on the current position
		 * and rotation
		 ***********************************************/
		void CalculateViewMatrix();
	
	private:
		Base::cVector3		m_vPosition;	/*!< The position of the camera */
		Base::cVector3		m_vRotation;	/*!< The rotation of the camera */
		XMFLOAT4X4			m_matView;		/*!< The current view matrix */
		bool				m_bIsDirty;		/*!< True if the view matrix needs to be recalculated because of change in position or rotation*/
	};
}
#endif // Camera_h__
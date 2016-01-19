// *****************************************************************************
//  Camera   version:  1.0   Ankur Sheel  date: 2012/09/16
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************

#include "GraphicEngineDefines.h"

namespace Base
{
	class cVector3;
}

typedef struct _XMFLOAT4X4 XMFLOAT4X4;

namespace Graphics
{
	/********************************************//**
	 * @brief Interface to keep track of where the camera is
	 * and its current rotation
	 ***********************************************/
	class ICamera
	{
	public:
		virtual ~ICamera(){}
		/********************************************//**
		 *
		 * Updates the view matrix of the camera if required
		 ***********************************************/
		virtual void VUpdate() = 0;
		 /********************************************//**
 		 * @param[in] vPosition The position of the camera
		 *
		 * Sets the position of the camera 
		 ***********************************************/
		virtual void VSetPosition(const Base::cVector3 & vPosition) = 0;
		/********************************************//**
 		 * @return The position of the camera
		 *
		 * Gets the position of the camera 
		 ***********************************************/
		virtual Base::cVector3 VGetPosition() const = 0;
		/********************************************//**
 		 * @param[in] vRotation The rotation of the camera
		 *
		 * Sets the rotation of the camera 
		 ***********************************************/
		virtual void VSetRotation(const Base::cVector3 & vRotation) = 0;
		/********************************************//**
 		 * @return The view matrix
		 *
		 * Returns the view matrix based on the current position
		 * and rotation
		 ***********************************************/
		virtual const XMFLOAT4X4 & VGetViewMatrix() const = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		GRAPHIC_API static ICamera * CreateCamera();
	};
}
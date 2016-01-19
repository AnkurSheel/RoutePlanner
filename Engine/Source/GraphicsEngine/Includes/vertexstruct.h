// ***************************************************************
//  vertexstruct   version:  1.0   Ankur Sheel  date: 05/25/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef vertexstruct_h__
#define vertexstruct_h__

#include "GraphicEngineDefines.h"

namespace Graphics
{ 
	/********************************************//**
	 * @brief Structure of vertex data having position
	 * and texture
	 *
	 ***********************************************/
	struct stTexVertex
	{
	public:
		float		m_fX, m_fY, m_fZ;		/*!< The (X,Y,Z)position of this vertex in world space */
		float		m_fTex0, m_fTex1;		/*!< The (U,V) coordinates of the texture associated with this vertex */
		GRAPHIC_API stTexVertex();
		GRAPHIC_API stTexVertex(const float fX, const float fY, const float fZ, 
			const float fTex0, const float fTex1);
	};
}
#endif // vertexstruct_h__
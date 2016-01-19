// *****************************************************************************
//  ShaderManager   version:  1.0   Ankur Sheel  date: 2012/10/26
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "GraphicEngineDefines.h"

namespace Graphics
{
	class IShader;
}

namespace Graphics
{
	/********************************************//**
	 * @brief Interface for shader manager.
	 *
	 * Use this class to create and use Shaders
	 * 
	 * Singleton class.\n
	 * Usage :
	 * \li Call \c GetInstance() to use this class.
	 * \li Call \c VOnDestroy() when the application quits
	 ***********************************************/
	class IShaderManager
	{
	public:
		virtual ~IShaderManager(){}
		/********************************************//**
		 * @param[out] pShader The pointer to the existing shader
 		 * @param[in] strShaderName The name of the shader. This should be the same as the vertex and pixel shader files without the extension
		 * @return True if the shader was found or created. False otherwise
		 *
		 * Loads and creates the shader if it has not been created already.
		 * Adds the texture to the shader list
		 * Returns true if the shader was found or created. False otherwise
		 ***********************************************/
		virtual bool VGetShader(shared_ptr<IShader> & pShader, 
			const Base::cString & strShaderName) = 0;

		static IShaderManager * GetInstance();
		static void Destroy();
	};
}
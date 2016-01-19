// *************************************************************************
//  ObjModelLoader   version:  1.0   Ankur Sheel  date: 2012/10/29
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class IModel;
	struct stModelDef;
}

namespace Graphics
{
	/********************************************//**
	 * @brief Interface for loading model files with extension .spdo
	 ***********************************************/
	class IObjModelLoader
	{
	public:
		virtual ~IObjModelLoader(){}
		/********************************************//**
 		 * @param[in] strModelFile The path of the model file
		 * @return The model
		 *
		 * Loads and creates the model definition if it has not been created already.
		 * Adds the model definition to the map.
		 * Returns a pointer to the modeldef
		 ***********************************************/
		virtual shared_ptr<stModelDef> VGetModelDef(const Base::cString & strModelFile) = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		GRAPHIC_API static IObjModelLoader * GetInstance();
		GRAPHIC_API static void Destroy();
	};
}
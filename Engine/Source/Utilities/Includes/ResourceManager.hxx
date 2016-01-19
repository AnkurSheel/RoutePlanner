// ****************************************************************************
//  ResourceManager   version:  1.0   Ankur Sheel  date: 2011/11/16
//  ---------------------------------------------------------------------------
//  
//  ---------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ****************************************************************************
// 
// ****************************************************************************
#ifndef ResourceManager_hxx__
#define ResourceManager_hxx__

#include "UtilitiesDefines.h"

namespace Base
{
	class cString;
}

namespace Utilities
{
	class IResCache;
}

namespace Utilities
{
	/********************************************//**
	 * @brief Interface to encapsulate loading and usage
	 * of the game assets
	 *
	 * Singleton class.\n
	 * Usage :
	 * \li Call \c GetInstance() to use this class.
	 * \li Call \c VOnDestroy() when the application quits
	 ***********************************************/
	class IResourceManager
	{
	public:
		virtual ~IResourceManager(){}
		/********************************************//**
 		 * @param[in] strPath The path of the zip file 
		 * containing the assets
		 *
		 * Creates and Initializes the resource cache
		 ***********************************************/
		virtual void VInitialize(const int SizeInMB, const Base::cString & AssetsPath, const Base::cString & ResourceFileName, const bool UseDevelopmentDirectory) = 0;
		/********************************************//**
 		 * @return A pointer to the resource cache
		 *
		 * Returns a pointer to the resource cache
		 ***********************************************/
		virtual Utilities::IResCache * VGetResourceCache() const = 0;
		/********************************************//**
		 * @return Returns a pointer to the singleton object
		 *
		 * Creates and returns a pointer to a singleton object of this interface
		 ***********************************************/
		UTILITIES_API static IResourceManager* GetInstance();
		/********************************************//**
		 *
		 * Releases the resource manager object and deletes the singleton object
		 ***********************************************/
		UTILITIES_API static void Destroy();
	};
}
#endif // ResourceManager_hxx__
// ****************************************************************************
//  ResourceManager   version:  1.0   Ankur Sheel  date: 2011/11/16
//  ---------------------------------------------------------------------------
//  
//  ---------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ****************************************************************************
// 
// ****************************************************************************
#ifndef ResourceManager_h__
#define ResourceManager_h__

#include "ResourceManager.hxx"

namespace Utilities
{
	class IResCache;
}

namespace Utilities
{
	/********************************************//**
     * @brief Class Declaration for \c IResourceManager
     * interface
     ***********************************************/
	class cResourceManager
		: public IResourceManager
		, public Base::cNonCopyable
	{
	private:
		cResourceManager();
		~cResourceManager();
		void VInitialize(const int SizeInMB, const Base::cString & AssetsPath, const Base::cString & ResourceFileName, const bool UseDevelopmentDirectory);
		Utilities::IResCache * VGetResourceCache() const;

	private:
		Utilities::IResCache *	m_pResourceCache;		/*!< The resource cache */
		static IResourceManager* s_pResourceManager;	/*!< static object of this class */

	private:
		friend static IResourceManager * IResourceManager::GetInstance();
		friend static void IResourceManager::Destroy();
	};
}
#endif // ResourceManager_h__
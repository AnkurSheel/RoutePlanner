// *****************************************************************************
//  GameDirectories   version:  1.0   Ankur Sheel  date: 2013/01/22
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef GameDirectories_h__
#define GameDirectories_h__

#include "UtilitiesDefines.h"

namespace Utilities
{
	class IParamLoader;
}

namespace Utilities
{
	class cGameDirectories
	{
	public:
		UTILITIES_API static const cGameDirectories & GameDirectories();
		UTILITIES_API static void Initialize();

	public:
		Base::cString	strMediaDirectory;
		Base::cString	strFontDirectory;
		Base::cString	strShaderDirectory;
		Base::cString	strSpriteDirectory;
		Base::cString	strSoundSFXDirectory;
		Base::cString	strSoundMusicDirectory;
		Base::cString	strModelDirectory;
	};
}
#endif // GameDirectories_h__
//  *******************************************************************************************************************
//  GameDirectories   version:  1.0   Ankur Sheel  date: 2013/01/22
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef GameDirectories_h__
#define GameDirectories_h__

#include "UtilitiesDefines.h"

namespace Utilities
{
	class cGameDirectories
		: public Base::cNonCopyable
	{
	public:
		UTILITIES_API static void Initialize(const Base::cString & AssetsPath);
		UTILITIES_API static Base::cString GetMediaDirectory() { return MediaDirectory; }
		UTILITIES_API static Base::cString GetFontDirectory() { return FontDirectory; }
		UTILITIES_API static Base::cString GetShaderDirectory() { return ShaderDirectory; }
		UTILITIES_API static Base::cString GetSpriteDirectory() { return SpriteDirectory; }
		UTILITIES_API static Base::cString GetSoundSFXDirectory() { return SoundSFXDirectory; }
		UTILITIES_API static Base::cString GetSoundMusicDirectory() { return SoundMusicDirectory; }
		UTILITIES_API static Base::cString GetModelDirectory() { return ModelDirectory; }
		UTILITIES_API static Base::cString GetDesignDirectory() { return DesignDirectory; }
		UTILITIES_API static Base::cString GetUiDirectory() { return UiDirectory; }

	private:
		cGameDirectories();
		~cGameDirectories();

	private:
		static Base::cString	MediaDirectory;
		static Base::cString	FontDirectory;
		static Base::cString	ShaderDirectory;
		static Base::cString	SpriteDirectory;
		static Base::cString	SoundSFXDirectory;
		static Base::cString	SoundMusicDirectory;
		static Base::cString	ModelDirectory;
		static Base::cString	DesignDirectory;
		static Base::cString	UiDirectory;
	};
}
#endif // GameDirectories_h__
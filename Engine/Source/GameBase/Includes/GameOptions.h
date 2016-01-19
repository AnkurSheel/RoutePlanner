#ifndef GameOptions_h__
#define GameOptions_h__

#include "GameBaseDefines.h"

namespace Utilities
{
	class IParamLoader;
}

namespace GameBase
{
	class cGameOptions
	{
	public:
		cGameOptions();
		~cGameOptions();
		GAMEBASE_API static cGameOptions & GameOptions();
		static void InitializeGameOptions(const Base::cString & strPlayerOptionsFile);
		GAMEBASE_API static void SaveGameOptions(const Base::cString & strPlayerOptionsFile);

	public:
		bool	bFullScreen;	///< True if in fullscreen mode
		int		iWidth;			///< Screen width
		int		iHeight;		///< Screen height

		bool	bPlaySfx;
		bool	bPlayMusic;
		int		iSFXVolume;
		int		iMusicVolume;

	};
}
#endif GameOptions_h__

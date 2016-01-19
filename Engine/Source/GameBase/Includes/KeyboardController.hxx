// *****************************************************************************
//  KeyboardController   version:  1.0   Ankur Sheel  date: 2013/05/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef KeyboardController_hxx__
#define KeyboardController_hxx__

#include "GameBaseDefines.h"

namespace GameBase
{
	class IKeyboardController
	{
	public:
		virtual void VOnKeyDown(const unsigned int CharID) = 0;
		virtual void VOnKeyUp(const unsigned int CharID) = 0;
		virtual void VLockKey(const unsigned int CharID) = 0;
		virtual void VUnlockKey(const unsigned int CharID) = 0;
		virtual bool VIsKeyPressed(const unsigned int CharID) const = 0;
		virtual bool VIsKeyLocked(const unsigned int CharID) const = 0;

		GAMEBASE_API static IKeyboardController * Instance();
		static void Destroy();
	};
}
#endif // KeyboardController_hxx__
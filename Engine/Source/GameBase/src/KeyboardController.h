// *****************************************************************************
//  KeyboardController   version:  1.0   Ankur Sheel  date: 2013/05/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef KeyboardController_h__
#define KeyboardController_h__

#include "KeyboardController.hxx"

namespace GameBase
{
	class cKeyboardController
		: public IKeyboardController
		, public Base::cNonCopyable
	{
	public:
		~cKeyboardController();

	private:
		cKeyboardController();
		void VOnKeyDown(const unsigned int CharID);
		void VOnKeyUp(const unsigned int CharID);
		void VLockKey(const unsigned int CharID) { m_bLockedKeys[CharID] = true; }
		void VUnlockKey(const unsigned int CharID) { m_bLockedKeys[CharID] = false; }

		bool VIsKeyPressed(const unsigned int CharID) const { return (m_Keys[CharID]); }
		bool VIsKeyLocked(const unsigned int CharID) const { return (m_bLockedKeys[CharID]); }

	private:
		bool	m_Keys[KEYBOARD_KEYS];
		bool	m_bLockedKeys[KEYBOARD_KEYS];

		static cKeyboardController  * m_spKeyboardController;

	private:
		friend static IKeyboardController * IKeyboardController::Instance();
		friend static void IKeyboardController::Destroy();
	};
}
#endif // KeyboardController_h__
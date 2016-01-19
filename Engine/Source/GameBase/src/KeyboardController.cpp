// *****************************************************************************
//  KeyboardController   version:  1.0   Ankur Sheel  date: 2013/05/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "KeyboardController.h"

using namespace GameBase;

cKeyboardController * cKeyboardController::m_spKeyboardController = NULL;

// *****************************************************************************
cKeyboardController::cKeyboardController()
{
	memset(m_Keys, 0, sizeof(m_Keys));
	memset(m_bLockedKeys, 0, sizeof(m_bLockedKeys));
}

// *****************************************************************************
cKeyboardController::~cKeyboardController()
{
}

// *****************************************************************************
void cKeyboardController::VOnKeyDown(const unsigned int CharID)
{
	m_Keys[CharID] = true;
}

// *****************************************************************************
void cKeyboardController::VOnKeyUp(const unsigned int CharID)
{
	m_Keys[CharID] = false;
}

// *****************************************************************************
IKeyboardController * IKeyboardController::Instance()
{
	if(cKeyboardController::m_spKeyboardController == NULL)
		cKeyboardController::m_spKeyboardController = DEBUG_NEW cKeyboardController();
	return cKeyboardController::m_spKeyboardController;

}

// *****************************************************************************
void IKeyboardController::Destroy()
{
	SafeDelete(&cKeyboardController::m_spKeyboardController);
}
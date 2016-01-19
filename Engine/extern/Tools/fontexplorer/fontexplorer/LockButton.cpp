/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  4-Nov-08 | REQ #090: Created
*****************************************************************************/

// LockButton.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "LockButton.h"


// CLockButton

IMPLEMENT_DYNAMIC(CLockButton, CImageButton)


/****************************************************************************
*                          CLockButton::CLockButton
*                          CLockButton::~CLockButton
* Effect: 
*       Initializes the lock button state
****************************************************************************/

CLockButton::CLockButton()
   {
    LockState = FALSE; // unlocked
   }

CLockButton::~CLockButton()
   {
   }

/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CLockButton, CImageButton)                        // REQ #090
    ON_CONTROL_REFLECT_EX(BN_CLICKED, &CLockButton::OnBnClicked)    // REQ #090
END_MESSAGE_MAP()                                                   // REQ #090

// CLockButton message handlers                                     // REQ #090

/****************************************************************************
*                          CLockButton::updateImage
* Result: void
*       
* Effect: 
*       Updates the image
****************************************************************************/

void CLockButton::updateImage()                                     // REQ #090
    {                                                               // REQ #090
     LoadBitmaps(LockState ? IDB_LOCKED : IDB_UNLOCKED);            // REQ #090
     Invalidate();                                                  // REQ #090
    } // CLockButton::updateImage                                   // REQ #090

/****************************************************************************
*                        CLockButton::PreSubclassWindow
* Result: void
*       
* Effect: 
*       Updates the image
****************************************************************************/

void CLockButton::PreSubclassWindow()                               // REQ #090
    {                                                               // REQ #090
     CImageButton::PreSubclassWindow();                             // REQ #090
     updateImage();                                                 // REQ #090
    }                                                               // REQ #090


/****************************************************************************
*                           CLockButton::OnBnClicked
* Result: BOOL
*       
* Effect: 
*       Toggles the button state
****************************************************************************/

BOOL CLockButton::OnBnClicked()                                     // REQ #090
    {                                                               // REQ #090
     LockState = !LockState;                                        // REQ #090
     updateImage();                                                 // REQ #090
     return FALSE;                                                  // REQ #090
    }                                                               // REQ #090

/****************************************************************************
*                          CLockButton::GetLockState
* Result: BOOL
*       Lock state
****************************************************************************/

BOOL CLockButton::GetLockState()
    {
     return LockState;
    } // CLockButton::GetLockState

/****************************************************************************
*                          CLockButton::SetLockState
* Inputs:
*       BOOL mode: Desired lock state
* Result: void
*       
* Effect: 
*       Sets the lock state
****************************************************************************/

void CLockButton::SetLockState(BOOL mode)
    {
     if(LockState == mode)
        return;
     LockState = mode;
     updateImage();
    } // CLockButton::SetLockState

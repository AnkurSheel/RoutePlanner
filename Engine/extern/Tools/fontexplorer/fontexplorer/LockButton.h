/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  4-Nov-08 | Created
*  4-Nov-08 | REQ #090: Added lock button
*****************************************************************************/
#pragma once                                                        // REQ #090

#include "ImageButton.h"                                            // REQ #090
// CLockButton                                                      // REQ #090
                                                                    // REQ #090
class CLockButton : public CImageButton                             // REQ #090
{                                                                   // REQ #090
        DECLARE_DYNAMIC(CLockButton)                                // REQ #090
                                                                    // REQ #090
public:                                                             // REQ #090
        CLockButton();                                              // REQ #090
        virtual ~CLockButton();                                     // REQ #090
        BOOL GetLockState();                                        // REQ #090
        void SetLockState(BOOL mode);                               // REQ #090
                                                                    // REQ #090
protected:                                                          // REQ #090
        BOOL LockState;                                             // REQ #090
        DECLARE_MESSAGE_MAP()                                       // REQ #090
        virtual void PreSubclassWindow();                           // REQ #090
        void updateImage();                                         // REQ #090
        afx_msg BOOL OnBnClicked();                                 // REQ #090
    };



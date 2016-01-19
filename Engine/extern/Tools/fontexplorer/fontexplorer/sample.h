/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 19-Oct-08 | REQ #059: Created
* 19-Oct-08 | REQ #059: Show grid on display
*****************************************************************************/
// Sample.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSample window
#pragma once

class CSample : public CStatic
{
// Construction
public:
        CSample();
        void SetGraphicsMode(DWORD mode);
        void ShowGrid(BOOL m);                                      // REQ #059
        void SetTextAlign(DWORD mode);                              // REQ #060
// Attributes
public:

// Operations
public:

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CSample)
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~CSample();

        // Generated message map functions
protected:
        BOOL Grid;                                                  // REQ #059
        DWORD TextAlign;                                            // REQ #060
        int GraphicsMode;
        //{{AFX_MSG(CSample)
        afx_msg void OnPaint();
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  8-May-08 | Created change log
*  8-May-08 | REQ #042: Unicode conversion
*****************************************************************************/
// Message.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessage window
#pragma once

class CMessage : public CEdit
{
// Construction
public:
        CMessage();

// Attributes
public:

// Operations
public:
        HBRUSH OnCtlColor(CDC * pdc);
        void SetWindowText(LPCTSTR text);                           // REQ #042

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CMessage)
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~CMessage();

        // Generated message map functions
protected:
        //{{AFX_MSG(CMessage)
                // NOTE - the ClassWizard will add and remove member functions here.
        //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

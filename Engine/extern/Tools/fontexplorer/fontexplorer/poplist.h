/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 24-Apr-08 | Created
* 24-Apr-08 | REQ #009: Added #pragma once
*****************************************************************************/

#pragma once                                                        // REQ #009

// poplist.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPopupList window

class CPopupList : public CListBox
{
// Construction
public:
        CPopupList();

// Attributes
public:

// Operations
public:

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CPopupList)
        protected:
        virtual void PostNcDestroy();
        virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~CPopupList();

        void DoLButtonDown(UINT nFlags, CPoint point);
        void DoLButtonUp(UINT nFlags, CPoint point);
        void DoLButtonDblClk(UINT nFlags, CPoint point);
        void DoRButtonDblClk(UINT nFlags, CPoint point);
        void DoRButtonDown(UINT nFlags, CPoint point);
        void DoRButtonUp(UINT nFlags, CPoint point);
        // Generated message map functions
protected:
        //{{AFX_MSG(CPopupList)
        //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

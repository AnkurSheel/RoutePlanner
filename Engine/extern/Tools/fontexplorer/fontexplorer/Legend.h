/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 24-Apr-08 | Created
* 24-Apr-08 | REQ #009: Rearranged #include directives, added #pragma once
*****************************************************************************/
// Legend.h : header file
//
#pragma once

#include "legendi.h"                                                // REQ #009

/////////////////////////////////////////////////////////////////////////////
// CLegend window

class CLegend : public CComboBox
{
// Construction
public:
        CLegend();

// Attributes
public:
        int AddString(LegendInfo * li);
        void AddLegends(LegendInfo ** li);
// Operations
public:

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CLegend)
        public:
        virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
        virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
        virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~CLegend();

        // Generated message map functions
protected:
        //{{AFX_MSG(CLegend)
        afx_msg void OnDropdown();
        //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

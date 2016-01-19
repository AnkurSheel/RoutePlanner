/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 28-Oct-08 | Created change log
* 28-Oct-08 | REQ #074: AddStrings: first parameter is now const
* 28-Oct-08 | REQ #075: Use ON_CONTROL_REFLECT_EX
* 31-Oct-08 | REQ #079: Added Select method
*****************************************************************************/
// IDCombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIDCombo window
#pragma once

typedef struct {
        int id;  // IDS_ for string, or 0 for end of table for AddStrings
        int val; // value for itemdata
               } IDData;


class CIDCombo : public CComboBox
{
// Construction
public:
        CIDCombo();

// Attributes
public:

// Operations
public:

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CIDCombo)
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~CIDCombo();
        int AddString(const IDData * data);                         // REQ #074
        BOOL AddStrings(const IDData * data, int def = 0);          // REQ #074
        INT_PTR Select(DWORD_PTR data);                             // REQ #079

        // Generated message map functions
protected:
        //{{AFX_MSG(CIDCombo)
        afx_msg BOOL OnDropdown();                                  // REQ #075
        //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

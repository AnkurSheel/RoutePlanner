/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 24-Apr-08 | Created
* 24-Apr-08 | REQ #008: Removed FontExplorer.h
* 15-Oct-08 | REQ #046: Changed default logic
* 28-Oct-08 | REQ #074: AddStrings: first parameter is now const
* 28-Oct-08 | REQ #075: Use ON_CONTROL_REFLECT_EX
* 31-Oct-08 | REQ #079: Added Select
*****************************************************************************/
// IDCombo.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"                                               // REQ #008
#include "IDCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIDCombo

CIDCombo::CIDCombo()
{
}

CIDCombo::~CIDCombo()
{
}


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CIDCombo, CComboBox)
        //{{AFX_MSG_MAP(CIDCombo)
        ON_CONTROL_REFLECT_EX(CBN_DROPDOWN, OnDropdown)             // REQ #075
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIDCombo message handlers

/****************************************************************************
*                             CIDCombo::AddString
* Inputs:
*       IDData * data: Data to add
* Result: int
*       Index of insertion, or CB_ERR
* Effect: 
*       Adds the string designated by the ID to the combo box, and adds its
*       value to the itemdata
****************************************************************************/

int CIDCombo::AddString(const IDData * data)                        // REQ #074
    {
     CString s;
     if(s.LoadString(data->id) == 0)
        return CB_ERR;

     int i = CComboBox::AddString(s);
     if(i == CB_ERR)
        return CB_ERR;
     CComboBox::SetItemData(i, data->val);
     return i;
    }

/****************************************************************************
*                            CIDCombo::AddStrings
* Inputs:
*       const IDData * data: Pointer to data table
*       int def: ItemData of default control
* Result: BOOL
*       TRUE if successful
*       FALSE if any error
* Effect: 
*       Adds the strings in the table to the combo box.  The table is 
*       terminated by an entry whose id field is 0
****************************************************************************/

BOOL CIDCombo::AddStrings(const IDData * data, int def)             // REQ #074
    {
     for(int i = 0; data[i].id != 0; i++)
        { /* add it */
         int index = AddString(&data[i]);
         if(index == CB_ERR)
           return FALSE;
        } /* add it */

     for(int i = 0; data[i].id != 0; i++)                           // REQ #046
        { /* set default */                                         // REQ #046
         if(GetItemData(i) == def)                                  // REQ #046
            SetCurSel(i);                                           // REQ #046
        } /* set default */                                         // REQ #046
     return TRUE;
    }


/****************************************************************************
*                             CIDCombo::OnDropdown
* Result: BOOL
*       
* Effect: 
*       Handles dropdown resizing, then allows parent to see message
****************************************************************************/

BOOL CIDCombo::OnDropdown()                                         // REQ #075
{
 int n = GetCount();
 n = max(n, 2);

 int ht = GetItemHeight(0);
 CRect r;
 GetWindowRect(&r);

 CSize sz;
 sz.cx = r.Width();
 sz.cy = ht * (n + 2);

 SetWindowPos(NULL, 0, 0, sz.cx, sz.cy, SWP_NOMOVE | SWP_NOZORDER);
 return FALSE; // allow parent to handle it now                     // REQ #075
}

/****************************************************************************
*                              CIDCombo::Select
* Inputs:
*       DWORD_PTR data: Data to match
* Result: INT_PTR
*       Index of item selected, or CB_ERR if not found
* Effect: 
*       Selects the item, or does nothing if no match
****************************************************************************/

INT_PTR CIDCombo::Select(DWORD_PTR data)                            // REQ #079
    {                                                               // REQ #079
     for(int i = 0; i < CComboBox::GetCount(); i++)                 // REQ #079
        { /* scan elements */                                       // REQ #079
         if(CComboBox::GetItemData(i) == data)                      // REQ #079
            { /* found it */                                        // REQ #079
             CComboBox::SetCurSel(i);                               // REQ #079
             return i;                                              // REQ #079
            } /* found it */                                        // REQ #079
        } /* scan elements */                                       // REQ #079
     return CB_ERR;                                                 // REQ #079
    } // CIDCombo::Select                                           // REQ #079

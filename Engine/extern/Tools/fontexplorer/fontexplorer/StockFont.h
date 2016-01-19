/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 19-Oct-08 | Created
* 19-Oct-08 | REQ #055: Converted to CFormView
* 20-Oct-08 | REQ #064: Added DEFAULT_GUI_FONT
*  2-Nov-08 | REQ #084: Renamed StockFnt.* to StockFont.*
*  2-Nov-08 | REQ #085: Show stock font face name
*  2-Nov-08 | REQ #086: Use copy button image
*****************************************************************************/
// StockFont.h : header file                                        // REQ #084
//

/////////////////////////////////////////////////////////////////////////////
// CStockFont dialog

#include "afxwin.h"
#include "ImageButton.h"                                            // REQ #086

class CStockFont : public CFormView                                 // REQ #055
{
    DECLARE_DYNCREATE(CStockFont)                                   // REQ #055
// Construction
public:
        CStockFont();   // standard constructor                     // REQ #055

// Dialog Data
        enum { IDD = IDD_STOCKFONTS };
protected:
        CButton c_SYSTEM_FONT;
        CButton c_SYSTEM_FIXED_FONT;
        CButton c_OEM_FIXED_FONT;
        CButton c_DEVICE_DEFAULT_FONT;
        CButton c_ANSI_VAR_FONT;
        CButton c_ANSI_FIXED_FONT;
        CButton c_DEFAULT_GUI_FONT;                                 // REQ #064
        CStatic c_Sample;
        CEdit c_FontName;                                           // REQ #085
        CImageButton c_Copy;                                        // REQ #086

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CStockFont)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

#ifdef _DEBUG
        virtual void AssertValid() const;
        virtual void Dump(CDumpContext& dc) const;
#endif

// Implementation
protected:
        void setSample(CButton & caption, int fontid);

        // Generated message map functions
        //{{AFX_MSG(CStockFont)
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
        virtual void OnInitialUpdate();
        afx_msg void OnAnsiFixedFont();
        afx_msg void OnAnsiVarFont();
        afx_msg void OnCopy();
        afx_msg void OnDeviceDefaultFont();
        afx_msg void OnOemFixedFont();
        afx_msg void OnSystemFixedFont();
        afx_msg void OnSystemFont();
        afx_msg void OnDefaultGUIFont();                            // REQ #064
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
    };

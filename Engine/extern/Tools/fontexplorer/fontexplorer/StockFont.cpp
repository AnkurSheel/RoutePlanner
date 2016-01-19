/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 19-Oct-08 | Created
* 19-Oct-08 | REQ #055: Converted to CFormView
* 19-Oct-08 | REQ #061: Set caption
* 20-Oct-08 | REQ #062: ResizeParentToFit                           
* 20-Oct-08 | REQ #064: Default GUI font
*  2-Nov-08 | REQ #084: Renamed StockFnt.* to StockFont.*
*  2-Nov-08 | REQ #085: Show stock font facename
*  2-Nov-08 | REQ #086: Change to use copy image button
*****************************************************************************/
// StockFont.cpp : implementation file                              // REQ #084
//

#include "stdafx.h"
#include "resource.h"
#include "StockFont.h"                                              // REQ #084
#include "toclip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CStockFont, CFormView)

#ifdef _DEBUG
void CStockFont::AssertValid() const
   {
    CFormView::AssertValid();
   }

void CStockFont::Dump(CDumpContext& dc) const
   {
    CFormView::Dump(dc);
   }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStockFont dialog


CStockFont::CStockFont()                                            // REQ #055
        : CFormView(CStockFont::IDD)                                // REQ #055
{
        //{{AFX_DATA_INIT(CStockFont)
                // NOTE: the ClassWizard will add member initialization here
        //}}AFX_DATA_INIT
}


void CStockFont::DoDataExchange(CDataExchange* pDX)
   {
    CFormView::DoDataExchange(pDX);                                 // REQ #055
    DDX_Control(pDX, IDC_SYSTEM_FONT, c_SYSTEM_FONT);
    DDX_Control(pDX, IDC_SYSTEM_FIXED_FONT, c_SYSTEM_FIXED_FONT);
    DDX_Control(pDX, IDC_OEM_FIXED_FONT, c_OEM_FIXED_FONT);
    DDX_Control(pDX, IDC_DEVICE_DEFAULT_FONT, c_DEVICE_DEFAULT_FONT);
    DDX_Control(pDX, IDC_ANSI_VAR_FONT, c_ANSI_VAR_FONT);
    DDX_Control(pDX, IDC_ANSI_FIXED_FONT, c_ANSI_FIXED_FONT);
    DDX_Control(pDX, IDC_SAMPLE, c_Sample);
    DDX_Control(pDX, IDC_DEFAULT_GUI_FONT, c_DEFAULT_GUI_FONT);     // REQ #064
    DDX_Control(pDX, IDC_COPY, c_Copy);                             // REQ #086
    DDX_Control(pDX, IDC_FONTNAME, c_FontName);                     // REQ #085
   }


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CStockFont, CFormView)                            // REQ #055
        //{{AFX_MSG_MAP(CStockFont)
        ON_WM_CTLCOLOR()
        ON_BN_CLICKED(IDC_ANSI_FIXED_FONT, OnAnsiFixedFont)
        ON_BN_CLICKED(IDC_ANSI_VAR_FONT, OnAnsiVarFont)
        ON_BN_CLICKED(IDC_COPY, OnCopy)
        ON_BN_CLICKED(IDC_DEVICE_DEFAULT_FONT, OnDeviceDefaultFont)
        ON_BN_CLICKED(IDC_OEM_FIXED_FONT, OnOemFixedFont)
        ON_BN_CLICKED(IDC_SYSTEM_FIXED_FONT, OnSystemFixedFont)
        ON_BN_CLICKED(IDC_SYSTEM_FONT, OnSystemFont)
        ON_BN_CLICKED(IDC_DEFAULT_GUI_FONT, OnDefaultGUIFont)      // REQ #064
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockFont message handlers


/****************************************************************************
*                            CStockFont::OnCtlColor
* Inputs:
*       CDC * pDC:
*       CWnd * pWnd:
*       UINT nCtlColor
* Result: HBRUSH
*       
* Effect: 
*       Sets the background to white for the sample control
****************************************************************************/

HBRUSH CStockFont::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
   {
    if(pWnd->m_hWnd == c_Sample.m_hWnd)
       return (HBRUSH)::GetStockObject(WHITE_BRUSH);

    HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);       // REQ #055
        

    return hbr;
   }

/****************************************************************************
*                         CStockFont::OnInitialUpdate
* Result: void
*       
* Effect: 
*       Initializes the form
****************************************************************************/

void CStockFont::OnInitialUpdate()                                  // REQ #055
   {
    CFormView::OnInitialUpdate();                                   // REQ #055
        
    CString s;
    s.LoadString(IDS_STOCKFONT_EXPLORER_CAPTION);                   // REQ #061
    GetParentFrame()->SetWindowText(s);                             // REQ #061

    CheckRadioButton(IDC_ANSI_FIXED_FONT, IDC_SYSTEM_FONT, 
                                                        IDC_SYSTEM_FONT);

    c_Copy.LoadBitmaps(IDB_COPY);                                   // REQ #086
    GetParentFrame()->RecalcLayout();                               // REQ #062
    ResizeParentToFit(FALSE);                                       // REQ #062
    OnSystemFont();
   }

/****************************************************************************
*                            CStockFont::setSample
* Inputs:
*       CButton & caption: Caption for contents
*       int fontid: Font ID value for stock object
* Result: void
*       
* Effect: 
*       Selects the stock font into the static control.  Uses the caption
*       from the 'caption' parameter as the contents
****************************************************************************/

void CStockFont::setSample(CButton & caption, int fontid)
    {
     CString s;
     caption.GetWindowText(s);

     CString extra;
     extra.LoadString(IDS_CHARS_HIGH);
     s += _T("   ");
     s += extra;

     CFont f;
     f.CreateStockObject(fontid);
     c_Sample.SetFont(&f);
     c_Sample.SetWindowText(s);

     LOGFONT lf;                                                    // REQ #085
     f.GetLogFont(&lf);                                             // REQ #085
                                                                    // REQ #085
     s.Format(_T("%s %d"), lf.lfFaceName, lf.lfHeight);             // REQ #085
     c_FontName.SetWindowText(s);                                   // REQ #085
    }

/****************************************************************************
*                         CStockFont::OnAnsiFixedFont
* Result: void
*       
* Effect: 
*       Sets the ANSI fixed font
****************************************************************************/

void CStockFont::OnAnsiFixedFont() 
   {
    setSample(c_ANSI_FIXED_FONT, ANSI_FIXED_FONT);
   }

/****************************************************************************
*                          CStockFont::OnAnsiVarFont
* Result: void
*       
* Effect: 
*       Sets the ANSI variable font
****************************************************************************/

void CStockFont::OnAnsiVarFont() 
   {
    setSample(c_ANSI_VAR_FONT, ANSI_VAR_FONT);
   }

/****************************************************************************
*                              CStockFont::OnCopy
* Result: void
*       
* Effect: 
*       Copies the bitmap of the sample window to the clipboard
****************************************************************************/

void CStockFont::OnCopy() 
   {
    toClipboard(&c_Sample, FALSE);
   }

/****************************************************************************
*                       CStockFont::OnDeviceDefaultFont
* Result: void
*       
* Effect: 
*       Selects the default font
****************************************************************************/

void CStockFont::OnDeviceDefaultFont() 
   {
    setSample(c_DEVICE_DEFAULT_FONT, DEVICE_DEFAULT_FONT);
   }

/****************************************************************************
*                          CStockFont::OnOemFixedFont
* Result: void
*       
* Effect: 
*       Sets the OEM Fixed Font
****************************************************************************/

void CStockFont::OnOemFixedFont() 
   {
    setSample(c_OEM_FIXED_FONT, OEM_FIXED_FONT);   
   }

/****************************************************************************
*                        CStockFont::OnSystemFixedFont
* Result: void
*       
* Effect: 
*       Sets the System Fixed Font
****************************************************************************/

void CStockFont::OnSystemFixedFont() 
   {
    setSample(c_SYSTEM_FIXED_FONT, SYSTEM_FIXED_FONT);
   }

/****************************************************************************
*                           CStockFont::OnSystemFont
* Result: void
*       
* Effect: 
*       Sets the system font
****************************************************************************/

void CStockFont::OnSystemFont() 
   {
    setSample(c_SYSTEM_FONT, SYSTEM_FONT); 
   }

/****************************************************************************
*                        CStockFont::OnDefaultGUIFont
* Result: void
*       
* Effect: 
*       Uses default GUI font
****************************************************************************/

void CStockFont::OnDefaultGUIFont()                                 // REQ #064
    {                                                               // REQ #064
     setSample(c_DEFAULT_GUI_FONT, DEFAULT_GUI_FONT);               // REQ #064
    } // CStockFont::OnDefaultGUIFont                               // REQ #064

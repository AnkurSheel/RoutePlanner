/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 24-Apr-08 | Created
* 24-Apr-08 | REQ #008: Removed FontExplorer.h
*  4-Nov-08 | REQ #089: Completed code
* 12-Nov-08 | REQ #092: Wiggle window to keep GCP results visible
* 12-Nov-08 | REQ #093: Clean up status display
*****************************************************************************/
// GetCharacterPlacement.cpp : implementation file
//

#include "stdafx.h"                                                 // REQ #089
#include "resource.h"                                               // REQ #008
#include "GetCharacterPlacement.h"                                  // REQ #089
#include "Language.h"                                               // REQ #089
#include "ToString.h"                                               // REQ #089
#include "ErrorString.h"                                            // REQ #089
                                                                    // REQ #089
// CGetCharacterPlacement                                           // REQ #089
                                                                    // REQ #089
IMPLEMENT_DYNCREATE(CGetCharacterPlacement, CFormView)              // REQ #089
                                                                    // REQ #089
static const IDData Languages[] = {                                 // REQ #089
   { IDS_C6, LANGUAGE_C6},                                          // REQ #089
   { IDS_C2008, LANGUAGE_C2008},                                    // REQ #089
   { IDS_MFC6, LANGUAGE_MFC6},                                      // REQ #089
   { IDS_MFC2008, LANGUAGE_MFC2008},                                // REQ #089
   { 0, 0} // EOT                                                   // REQ #089
};                                                                  // REQ #089


/****************************************************************************
*               CGetCharacterPlacement::CGetCharacterPlacement
*               CGetCharacterPlacement::~CGetCharacterPlacement
* Effect: 
*       COnstructor/destructor
****************************************************************************/

CGetCharacterPlacement::CGetCharacterPlacement()                    // REQ #089
        : CFormView(CGetCharacterPlacement::IDD)                    // REQ #089
   {                                                                // REQ #089
    initialized = FALSE;                                            // REQ #089
   }                                                                // REQ #089

CGetCharacterPlacement::~CGetCharacterPlacement()                   // REQ #089
{                                                                   // REQ #089
}                                                                   // REQ #089

/****************************************************************************
*                    CGetCharacterPlacement::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CGetCharacterPlacement::DoDataExchange(CDataExchange* pDX)     // REQ #089
   {                                                                // REQ #089
   CFormView::DoDataExchange(pDX);                                  // REQ #089
   DDX_Control(pDX, IDC_STR, c_Str);                                // REQ #089
   DDX_Control(pDX, IDC_MAXEXTENT_CAPTION, x_MaxExtent);            // REQ #089
   DDX_Control(pDX, IDC_MAXEXTENT, c_MaxExtent);                    // REQ #089
   DDX_Control(pDX, IDC_SPIN_MAXEXTENT, c_SpinMaxExtent);           // REQ #089
   DDX_Control(pDX, IDC_PRINTERNAME, c_PrinterName);                // REQ #089
   DDX_Control(pDX, IDC_FONT_NAME, c_FontName);                     // REQ #089
   DDX_Control(pDX, IDC_GCP_CLASSIN, c_GCP_CLASSIN);                // REQ #089
   DDX_Control(pDX, IDC_GCP_DIACRITIC, c_GCP_DIACRITIC);            // REQ #089
   DDX_Control(pDX, IDC_GCP_DISPLAYZWG, c_GCP_DISPLAYZWG);          // REQ #089
   DDX_Control(pDX, IDC_GCP_GLYPHSHAPE, c_GCP_GLYPHSHAPE);          // REQ #089
   DDX_Control(pDX, IDC_GCP_JUSTIFY, c_GCP_JUSTIFY);                // REQ #089
   DDX_Control(pDX, IDC_GCP_KASHIDA, c_GCP_KASHIDA);                // REQ #089
   DDX_Control(pDX, IDC_GCP_LIGATE, c_GCP_LIGATE);                  // REQ #089
   DDX_Control(pDX, IDC_GCP_MAXEXTENT, c_GCP_MAXEXTENT);            // REQ #089
   DDX_Control(pDX, IDC_GCP_NEUTRALOVERRIDE, c_GCP_NEUTRALOVERRIDE);// REQ #089
   DDX_Control(pDX, IDC_GCP_NUMERICOVERRIDE, c_GCP_NUMERICOVERRIDE);// REQ #089
   DDX_Control(pDX, IDC_GCP_NUMERICSLATIN, c_GCP_NUMERICSLATIN);    // REQ #089
   DDX_Control(pDX, IDC_GCP_NUMERICSLOCAL, c_GCP_NUMERICSLOCAL);    // REQ #089
   DDX_Control(pDX, IDC_GCP_REORDER, c_GCP_REORDER);                // REQ #089
   DDX_Control(pDX, IDC_GCP_SYMSWAPOFF, c_GCP_SYMSWAPOFF);          // REQ #089
   DDX_Control(pDX, IDC_GCP_USEKERNING, c_GCP_USEKERNING);          // REQ #089
   DDX_Control(pDX, IDC_CODE, c_Code);                              // REQ #089
   DDX_Control(pDX, IDC_COPY, c_Copy);                              // REQ #089
   DDX_Control(pDX, IDC_LANGUAGE, c_Language);                      // REQ #089
   DDX_Control(pDX, IDC_USE_PRINTER_DC, c_UsePrinterDC);            // REQ #089
   DDX_Control(pDX, IDC_LGCPRESULTS, c_GCPResults);                 // REQ #089
   DDX_Control(pDX, IDC_STATUS, c_Status);                          // REQ #089
   DDX_Control(pDX, IDC_USE_LPOUTSTRING, c_UselpOutString);         // REQ #089
   DDX_Control(pDX, IDC_USE_LPORDER, c_UselpOrder);                 // REQ #089
   DDX_Control(pDX, IDC_USE_LPDX, c_UselpDx);                       // REQ #089
   DDX_Control(pDX, IDC_USE_LPCARETPOS, c_UselpCaretPos);           // REQ #089
   DDX_Control(pDX, IDC_USE_LPCLASS, c_UselpClass);                 // REQ #089
   DDX_Control(pDX, IDC_USE_LPGLYPHS, c_UselpGlyphs);               // REQ #089
   DDX_Control(pDX, IDC_LPOUTSTRING, c_lpOutString);                // REQ #089
   DDX_Control(pDX, IDC_LPORDER, c_lpOrder);                        // REQ #089
   DDX_Control(pDX, IDC_LPDX, c_lpDx);                              // REQ #089
   DDX_Control(pDX, IDC_LPCARETPOS, c_lpCaretPos);                  // REQ #089
   DDX_Control(pDX, IDC_LPCLASS, c_lpClass);                        // REQ #089
   DDX_Control(pDX, IDC_LPGLYPHS, c_lpGlyphs);                      // REQ #089
   DDX_Control(pDX, IDC_LPSTRUCTSIZE, c_lpStructSize);              // REQ #089
    }                                                               // REQ #089

/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CGetCharacterPlacement, CFormView)                                                // REQ #089
    ON_UPDATE_COMMAND_UI(IDM_GETCHARPLACEMENT, OnUpdateGetcharplacement)                            // REQ #089
    ON_BN_CLICKED(IDC_FONT, &CGetCharacterPlacement::OnBnClickedFont)                               // REQ #089
    ON_CBN_SELENDOK(IDC_LANGUAGE, &CGetCharacterPlacement::OnCbnSelendokLanguage)                   // REQ #089
    ON_BN_CLICKED(IDC_GCP_CLASSIN, &CGetCharacterPlacement::OnBnClickedGcpClassin)                  // REQ #089
    ON_BN_CLICKED(IDC_GCP_DIACRITIC, &CGetCharacterPlacement::OnBnClickedGcpDiacritic)              // REQ #089
    ON_BN_CLICKED(IDC_GCP_DISPLAYZWG, &CGetCharacterPlacement::OnBnClickedGcpDisplayzwg)            // REQ #089
    ON_BN_CLICKED(IDC_GCP_GLYPHSHAPE, &CGetCharacterPlacement::OnBnClickedGcpGlyphshape)            // REQ #089
    ON_BN_CLICKED(IDC_GCP_JUSTIFY, &CGetCharacterPlacement::OnBnClickedGcpJustify)                  // REQ #089
    ON_BN_CLICKED(IDC_GCP_KASHIDA, &CGetCharacterPlacement::OnBnClickedGcpKashida)                  // REQ #089
    ON_BN_CLICKED(IDC_GCP_LIGATE, &CGetCharacterPlacement::OnBnClickedGcpLigate)                    // REQ #089
    ON_BN_CLICKED(IDC_GCP_MAXEXTENT, &CGetCharacterPlacement::OnBnClickedGcpMaxextent)              // REQ #089
    ON_BN_CLICKED(IDC_GCP_NEUTRALOVERRIDE, &CGetCharacterPlacement::OnBnClickedGcpNeutraloverride)  // REQ #089
    ON_BN_CLICKED(IDC_GCP_NUMERICOVERRIDE, &CGetCharacterPlacement::OnBnClickedGcpNumericoverride)  // REQ #089
    ON_BN_CLICKED(IDC_GCP_NUMERICSLATIN, &CGetCharacterPlacement::OnBnClickedGcpNumericslatin)      // REQ #089
    ON_BN_CLICKED(IDC_GCP_NUMERICSLOCAL, &CGetCharacterPlacement::OnBnClickedGcpNumericslocal)      // REQ #089
    ON_BN_CLICKED(IDC_GCP_REORDER, &CGetCharacterPlacement::OnBnClickedGcpReorder)                  // REQ #089
    ON_BN_CLICKED(IDC_GCP_SYMSWAPOFF, &CGetCharacterPlacement::OnBnClickedGcpSymswapoff)            // REQ #089
    ON_BN_CLICKED(IDC_GCP_USEKERNING, &CGetCharacterPlacement::OnBnClickedGcpUsekerning)            // REQ #089
    ON_BN_CLICKED(IDC_COPY, &CGetCharacterPlacement::OnBnClickedCopy)                               // REQ #089
    ON_BN_CLICKED(IDC_PRINTER, &CGetCharacterPlacement::OnBnClickedPrinter)                         // REQ #089
    ON_WM_SIZE()                                                                                    // REQ #089
    ON_BN_CLICKED(IDC_USE_LPOUTSTRING, &CGetCharacterPlacement::OnBnClickedUseLpoutstring)          // REQ #089
    ON_BN_CLICKED(IDC_USE_LPORDER, &CGetCharacterPlacement::OnBnClickedUseLporder)                  // REQ #089
    ON_BN_CLICKED(IDC_USE_LPDX, &CGetCharacterPlacement::OnBnClickedUseLpdx)                        // REQ #089
    ON_BN_CLICKED(IDC_USE_LPCARETPOS, &CGetCharacterPlacement::OnBnClickedUseCaretPos)              // REQ #089
    ON_BN_CLICKED(IDC_USE_LPCLASS, &CGetCharacterPlacement::OnBnClickedUseLpclass)                  // REQ #089
    ON_BN_CLICKED(IDC_USE_LPGLYPHS, &CGetCharacterPlacement::OnBnClickedUseLpglyphs)                // REQ #089
    ON_EN_CHANGE(IDC_MAXEXTENT, &CGetCharacterPlacement::OnChangeMaxExtent)                         // REQ #089
    ON_EN_CHANGE(IDC_STR, &CGetCharacterPlacement::OnChangeStr)                                     // REQ #089
END_MESSAGE_MAP()                                                                                   // REQ #089



// CGetCharacterPlacement diagnostics

#ifdef _DEBUG                                                       // REQ #089
void CGetCharacterPlacement::AssertValid() const                    // REQ #089
{                                                                   // REQ #089
        CFormView::AssertValid();                                   // REQ #089
}                                                                   // REQ #089

void CGetCharacterPlacement::Dump(CDumpContext& dc) const           // REQ #089
{                                                                   // REQ #089
        CFormView::Dump(dc);                                        // REQ #089
}                                                                   // REQ #089
#endif //_DEBUG                                                     // REQ #089


// CGetCharacterPlacement message handlers


/****************************************************************************
*               CGetCharacterPlacement::OnUpdateGetcharplacement
* Inputs:
*       CCmdUI * pCmdUI
* Result: void
*       
* Effect: 
*       Disables the button if this is active
****************************************************************************/

void CGetCharacterPlacement::OnUpdateGetcharplacement(CCmdUI *pCmdUI)// REQ #089
    {                                                               // REQ #089
     pCmdUI->Enable(FALSE);                                         // REQ #089
    }                                                               // REQ #089

/****************************************************************************
*                   CGetCharacterPlacement::OnBnClickedFont
* Result: void
*       
* Effect: 
*       Sets the font
****************************************************************************/

void CGetCharacterPlacement::OnBnClickedFont()                      // REQ #089
    {                                                               // REQ #089
     LOGFONT lf ={0};                                               // REQ #089
     if(Font.GetSafeHandle() != NULL)                               // REQ #089
        Font.GetLogFont(&lf);                                       // REQ #089
                                                                    // REQ #089
     CFontDialog dlg(&lf, CF_SCREENFONTS | CF_PRINTERFONTS | CF_USESTYLE);// REQ #089
     if(dlg.DoModal() != IDOK)                                      // REQ #089
        return;                                                     // REQ #089
                                                                    // REQ #089
     dlg.GetCurrentFont(&lf);                                       // REQ #089
     CFont newfont;                                                 // REQ #089
     if(!newfont.CreateFontIndirect(&lf))                           // REQ #089
        { /* failed */                                              // REQ #089
         // TODO: deal with error                                   // REQ #089
         return;                                                    // REQ #089
        } /* failed */                                              // REQ #089
                                                                    // REQ #089
     Font.DeleteObject();                                           // REQ #089
     Font.Attach(newfont.Detach());                                 // REQ #089
                                                                    // REQ #089
     CString s;                                                     // REQ #089
     s.Format(_T("%s (%d)"), lf.lfFaceName, lf.lfHeight);           // REQ #089
     c_FontName.SetWindowText(s);                                   // REQ #089
                                                                    // REQ #089
     // Note that this is set here ONLY when the font is changed    // REQ #089
     // (so it can be unchecked later by the user to see the        // REQ #089
     // effects of deselecting it)                                  // REQ #089
     CClientDC dc(this);                                            // REQ #089
     dc.SelectObject(&Font);                                        // REQ #089
     DWORD info = ::GetFontLanguageInfo(dc);                        // REQ #089
                                                                    // REQ #089
     if(info & GCP_GLYPHSHAPE)                                      // REQ #089
        c_GCP_GLYPHSHAPE.SetCheck(BST_CHECKED);                     // REQ #089
                                                                    // REQ #089
     updateControls();                                              // REQ #089
     updateStatus();                                                // REQ #089
     updateCode();                                                  // REQ #089
    }                                                               // REQ #089

/****************************************************************************
*                   CGetCharacterPlacement::ControlsToFlags
* Result: DWORD
*       Flags for GetCharacterPlacement
****************************************************************************/

DWORD CGetCharacterPlacement::ControlsToFlags()                     // REQ #089
    {                                                               // REQ #089
     DWORD flags = 0;                                               // REQ #089
#define AddFlag(x) flags |= (!c_##x.IsWindowEnabled() ? 0 : (c_##x.GetCheck() == BST_CHECKED ? x : 0))// REQ #089
     AddFlag(GCP_CLASSIN);                                          // REQ #089
     AddFlag(GCP_DIACRITIC);                                        // REQ #089
     AddFlag(GCP_DISPLAYZWG);                                       // REQ #089
     AddFlag(GCP_GLYPHSHAPE);                                       // REQ #089
     AddFlag(GCP_JUSTIFY);                                          // REQ #089
     AddFlag(GCP_KASHIDA);                                          // REQ #089
     AddFlag(GCP_LIGATE);                                           // REQ #089
     if(c_GCP_MAXEXTENT.GetCheck() == BST_CHECKED)                  // REQ #089
        AddFlag(GCP_MAXEXTENT);                                     // REQ #089
     AddFlag(GCP_NEUTRALOVERRIDE);                                  // REQ #089
     AddFlag(GCP_NUMERICOVERRIDE);                                  // REQ #089
     AddFlag(GCP_NUMERICSLATIN);                                    // REQ #089
     AddFlag(GCP_NUMERICSLOCAL);                                    // REQ #089
     AddFlag(GCP_REORDER);                                          // REQ #089
     AddFlag(GCP_SYMSWAPOFF);                                       // REQ #089
     AddFlag(GCP_USEKERNING);                                       // REQ #089
#undef AddFlag                                                      // REQ #089
     return flags;                                                  // REQ #089
    } // CGetCharacterPlacement::ControlsToFlags                    // REQ #089

/****************************************************************************
*                    CGetCharacterPlacement::ClassToString
* Inputs:
*       char Class: Class value
* Result: CString
*       String representation of class
****************************************************************************/

CString CGetCharacterPlacement::ClassToString(char Class)           // REQ #089
    {                                                               // REQ #089
     CString flags;                                                 // REQ #089
     CString result;                                                // REQ #089
     CString sep;                                                   // REQ #089
#define AddFlag(x) if((Class & (x)) != 0)                                       \
                   {                                                            \
                   flags += sep  + _T(#x);                                      \
                   sep = _T(" | ");                                             \
                   Class &= ~(x);                                               \
                   }
     AddFlag(GCPCLASS_PREBOUNDLTR);                                 // REQ #089
     AddFlag(GCPCLASS_PREBOUNDRTL);                                 // REQ #089
     AddFlag(GCPCLASS_POSTBOUNDLTR);                                // REQ #089
     AddFlag(GCPCLASS_POSTBOUNDRTL);                                // REQ #089
#undef AddFlag                                                      // REQ #089
                                                                    // REQ #089
#define CaseFlag(x) case x: flags += sep + _T(#x); sep = _T(" | "); break;// REQ #089
     switch(Class & 0x0F)                                           // REQ #089
        { /* class designation */                                   // REQ #089
         case 0:                                        // 0        // REQ #089
            break;                                                  // REQ #089
            CaseFlag(GCPCLASS_LATIN);                   // 1        // REQ #089
            CaseFlag(GCPCLASS_HEBREW);                  // 2        // REQ #089
         // CaseFlag(GCPCLASS_ARABIC);                  // 2 // Weird: why use politically-charged names when GCPCLASS_RTL would have been a better name?// REQ #089
            CaseFlag(GCPCLASS_NEUTRAL);                 // 3        // REQ #089
            CaseFlag(GCPCLASS_LOCALNUMBER);             // 4        // REQ #089
            CaseFlag(GCPCLASS_LATINNUMBER);             // 5        // REQ #089
            CaseFlag(GCPCLASS_LATINNUMERICTERMINATOR);  // 6        // REQ #089
            CaseFlag(GCPCLASS_LATINNUMERICSEPARATOR);   // 7        // REQ #089
            CaseFlag(GCPCLASS_NUMERICSEPARATOR);        // 8        // REQ #089
        } /* class designation */                                   // REQ #089
     Class &= ~0x0F; // remove low-order nybble                     // REQ #089
     if(Class != 0)                                                 // REQ #089
        { /* leftovers */                                           // REQ #089
         flags += sep + ToString(_T("0x%02x"), Class);              // REQ #089
        } /* leftovers */                                           // REQ #089
     if(flags.IsEmpty())                                            // REQ #089
        flags = _T("0");                                            // REQ #089
     return flags;                                                  // REQ #089
    } // CGetCharacterPlacement::ClassToString                      // REQ #089


/****************************************************************************
*                CGetCharacterPlacement::GCPResultsToControls
* Inputs:
*       GPC_RESULTS results:
*       DWORD retval;
* Result: void
*           
* Effect: 
*       Update the result display
****************************************************************************/

void CGetCharacterPlacement::GCPResultsToControls(GCP_RESULTS & results, DWORD retval, DWORD err)// REQ #089
    {                                                               // REQ #089
     c_GCPResults.DeleteAllItems();                                 // REQ #089
                                                                    // REQ #089
     HTREEITEM root = c_GCPResults.InsertItem(_T("GCP_RESULTS"));   // REQ #089
     if(retval == 0)                                                // REQ #089
        { /* failed */                                              // REQ #089
         c_GCPResults.InsertItem(ErrorString(err), root);           // REQ #089
         ResultString.Format(_T("GetCharacterPlacement => %s\r\n"), ErrorString(err));// REQ #089
         return;                                                    // REQ #089
        } /* failed */                                              // REQ #089
     ResultString.Format(_T("GetCharacterPlacement => (%d, %d)\r\n"), LOWORD(retval), HIWORD(retval)); // REQ #093
                                                                    // REQ #089
     //----------------                                             // REQ #089
     // result                                                      // REQ #089
     //----------------                                             // REQ #089
     { /* size */                                                   // REQ #089
      CString s;                                                    // REQ #089
      s.Format(_T("(%d, %d)"), LOWORD(retval), HIWORD(retval));     // REQ #089
      c_GCPResults.InsertItem(s, root);                             // REQ #089
      ResultString.Format(_T("GetCharacterPlacement => (%d, %d)\r\n"), LOWORD(retval), HIWORD(retval));// REQ #089
     } /* size */                                                   // REQ #089
                                                                    // REQ #089
     //----------------                                             // REQ #089
     // lpStructSize                                                // REQ #089
     //----------------                                             // REQ #089
     HTREEITEM lStructSize = c_GCPResults.InsertItem(_T("lStructSize"), root);// REQ #089
     c_GCPResults.InsertItem(ToString(_T("%d"), results.lStructSize), lStructSize);// REQ #089
                                                                    // REQ #089
     //----------------                                             // REQ #089
     // lpOutString                                                 // REQ #089
     //----------------                                             // REQ #089
     HTREEITEM lpOutString = c_GCPResults.InsertItem(_T("lpOutString"), root);// REQ #089
     HTREEITEM lpOutStringValue;                                    // REQ #089
     if(results.lpOutString == NULL)                                // REQ #089
        lpOutStringValue = c_GCPResults.InsertItem(_T("NULL"), lpOutString);// REQ #089
     else                                                           // REQ #089
        { /* has string */                                          // REQ #089
         UINT limit = results.nGlyphs;                              // REQ #089
         if(c_GCP_MAXEXTENT.GetCheck() == BST_CHECKED)              // REQ #089
            limit = (UINT)results.nMaxFit;                          // REQ #089
         for(UINT i = 0; i < limit; i++)                            // REQ #089
            { /* show out string */                                 // REQ #089
             CString s;                                             // REQ #089
#ifdef _UNICODE                                                     // REQ #089
             s.Format(_T("[%d] 0x%04x '%c'"),                       // REQ #089
                      i,                                            // REQ #089
                      results.lpOutString[i],                       // REQ #089
                      results.lpOutString[i]);                      // REQ #089
#else                                                               // REQ #089
             s.Format(_T("[%d] 0x%02x '%c'"),                       // REQ #089
                      i,                                            // REQ #089
                      results.lpOutString[i],                       // REQ #089
                      results.lpOutString[i]);                      // REQ #089
#endif                                                              // REQ #089
             c_GCPResults.InsertItem(s, lpOutString);               // REQ #089
            } /* show out string */                                 // REQ #089
        } /* has string */                                          // REQ #089
                                                                    // REQ #089
     //----------------                                             // REQ #089
     // lpOrder                                                     // REQ #089
     //----------------                                             // REQ #089
     HTREEITEM lpOrder = c_GCPResults.InsertItem(_T("lpOrder"), root);// REQ #089
     HTREEITEM lpOrderValue;                                        // REQ #089
     if(results.lpOrder == NULL)                                    // REQ #089
        lpOrderValue = c_GCPResults.InsertItem(_T("NULL"), lpOrder);// REQ #089
     else                                                           // REQ #089
        { /* has order */                                           // REQ #089
         for(UINT i = 0; i < results.nGlyphs; i++)                  // REQ #089
            { /* Show order */                                      // REQ #089
             CString s;                                             // REQ #089
             s.Format(_T("[%d] %d"), i, results.lpOrder[i]);        // REQ #089
             c_GCPResults.InsertItem(s, lpOrder);                   // REQ #089
            } /* Show order */                                      // REQ #089
        } /* has order */                                           // REQ #089
                                                                    // REQ #089
     //----------------                                             // REQ #089
     // lpDX                                                        // REQ #089
     //----------------                                             // REQ #089
     HTREEITEM lpDxValue;                                           // REQ #089
     HTREEITEM lpDx = c_GCPResults.InsertItem(_T("lpDx"), root);    // REQ #089
     if(results.lpDx == NULL)                                       // REQ #089
        lpDxValue = c_GCPResults.InsertItem(_T("NULL"), lpDx);      // REQ #089
     else                                                           // REQ #089
        { /* has Dx */                                              // REQ #089
         for(UINT i = 0; i < results.nGlyphs; i++)                  // REQ #089
            { /* show each */                                       // REQ #089
             CString s;                                             // REQ #089
             s.Format(_T("[%d] %d"), i, results.lpDx[i]);           // REQ #089
             c_GCPResults.InsertItem(s, lpDx);                      // REQ #089
            } /* show each */                                       // REQ #089
        } /* has Dx */                                              // REQ #089
                                                                    // REQ #089
     //----------------                                             // REQ #089
     // lpCaretPos                                                  // REQ #089
     //----------------                                             // REQ #089
     HTREEITEM lpCaretPos = c_GCPResults.InsertItem(_T("lpCaretPos"), root);// REQ #089
     HTREEITEM lpCaretPosValue;                                     // REQ #089
     if(results.lpCaretPos == NULL)                                 // REQ #089
        lpCaretPosValue = c_GCPResults.InsertItem(_T("NULL"), lpCaretPos);// REQ #089
     else                                                           // REQ #089
        { /* has lpCaretPos */                                      // REQ #089
         for(UINT i = 0; i < results.nGlyphs; i++)                  // REQ #089
            { /* show each caret */                                 // REQ #089
             CString s;                                             // REQ #089
             s.Format(_T("[%d] %d"), i, results.lpCaretPos[i]);     // REQ #089
             c_GCPResults.InsertItem(s, lpCaretPos);                // REQ #089
            } /* show each caret */                                 // REQ #089
        } /* has lpCaretPos */                                      // REQ #089
                                                                    // REQ #089
     //----------------                                             // REQ #089
     // lpClass                                                     // REQ #089
     //----------------                                             // REQ #089
     HTREEITEM lpClass = c_GCPResults.InsertItem(_T("lpClass"), root);// REQ #089
     HTREEITEM lpClassValue;                                        // REQ #089
     if(results.lpClass == NULL)                                    // REQ #089
        lpClassValue = c_GCPResults.InsertItem(_T("NULL"), lpClass);// REQ #089
     else                                                           // REQ #089
        { /* has lpClass */                                         // REQ #089
         for(UINT i = 0; i < results.nGlyphs; i++)                  // REQ #089
            { /* show each class */                                 // REQ #089
             CString s;                                             // REQ #089
             s.Format(_T("[%d] %s"), i, ClassToString(results.lpClass[i]));// REQ #089
             c_GCPResults.InsertItem(s, lpClass);                   // REQ #089
            } /* show each class */                                 // REQ #089
        } /* has lpClass */                                         // REQ #089
                                                                    // REQ #089
     //----------------                                             // REQ #089
     // lpGlyphs                                                    // REQ #089
     //----------------                                             // REQ #089
     HTREEITEM lpGlyphs = c_GCPResults.InsertItem(_T("lpGlyphs"), root);// REQ #089
     HTREEITEM lpGlyphsValue;                                       // REQ #089
     if(results.lpGlyphs == NULL)                                   // REQ #089
        lpGlyphsValue = c_GCPResults.InsertItem(_T("NULL"), lpGlyphs);// REQ #089
     else                                                           // REQ #089
        { /* has lpGlyphs */                                        // REQ #089
         for(UINT i = 0; i < results.nGlyphs; i++)                  // REQ #089
            { /* show each glyph */                                 // REQ #089
             CString s;                                             // REQ #089
             s.Format(_T("[%d] 0x%04x"), i, results.lpGlyphs[i]);   // REQ #089
             c_GCPResults.InsertItem(s, lpGlyphs);                  // REQ #089
            } /* show each glyph */                                 // REQ #089
        } /* has lpGlyphs */                                        // REQ #089
                                                                    // REQ #089
     //----------------                                             // REQ #089
     // nGlyphs                                                     // REQ #089
     //----------------                                             // REQ #089
     HTREEITEM nGlyphs = c_GCPResults.InsertItem(_T("nGlyphs"), root);// REQ #089
     c_GCPResults.InsertItem(ToString(_T("%d"), results.nGlyphs), nGlyphs);// REQ #089
                                                                    // REQ #089
     //----------------                                             // REQ #089
     // nMaxFit                                                     // REQ #089
     //----------------                                             // REQ #089
     HTREEITEM nMaxFit = c_GCPResults.InsertItem(_T("nMaxFit"), root);// REQ #089
     c_GCPResults.InsertItem(ToString(_T("%d"), results.nMaxFit), nMaxFit);// REQ #089
                                                                    // REQ #089
     CRect r;                                                       // REQ #092
     c_GCPResults.GetWindowRect(&r);                                // REQ #092
     ScreenToClient(&r);                                            // REQ #092
     r.bottom++;                                                    // REQ #092
     c_GCPResults.MoveWindow(&r);                                   // REQ #092
     r.bottom--;                                                    // REQ #092
     c_GCPResults.MoveWindow(&r);                                   // REQ #092
     updateStatus();                                                // REQ #093
    } // CGetCharacterPlacement::GCPResultsToControls               // REQ #089

/****************************************************************************
*                CGetCharacterPlacement::ControlsToFlagsString
* Inputs:
*       const CString & indent: Indent
* Result: CString
*       Flags
****************************************************************************/

CString CGetCharacterPlacement::ControlsToFlagsString(const CString & indent)// REQ #089
    {                                                               // REQ #089
     CString flags;                                                 // REQ #089
     CString sep;                                                   // REQ #089
#define AddFlag(x) if(c_##x.IsWindowEnabled() && c_##x.GetCheck() == BST_CHECKED)   \
                       {                                                            \
                        flags += sep + indent + _T(#x);                             \
                        sep = _T(" |\r\n");                                         \
                       }
     
     AddFlag(GCP_CLASSIN);                                          // REQ #089
     AddFlag(GCP_DIACRITIC);                                        // REQ #089
     AddFlag(GCP_DISPLAYZWG);                                       // REQ #089
     AddFlag(GCP_GLYPHSHAPE);                                       // REQ #089
     AddFlag(GCP_JUSTIFY);                                          // REQ #089
     AddFlag(GCP_KASHIDA);                                          // REQ #089
     AddFlag(GCP_LIGATE);                                           // REQ #089
     if(c_GCP_MAXEXTENT.GetCheck() == BST_CHECKED)                  // REQ #089
        AddFlag(GCP_MAXEXTENT);                                     // REQ #089
     AddFlag(GCP_NEUTRALOVERRIDE);                                  // REQ #089
     AddFlag(GCP_NUMERICOVERRIDE);                                  // REQ #089
     AddFlag(GCP_NUMERICSLATIN);                                    // REQ #089
     AddFlag(GCP_NUMERICSLOCAL);                                    // REQ #089
     AddFlag(GCP_REORDER);                                          // REQ #089
     AddFlag(GCP_SYMSWAPOFF);                                       // REQ #089
     AddFlag(GCP_USEKERNING);                                       // REQ #089
#undef AddFlag                                                      // REQ #089
     if(flags.IsEmpty())                                            // REQ #089
        flags = indent + _T("0");                                   // REQ #089
     return flags;                                                  // REQ #089
    } // CGetCharacterPlacement::ControlsToFlagsString              // REQ #089


/****************************************************************************
*               CGetCharacterPlacement::DoGetCharacterPlacement
* Result: void
*       
* Effect: 
*       Issues a GetCharacterPlacement call
****************************************************************************/

void CGetCharacterPlacement::DoGetCharacterPlacement()              // REQ #089
    {                                                               // REQ #089
     CString text;                                                  // REQ #089
     c_Str.GetWindowText(text);                                     // REQ #089
                                                                    // REQ #089
     GCP_RESULTS results = { sizeof(GCP_RESULTS) };                 // REQ #089
     CString OutString;                                             // REQ #089
     CArray<UINT> Order;                                            // REQ #089
     CArray<int> Dx;                                                // REQ #089
     CArray<int> CaretPos;                                          // REQ #089
     CArray<char> Class;                                            // REQ #089
     CArray<WCHAR> Glyphs;                                          // REQ #089
                                                                    // REQ #089
     if(c_UselpOutString.GetCheck() == BST_CHECKED)                 // REQ #089
        results.lpOutString = OutString.GetBuffer(text.GetLength() + 1);// REQ #089
                                                                    // REQ #089
     if(c_UselpOrder.GetCheck() == BST_CHECKED)                     // REQ #089
        { /* order array */                                         // REQ #089
         Order.SetSize(text.GetLength());                           // REQ #089
         results.lpOrder = Order.GetData();                         // REQ #089
        } /* order array */                                         // REQ #089
                                                                    // REQ #089
     if(c_UselpDx.GetCheck() == BST_CHECKED)                        // REQ #089
        { /* Dx array */                                            // REQ #089
         Dx.SetSize(text.GetLength());                              // REQ #089
         results.lpDx = Dx.GetData();                               // REQ #089
        } /* Dx array */                                            // REQ #089
                                                                    // REQ #089
     if(c_UselpCaretPos.GetCheck() == BST_CHECKED)                  // REQ #089
        { /* CaretPos array */                                      // REQ #089
         CaretPos.SetSize(text.GetLength());                        // REQ #089
         results.lpCaretPos = CaretPos.GetData();                   // REQ #089
        } /* CaretPos array */                                      // REQ #089
                                                                    // REQ #089
     if(c_UselpClass.GetCheck() == BST_CHECKED)                     // REQ #089
        { /* Class arran */                                         // REQ #089
         Class.SetSize(text.GetLength());                           // REQ #089
         results.lpClass = Class.GetData();                         // REQ #089
        } /* Class arran */                                         // REQ #089
                                                                    // REQ #089
     if(c_UselpGlyphs.GetCheck() == BST_CHECKED)                    // REQ #089
        { /* Glyphs arran */                                        // REQ #089
         Glyphs.SetSize(text.GetLength());                          // REQ #089
         results.lpGlyphs = Glyphs.GetData();                       // REQ #089
        } /* Glyphs arran */                                        // REQ #089
                                                                    // REQ #089
     DWORD flags = ControlsToFlags();                               // REQ #089
     int maxextent = 0;                                             // REQ #089
     if(c_GCP_MAXEXTENT.GetCheck() == BST_CHECKED)                  // REQ #089
        maxextent = c_SpinMaxExtent.GetPos32();                     // REQ #089
                                                                    // REQ #089
     results.nGlyphs = text.GetLength();                            // REQ #089
                                                                    // REQ #089
     CClientDC dc(this);                                            // REQ #089
     dc.SelectObject(&Font);                                        // REQ #089
     DWORD sz = dc.GetCharacterPlacement(text,                      // REQ #089
                                         maxextent,                 // REQ #089
                                         &results,                  // REQ #089
                                         flags);                    // REQ #089
                                                                    // REQ #089
     DWORD err = ::GetLastError(); // will only be used if sz == 0  // REQ #089
     GCPResultsToControls(results, sz, err);                        // REQ #089
    } // CGetCharacterPlacement::DoGetCharacterPlacement            // REQ #089

/****************************************************************************
*                   CGetCharacterPlacement::updateControls
* Result: void
*       
* Effect: 
*       Updates the controls and the font
****************************************************************************/

void CGetCharacterPlacement::updateControls()                       // REQ #089
    {                                                               // REQ #089
     if(!initialized)                                               // REQ #089
        return;                                                     // REQ #089
     CClientDC dc(this);                                            // REQ #089
     dc.SelectObject(&Font);                                        // REQ #089
     DWORD info = ::GetFontLanguageInfo(dc);                        // REQ #089
                                                                    // REQ #089
     c_SpinMaxExtent.EnableWindow(c_GCP_MAXEXTENT.GetCheck() == BST_CHECKED);// REQ #089
     c_MaxExtent.EnableWindow(c_GCP_MAXEXTENT.GetCheck() == BST_CHECKED);// REQ #089
     x_MaxExtent.EnableWindow(c_GCP_MAXEXTENT.GetCheck() == BST_CHECKED);// REQ #089
                                                                    // REQ #089
     c_GCP_CLASSIN.EnableWindow(info & GCP_REORDER ? TRUE : FALSE); // REQ #089
     c_GCP_DIACRITIC.EnableWindow(info & GCP_DIACRITIC ? TRUE : FALSE);// REQ #089
     // c_GCP_GLYPHSHAPE.EnableWindow();                            // REQ #089
     c_GCP_LIGATE.EnableWindow(info & GCP_LIGATE ? TRUE : FALSE);   // REQ #089
     c_GCP_USEKERNING.EnableWindow(info & GCP_USEKERNING ? TRUE : FALSE);// REQ #089
     c_GCP_REORDER.EnableWindow(info & GCP_REORDER ? TRUE : FALSE); // REQ #089
     c_UsePrinterDC.EnableWindow(PrinterDC.m_hDC != NULL);          // REQ #089
                                                                    // REQ #089// REQ #089
     BOOL reorderRequired = c_GCP_REORDER.IsWindowEnabled() && c_GCP_REORDER.GetCheck() == BST_CHECKED;// REQ #089
                                                                    // REQ #089
     c_GCP_NEUTRALOVERRIDE.EnableWindow(reorderRequired);           // REQ #089
     c_GCP_NUMERICOVERRIDE.EnableWindow(reorderRequired);           // REQ #089
                                                                    // REQ #089
     // c_GCP_NUMERICSLATIN is enabled only if GetStringTypeEx indicates more than one numeric format// REQ #089
                                                                    // REQ #089
     if(c_GCP_MAXEXTENT.GetCheck() == BST_CHECKED)                  // REQ #089
        { /* using MaxExtent */                                     // REQ #089
         c_GCP_JUSTIFY.EnableWindow(TRUE);                          // REQ #089
        } /* using MaxExtent */                                     // REQ #089
     else                                                           // REQ #089
        { /* no MaxExtent */                                        // REQ #089
         c_GCP_JUSTIFY.EnableWindow(FALSE);                         // REQ #089
        } /* no MaxExtent */                                        // REQ #089
                                                                    // REQ #089
     c_lpStructSize.SetWindowText(ToString(_T("%d"), sizeof(GCP_RESULTS) ));// REQ #089
                                                                    // REQ #089
     if(c_UselpOutString.GetCheck() == BST_CHECKED)                 // REQ #089
        c_lpOutString.SetWindowText(_T("OutString"));               // REQ #089
     else                                                           // REQ #089
        c_lpOutString.SetWindowText(_T("NULL"));                    // REQ #089
                                                                    // REQ #089
     if(c_UselpOrder.GetCheck() == BST_CHECKED)                     // REQ #089
        c_lpOrder.SetWindowText(_T("Order"));                       // REQ #089
     else                                                           // REQ #089
        c_lpOrder.SetWindowText(_T("NULL"));                        // REQ #089
                                                                    // REQ #089
     if(c_UselpDx.GetCheck() == BST_CHECKED)                        // REQ #089
        c_lpDx.SetWindowText(_T("Dx"));                             // REQ #089
     else                                                           // REQ #089
        c_lpDx.SetWindowText(_T("NULL"));                           // REQ #089
                                                                    // REQ #089
     if(c_UselpCaretPos.GetCheck() == BST_CHECKED)                  // REQ #089
        c_lpCaretPos.SetWindowText(_T("CaretPos"));                 // REQ #089
     else                                                           // REQ #089
        c_lpCaretPos.SetWindowText(_T("NULL"));                     // REQ #089
                                                                    // REQ #089
     if(c_UselpClass.GetCheck() == BST_CHECKED)                     // REQ #089
        c_lpClass.SetWindowText(_T("Class"));                       // REQ #089
     else                                                           // REQ #089
        c_lpClass.SetWindowText(_T("NULL"));                        // REQ #089
                                                                    // REQ #089
     if(c_UselpGlyphs.GetCheck() == BST_CHECKED)                    // REQ #089
        c_lpGlyphs.SetWindowText(_T("Glyphs"));                     // REQ #089
     else                                                           // REQ #089
        c_lpGlyphs.SetWindowText(_T("NULL"));                       // REQ #089
                                                                    // REQ #089
                                                                    // REQ #089
     c_GCP_KASHIDA.EnableWindow((info & GCP_KASHIDA) ? (c_GCP_MAXEXTENT.GetCheck() == BST_CHECKED &&// REQ #089
                                                        c_GCP_JUSTIFY.GetCheck() == BST_CHECKED)// REQ #089
                                                     : FALSE);      // REQ #089
                                                                    // REQ #089
     DoGetCharacterPlacement();                                     // REQ #089
                                                                    // REQ #089
     updateCode();                                                  // REQ #089
                                                                    // REQ #089
    } // CGetCharacterPlacement::updateControls                     // REQ #089

/****************************************************************************
*                   CGetCharacterPlacement::OnInitialUpdate
* Result: void
*       
* Effect: 
*       Initializes dialog
****************************************************************************/

void CGetCharacterPlacement::OnInitialUpdate()                      // REQ #089
    {                                                               // REQ #089
     CFormView::OnInitialUpdate();                                  // REQ #089
     CString s;                                                     // REQ #089
     s.LoadString(IDS_GETCHARACTERPLACEMENT_EXPLORER_CAPTION);      // REQ #089
     GetParentFrame()->SetWindowText(s);                            // REQ #089
     c_Language.AddStrings(Languages, LANGUAGE_MFC2008);            // REQ #089
     CodeFont.CreatePointFont(90, _T("Courier New"));               // REQ #089
     c_Code.SetFont(&CodeFont);                                     // REQ #089
     c_Copy.LoadBitmaps(IDB_COPY);                                  // REQ #089
                                                                    // REQ #089
     c_FontName.SetWindowText(_T(""));                              // REQ #089
                                                                    // REQ #089
     initialized = TRUE;                                            // REQ #089
     updateControls();                                              // REQ #089
     updateStatus();                                                // REQ #089
     updateCode();                                                  // REQ #089
    } // CGetCharacterPlacement::OnInitialUpdate                    // REQ #089

/****************************************************************************
*                     CGetCharacterPlacement::updateCode
* Result: void
*       
* Effect: 
*       Updates the code
****************************************************************************/

void CGetCharacterPlacement::updateCode()                           // REQ #089
    {                                                               // REQ #089
     CString code;                                                  // REQ #089
     Language language = (Language)c_Language.GetItemData(c_Language.GetCurSel());// REQ #089
     //-------------------------------------------------------------// REQ #089
     // top-level declarations                                      // REQ #089
     //-------------------------------------------------------------// REQ #089
     switch(language)                                               // REQ #089
        { /* language */                                            // REQ #089
         case LANGUAGE_C6:                                          // REQ #089
         case LANGUAGE_C2008:                                       // REQ #089
            code += _T("HDC dc;\r\n");                              // REQ #089
            code += _T("LPCTSTR text = ...;\r\n");                  // REQ #089
            if(c_UselpOutString.GetCheck() == BST_CHECKED)          // REQ #089
               code += _T("LPTSTR OutString = NULL;\r\n");          // REQ #089
                                                                    // REQ #089
            if(c_UselpOrder.GetCheck() == BST_CHECKED)              // REQ #089
               code += _T("LPUINT Order = NULL;\r\n");              // REQ #089
                                                                    // REQ #089
            if(c_UselpDx.GetCheck() == BST_CHECKED)                 // REQ #089
               code += _T("LPINT Dx = NULL;\r\n");                  // REQ #089
                                                                    // REQ #089
            if(c_UselpCaretPos.GetCheck() == BST_CHECKED)           // REQ #089
               code += _T("LPINT Dx = NULL;\r\n");                  // REQ #089
                                                                    // REQ #089
            if(c_UselpClass.GetCheck() == BST_CHECKED)              // REQ #089
               code += _T("LPSTR Class = NULL;\r\n");               // REQ #089
                                                                    // REQ #089
            if(c_UselpGlyphs.GetCheck() == BST_CHECKED)             // REQ #089
               code += _T("LPUINT Glyphs = NULL;\r\n");             // REQ #089
                                                                    // REQ #089
            code += _T("DWORD sz;\r\n");                            // REQ #089
            code += _T("SIZE size;\r\n");                           // REQ #089
            break;                                                  // REQ #089
         case LANGUAGE_MFC6:                                        // REQ #089
         case LANGUAGE_MFC2008:                                     // REQ #089
            code += _T("CString text = ...;\r\n");                  // REQ #089
            if(c_UselpOutString.GetCheck() == BST_CHECKED)          // REQ #089
               code += _T("CString OutString;\r\n");                // REQ #089
            if(c_UselpOrder.GetCheck() == BST_CHECKED)              // REQ #089
               code += _T("CArray<UINT> Order;\r\n");               // REQ #089
            if(c_UselpDx.GetCheck() == BST_CHECKED)                 // REQ #089
               code += _T("CArray<int> Dx\r\n");                    // REQ #089
            if(c_UselpCaretPos.GetCheck() == BST_CHECKED)           // REQ #089
               code += _T("CArray<int> Dx;\r\n");                   // REQ #089
            if(c_UselpClass.GetCheck() == BST_CHECKED)              // REQ #089
               code += _T("CArray<char> Class;\r\n");               // REQ #089
            if(c_UselpGlyphs.GetCheck() == BST_CHECKED)             // REQ #089
               code += _T("CArray<UINT> Glyphs;\r\n");              // REQ #089
            break;                                                  // REQ #089
        } /* language */                                            // REQ #089
                                                                    // REQ #089
     if(c_GCP_MAXEXTENT.GetCheck() == BST_CHECKED)                  // REQ #089
        code += _T("int maxextent = ...;\r\n");                     // REQ #089
                                                                    // REQ #089
     code += _T("GCP_RESULTS results = { sizeof(GCP_RESULTS) };\r\n");// REQ #089
                                                                    // REQ #089
     code += _T("\r\n");                                            // REQ #089
                                                                    // REQ #089
     //-------------------------------------------------------------// REQ #089
     // Initialize GCP_RESULTS                                      // REQ #089
     //-------------------------------------------------------------// REQ #089
     switch(language)                                               // REQ #089
        { /* language */                                            // REQ #089
         case LANGUAGE_C6:                                          // REQ #089
         case LANGUAGE_C2008:                                       // REQ #089
            if(c_UselpOutString.GetCheck() == BST_CHECKED)          // REQ #089
               code += _T("results.lpOutString = OutString;\r\n");  // REQ #089
                                                                    // REQ #089
            if(c_UselpOrder.GetCheck() == BST_CHECKED)              // REQ #089
               { /* order array */                                  // REQ #089
                code += _T("results.lpOrder = (LPUINT)malloc(lstrlen(text) * sizeof(UINT));\r\n");// REQ #089
               } /* order array */                                  // REQ #089
                                                                    // REQ #089
            if(c_UselpDx.GetCheck() == BST_CHECKED)                 // REQ #089
               { /* Dx array */                                     // REQ #089
                code += _T("results.lpDx = (LPINT)malloc(lstrlen(text) * sizeof(int));\r\n");// REQ #089
               } /* Dx array */                                     // REQ #089
                                                                    // REQ #089
            if(c_UselpCaretPos.GetCheck() == BST_CHECKED)           // REQ #089
               { /* CaretPos array */                               // REQ #089
                code += _T("results.lpCaretPos = (LPINT)malloc(lstrlen(text) * sizeof(int));\r\n");// REQ #089
               } /* CaretPos array */                               // REQ #089
                                                                    // REQ #089
            if(c_UselpClass.GetCheck() == BST_CHECKED)              // REQ #089
               { /* Class arran */                                  // REQ #089
                code += _T("results.lpCaretPos = (char*)malloc(lstrlen(text));\r\n");// REQ #089
               } /* Class arran */                                  // REQ #089
                                                                    // REQ #089
            if(c_UselpGlyphs.GetCheck() == BST_CHECKED)             // REQ #089
               { /* Glyphs arran */                                 // REQ #089
                code += _T("results.lpCaretPos = (LPWSTR)malloc(lstrlen(text) * sizeof(WCHAR));\r\n");// REQ #089
               } /* Glyphs arran */                                 // REQ #089
            break;                                                  // REQ #089
         case LANGUAGE_MFC6:                                        // REQ #089
         case LANGUAGE_MFC2008:                                     // REQ #089
            if(c_UselpOutString.GetCheck() == BST_CHECKED)          // REQ #089
               code += _T("results.lpOutString = OutString.GetBuffer(text.GetLength() + 1);\r\n");// REQ #089
            if(c_UselpOrder.GetCheck() == BST_CHECKED)              // REQ #089
               { /* order array */                                  // REQ #089
                code += _T("\r\n");                                 // REQ #089
                code += _T("Order.SetSize(text.GetLength());\r\n"); // REQ #089
                code += _T("results.lpOrder = Order.GetData();\r\n");// REQ #089
               } /* order array */                                  // REQ #089
                                                                    // REQ #089
            if(c_UselpDx.GetCheck() == BST_CHECKED)                 // REQ #089
               { /* Dx array */                                     // REQ #089
                code += _T("\r\n");                                 // REQ #089
                code += _T("Dx.SetSize(text.GetLength());\r\n");    // REQ #089
                code += _T("results.lpDx = Dx.GetData();\r\n");     // REQ #089
               } /* Dx array */                                     // REQ #089
                                                                    // REQ #089
            if(c_UselpCaretPos.GetCheck() == BST_CHECKED)           // REQ #089
               { /* CaretPos array */                               // REQ #089
                code += _T("\r\n");                                 // REQ #089
                code += _T("CaretPos.SetSize(text.GetLength());\r\n");// REQ #089
                code += _T("results.lpCaretPos = CaretPos.GetData();\r\n");// REQ #089
               } /* CaretPos array */                               // REQ #089
                                                                    // REQ #089
            if(c_UselpClass.GetCheck() == BST_CHECKED)              // REQ #089
               { /* Class arran */                                  // REQ #089
                code += _T("\r\n");                                 // REQ #089
                code += _T("Class.SetSize(text.GetLength());\r\n"); // REQ #089
                code += _T("results.lpClass = Class.GetData();\r\n");// REQ #089
               } /* Class arran */                                  // REQ #089
                                                                    // REQ #089
            if(c_UselpGlyphs.GetCheck() == BST_CHECKED)             // REQ #089
               { /* Glyphs arran */                                 // REQ #089
                code += _T("\r\n");                                 // REQ #089
                code += _T("Glyphs.SetSize(text.GetLength());\r\n");// REQ #089
                code += _T("results.lpGlyphs = Glyphs.GetData();\r\n");// REQ #089
               } /* Glyphs arran */                                 // REQ #089
            break;                                                  // REQ #089
        } /* language */                                            // REQ #089
                                                                    // REQ #089
     //-------------------------------------------------------------// REQ #089
     // ::GetCharacterPlacement(dc, text                            // REQ #089
     // dc.GetCharacterPlacement(text,                              // REQ #089
     //-------------------------------------------------------------// REQ #089
     CString indent;                                                // REQ #089
     switch(language)                                               // REQ #089
        { /* language */                                            // REQ #089
         case LANGUAGE_C6:                                          // REQ #089
         case LANGUAGE_C2008:                                       // REQ #089
            indent = CString(_T(' '), 29);                          // REQ #089
            break;                                                  // REQ #089
         case LANGUAGE_MFC6:                                        // REQ #089
         case LANGUAGE_MFC2008:                                     // REQ #089
            indent = CString(_T(' '), 36);                          // REQ #089
            break;                                                  // REQ #089
        } /* language */                                            // REQ #089
                                                                    // REQ #089
     switch(language)                                               // REQ #089
        { /* language */                                            // REQ #089
         case LANGUAGE_C6:                                          // REQ #089
         case LANGUAGE_C2008:                                       // REQ #089
            code += _T("sz = ::GetCharacterPlacement(dc,              //  hdc\r\n");// REQ #089
            code += indent +_T("text,            // lpString\r\n"); // REQ #089
            code += indent + _T("lstrlen(text),   // nCount\r\n");  // REQ #089
            break;                                                  // REQ #089
         case LANGUAGE_MFC6:                                        // REQ #089
         case LANGUAGE_MFC2008:                                     // REQ #089
            code += _T("DWORD sz = dc.GetCharacterPlacement(text,          // str\r\n");// REQ #089
            break;                                                  // REQ #089
        } /* language */                                            // REQ #089
                                                                    // REQ #089
     //----------------                                             // REQ #089
     // nMaxExtent                                                  // REQ #089
     //----------------                                             // REQ #089
     switch(language)                                               // REQ #089
        { /* language */                                            // REQ #089
         case LANGUAGE_C6:                                          // REQ #089
         case LANGUAGE_C2008:                                       // REQ #089
            if(c_GCP_MAXEXTENT.GetCheck() == BST_CHECKED)           // REQ #089
               { /* C has max extent */                             // REQ #089
                code += indent + _T("maxextent, // nMaxExtent\r\n");// REQ #089
               } /* C has max extent */                             // REQ #089
            else                                                    // REQ #089
               code += indent + _T("0,               // nMaxExtent\r\n");// REQ #089
            break;                                                  // REQ #089
         case LANGUAGE_MFC6:                                        // REQ #089
         case LANGUAGE_MFC2008:                                     // REQ #089
            if(c_GCP_MAXEXTENT.GetCheck() == BST_CHECKED)           // REQ #089
               { /* MFC has max extent */                           // REQ #089
                code += indent + _T("maxextent, // nMaxExtent\r\n");// REQ #089
               } /* MFC has max extent */                           // REQ #089
            else                                                    // REQ #089
               code += indent + _T("0,             // nMaxExtent\r\n");// REQ #089
            break;                                                  // REQ #089
        } /* language */                                            // REQ #089
                                                                    // REQ #089
     //----------------                                             // REQ #089
     // lpResults                                                   // REQ #089
     //----------------                                             // REQ #089
     switch(language)                                               // REQ #089
        { /* language */                                            // REQ #089
         case LANGUAGE_C6:                                          // REQ #089
         case LANGUAGE_C2008:                                       // REQ #089
            code += indent + _T("&results,      // lpResults\r\n"); // REQ #089
            break;                                                  // REQ #089
         case LANGUAGE_MFC6:                                        // REQ #089
         case LANGUAGE_MFC2008:                                     // REQ #089
            code += indent + _T("&results,     // lpResults\r\n");  // REQ #089
            break;                                                  // REQ #089
        } /* language */                                            // REQ #089
                                                                    // REQ #089
     //----------------                                             // REQ #089
     // dwFlags                                                     // REQ #089
     //----------------                                             // REQ #089
                                                                    // REQ #089
                                                                    // REQ #089
     CString flags = ControlsToFlagsString(indent);                 // REQ #089
     code += flags;                                                 // REQ #089
                                                                    // REQ #089
     code += _T(");\r\n");                                          // REQ #089
                                                                    // REQ #089
     code += _T("if(sz == 0)\r\n");                                 // REQ #089
     code += _T("   {\r\n");                                        // REQ #089
                                                                    // REQ #089
     CString action;                                                // REQ #089
     action.LoadString(IDS_APPROPRIATE_ACTION);                     // REQ #089
     code += ToString(_T("    return; // %s\r\n"), action);         // REQ #089
                                                                    // REQ #089
     code += _T("   }\r\n");                                        // REQ #089
                                                                    // REQ #089
     switch(language)                                               // REQ #089
        { /* language */                                            // REQ #089
         case LANGUAGE_C6:                                          // REQ #089
         case LANGUAGE_C2008:                                       // REQ #089
            code += _T("size.cx = LOWORD(sz);\r\n");                // REQ #089
            code += _T("size.cy = HIWORD(sz);\r\n");                // REQ #089
            break;                                                  // REQ #089
         case LANGUAGE_MFC6:                                        // REQ #089
         case LANGUAGE_MFC2008:                                     // REQ #089
            if(c_UselpOutString.GetCheck() == BST_CHECKED)          // REQ #089
               code += _T("text.ReleaseBuffer();\r\n");             // REQ #089
            code += _T("CSize size(LOWORD(sz), HIWORD(sz));\r\n");  // REQ #089
            break;                                                  // REQ #089
        } /* language */                                            // REQ #089
                                                                    // REQ #089
     CString UseValues;                                             // REQ #089
     UseValues.LoadString(IDS_USE_VALUES);                          // REQ #089
     UseValues = UseValues;                                         // REQ #089
                                                                    // REQ #089
     code += UseValues;                                             // REQ #089
                                                                    // REQ #089
     //-------------------------------------------------------------// REQ #089
     // Cleanup                                                     // REQ #089
     //-------------------------------------------------------------// REQ #089
                                                                    // REQ #089
     switch(language)                                               // REQ #089
        { /* language */                                            // REQ #089
         case LANGUAGE_C6:                                          // REQ #089
         case LANGUAGE_C2008:                                       // REQ #089
            if(c_UselpOrder.GetCheck() == BST_CHECKED)              // REQ #089
               { /* order array */                                  // REQ #089
                code += _T("free(results.lpOrder);\r\n");           // REQ #089
               } /* order array */                                  // REQ #089
                                                                    // REQ #089
            if(c_UselpDx.GetCheck() == BST_CHECKED)                 // REQ #089
               { /* Dx array */                                     // REQ #089
                code += _T("free(results.lpDx);\r\n");              // REQ #089
               } /* Dx array */                                     // REQ #089
                                                                    // REQ #089
            if(c_UselpCaretPos.GetCheck() == BST_CHECKED)           // REQ #089
               { /* CaretPos array */                               // REQ #089
                code += _T("free(results.lpCaretPos);\r\n");        // REQ #089
               } /* CaretPos array */                               // REQ #089
                                                                    // REQ #089
            if(c_UselpClass.GetCheck() == BST_CHECKED)              // REQ #089
               { /* Class arran */                                  // REQ #089
                code += _T("free(results.lpCaretPos);\r\n");        // REQ #089
               } /* Class arran */                                  // REQ #089
                                                                    // REQ #089
            if(c_UselpGlyphs.GetCheck() == BST_CHECKED)             // REQ #089
               { /* Glyphs arran */                                 // REQ #089
                code += _T("free(results.lpCaretPos);\r\n");        // REQ #089
               } /* Glyphs arran */                                 // REQ #089
            break;                                                  // REQ #089
         case LANGUAGE_MFC6:                                        // REQ #089
         case LANGUAGE_MFC2008:                                     // REQ #089
            break;                                                  // REQ #089
        } /* language */                                            // REQ #089
                                                                    // REQ #089
     c_Code.SetWindowText(code);                                    // REQ #089
                                                                    // REQ #089
    } // CGetCharacterPlacement::updateCode                         // REQ #089

/****************************************************************************
*                  CGetCharacterPlacement::FontInfoToString
* Inputs:
*       DWORD info: Font info
* Result: CString
*       String rendering
****************************************************************************/

CString CGetCharacterPlacement::FontInfoToString(DWORD info)        // REQ #089
    {                                                               // REQ #089
     CString flags;                                                 // REQ #089
     CString sep;                                                   // REQ #089
#define AddFlag(x) if((info & (x)) != 0)                                        \
                   {                                                            \
                   flags += sep  + _T(#x);                                      \
                   sep = _T(" | ");                                             \
                   info &= ~(x);                                                \
                   }
     AddFlag(GCP_DBCS);                                             // REQ #089
     AddFlag(GCP_DIACRITIC);                                        // REQ #089
     AddFlag(GCP_GLYPHSHAPE);                                       // REQ #089
     AddFlag(GCP_KASHIDA);                                          // REQ #089
     AddFlag(GCP_LIGATE);                                           // REQ #089
     AddFlag(GCP_USEKERNING);                                       // REQ #089
     AddFlag(GCP_REORDER);                                          // REQ #089
     AddFlag(FLI_GLYPHS);                                           // REQ #089
#undef AddFlag                                                      // REQ #089
     if(info != 0)                                                  // REQ #089
        { /* has leftover */                                        // REQ #089
         flags += ToString(_T("%s0x%x"), sep, info);                // REQ #089
        } /* has leftover */                                        // REQ #089
     return flags;                                                  // REQ #089
    } // CGetCharacterPlacement::FontInfoToString                   // REQ #089

/****************************************************************************
*                    CGetCharacterPlacement::updateStatus
* Result: void
*       
* Effect: 
*       Updates the status displays
****************************************************************************/

void CGetCharacterPlacement::updateStatus()                         // REQ #089
    {                                                               // REQ #089
     CString status;                                                // REQ #089
                                                                    // REQ #089
     c_PrinterName.SetWindowText(PrinterName);                      // REQ #089
                                                                    // REQ #089
     // Font: %s (%d) %s                                            // REQ #089
     CString fmt;                                                   // REQ #089
     fmt.LoadString(IDS_FONT_STATUS);                               // REQ #089
                                                                    // REQ #089
     if(Font.GetSafeHandle() != NULL)                               // REQ #089
        { /* has font */                                            // REQ #089
         CClientDC dc(this);                                        // REQ #089
         dc.SelectObject(&Font);                                    // REQ #089
         DWORD info = ::GetFontLanguageInfo(dc);                    // REQ #089
                                                                    // REQ #089
         CString flags = FontInfoToString(info);                    // REQ #089
         LOGFONT lf;                                                // REQ #089
         Font.GetLogFont(&lf);                                      // REQ #089
         CString s;                                                 // REQ #089
         s.Format(fmt, lf.lfFaceName, lf.lfHeight, flags);          // REQ #089
         status += s;                                               // REQ #089
        } /* has font */                                            // REQ #089
                                                                    // REQ #089
     if(!ResultString.IsEmpty())                                    // REQ #089
        { /* add result */                                          // REQ #093
         if(!status.IsEmpty())                                      // REQ #093
            status += _T("\r\n");                                   // REQ #093
         status += ResultString;                                    // REQ #089
        } /* add result */                                          // REQ #093
                                                                    // REQ #089
     c_Status.SetWindowText(status);                                // REQ #089
    } // CGetCharacterPlacement::updateStatus                       // REQ #089

/****************************************************************************
*                CGetCharacterPlacement::OnCbnSelendokLanguage
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CGetCharacterPlacement::OnCbnSelendokLanguage()                // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpClassin()                // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpDiacritic()              // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpDisplayzwg()             // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpGlyphshape()             // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpJustify()                // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpKashida()                // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpLigate()                 // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpMaxextent()              // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpNeutraloverride()        // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpNumericoverride()        // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpNumericslatin()          // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpNumericslocal()          // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpReorder()                // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpSymswapoff()             // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedGcpUsekerning()             // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedUseLpoutstring()            // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedUseLporder()                // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedUseLpdx()                   // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedUseCaretPos()               // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedUseLpclass()                // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

void CGetCharacterPlacement::OnBnClickedUseLpglyphs()               // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

/****************************************************************************
*                   CGetCharacterPlacement::OnBnClickedCopy
* Result: void
*       
* Effect: 
*       Copies the code to the clipboard
****************************************************************************/

void CGetCharacterPlacement::OnBnClickedCopy()                      // REQ #089
    {                                                               // REQ #089
     c_Code.SetRedraw(FALSE);                                       // REQ #089
     int low;                                                       // REQ #089
     int high;                                                      // REQ #089
     c_Code.GetSel(low, high);                                      // REQ #089
     c_Code.SetSel(0, -1);                                          // REQ #089
     c_Code.SendMessage(WM_COPY);                                   // REQ #089
     c_Code.SetSel(low, high);                                      // REQ #089
     c_Code.SetRedraw(TRUE);                                        // REQ #089
    }                                                               // REQ #089

/****************************************************************************
*                  CGetCharacterPlacement::OnBnClickedPrinter
* Result: void
*       
* Effect: 
*       Establishes a printer DC
****************************************************************************/

void CGetCharacterPlacement::OnBnClickedPrinter()                   // REQ #089
    {                                                               // REQ #089
     CPrintDialog dlg(TRUE, PD_RETURNDC);                           // REQ #089
     if(dlg.DoModal() != IDOK)                                      // REQ #089
        return;                                                     // REQ #089
     if(dlg.m_pd.hDC != NULL)                                       // REQ #089
        { /* has DC */                                              // REQ #089
         if(PrinterDC.m_hDC != NULL)                                // REQ #089
            PrinterDC.DeleteDC();                                   // REQ #089
         PrinterDC.Attach(dlg.m_pd.hDC);                            // REQ #089
         PrinterName = dlg.GetDeviceName();                         // REQ #089
        } /* has DC */                                              // REQ #089
     else                                                           // REQ #089
        { /* no DC */                                               // REQ #089
         PrinterDC.DeleteDC();                                      // REQ #089
        } /* no DC */                                               // REQ #089
                                                                    // REQ #089
     updateStatus();                                                // REQ #089
     updateControls();                                              // REQ #089
    }                                                               // REQ #089

/****************************************************************************
*                        CGetCharacterPlacement::OnSize
* Inputs:
*       UINT nType:
*       int cx:
*       int cy:
* Result: void
*       
* Effect: 
*       Resizes the window
****************************************************************************/

void CGetCharacterPlacement::OnSize(UINT nType, int cx, int cy)     // REQ #089
    {                                                               // REQ #089
     CFormView::OnSize(nType, cx, cy);                              // REQ #089
                                                                    // REQ #089
     if(c_GCPResults.GetSafeHwnd() != NULL)                         // REQ #089
        { /* resize GCP results */                                  // REQ #089
         CRect r;                                                   // REQ #089
         c_GCPResults.GetWindowRect(&r);                            // REQ #089
         ScreenToClient(&r);                                        // REQ #089
         c_GCPResults.SetWindowPos(NULL,                            // REQ #089
                                   0, 0,                            // REQ #089
                                   cx - r.left, r.Height(),         // REQ #089
                                   SWP_NOMOVE | SWP_NOZORDER);      // REQ #089
        } /* resize GCP results */                                  // REQ #089
                                                                    // REQ #089
     if(c_Code.GetSafeHwnd() != NULL)                               // REQ #089
        { /* resize code */                                         // REQ #089
         CRect r;                                                   // REQ #089
         c_Code.GetWindowRect(&r);                                  // REQ #089
         ScreenToClient(&r);                                        // REQ #089
         c_Code.SetWindowPos(NULL,                                  // REQ #089
                             0, 0,                                  // REQ #089
                             cx, cy - r.top,                        // REQ #089
                             SWP_NOMOVE | SWP_NOZORDER);            // REQ #089
        } /* resize code */                                         // REQ #089
    }


/****************************************************************************
*                  CGetCharacterPlacement::OnChangeMaxExtent
* Result: void
*       
* Effect: 
*       Updates the controls
****************************************************************************/

void CGetCharacterPlacement::OnChangeMaxExtent()                    // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    } // CGetCharacterPlacement::OnChangeMaxExtent                  // REQ #089

/****************************************************************************
*                     CGetCharacterPlacement::OnChangeStr
* Result: void
*       
* Effect: 
*       Updates controls
****************************************************************************/

void CGetCharacterPlacement::OnChangeStr()                          // REQ #089
    {                                                               // REQ #089
     updateControls();                                              // REQ #089
    } // CGetCharacterPlacement::OnChangeStr                        // REQ #089


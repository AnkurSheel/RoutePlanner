/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 24-Apr-08 | Created
* 24-Apr-08 | REQ #001: Allow negative track kerning offsets
* 24-Apr-08 | REQ #005: Made KerningExplorer an MDI page
* 24-Apr-08 | REQ #008: Removed FontExplorer.h
* 24-Apr-08 | REQ #010: Made opts protected member of FontDisp
* 24-Apr-08 | REQ #011: Added CFontDisplay::SetWindowText
* 27-Apr-08 | REQ #017: Added pair-kerning detection option
* 28-Apr-08 | REQ #022: Support vertical offset
* 28-Apr-08 | REQ #023: Fixed problem with losing dialog font
* 29-Apr-08 | REQ #026: Retain settings
* 29-Apr-08 | REQ #027: Use bitmap button for copy
* 29-Apr-08 | REQ #029: Added button to copy only images
* 29-Apr-08 | REQ #031: Added support to ignore ABC widths
*  4-May-08 | REQ #037: Code cleanup
* 19-Oct-08 | REQ #061: Set captions
* 20-Oct-08 | REQ #062: ResizeParentToFit
* 29-Oct-08 | REQ #066: Show pixels on fonts
*  2-Nov-08 | REQ #081: Changed name from TEXTOUTEX to EXTTEXTOUT_
*****************************************************************************/
// KerningExplorer.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"                                               // REQ #008
#include "KerningExplorer.h"
#include "fontdesc.h"
#include "color.h"
#include "toclip.h"

// CKerningExplorer

IMPLEMENT_DYNCREATE(CKerningExplorer, CFormView)

static const IDData Quality[] = {                                   // REQ #066
   { IDS_DEFAULT_QUALITY, DEFAULT_QUALITY},                         // REQ #066
   { IDS_ANTIALIASED_QUALITY, ANTIALIASED_QUALITY},                 // REQ #066
   { IDS_CLEARTYPE_QUALITY, CLEARTYPE_QUALITY},                     // REQ #066
   { IDS_CLEARTYPE_NATURAL_QUALITY, CLEARTYPE_QUALITY},             // REQ #066
   { IDS_DRAFT_QUALITY,   DRAFT_QUALITY},                           // REQ #066
   { IDS_NONANTIALIASED_QUALITY, NONANTIALIASED_QUALITY},           // REQ #066
   { IDS_PROOF_QUALITY,   PROOF_QUALITY},                           // REQ #066
   { 0, 0 } // EOT                                                  // REQ #066
};                                                                  // REQ #066

CKerningExplorer::CKerningExplorer()                                // REQ #005
        : CFormView(CKerningExplorer::IDD)                          // REQ #005
   {                                                                // REQ #005
    c_Kerned.color = ::GetSysColor(COLOR_WINDOWTEXT);               // REQ #005
    c_Unkerned.color = ::GetSysColor(COLOR_WINDOWTEXT);             // REQ #005
                                                                    // REQ #005
    kernedonly = FALSE;                                             // REQ #005
   }                                                                // REQ #005

CKerningExplorer::~CKerningExplorer()                               // REQ #005
{                                                                   // REQ #005
}                                                                   // REQ #005

/****************************************************************************
*                         CKerningExplorer::FontTrace
* Result: void
*       
* Effect: 
*       Debug tracing of font
****************************************************************************/

#ifdef _DEBUGFONT                                                   // REQ #019
void CKerningExplorer::FontTrace(LPCTSTR site)                      // REQ #019
    {                                                               // REQ #019
     CFont * f = GetFont();                                         // REQ #019
     if(f == NULL)                                                  // REQ #019
        { /* failed */                                              // REQ #019
         TRACE(_T("%s: Font is NULL\n"), site);                     // REQ #019
         return;                                                    // REQ #019
        } /* failed */                                              // REQ #019
                                                                    // REQ #019
     TRACE(_T("%s: GetLogFont->%p\n"), site, f->m_hObject);         // REQ #019
                                                                    // REQ #019
     LOGFONT lf;                                                    // REQ #019
     if(!f->GetLogFont(&lf))                                        // REQ #019
        TRACE(_T("%s: GetLogFont failed\n"), site);                 // REQ #019
     else                                                           // REQ #019
        TRACE(_T("%s: font is %p \"%s\" %d\n"), site, f->m_hObject, lf.lfFaceName, lf.lfHeight);// REQ #019
                                                                    // REQ #019
    } // CKerningExplorer::FontTrace                                // REQ #019
#endif

/****************************************************************************
*                      CKerningExplorer::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CKerningExplorer::DoDataExchange(CDataExchange* pDX)
   {
    CFormView::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COPYIMAGE, c_CopyImage);                   // REQ #029
    DDX_Control(pDX, IDC_COPY, c_Copy);                             // REQ #027
    DDX_Control(pDX, IDC_ADD, c_Add);                               // REQ #026
    DDX_Control(pDX, IDC_DELETE, c_Delete);                         // REQ #026
    DDX_Control(pDX, IDC_SPIN_VOFFSET, c_SpinVerticalOffset);       // REQ #022
    DDX_Control(pDX, IDC_SPIN_HOFFSET, c_SpinHorizontalOffset);     // REQ #066
    DDX_Control(pDX, IDC_VOFFSET, c_VerticalOffset);                // REQ #022
    DDX_Control(pDX, IDC_HOFFSET, c_HorizontalOffset);              // REQ #066
    DDX_Control(pDX, IDC_QUALITY, c_Quality);                       // REQ #066
    DDX_Control(pDX, IDC_ADVANCED, c_Advanced);                     // REQ #018
    DDX_Control(pDX, IDC_DETECT_PAIR_KERNING, c_DetectPairKerning); // REQ #017
    DDX_Control(pDX, IDC_KERNED_ONLY, c_KernedOnly);
    DDX_Control(pDX, IDC_SPINTRACK, c_SpinTrack);
    DDX_Control(pDX, IDC_TRACKVAL, c_TrackVal);
    DDX_Control(pDX, IDC_SAMPLE, c_Sample);
    DDX_Control(pDX, IDC_KERNED, c_Kerned);
    DDX_Control(pDX, IDC_UNKERNED, c_Unkerned);
    DDX_Control(pDX, IDC_PAIR, c_Pair);
    DDX_Control(pDX, IDC_HRULE, c_HorizontalRule);
    DDX_Control(pDX, IDC_VRULE, c_VerticalRule);
    DDX_Control(pDX, IDC_CHRULE, c_CharacterRule);
    DDX_Control(pDX, IDC_WHITE, c_White);
    DDX_Control(pDX, IDC_TRACK, c_UseTrack);
    DDX_Control(pDX, IDC_DEBUG, c_Debug);
    DDX_Control(pDX, IDC_COLORS, c_UseColors);
    DDX_Control(pDX, IDC_NONE, c_None);                             // REQ #011
    DDX_Control(pDX, IDC_TEXTOUT, c_TextOut);                       // REQ #011
    DDX_Control(pDX, IDC_EXTTEXTOUT, c_ExtTextOut);                 // REQ #011
    DDX_Control(pDX, IDC_IGNOREABC, c_IgnoreABC);                   // REQ #031
    DDX_Control(pDX, IDC_SHOW_PIXELS, c_ShowPixels);                // REQ #066
    DDX_Control(pDX, IDC_SHOW_OVERLAY, c_ShowOverlay);              // REQ #066
    DDX_Control(pDX, IDC_PRESETS, c_Presets);                       // REQ #076
   }

/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CKerningExplorer, CFormView)                      // REQ #005
    ON_EN_CHANGE(IDC_SAMPLE, OnChangeSample)
    ON_WM_SIZE()
    ON_WM_GETMINMAXINFO()
    ON_BN_CLICKED(IDC_FONT, OnFont)
    ON_WM_VSCROLL()
    ON_BN_CLICKED(IDC_COPY, OnCopy)
    ON_MESSAGE(WM_CHOOSEFONT_GETLOGFONT, OnGetLogFont)
    ON_MESSAGE(UWM_GETCOLOR, OnGetColor)
    ON_BN_CLICKED(IDC_COLORS, OnBnClickedColors)
    ON_BN_CLICKED(IDC_WHITE, OnBnClickedWhite)
    ON_BN_CLICKED(IDC_KERNED_ONLY, OnBnClickedKernedOnly)
    ON_BN_CLICKED(IDC_HRULE, OnBnClickedHrule)
    ON_BN_CLICKED(IDC_VRULE, OnBnClickedVrule)
    ON_BN_CLICKED(IDC_CHRULE, OnBnClickedChrule)
    ON_BN_CLICKED(IDC_TRACK, OnBnClickedTrack)
    ON_BN_CLICKED(IDC_NONE, OnBnClickedNone)                        // REQ #011
    ON_BN_CLICKED(IDC_TEXTOUT, OnBnClickedTextout)                  // REQ #011
    ON_BN_CLICKED(IDC_EXTTEXTOUT, OnBnClickedExttextout)            // REQ #011
    ON_BN_CLICKED(IDC_IGNOREABC, OnBnClickedIgnoreABC)              // REQ #031
    ON_BN_CLICKED(IDC_ADVANCED, OnBnClickedAdvanced)                // REQ #018
    ON_BN_CLICKED(IDC_SHOW_PIXELS, OnBnClickedShowPixels)           // REQ #066
    ON_BN_CLICKED(IDC_SHOW_OVERLAY, OnBnClickedShowOverlay)         // REQ #066
    ON_EN_CHANGE(IDC_HOFFSET, OnEnChangeHoffset)
    ON_BN_CLICKED(IDC_PAIR, OnBnClickedPair)
    ON_BN_CLICKED(IDC_ADD, OnBnClickedAdd)
    ON_BN_CLICKED(IDC_DELETE, OnBnClickedDelete)
    ON_BN_CLICKED(IDC_COPYIMAGE, OnBnClickedCopyimage)
    ON_BN_CLICKED(IDC_DEBUG, OnBnClickedDebug)
    ON_EN_CHANGE(IDC_VOFFSET, &CKerningExplorer::OnEnChangeVoffset) // REQ #066
    ON_CBN_SELENDOK(IDC_PRESETS, OnSelendOkPresets)                 // REQ #076
    ON_CBN_SELENDOK(IDC_QUALITY, OnSelendOkQuality)                 // REQ #066
END_MESSAGE_MAP()                                                   // REQ #005

#ifdef _DEBUG                                                       // REQ #005
void CKerningExplorer::AssertValid() const                          // REQ #005
{                                                                   // REQ #005
        CFormView::AssertValid();                                   // REQ #005
}                                                                   // REQ #005

void CKerningExplorer::Dump(CDumpContext& dc) const                 // REQ #005
{                                                                   // REQ #005
        CFormView::Dump(dc);                                        // REQ #005
}                                                                   // REQ #005
#endif //_DEBUG                                                     // REQ #005


// CKerningExplorer message handlers


/****************************************************************************
*                       CKerningExplorer::OnChangeSample
* Result: void
*       
* Effect: 
*       Handles a change in the sample text
****************************************************************************/

void CKerningExplorer::OnChangeSample()                             // REQ #005
   {
    CString s;
    c_Sample.GetWindowText(s);

    c_Unkerned.SetWindowText(s);
    c_Kerned.SetWindowText(s);

//    c_Unkerned.InvalidateRect(NULL);                              // REQ #011
//    c_Kerned.InvalidateRect(NULL);                                // REQ #011
   }

/****************************************************************************
*                              CKerningExplorer::Resize
* Result: void
*       
* Effect: 
*       Recomputes the sizes of the windows based on the dialog size and
*       the display options.
****************************************************************************/

void CKerningExplorer::Resize()                                     // REQ #005
    {
     CRect unkerned;
     CRect kerned;

     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     // Handle the startup transient, where we get the initial WM_SIZE
     // long before the DDX has initialized the c_Kerned/c_Unkerned
     // variables...

     if(c_Kerned.m_hWnd == NULL)
        return;
     if(c_Unkerned.m_hWnd == NULL)
        return;

     c_Kerned.GetWindowRect(&kerned);
     c_Unkerned.GetWindowRect(&unkerned);

     ScreenToClient(&unkerned);
     ScreenToClient(&kerned);

     // The top of the unkerned rectangle remains constant; the two
     // rectangles split the remainging client space

     CRect client;
     GetClientRect(&client);

     CRect newKerned;
     CRect newUnkerned;

     /*
           client.left
           |
           V
           +----------------------------------------------------+ <--client.top
           |                                                    |
           |unkerned.top                                        |
           +----------------------------------------------------+
           |                                                    |
           |                                                    |
           |                                                    |
           |                                                    |
           +----------------------------------------------------+
           |kerned.top                           unkerned.bottom|
           |                                                    |
           |                                                    |
           |                                                    |
           +----------------------------------------------------+ <--client.bottm
                                                                ^
                                                                |
                                                     client.right
     */
     newUnkerned.top = unkerned.top;
     newUnkerned.left = client.left;
     newUnkerned.right = client.right;
     newUnkerned.bottom = unkerned.top + (client.bottom - unkerned.top) / 2;

     if(kernedonly)
        { /* kerned only */
         newKerned.top = unkerned.top;
         newKerned.left = client.left;
         newKerned.right = client.right;
         newKerned.bottom = client.bottom;
        } /* kerned only */
     else
        { /* both displays */
         newKerned.top = newUnkerned.bottom + 1;
         newKerned.left = client.left;
         newKerned.right = client.right;
         newKerned.bottom = client.bottom;
        } /* both displays */

     c_Unkerned.MoveWindow(&newUnkerned);
     c_Kerned.MoveWindow(&newKerned);
     
    }

/****************************************************************************
*                              CKerningExplorer::OnSize
* Inputs:
*       UINT nType:
*       int cx:
*       int cy:
* Result: void
*       
* Effect: 
*       Resizes the window
****************************************************************************/

void CKerningExplorer::OnSize(UINT nType, int cx, int cy)           // REQ #005
{
        CFormView::OnSize(nType, cx, cy);

        Resize();
}


/****************************************************************************
*                      CKerningExplorer::OnGetMinMaxInfo
* Inputs:
*       ¶
* Result: void
*       
* Effect: 
*       Handles resize logic (not required for MDI)
****************************************************************************/

void CKerningExplorer::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)       // REQ #005
   {                                                                // REQ #005
    // TODO: Add your message handler code here and/or call default // REQ #005
                                                                    // REQ #005
    CFormView::OnGetMinMaxInfo(lpMMI);                              // REQ #005
   }                                                                // REQ #005


/****************************************************************************
*                        CKerningExplorer::UpdateFont
* Inputs:
*       CFont * oldFont: previous font
*       LOGFONT & lf: New font to create
* Result: void
*       
* Effect: 
*       Creates the font and binds it to the controls
****************************************************************************/

void CKerningExplorer::UpdateFont(CFont * oldFont, LOGFONT & lf)    // REQ #066
    {                                                               // REQ #066
     CFont newFont;
     if(newFont.CreateFontIndirect(&lf))
        { /* successful creation */
         c_Kerned.SetFont(&newFont);
         c_Unkerned.SetFont(&newFont);
//            c_Kerned.InvalidateRect(NULL);                        // REQ #011
//            c_Unkerned.InvalidateRect(NULL);                      // REQ #011
         newFont.Detach();
         oldFont->DeleteObject();
         TRACE(_T(__FUNCTION__) _T(": DeleteObject(font=%p)\n"), oldFont->m_hObject);// REQ #021
//         c_Kerned.color = fd.GetColor();
//         c_Unkerned.color = fd.GetColor();
         Resize();                                                  // REQ #005
        } /* successful creation */
    } // CKerningExplorer::UpdateFont                               // REQ #066

/****************************************************************************
*                           CKerningExplorer::OnFont
* Result: void
*       
* Effect: 
*       Invokes the font dialog
****************************************************************************/

void CKerningExplorer::OnFont()                                     // REQ #005
   {
    CFont * oldFont;
    oldFont = c_Kerned.GetFont();

    LOGFONT lf;

    oldFont->GetLogFont(&lf);

    CFontDialog fd(&lf);
    if(fd.DoModal())
       { /* successful choice */
        if(c_Quality.GetCurSel() >= 0)                              // REQ #066
           lf.lfQuality = (BYTE)c_Quality.GetItemData(c_Quality.GetCurSel());// REQ #066
        UpdateFont(oldFont, lf);                                    // REQ #066
       } /* successful choice */
   }

/****************************************************************************
*                           CKerningExplorer::OnGetLogFont
* Inputs:
*       WPARAM: ignored
*       LPARAM: (LPARAM)LOGFONT
* Result: LRESULT
*       0, always (logically void)
* Effect: 
*       Copies the contents of the logfont to the logfont of the lParam
****************************************************************************/

LRESULT CKerningExplorer::OnGetLogFont(WPARAM, LPARAM lParam)       // REQ #005
    {
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     LPLOGFONT lf = (LPLOGFONT)lParam;
     CFont * font = c_Unkerned.GetFont();
     if(font == NULL)
        { /* no font */
         ::ZeroMemory(lf, sizeof(LOGFONT));                         // REQ #037
        } /* no font */
     else
        { /* has font */
         font->GetObject(sizeof(LOGFONT), lf);
        } /* has font */
     return 0;
    }

/****************************************************************************
*                            CKerningExplorer::OnGetColor
* Inputs:
*       WPARAM: ignored
*       LPARAM: ignored
* Result: LRESULT
*       (LRESULT)(COLORREF)
****************************************************************************/

LRESULT CKerningExplorer::OnGetColor(WPARAM, LPARAM)                // REQ #005
    {
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     return (LRESULT)c_Kerned.color;
    }

/****************************************************************************
*                       CKerningExplorer::GetOutputMode
* Result: display_options::OutputOptions
*       Appropriate output mode
****************************************************************************/

display_options::OutputOptions CKerningExplorer::GetOutputMode()    // REQ #011
   {                                                                // REQ #011
    FontTrace(_T(__FUNCTION__));                                    // REQ #019
    if(c_None.GetCheck() == BST_CHECKED)                            // REQ #011
       return display_options::NONE;                                // REQ #011
    if(c_TextOut.GetCheck() == BST_CHECKED)                         // REQ #011
       return display_options::TEXTOUT;                             // REQ #011
    if(c_ExtTextOut.GetCheck() == BST_CHECKED)                      // REQ #011
       return display_options::EXTTEXTOUT_;                         // REQ #011// REQ #081
    if(c_IgnoreABC.GetCheck() == BST_CHECKED)                       // REQ #031
       return display_options::IGNOREABC;                           // REQ #031
    ASSERT(FALSE);                                                  // REQ #011
    return display_options::NONE;                                   // REQ #011
   } // CKerningExplorer::GetOutputMode                             // REQ #011

/****************************************************************************
*                       CKerningExplorer::SetOutputMode
* Result: void
*       
* Effect: 
*       Sets the output mode in the kerned window
****************************************************************************/

void CKerningExplorer::SetOutputMode()                              // REQ #011
    {                                                               // REQ #011
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     c_Kerned.SetOutputMode(GetOutputMode());                       // REQ #011
    } // CKerningExplorer::SetOutputMode                            // REQ #011

/****************************************************************************
*                          CKerningExplorer::updateControls
* Result: void
*       
* Effect: 
*       Enables or disables appropriate controls
****************************************************************************/

void CKerningExplorer::updateControls()                             // REQ #005
    {                                                               // REQ #010
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     c_UseTrack.SetCheck(c_Kerned.GetTrackMode() ? BST_CHECKED : BST_UNCHECKED);// REQ #010
     c_Unkerned.ShowWindow(kernedonly ? SW_HIDE : SW_SHOW);         // REQ #010
     c_SpinTrack.EnableWindow(c_Kerned.GetTrackMode());             // REQ #010
     c_TrackVal.EnableWindow(c_Kerned.GetTrackMode());              // REQ #010
     c_UseColors.SetCheck(c_Kerned.GetUseColors());                 // REQ #010
     c_VerticalRule.SetCheck(c_Kerned.GetVerticalRule());           // REQ #010
     c_HorizontalRule.SetCheck(c_Kerned.GetHorizontalRule());       // REQ #010
     c_CharacterRule.SetCheck(c_Kerned.GetCharacterRule());         // REQ #010
     c_White.SetCheck(c_Kerned.GetWhite());                         // REQ #010
     c_Pair.SetCheck(c_Kerned.GetUsePairKerning());                 // REQ #010
     c_ExtTextOut.EnableWindow(c_Advanced.GetCheck() == BST_CHECKED);// REQ #018
                                                                    // REQ #011
     UINT id = IDC_NONE;                                            // REQ #011
     switch(c_Kerned.GetOutputMode())                               // REQ #011
        { /* output mode */                                         // REQ #011
         case display_options::NONE:                                // REQ #011
               id = IDC_NONE;                                       // REQ #011
               break;                                               // REQ #011
         case display_options::TEXTOUT:                             // REQ #011
               id = IDC_TEXTOUT;                                    // REQ #011
               break;                                               // REQ #011
         case display_options::EXTTEXTOUT_:                          // REQ #011// REQ #081
               id = IDC_EXTTEXTOUT;                                 // REQ #011
               break;                                               // REQ #011
         case display_options::IGNOREABC:                           // REQ #031
               id = IDC_IGNOREABC;                                  // REQ #031
               break;                                               // REQ #031
         default:                                                   // REQ #011
               ASSERT(FALSE);                                       // REQ #011
               break;                                               // REQ #011
        } /* output mode */                                         // REQ #011
     CheckRadioButton(IDC_NONE, IDC_IGNOREABC, id);                 // REQ #011// REQ #031

     CString s;                                                     // REQ #076
     c_Sample.GetWindowText(s);                                     // REQ #076
     BOOL enable = !s.IsEmpty();                                    // REQ #076
     enable &= FindEntry(s) < 0;                                    // REQ #076
     c_Presets.EnableWindow(c_Presets.GetCount() > 0);              // REQ #076
     c_Delete.EnableWindow(c_Presets.GetCurSel() >= 0);             // REQ #076
     c_Add.EnableWindow(enable);                                    // REQ #076
    }

/****************************************************************************
*                      CKerningExplorer::OnInitialUpdate
* Result: void
*       
* Effect: 
*       Handles the initialization of the controls
****************************************************************************/

void CKerningExplorer::OnInitialUpdate()                            // REQ #005
   {
    CFormView::OnInitialUpdate();                                   // REQ #005
        
    FontTrace(_T(__FUNCTION__));                                    // REQ #019

    c_Kerned.SetUsePairKerning(TRUE);                               // REQ #010
    c_Kerned.SetTrackMode(TRUE);  // assume track kerning active    // REQ #010
    c_Kerned.SetTrackValue(0);                                      // REQ #010

    c_SpinTrack.SetRange(-20, 20);                                  // REQ #001
    c_SpinTrack.SetPos(0);

    CString s;

    s.LoadString(IDS_KERNING_EXPLORER_CAPTION);                     // REQ #061
    GetParentFrame()->SetWindowText(s);                             // REQ #061

    c_Kerned.GetWindowText(s);
    c_Sample.SetWindowText(s);

    // In the past, a stock font was used by Windows                // REQ #023
    // There was a DeleteObject which didn't do anything to the font// REQ #023
    // because DeleteObject won't delete a stock font               // REQ #023
    // But starting after VS4.2, a non-stock dialog font was used   // REQ #023
    // So the DeleteObject killed the whole dialog's font           // REQ #023
    // To avoid this, the default font is set initially as a copy   // REQ #023
    // of the default font, so the copy is deleted                  // REQ #023
    // Oh, for smart handles...                                     // REQ #023
    LOGFONT lf;                                                     // REQ #023
    CFont * f = GetFont();                                          // REQ #023
    f->GetLogFont(&lf);                                             // REQ #023
                                                                    // REQ #023
    CFont * nf = new CFont;                                         // REQ #023
    nf->CreateFontIndirect(&lf);                                    // REQ #023
    c_Kerned.SetFont(nf);                                           // REQ #023
    c_Unkerned.SetFont(nf);                                         // REQ #023

static const int OFFSET_RANGE = 300;
    c_SpinVerticalOffset.SetRange(-OFFSET_RANGE, OFFSET_RANGE);     // REQ #022// REQ #066
    c_SpinVerticalOffset.SetPos(0);                                 // REQ #022// REQ #066
    c_SpinHorizontalOffset.SetRange(-OFFSET_RANGE, OFFSET_RANGE);   // REQ #066
    c_SpinHorizontalOffset.SetPos(0);                               // REQ #066

    HBITMAP bmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),      // REQ #027
                              MAKEINTRESOURCE(IDB_COPY),            // REQ #027
                              IMAGE_BITMAP,                         // REQ #027
                              0, 0, LR_SHARED | LR_LOADMAP3DCOLORS);// REQ #027
    c_Copy.SetBitmap(bmp);                                          // REQ #027
    c_CopyImage.SetBitmap(bmp);                                     // REQ #029
                              
    bmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),              // REQ #026
                      MAKEINTRESOURCE(IDB_ADD), IMAGE_BITMAP, 0, 0, // REQ #026
                      LR_SHARED | LR_LOADMAP3DCOLORS);              // REQ #026
    c_Add.SetBitmap(bmp);                                           // REQ #026
                                                                    // REQ #026
    bmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),              // REQ #026
                      MAKEINTRESOURCE(IDB_DELETE),                  // REQ #026
                      IMAGE_BITMAP, 0, 0,                           // REQ #026
                      LR_SHARED | LR_LOADMAP3DCOLORS);              // REQ #026
    c_Delete.SetBitmap(bmp);                                        // REQ #026

    display_options opts = c_Kerned.GetOpts();                               // REQ #066
    c_ShowPixels.SetCheck(opts.ShowPixels ? BST_CHECKED : BST_UNCHECKED);    // REQ #066
    c_ShowOverlay.SetCheck(opts.ShowOverlay ? BST_CHECKED : BST_UNCHECKED);  // REQ #066

    GetParentFrame()->RecalcLayout();                               // REQ #062
    ResizeParentToFit(FALSE);                                       // REQ #062
    c_Quality.AddStrings(Quality, DEFAULT_QUALITY);                 // REQ #066
    updateControls();
   }

/****************************************************************************
*                         CKerningExplorer::OnVScroll
* Inputs:
*       UINT nSBCode:
*       UINT nPos:
*       CScrollBar * pScrollBar:
* Result: void
*       
* Effect: 
*       Handles scrolling events
****************************************************************************/

void CKerningExplorer::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) // REQ #005
   {
    if(pScrollBar != NULL)                                          // REQ #005
        { /* spin control */                                        // REQ #005
         FontTrace(_T(__FUNCTION__));                               // REQ #019
         if(pScrollBar->m_hWnd == c_SpinTrack.m_hWnd)
            { /* track kerning */
             c_Kerned.SetTrackValue(((CSpinButtonCtrl *)pScrollBar)->GetPos32());  // REQ #001// REQ #010
             return;
            } /* track kerning */
        } /* spin control */                                        // REQ #005
    else                                                            // REQ #005
       CFormView::OnVScroll(nSBCode, nPos, pScrollBar);
   }

/****************************************************************************
*                           CKerningExplorer::OnCopy
* Result: void
*       
* Effect: 
*       Copies the image to the clipboard
****************************************************************************/

void CKerningExplorer::OnCopy()                                     // REQ #005
   {
    toClipboard(this, TRUE);
   }

/****************************************************************************
*                     CKerningExplorer::OnBnClickedColors
* Result: void
*       
* Effect: 
*       Handles a change of the "use colors" option
****************************************************************************/

void CKerningExplorer::OnBnClickedColors()                          // REQ #005
    {                                                               // REQ #005
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     BOOL mode = c_UseColors.GetCheck() == BST_CHECKED;             // REQ #005
     c_Kerned.SetUseColors(mode);                                   // REQ #005
     c_Unkerned.SetUseColors(mode);                                 // REQ #005
     updateControls();                                              // REQ #005
    }                                                               // REQ #005

/****************************************************************************
*                      CKerningExplorer::OnBnClickedWhite
* Result: void
*       
* Effect: 
*       ¶
****************************************************************************/

void CKerningExplorer::OnBnClickedWhite()                           // REQ #005
    {                                                               // REQ #005
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     c_Kerned.SetWhite(c_White.GetCheck() == BST_CHECKED);          // REQ #005
     c_Unkerned.SetWhite(c_White.GetCheck() == BST_CHECKED);        // REQ #005
    }                                                               // REQ #005

/****************************************************************************
*                   CKerningExplorer::OnBnClickedKernedOnly
* Result: void
*       
* Effect: 
*       Enables the display of the unkerned display
****************************************************************************/

void CKerningExplorer::OnBnClickedKernedOnly()                      // REQ #005
    {                                                               // REQ #005
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     kernedonly = c_KernedOnly.GetCheck() == BST_CHECKED;           // REQ #005
     Resize();                                                      // REQ #005
     updateControls();                                              // REQ #005
    }                                                               // REQ #005

/****************************************************************************
*                      CKerningExplorer::OnBnClickedHrule
* Result: void
*       
* Effect: 
*       Sets the horizontal rule
****************************************************************************/

void CKerningExplorer::OnBnClickedHrule()                           // REQ #005
    {                                                               // REQ #005
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     c_Kerned.SetHorizontalRule(c_HorizontalRule.GetCheck() == BST_CHECKED); // REQ #005 // REQ #010
    }                                                               // REQ #005


/****************************************************************************
*                      CKerningExplorer::OnBnClickedVrule
* Result: void
*       
* Effect: 
*       Enables/disables vertical rule
****************************************************************************/

void CKerningExplorer::OnBnClickedVrule()                           // REQ #005
    {                                                               // REQ #005
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     c_Kerned.SetVerticalRule(c_VerticalRule.GetCheck() == BST_CHECKED); // REQ #010// REQ #005
    }                                                               // REQ #005

/****************************************************************************
*                     CKerningExplorer::OnBnClickedChrule
* Result: void
*       
* Effect: 
*       Enables/disables character rule
****************************************************************************/

void CKerningExplorer::OnBnClickedChrule()                          // REQ #010
    {                                                               // REQ #010
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     c_Kerned.SetCharacterRule(c_CharacterRule.GetCheck() == BST_CHECKED);// REQ #010
    }                                                               // REQ #010

/****************************************************************************
*                      CKerningExplorer::OnBnClickedTrack
* Result: void
*       
* Effect: 
*       Sets the tracking mode
****************************************************************************/

void CKerningExplorer::OnBnClickedTrack()                           // REQ #010
    {                                                               // REQ #010
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     c_Kerned.SetTrackMode(c_UseTrack.GetCheck() == BST_CHECKED);   // REQ #010 
     updateControls();                                              // REQ #010
    }                                                               // REQ #010


/****************************************************************************
*                      CKerningExplorer::OnBnClickedNone
* Result: void
*       
* Effect: 
*       Handles the none button
****************************************************************************/

void CKerningExplorer::OnBnClickedNone()                            // REQ #011
    {                                                               // REQ #011
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     if(c_None.GetCheck() == BST_CHECKED)                           // REQ #011
        c_Kerned.SetOutputMode(display_options::NONE);              // REQ #011
     updateControls();                                              // REQ #011
    }                                                               // REQ #011

/****************************************************************************
*                     CKerningExplorer::OnBnClickedTextout
* Result: void
*       
* Effect: 
*       Handles the TextOut
****************************************************************************/

void CKerningExplorer::OnBnClickedTextout()                         // REQ #011
    {                                                               // REQ #011
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     if(c_TextOut.GetCheck() == BST_CHECKED)                        // REQ #011
        c_Kerned.SetOutputMode(display_options::TEXTOUT);           // REQ #011
     updateControls();                                              // REQ #011
    }                                                               // REQ #011

/****************************************************************************
*                   CKerningExplorer::OnBnClickedExttextout
* Result: void
*       
* Effect: 
*       Handles the ExtTextOut button click
****************************************************************************/

void CKerningExplorer::OnBnClickedExttextout()                      // REQ #011
    {                                                               // REQ #011
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     if(c_ExtTextOut.GetCheck() == BST_CHECKED)                     // REQ #011
        c_Kerned.SetOutputMode(display_options::EXTTEXTOUT_);       // REQ #011// REQ #081
     updateControls();                                              // REQ #011
    }                                                               // REQ #011

/****************************************************************************
*                   CKerningExplorer::OnBnClickedIgnoreABC
* Result: void
*       
* Effect: 
*       Handles the IgnoreABC button click
****************************************************************************/

void CKerningExplorer::OnBnClickedIgnoreABC()                       // REQ #031
    {                                                               // REQ #031
     FontTrace(_T(__FUNCTION__));                                   // REQ #031
     if(c_IgnoreABC.GetCheck() == BST_CHECKED)                      // REQ #031
        c_Kerned.SetOutputMode(display_options::IGNOREABC);         // REQ #031
     updateControls();                                              // REQ #031
    }                                                               // REQ #031

/****************************************************************************
*                     CKerningExplorer::OnBnClickedDebug
* Result: void
*       
* Effect: 
*       Sets the debug state
****************************************************************************/

void CKerningExplorer::OnBnClickedDebug()
    {
     c_Kerned.SetDebug(c_Debug.GetCheck() == BST_CHECKED);
     c_Unkerned.SetDebug(c_Debug.GetCheck() == BST_CHECKED);
    } // CKerningExplorer::OnBnClickedDebug

/****************************************************************************
*                    CKerningExplorer::OnBnClickedAdvanced
* Result: void
*       
* Effect: 
*       Sets GM_ADVANCED/GM_COMPATIBLE mode
****************************************************************************/

void CKerningExplorer::OnBnClickedAdvanced()                        // REQ #018
    {                                                               // REQ #018
     c_Kerned.SetGMAdvanced(c_Advanced.GetCheck() == BST_CHECKED);  // REQ #018
     c_Unkerned.SetGMAdvanced(c_Advanced.GetCheck() == BST_CHECKED);// REQ #018
     updateControls();                                              // REQ #018
    } // CKerningExplorer::OnBnClickedAdvanced                      // REQ #018

/****************************************************************************
*                     CKerningExplorer::OnEnChangeVoffset
* Result: void
*       
* Effect: 
*       Updates the vertical offset
****************************************************************************/

void CKerningExplorer::OnEnChangeHoffset()                          // REQ #022// REQ #066
    {                                                               // REQ #022
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     if(c_HorizontalOffset.GetSafeHwnd() == NULL)                   // REQ #022// REQ #066
        return;                                                     // REQ #022
     if(c_SpinHorizontalOffset.GetSafeHwnd() == NULL)               // REQ #022// REQ #066
        return;                                                     // REQ #022
                                                                    // REQ #022
     display_options opts = c_Kerned.GetOpts();                     // REQ #066
     opts.OverlayX = (c_SpinHorizontalOffset.GetPos32());           // REQ #066
     c_Kerned.SetOpts(opts);                                        // REQ #066
                                                                    // REQ #066
     opts = c_Unkerned.GetOpts();                                   // REQ #066
     opts.OverlayX = (c_SpinHorizontalOffset.GetPos32());           // REQ #066
     c_Unkerned.SetOpts(opts);                                      // REQ #066
    }                                                               // REQ #022


/****************************************************************************
*                      CKerningExplorer::OnBnClickedPair
* Result: void
*       
* Effect: 
*       Handles the pair-kerning option
****************************************************************************/

void CKerningExplorer::OnBnClickedPair()                            // REQ #010
    {                                                               // REQ #010
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     c_Kerned.SetUsePairKerning(c_Pair.GetCheck() == BST_CHECKED);  // REQ #010
     updateControls();                                              // REQ #010
    }                                                               // REQ #010

/****************************************************************************
*                         CKerningExplorer::FindEntry
* Inputs:
*       const CString & s: String to find
* Result: int
*       >= 0 is index of string in Presets combo
*       CB_ERR if not found
****************************************************************************/

int CKerningExplorer::FindEntry(const CString & s)                  // REQ #076
    {                                                               // REQ #076
     for(int i = 0; i < c_Presets.GetCount(); i++)                  // REQ #076
        { /* search */                                              // REQ #076
         // Note that FindStringExact cannot be used because it is  // REQ #076
         // case-insensitive                                        // REQ #076
         CString t;                                                 // REQ #076
         c_Presets.GetLBText(i, t);                                 // REQ #076
         if(t == s)                                                 // REQ #076
            { /* already present */                                 // REQ #076
             return i;                                              // REQ #076
            } /* already present */                                 // REQ #076
        } /* search */                                              // REQ #076
     return CB_ERR;                                                 // REQ #076
    } // CKerningExplorer::FindEntry                                // REQ #076


/****************************************************************************
*                       CKerningExplorer::OnBnClickedAdd
* Result: void
*       
* Effect: 
*       Adds the current string to the presets
****************************************************************************/

void CKerningExplorer::OnBnClickedAdd()                             // REQ #076
    {                                                               // REQ #076
     CString s;                                                     // REQ #076
     c_Sample.GetWindowText(s);                                     // REQ #076
     int n = FindEntry(s);                                          // REQ #076
     if(n >= 0)                                                     // REQ #076
        { /* already present */                                     // REQ #076
         c_Presets.SetCurSel(n);                                    // REQ #076
         return;                                                    // REQ #076
        }                                                           // REQ #076
     // If we get here, it wasn't found                             // REQ #076
     n = c_Presets.AddString(s);                                    // REQ #076
     c_Presets.SetCurSel(n);                                        // REQ #076
     updateControls();                                              // REQ #076
    }                                                               // REQ #076

/****************************************************************************
*                     CKerningExplorer::OnBnClickedDelete
* Result: void
*       
* Effect: 
*       Deletes a saved configuration
****************************************************************************/

void CKerningExplorer::OnBnClickedDelete()                          // REQ #076
    {                                                               // REQ #076
     int n = c_Presets.GetCurSel();                                 // REQ #076
     if(n < 0)                                                      // REQ #076
        return;                                                     // REQ #076
     c_Presets.DeleteString(n);                                     // REQ #076
     updateControls();                                              // REQ #076
    }                                                               // REQ #076

/****************************************************************************
*                    CKerningExplorer::OnBnClickedCopyimage
* Result: void
*       
* Effect: 
*       OnBnClickedCopyImage
* Notes:
*       The assumption is that the arrangement is that the kerned is the top window
*       The unkerned window may not be visible and the kerned window may occupy the space
*
*                   c_Unkerned.GetImageSize().cx
*                   |
*       +-----------------------------+
*       |############                 |  Unkerned
*       |############                 |
*       |############                 |
*       +-----------------------------+ --- c_Unkerned.GetImageSize().cy
*       +-----------------------------+
*       |#####################        |  Kerned
*       |#####################        |
*       |#####################        |
*       +-----------------------------+ --- c_Kerned.GetImageSize().cy
*                            |
*                            c_Kerned.GetImageSize().cx
*
****************************************************************************/

void CKerningExplorer::OnBnClickedCopyimage()                       // REQ #029
    {                                                               // REQ #029
     CRect bb;                                                      // REQ #029
                                                                    // REQ #029
     CRect r;                                                       // REQ #029
     CRect rk;                                                      // REQ #029
     c_Kerned.GetWindowRect(&rk);                                   // REQ #029
     ScreenToClient(&rk);                                           // REQ #029
     CSize szk = c_Kerned.GetImageSize();                           // REQ #029
                                                                    // REQ #029
     if(kernedonly)                                                 // REQ #029
        { /* kerned only */                                         // REQ #029
         bb = rk;                                                   // REQ #029
         bb.right = bb.left + szk.cx;                               // REQ #029
        } /* kerned only */                                         // REQ #029
     else                                                           // REQ #029
        { /* do both */                                             // REQ #029
         CRect ru;                                                  // REQ #029
         c_Unkerned.GetWindowRect(&ru);                             // REQ #029
         ScreenToClient(&ru);                                       // REQ #029
                                                                    // REQ #029
         CSize szu = c_Unkerned.GetImageSize();                     // REQ #029
                                                                    // REQ #029
         bb.left = ru.left;                                         // REQ #029
         bb.top  = ru.top;                                          // REQ #029
         bb.right = ru.left + max(szu.cx, szk.cx);                  // REQ #029
         bb.bottom = rk.bottom;                                     // REQ #029
        } /* do both */                                             // REQ #029
                                                                    // REQ #029
     toClipboard(this, bb);                                         // REQ #029
    }                                                               // REQ #029


/****************************************************************************
*                     CKerningExplorer::OnEnChangeVoffset
* Result: void
*       
* Effect: 
*       Changes the vertical offset
****************************************************************************/

void CKerningExplorer::OnEnChangeVoffset()
    {
     FontTrace(_T(__FUNCTION__));                                   // REQ #019
     if(c_VerticalOffset.GetSafeHwnd() == NULL)                     // REQ #022
        return;                                                     // REQ #022
     if(c_SpinVerticalOffset.GetSafeHwnd() == NULL)                 // REQ #022
        return;                                                     // REQ #022
                                                                    // REQ #022
     display_options opts = c_Kerned.GetOpts();                     // REQ #066
     opts.OverlayY = (c_SpinVerticalOffset.GetPos32());             // REQ #066
     c_Kerned.SetOpts(opts);                                        // REQ #066
     opts = c_Unkerned.GetOpts();                                   // REQ #066
     opts.OverlayY = (c_SpinVerticalOffset.GetPos32());             // REQ #066
     c_Unkerned.SetOpts(opts);                                      // REQ #066
    }

/****************************************************************************
*                     CKerningExplorer::OnSelendOkQuality
* Result: void
*       
* Effect: 
*       Quality changed
****************************************************************************/

void CKerningExplorer::OnSelendOkQuality()                          // REQ #066
    {                                                               // REQ #066
     CFont * oldFont;                                               // REQ #066
     oldFont = c_Kerned.GetFont();                                  // REQ #066
                                                                    // REQ #066
     LOGFONT lf;                                                    // REQ #066
     oldFont->GetLogFont(&lf);                                      // REQ #066
                                                                    // REQ #066
     if(c_Quality.GetCurSel() >= 0)                                 // REQ #066
        lf.lfQuality = (BYTE)c_Quality.GetItemData(c_Quality.GetCurSel());// REQ #066
     UpdateFont(oldFont, lf);                                       // REQ #066
    } // CKerningExplorer::OnSelendOkQuality                        // REQ #066

/****************************************************************************
*                  CKerningExplorer::OnBnClickedShowOverlay
* Result: void
*       
* Effect: 
*       ¶
****************************************************************************/

void CKerningExplorer::OnBnClickedShowOverlay()                     // REQ #066
    {                                                               // REQ #066
     display_options opts = c_Kerned.GetOpts();                     // REQ #066
     opts.ShowOverlay = (c_ShowOverlay.GetCheck() == BST_CHECKED);  // REQ #066
     c_Kerned.SetOpts(opts);                                        // REQ #066
                                                                    // REQ #066
     opts = c_Unkerned.GetOpts();                                   // REQ #066
     opts.ShowOverlay = (c_ShowOverlay.GetCheck() == BST_CHECKED);  // REQ #066
     c_Unkerned.SetOpts(opts);                                      // REQ #066
    } // CKerningExplorer::OnBnClickedShowOverlay                   // REQ #066

/****************************************************************************
*                   CKerningExplorer::OnBnClickedShowPixels
* Result: void
*       
* Effect: 
*       ¶
****************************************************************************/

void CKerningExplorer::OnBnClickedShowPixels()                      // REQ #066
    {                                                               // REQ #066
     display_options opts = c_Kerned.GetOpts();                     // REQ #066
     opts.ShowPixels = (c_ShowPixels.GetCheck() == BST_CHECKED);    // REQ #066
     c_Kerned.SetOpts(opts);                                        // REQ #066
                                                                    // REQ #066
     opts = c_Unkerned.GetOpts();                                   // REQ #066
     opts.ShowPixels = (c_ShowPixels.GetCheck() == BST_CHECKED);    // REQ #066
     c_Unkerned.SetOpts(opts);                                      // REQ #066
    } // CKerningExplorer::OnBnClickedShowPixels                    // REQ #066

/****************************************************************************
*                     CKerningExplorer::OnSelendOkPresets
* Result: void
*       
* Effect: 
*       Sets the test string to be the selected string
****************************************************************************/

void CKerningExplorer::OnSelendOkPresets()                          // REQ #076
    {                                                               // REQ #076
     int n = c_Presets.GetCurSel();                                 // REQ #076
     if(n < 0)                                                      // REQ #076
        return;                                                     // REQ #076
     CString s;                                                     // REQ #076
     c_Presets.GetLBText(n, s);                                     // REQ #076
     c_Sample.SetWindowText(s);                                     // REQ #076
    } // CKerningExplorer::OnSelendOkPresets                        // REQ #076

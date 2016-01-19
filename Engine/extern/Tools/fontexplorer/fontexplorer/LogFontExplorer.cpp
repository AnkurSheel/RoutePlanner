/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  4-Jan-99 | Created change log
*  4-Jan-99 | Added new _CHARSET symbols for Windows 2000
* 23-Apr-08 | REQ #006: Added changes for 64-bit compatibility
* 24-Apr-08 | REQ #008: Removed fontexplorer.h
* 28-Apr-08 | REQ #024: Added ErrorString
*  4-May-08 | REQ #037: Code cleanup
* 15-Oct-08 | REQ #043: Replace CDC * with CDC & for cleaner code
* 15-Oct-08 | REQ #044: Remove unused cases
* 15-Oct-08 | REQ #045: Show code; resizable
* 18-Oct-08 | REQ #053: Made LogFontExplorer be a view
* 19-Oct-08 | REQ #057: Update font to track changes immediately
* 19-Oct-08 | REQ #058: Sample text
* 19-Oct-08 | REQ #059: Show grid for font sample
* 19-Oct-08 | REQ #060: Support horizontal and vertical alignment selections
* 20-Oct-08 | REQ #062: ResizeParentToFit
* 28-Oct-08 | REQ #074: Made AddStrings parameter const and change decls
*  2-Nov-08 | REQ #083: Added copy button
*  4-Nov-08 | REQ #090: Allow "locking" orientation and escapement
*****************************************************************************/
// LogFontExplorer.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"                                               // REQ #008
#include "logfont.h"
#include "LogFontExplorer.h"
#include "tm.h"
#include "kp.h"
#include "otm.h"
#include "ErrorString.h"
#include "ToString.h"                                               // REQ #045
#include "Language.h"                                               // REQ #078

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CLogFontExplorer, CFormView)

//static int CALLBACK LoadFontProc(const LOGFONT * elf, 
//                                 const TEXTMETRIC * ntm, 
//                                 DWORD type, 
//                                 LPARAM lParam);


static const IDData t_Weight[] = {                                  // REQ #074
        { IDS_FW_DONTCARE,     0},
        { IDS_FW_THIN,       100},
        { IDS_FW_EXTRALIGHT, 200},
        { IDS_FW_ULTRALIGHT, 200},
        { IDS_FW_LIGHT,      300},
        { IDS_FW_NORMAL,     400},
        { IDS_FW_REGULAR,    400},
        { IDS_FW_MEDIUM,     500},
        { IDS_FW_SEMIBOLD,   600},
        { IDS_FW_DEMIBOLD,   600},
        { IDS_FW_BOLD,       700},
        { IDS_FW_EXTRABOLD,  800},
        { IDS_FW_ULTRABOLD,  800},
        { IDS_FW_HEAVY,      900},
        { IDS_FW_BLACK,      900},
        { 0, 0} // EOT
                           };

// This encompasses the character sets for Windows 2000
static const IDData t_CharSet[] = {                                 // REQ #074
        { IDS_ANSI_CHARSET, ANSI_CHARSET},
        { IDS_BALTIC_CHARSET,   BALTIC_CHARSET},
        { IDS_CHINESEBIG5_CHARSET, CHINESEBIG5_CHARSET},
        { IDS_DEFAULT_CHARSET, DEFAULT_CHARSET},
        { IDS_EASTEUROPE_CHARSET,       EASTEUROPE_CHARSET},
        { IDS_GB2312_CHARSET, GB2312_CHARSET},
        { IDS_GREEK_CHARSET,    GREEK_CHARSET},
        { IDS_HANGEUL_CHARSET, HANGEUL_CHARSET},
        { IDS_MAC_CHARSET,      MAC_CHARSET},
        { IDS_OEM_CHARSET, OEM_CHARSET},
        { IDS_RUSSIAN_CHARSET,  RUSSIAN_CHARSET},
        { IDS_SHIFTJIS_CHARSET, SHIFTJIS_CHARSET},
        { IDS_SYMBOL_CHARSET, SYMBOL_CHARSET},
        { IDS_TURKISH_CHARSET,  TURKISH_CHARSET},
        { 0, 0}, // EOT
                            };

static const IDData t_CharSet95[] = {                               // REQ #074
        { IDS_JOHAB_CHARSET, JOHAB_CHARSET},
        { IDS_HEBREW_CHARSET, HEBREW_CHARSET},
        { IDS_ARABIC_CHARSET, ARABIC_CHARSET},
        { IDS_GREEK_CHARSET, GREEK_CHARSET},
        { IDS_TURKISH_CHARSET, TURKISH_CHARSET},
        { IDS_THAI_CHARSET, THAI_CHARSET},
        { IDS_EASTEUROPE_CHARSET, EASTEUROPE_CHARSET},
        { IDS_RUSSIAN_CHARSET, RUSSIAN_CHARSET},
        { IDS_MAC_CHARSET, MAC_CHARSET},
        { IDS_BALTIC_CHARSET, BALTIC_CHARSET},
        { 0, 0 } // EOT
                              };

static const IDData t_OutPrecision[] = {                            // REQ #074
        { IDS_OUT_CHARACTER_PRECIS, OUT_CHARACTER_PRECIS},
        { IDS_OUT_DEFAULT_PRECIS, OUT_DEFAULT_PRECIS},
        { IDS_OUT_DEVICE_PRECIS, OUT_DEVICE_PRECIS},
        { IDS_OUT_OUTLINE_PRECIS, OUT_OUTLINE_PRECIS},
        { IDS_OUT_RASTER_PRECIS, OUT_RASTER_PRECIS},
        { IDS_OUT_STRING_PRECIS, OUT_STRING_PRECIS},
        { IDS_OUT_STROKE_PRECIS, OUT_STROKE_PRECIS},
        { IDS_OUT_TT_ONLY_PRECIS, OUT_TT_ONLY_PRECIS},
        { IDS_OUT_TT_PRECIS, OUT_TT_PRECIS},
        { 0, 0 } // EOT
                                 };

static const IDData t_ClipPrecision[] = {                           // REQ #074
//        { IDS_CLIP_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS},      // REQ #044
        { IDS_CLIP_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS},
        { IDS_CLIP_STROKE_PRECIS, CLIP_STROKE_PRECIS},
//        { IDS_CLIP_MASK, CLIP_MASK},                              // REQ #044
        { IDS_CLIP_EMBEDDED, CLIP_EMBEDDED},
        { IDS_CLIP_LH_ANGLES, CLIP_LH_ANGLES},
//      { IDS_CLIP_TT_ALWAYS, CLIP_TT_ALWAYS},                      // REQ #044
        { 0, 0} // EOT
                                  };

static const IDData t_Pitch[] = {                                   // REQ #074
        { IDS_DEFAULT_PITCH, DEFAULT_PITCH},
        { IDS_FIXED_PITCH, FIXED_PITCH},
        { IDS_VARIABLE_PITCH, VARIABLE_PITCH},
        { 0, 0 } // EOT
                           };

static const IDData t_Family[] = {                                  // REQ #074
        { IDS_FF_DECORATIVE, FF_DECORATIVE},
        { IDS_FF_DONTCARE,   FF_DONTCARE},
        { IDS_FF_MODERN,     FF_MODERN},
        { IDS_FF_ROMAN,      FF_ROMAN},
        { IDS_FF_SCRIPT,     FF_SCRIPT},
        { IDS_FF_SWISS,      FF_SWISS}, 
        { 0, 0} // EOT
                           };

static const IDData t_Quality[] = {                                 // REQ #074
        { IDS_DEFAULT_QUALITY, DEFAULT_QUALITY},
        { IDS_ANTIALIASED_QUALITY, ANTIALIASED_QUALITY},            // REQ #043
        { IDS_CLEARTYPE_QUALITY, CLEARTYPE_QUALITY},                // REQ #043
        { IDS_CLEARTYPE_NATURAL_QUALITY, CLEARTYPE_QUALITY},        // REQ #043
        { IDS_DRAFT_QUALITY,   DRAFT_QUALITY},
        { IDS_NONANTIALIASED_QUALITY, NONANTIALIASED_QUALITY},      // REQ #043
        { IDS_PROOF_QUALITY,   PROOF_QUALITY},
        { 0, 0 } // EOT
                            };

static const IDData Languages[] = {                                 // REQ #045// REQ #074
        { IDS_C6, LANGUAGE_C6},                                     // REQ #045
        { IDS_C2008, LANGUAGE_C2008},                               // REQ #045
        { IDS_MFC6, LANGUAGE_MFC6},                                 // REQ #045
        { IDS_MFC2008, LANGUAGE_MFC2008},                           // REQ #045
        { 0, 0} // EOT                                              // REQ #045
};                                                                  // REQ #045

static const IDData Horz[] = {                                      // REQ #060// REQ #074
        { IDS_TA_LEFT, TA_LEFT },                                   // REQ #060
        { IDS_TA_CENTER, TA_CENTER },                               // REQ #060
        { IDS_TA_RIGHT, TA_RIGHT },                                 // REQ #060
        { 0, 0} // EOT                                              // REQ #060
};// REQ #060

static const IDData Vert[] = {                                      // REQ #060// REQ #074
   { IDS_TA_TOP, TA_TOP },                                          // REQ #060
   { IDS_TA_BOTTOM, TA_BOTTOM },                                    // REQ #060
   { IDS_TA_BASELINE, TA_BASELINE },                                // REQ #060
   { 0, 0} // EOT                                                   // REQ #060
};                                                                  // REQ #060

/////////////////////////////////////////////////////////////////////////////
// CLogFontExplorer dialog

#ifdef _DEBUG                                                       // REQ #053
void CLogFontExplorer::AssertValid() const                          // REQ #053
{                                                                   // REQ #053
        CFormView::AssertValid();                                   // REQ #053
}                                                                   // REQ #053

void CLogFontExplorer::Dump(CDumpContext& dc) const                 // REQ #053
{                                                                   // REQ #053
        CFormView::Dump(dc);                                        // REQ #053
}                                                                   // REQ #053
#endif //_DEBUG                                                     // REQ #053




/****************************************************************************
*                     CLogFontExplorer::CLogFontExplorer
* Inputs:
*       CWnd * pParent:
* Effect: 
*       Constructor
****************************************************************************/

CLogFontExplorer::CLogFontExplorer()                                // REQ #053
   : CFormView(CLogFontExplorer::IDD)                               // REQ #053
   {
    ::ZeroMemory(&lf, sizeof(LOGFONT));                             // REQ #037
    font = NULL;
    initialized = FALSE;                                            // REQ #045
    AvoidLockedControlRecursion = FALSE;                            // REQ #090
        //{{AFX_DATA_INIT(CLogFontExplorer)
        //}}AFX_DATA_INIT
   }

CLogFontExplorer::~CLogFontExplorer()                               // REQ #053
   {                                                                // REQ #053
   }                                                                // REQ #053

/****************************************************************************
*                       CLogFontExplorer::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CLogFontExplorer::DoDataExchange(CDataExchange* pDX)
{
        CFormView::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CLogFontExplorer)
        DDX_Control(pDX, IDC_DATA, c_Data);
        DDX_Control(pDX, IDC_FACENAME, c_lfFaceName);
        DDX_Control(pDX, IDC_SAMPLE, c_Sample);
        DDX_Control(pDX, IDC_RESULT, c_Result);
        DDX_Control(pDX, IDC_LFWIDTH, c_lfWidth);
        DDX_Control(pDX, IDC_LFHEIGHT, c_lfHeight);
        DDX_Control(pDX, IDC_LFESCAPEMENT, c_lfEscapement);
        DDX_Control(pDX, IDC_LFORIENTATION, c_lfOrientation);
        DDX_Control(pDX, IDC_SPINORIENTATION, c_SpinOrientation);
        DDX_Control(pDX, IDC_SPINESCAPEMENT, c_SpinEscapement);
        DDX_Control(pDX, IDC_LFORIENTATION_CAPTION, c_c_lfOrientation);
        DDX_Control(pDX, IDC_GM_ADVANCED, c_GM_ADVANCED);
        DDX_Control(pDX, IDC_LFFAMILY, c_lfFamily);
        DDX_Control(pDX, IDC_LFPITCH, c_lfPitch);
        DDX_Control(pDX, IDC_LFWEIGHT, c_lfWeight);
        DDX_Control(pDX, IDC_LFQUALITY, c_lfQuality);
        DDX_Control(pDX, IDC_LFOUTPRECISION, c_lfOutPrecision);
        DDX_Control(pDX, IDC_LFCHARSET, c_lfCharSet);
        DDX_Control(pDX, IDC_LFCLIPPRECISION, c_lfClipPrecision);
        DDX_Control(pDX, IDC_LFUNDERLINE, c_lfUnderline);
        DDX_Control(pDX, IDC_LFITALIC, c_lfItalic);
        DDX_Control(pDX, IDC_LFSTRIKEOUT, c_lfStrikeOut);
        DDX_Control(pDX, IDC_FRAME, c_Frame);                       // REQ #045
        DDX_Control(pDX, IDC_CODE, c_Code);                         // REQ #045
        DDX_Control(pDX, IDC_LANGUAGE, c_Language);                 // REQ #045
        DDX_Control(pDX, IDC_SHOW_ZERO, c_ShowZero);                // REQ #045
        DDX_Control(pDX, IDC_TEXT, c_Text);                         // REQ #058
        DDX_Control(pDX, IDC_SHOW_GRID, c_ShowGrid);                // REQ #059
        DDX_Control(pDX, IDC_ALIGN_VERT, c_Vert);                   // REQ #060
        DDX_Control(pDX, IDC_ALIGN_HORZ, c_Horz);                   // REQ #060
        DDX_Control(pDX, IDC_COPY, c_Copy);                         // REQ #083
        DDX_Control(pDX, IDC_LOCK, c_Locked);                       // REQ #090
        //}}AFX_DATA_MAP
}

/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CLogFontExplorer, CFormView)
        //{{AFX_MSG_MAP(CLogFontExplorer)
        ON_WM_DESTROY()
        ON_EN_CHANGE(IDC_TEXT, OnEnChangeText)                      // REQ #058
        ON_EN_CHANGE(IDC_LFHEIGHT, OnEnChangelfHeight)              // REQ #045
        ON_EN_CHANGE(IDC_LFWIDTH, OnEnChangelfWidth)                // REQ #045
        ON_EN_CHANGE(IDC_LFESCAPEMENT, OnEnChangelfEscapement)      // REQ #045
        ON_EN_CHANGE(IDC_LFORIENTATION, OnEnChangelfOrientation)    // REQ #045
        ON_BN_CLICKED(IDC_LFITALIC, OnBnClickedlfItalic)            // REQ #045
        ON_BN_CLICKED(IDC_LFUNDERLINE, OnBnClickedlfUnderline)      // REQ #045
        ON_BN_CLICKED(IDC_LFSTRIKEOUT, OnBnClickedlfStrikeout)      // REQ #045
        ON_BN_CLICKED(IDC_SHOW_GRID, OnBnClickedShowGrid)           // REQ #059
        ON_CBN_SELENDOK(IDC_LFFAMILY, OnCbnSelendokLffamily)        // REQ #045
        ON_CBN_SELENDOK(IDC_LANGUAGE, OnCbnSelendOkLanguage)        // REQ #045
        ON_CBN_SELENDOK(IDC_LFWEIGHT, OnCbnSelendOkWeight)          // REQ #045
        ON_CBN_SELENDOK(IDC_LFCHARSET, OnCbnSelendOkCharSet)        // REQ #045
        ON_CBN_SELENDOK(IDC_LFOUTPRECISION, OnCbnSelendOkOutPrecision)// REQ #045
        ON_CBN_SELENDOK(IDC_LFCLIPPRECISION, OnCbnSelendOkClipPrecision)// REQ #045
        ON_CBN_SELENDOK(IDC_LFQUALITY, OnCbnSelendOkQuality)        // REQ #045
        ON_CBN_SELENDOK(IDC_FACENAME, OnCbnSelendOkFaceName)        // REQ #045
        ON_CBN_SELENDOK(IDC_LFPITCH, OnCbnSelendOkPitch)            // REQ #045
        ON_CBN_SELENDOK(IDC_LFFAMILY, OnCbnSelendOkFamily)          // REQ #045
        ON_CBN_SELENDOK(IDC_ALIGN_VERT, OnCbnSelendOkVert)          // REQ #060
        ON_CBN_SELENDOK(IDC_ALIGN_HORZ, OnCbnSelendOkHorz)          // REQ #060
        ON_BN_CLICKED(IDC_SHOW_ZERO, OnBnClickedShowZero)           // REQ #053
        ON_WM_VSCROLL()
        ON_WM_GETMINMAXINFO()                                       // REQ #045
        ON_WM_SIZE()                                                // REQ #045
        ON_BN_CLICKED(IDC_GM_ADVANCED, OnGmAdvanced)
        ON_BN_CLICKED(IDC_COPY, OnBnClickedCopy)                    // REQ #083
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogFontExplorer message handlers


/****************************************************************************
*                           CLogFontExplorer::Is95
* Result: BOOL
*       TRUE if running on Win95
*       FALSE if running on Win/NT
****************************************************************************/

BOOL CLogFontExplorer::Is95()
    {
     OSVERSIONINFO info;
     info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
     ::GetVersionEx(&info);
     return (info.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS);
    }

/****************************************************************************
*                               controls_to_lf
* Result: void
*       
* Effect: 
*       Loads the LOGFONT structure lf from the controls
****************************************************************************/

void CLogFontExplorer::controls_to_lf()
    {
     lf.lfHeight = GetDlgItemInt(IDC_LFHEIGHT);

     lf.lfWidth  = GetDlgItemInt(IDC_LFWIDTH);

     lf.lfEscapement = c_lfEscapement.GetWindowInt();

     if(c_GM_ADVANCED.GetCheck() == BST_UNCHECKED)
        { /* esc == orient */
         lf.lfOrientation = lf.lfEscapement;
        } /* esc == orient */
     else
        { /* esc != orient */
         lf.lfOrientation = c_lfOrientation.GetWindowInt();
        } /* esc != orient */

     int index = c_lfWeight.GetCurSel();
     DWORD data = (DWORD)c_lfWeight.GetItemData(index);             // REQ #006
     lf.lfWeight = (LONG)data;

     lf.lfItalic = c_lfItalic.GetCheck();
     lf.lfUnderline = c_lfUnderline.GetCheck();
     lf.lfStrikeOut = c_lfStrikeOut.GetCheck();

     index = c_lfCharSet.GetCurSel();
     data = (DWORD)c_lfCharSet.GetItemData(index);                  // REQ #006
     lf.lfCharSet = (BYTE)data;

     index = c_lfOutPrecision.GetCurSel();
     data = (DWORD)c_lfOutPrecision.GetItemData(index);             // REQ #006
     lf.lfOutPrecision = (BYTE)data;

     index = c_lfClipPrecision.GetCurSel();
     data = (DWORD)c_lfClipPrecision.GetItemData(index);            // REQ #006
     lf.lfClipPrecision = (BYTE)data;

     index = c_lfQuality.GetCurSel();
     data = (DWORD)c_lfQuality.GetItemData(index);                  // REQ #006
     lf.lfQuality = (BYTE)data;

     index = c_lfPitch.GetCurSel();
     data = (DWORD)c_lfPitch.GetItemData(index);                    // REQ #006

     lf.lfPitchAndFamily = (BYTE)data;

     index = c_lfFamily.GetCurSel();
     data = (DWORD)c_lfFamily.GetItemData(index);                   // REQ #006
     lf.lfPitchAndFamily |= (BYTE)data;

     index = c_lfFaceName.GetCurSel();
     data = (DWORD)c_lfFaceName.GetItemData(index);                 // REQ #006
     if(data == (DWORD)-1)
        { /* no font */
         lstrcpy(lf.lfFaceName, _T(""));
        } /* no font */
     else
        { /* load it */
         CString s;
         c_lfFaceName.GetWindowText(s);
         lstrcpy(lf.lfFaceName, s);
        } /* load it */
    }


/****************************************************************************
*                        CLogFontExplorer::OnInitialUpdate
* Result: void
*       
* Effect: 
*       Initializes the dialog
****************************************************************************/

void CLogFontExplorer::OnInitialUpdate()                            // REQ #053
{
        CFormView::OnInitialUpdate();                               // REQ #053
        
        CString s;
        s.LoadString(IDS_LOGFONT_EXPLORER_CAPTION);                 // REQ #061
        GetParentFrame()->SetWindowText(s);                         // REQ #061

        s.LoadString(IDS_SAMPLE);
        c_Sample.SetWindowText(s);

        c_lfWeight.AddStrings(t_Weight, FW_DONTCARE);
        
        c_lfCharSet.AddStrings(t_CharSet, ANSI_CHARSET);

        if(Is95())
           c_lfCharSet.AddStrings(t_CharSet95);
        
        c_GM_ADVANCED.EnableWindow(!Is95());

        c_SpinOrientation.SetBuddy(&c_lfOrientation);
        c_SpinOrientation.SetRange(-3600, 3600);
        c_SpinOrientation.SetPos(0);

        c_SpinEscapement.SetBuddy(&c_lfEscapement);
        c_SpinEscapement.SetRange(-3600, 3600);
        c_SpinEscapement.SetPos(0);

        c_lfOutPrecision.AddStrings(t_OutPrecision, OUT_DEFAULT_PRECIS);// REQ #045
        c_lfClipPrecision.AddStrings(t_ClipPrecision, CLIP_DEFAULT_PRECIS);// REQ #045
        c_lfPitch.AddStrings(t_Pitch, DEFAULT_PITCH);               // REQ #045
        c_lfFamily.AddStrings(t_Family, FF_DONTCARE);               // REQ #045
        c_lfQuality.AddStrings(t_Quality, DEFAULT_QUALITY);         // REQ #045

        c_Language.AddStrings(Languages, LANGUAGE_MFC2008);         // REQ #045

        c_Horz.AddStrings(Horz, TA_LEFT);                           // REQ #060
        c_Vert.AddStrings(Vert, TA_TOP);                            // REQ #060

        CClientDC dc(this); // sort-of-randomly-chosen DC
        ::EnumFontFamilies(dc.m_hDC, NULL, &CLogFontExplorer::LoadFontProc, (LPARAM)this); // REQ #053


        s.LoadString(IDS_NONE);
        int index = c_lfFaceName.AddString(s);
        c_lfFaceName.SetItemData(index, (DWORD)-1);

        index = c_lfFaceName.FindString(-1, _T("Arial"));
        if(index == CB_ERR)
           index = 0;
        c_lfFaceName.SetCurSel(index);

        /*****************************************************************************
          +-------------------------------------------------------------------------+
          |                                                                         |
          |                                                                         |
          |                                 c_Code                                  |   |
          |                                                                         |   |
          |                                                                         |   V
          +-------------------------------------------------------------------------+ -----

          +----------------------------------+   +----------------------------------+ -----
          |                                  |   |                                  |   ^
          |            c_Sample              |   |             c_Data               |   |
          |                                  |   |                                  |   |
          +----------------------------------+   +----------------------------------+   hgap
                                             |   |
                                         --->|   |<--- vgap
                                             |   |
        *****************************************************************************/
        CRect code;
        c_Code.GetWindowRect(&code);
        ScreenToClient(&code);

        CRect sample;
        c_Sample.GetWindowRect(&sample);
        ScreenToClient(&sample);

        CRect data;
        c_Data.GetWindowRect(&data);
        ScreenToClient(&data);

        hgap = data.top - code.bottom;
        vgap = data.left - sample.right;

        setMessage(0);

        CodeFont.CreatePointFont(90, _T("Courier New"));            // REQ #045
        c_Code.SetFont(&CodeFont);                                  // REQ #045

        s.LoadString(IDS_SAMPLE_TEXT);                              // REQ #058
        c_Text.SetWindowText(s);                                    // REQ #058
        
        GetParentFrame()->RecalcLayout();                           // REQ #062
        ResizeParentToFit(FALSE);                                   // REQ #062

        c_Copy.LoadBitmaps(IDB_COPY);                               // REQ #083

        initialized = TRUE;

        ResizeWindows();                                            // REQ #045
        updateFont();                                               // REQ #057
        updateCode();                                               // REQ #045
        updateControls();                                           // REQ #060
}

/****************************************************************************
*                      CLogFontExplorer::updateControls
* Result: void
*       
* Effect: 
*       Updates the controls
****************************************************************************/

void CLogFontExplorer::updateControls()                             // REQ #045
    {
     if(c_GM_ADVANCED.GetCheck() == BST_UNCHECKED)
        { /* not advanced */
         c_lfOrientation.ShowWindow(SW_HIDE);
         c_c_lfOrientation.EnableWindow(FALSE);
         c_SpinOrientation.EnableWindow(FALSE);
         c_Sample.SetGraphicsMode(GM_COMPATIBLE);
        } /* not advanced */
     else
        { /* advanced */
         c_lfOrientation.ShowWindow(SW_SHOW);
         c_c_lfOrientation.EnableWindow(TRUE);
         c_SpinOrientation.EnableWindow(TRUE);
         c_Sample.SetGraphicsMode(GM_ADVANCED);
        } /* advanced */

     DWORD align = 0;
     align |= (DWORD)c_Vert.GetItemData(c_Vert.GetCurSel());        // REQ #060
     align |= (DWORD)c_Horz.GetItemData(c_Horz.GetCurSel());        // REQ #060
     c_Sample.SetTextAlign(align);                                  // REQ #060
     
     c_Sample.ShowGrid(c_ShowGrid.GetCheck() == BST_CHECKED);       // REQ #059
    } // CLogFontExplorer::updateControls                           // REQ #045

/****************************************************************************
*                         CLogFontExplorer::OnDestroy
* Result: void
*       
* Effect: 
*       Deletes any resources consumed
****************************************************************************/

void CLogFontExplorer::OnDestroy() 
{
        CFormView::OnDestroy();                                     // REQ #053
        
        TRACE(_T(__FUNCTION__) _T(": DeleteObject(font=%p)\n"), font);// REQ #021
        ::DeleteObject(font);
        
}

/****************************************************************************
*                        CLogFontExplorer::updateFont
* Result: void
*       
* Effect: 
*       Updates the font
****************************************************************************/

void CLogFontExplorer::updateFont()                                 // REQ #053
    {                                                               // REQ #053
     controls_to_lf();
     HFONT f = ::CreateFontIndirect(&lf);
     if(f == NULL)
        { /* error */
         DWORD err = ::GetLastError();
         setMessage(err);
        } /* error */
     else
        { /* success */
         LOGFONT logf;

         TRACE(_T(__FUNCTION__) _T(": DeleteObject(font=%p)\n"), font);// REQ #021
         ::DeleteObject(font);

         font = f;
         c_Sample.SetFont(CFont::FromHandle(font));

         c_Data.DeleteAllItems();

         // Note that we want to get the stats on the actual font created
         // instead of the creation parameters themselves

         CFont * cf = CFont::FromHandle(f);

         cf->GetObject(sizeof(LOGFONT), &logf);

         loadLogFont(&logf, &c_Data, FALSE);


         {
          CClientDC dc(this);
          TEXTMETRIC tm;
          LPOUTLINETEXTMETRIC otm = NULL;

          dc.SelectObject(cf);

          int n = dc.GetOutlineTextMetrics(0, NULL);
          if(n > 0)
             { /* initialize */
              otm = (OUTLINETEXTMETRIC *)new BYTE[n];
              dc.GetOutlineTextMetrics(n, otm);
             } /* initialize */

          dc.GetTextMetrics(&tm);
          loadTextMetrics(&tm, &c_Data);

          loadOutlineTextMetrics(otm, &c_Data);

          loadKerningPairs(dc, &c_Data);

          if(otm != NULL)
             delete otm;
         }

         c_Sample.SetFont(cf);
         c_Sample.Invalidate();
        } /* success */
    } // CLogFontExplorer::updateFont                               // REQ #053

/****************************************************************************
*                     CLogFontExplorer::OnCbnSelendLffamily
* Result: void
*       
* Effect: 
*       NYI
****************************************************************************/

void CLogFontExplorer::OnCbnSelendokLffamily() 
   {                                                                // REQ #045
    updateFont();                                                   // REQ #057
    updateCode();                                                   // REQ #045
   }                                                                // REQ #045

/****************************************************************************
*                         CLogFontExplorer::OnVScroll
* Inputs:
*       UINT nSBCode: ignored except for passing to subclass
*       UINT nPos: ignored except for passing to subclass
*       CScrollBar * pScrollBar: ignored except for passing to subclass
* Result: void
*       
* Effect: 
*       Determines which spin control should receive the message
****************************************************************************/

void CLogFontExplorer::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
 if(pScrollBar != NULL)                                             // REQ #053
     {                                                              // REQ #053
      if(pScrollBar->m_hWnd == c_SpinOrientation.m_hWnd)
         c_SpinOrientation.OnVScroll(nSBCode, nPos, pScrollBar);
      else
      if(pScrollBar->m_hWnd == c_SpinEscapement.m_hWnd)
         c_SpinEscapement.OnVScroll(nSBCode, nPos, pScrollBar);
     }                                                              // REQ #053
 else
    CFormView::OnVScroll(nSBCode, nPos, pScrollBar);                // REQ #053
}

/****************************************************************************
*                       CLogFontExplorer::OnGmAdvanced
* Result: void
*       
* Effect: 
*       If GM_ADVANCED is turned ON (which is possible only on Win/NT)
*       we disabled the lfOrientation control; the lfEscapement is the
*       dominant control
****************************************************************************/

void CLogFontExplorer::OnGmAdvanced() 
   {
    updateControls();                                               // REQ #045
    updateCode();                                                   // REQ #045
   }

/****************************************************************************
*                                LoadFontProc
* Inputs:
*       ENUMLOGFONT * elf:
*       NEWTEXTMETRIC * ntm:
*       int type:
*       LPARAM lParam: (LPARAM)CLogFontExplorer *
* Result: int
*       
* Effect: 
*       Loads the control
****************************************************************************/

int CALLBACK CLogFontExplorer::LoadFontProc(const LOGFONT * elf,    // REQ #053
                                 const TEXTMETRIC * ntm, 
                                 DWORD type, 
                                 LPARAM lParam)
    {
     CLogFontExplorer * t = (CLogFontExplorer *)lParam;

     int index = t->c_lfFaceName.AddString(elf->lfFaceName);
     t->c_lfFaceName.SetItemData(index, type);

//     if(type & TRUETYPE_FONTTYPE)
//        { /* truetype font */
//       int index = t->c_lfFaceName.AddString(elf->lfFaceName);
//       t->c_lfFaceName.SetItemData(index, 0);
//      } /* truetype font */
     return TRUE; // continue enumeration
    }

/****************************************************************************
*                        CLogFontExplorer::setMessage
* Inputs:
*       DWORD result: Result to display
* Result: void
*       
* Effect: 
*       Puts the string representing the message in the c_Result box
****************************************************************************/

void CLogFontExplorer::setMessage(DWORD result)
    {
     if(result == 0)
        { /* no message */
         c_Result.SetWindowText(NULL);
         return;
        } /* no message */

     c_Result.SetWindowText(ErrorString(result)); // REQ #024
    }

/****************************************************************************
*                      CLogFontExplorer::OnGetMinMaxInfo
* Inputs:
*       MINMAXINFO * lpMMI:
* Result: void
*       
* Effect: 
*       Prevents resizing the dialog to hide any controls
****************************************************************************/

void CLogFontExplorer::OnGetMinMaxInfo(MINMAXINFO* lpMMI)           // REQ #045
    {                                                               // REQ #045
     if(c_Frame.GetSafeHwnd() != NULL)                              // REQ #045
        { /* can limit */                                           // REQ #045
         CRect r;                                                   // REQ #045
         c_Frame.GetWindowRect(&r);                                 // REQ #045
         ScreenToClient(&r);                                        // REQ #045
         CalcWindowRect(&r);                                        // REQ #045
         lpMMI->ptMinTrackSize.x = r.Width();                       // REQ #045
         lpMMI->ptMinTrackSize.y = r.Height();                      // REQ #045
         return;                                                    // REQ #045
        } /* can limit */                                           // REQ #045
     CFormView::OnGetMinMaxInfo(lpMMI);                             // REQ #045// REQ #053
    } // CLogFontExplorer::OnGetMinMaxInfo                          // REQ #045

/****************************************************************************
*                       CLogFontExplorer::ResizeWindows
* Result: void
*       
* Effect: 
*       Resizes the windows
****************************************************************************/

void CLogFontExplorer::ResizeWindows()                              // REQ #045
    {                                                               // REQ #045
     CRect r;                                                       // REQ #045
     GetClientRect(&r);                                             // REQ #045
     int cx = r.Width();                                            // REQ #045
     int cy = r.Height();                                           // REQ #045
                                                                    // REQ #045
     if(c_Sample.GetSafeHwnd() != NULL &&                           // REQ #045
        c_Data.GetSafeHwnd() != NULL &&                             // REQ #045
        c_Code.GetSafeHwnd() != NULL)                               // REQ #045
        { /* resize windows */                                      // REQ #045
         HDWP defer = ::BeginDeferWindowPos(3);                     // REQ #045
         //*********************************************************// REQ #045
         // Resize the code window                                  // REQ #045
         //*********************************************************// REQ #045
         CRect code;                                                // REQ #045
         c_Code.GetWindowRect(&code);                               // REQ #045
         ScreenToClient(&code);                                     // REQ #045
                                                                    // REQ #045
         CRect newcode;                                             // REQ #045
         newcode.left = code.left;                                  // REQ #045
         newcode.top = code.top;                                    // REQ #045
         newcode.right = cx;                                        // REQ #045
         newcode.bottom = code.top + (cy - code.top) / 2 - (hgap / 2);// REQ #045
                                                                      // REQ #045
         DeferWindowPos(defer,                                      // REQ #045
                        c_Code,                                     // REQ #045
                        NULL,                        // Z_order     // REQ #045
                        newcode.left, newcode.top,   // x, y        // REQ #045
                        newcode.Width(),             // width       // REQ #045
                        newcode.Height(),            // height      // REQ #045
                        SWP_NOMOVE | SWP_NOZORDER);                 // REQ #045
                                                                    // REQ #045
         TRACE(_T("    Code: [%d, %d, %d, %d]\r\n"), newcode.left, newcode.top, newcode.right, newcode.bottom);// REQ #045
         //*********************************************************// REQ #045
         // Resize the sample window                                // REQ #045
         //*********************************************************// REQ #045
         CRect sample;                                              // REQ #045
         c_Sample.GetWindowRect(&sample);                           // REQ #045
         ScreenToClient(&sample);                                   // REQ #045
                                                                    // REQ #045
         CRect newsample;                                           // REQ #045
         newsample.left = sample.left;                              // REQ #045
         newsample.top = newcode.bottom + hgap;                     // REQ #045
         newsample.right = (cx / 2) - vgap / 2;                     // REQ #045
         newsample.bottom = cy;                                     // REQ #045
                                                                    // REQ #045
         DeferWindowPos(defer,                                      // REQ #045
                        c_Sample, // hwnd                           // REQ #045
                        NULL,     // Z-order wnd                    // REQ #045
                        newsample.left,                             // REQ #045
                        newsample.top,                              // REQ #045
                        newsample.Width(),                          // REQ #045
                        newsample.Height(),                         // REQ #045
                        SWP_NOZORDER);                              // REQ #045
                                                                    // REQ #045
         TRACE(_T("    Sample: [%d, %d, %d, %d]\r\n"), newsample.left, newsample.top, newsample.right, newsample.bottom);// REQ #045
                                                                                                                         // REQ #045
         //*********************************************************// REQ #045
         // Resize the tree control                                 // REQ #045
         //*********************************************************// REQ #045
         CRect data;                                                // REQ #045
         c_Data.GetWindowRect(&data);                               // REQ #045
         ScreenToClient(&data);                                     // REQ #045
                                                                    // REQ #045
         CRect newdata;                                             // REQ #045
         newdata.left = newsample.right + vgap;                     // REQ #045
         newdata.top = newsample.top;                               // REQ #045
         newdata.right = cx;                                        // REQ #045
         newdata.bottom = cy;                                       // REQ #045
                                                                    // REQ #045
         DeferWindowPos(defer,                                      // REQ #045
                        c_Data,                                     // REQ #045
                        NULL,                                       // REQ #045
                        newdata.left,                               // REQ #045
                        newdata.top,                                // REQ #045
                        newdata.Width(),                            // REQ #045
                        newdata.Height(),                           // REQ #045
                        SWP_NOZORDER);                              // REQ #045
                                                                    // REQ #045
         TRACE(_T("    Data: [%d, %d, %d, %d]\r\n"), newdata.left, newdata.top, newdata.right, newdata.bottom);// REQ #045
         EndDeferWindowPos(defer);                                  // REQ #045
        } /* resize windows */                                      // REQ #045
    } // CLogFontExplorer::ResizeWindows

/****************************************************************************
*                          CLogFontExplorer::OnSize
* Inputs:
*       UINT nType: Sizing type
*       int cx: New client width
*       int cy: New client height
* Result: void
*       
* Effect: 
*       Resizes the child controls
****************************************************************************/

void CLogFontExplorer::OnSize(UINT nType, int cx, int cy)           // REQ #045
    {                                                               // REQ #045
     CFormView::OnSize(nType, cx, cy);                              // REQ #045// REQ #053
                                                                    // REQ #045
     TRACE(_T(__FUNCTION__) _T("(%d, %d, %d)\r\n"), nType, cx, cy); // REQ #045
     ResizeWindows();                                               // REQ #045
    } // CLogFontExplorer::OnSize                                   // REQ #045

/****************************************************************************
*                        CLogFontExplorer::updateCode
* Result: void
*       
* Effect: 
*       Updates the code and places it in the edit control
****************************************************************************/

void CLogFontExplorer::updateCode()                                 // REQ #045
    {                                                               // REQ #045
     if(!initialized)                                               // REQ #045
        return;                                                     // REQ #045
                                                                    // REQ #045
     int language;                                                  // REQ #045
     language = (int)c_Language.GetItemData(c_Language.GetCurSel());// REQ #045
                                                                    // REQ #045
     BOOL ShowZero = c_ShowZero.GetCheck() == BST_CHECKED;          // REQ #045
                                                                    // REQ #045
     /************************************************************* // REQ #045
       LOGFONT lf = {0};                                            // REQ #045
       lf.lfHeight = <height>;    // [omit if height is empty]      // REQ #045
       lf.lfWidth  = <width>;     // [omit if width is empty]       // REQ #045
       lf.lfUnderline = TRUE;     // [omit if lfUnderline FALSE]    // REQ #045
       lf.lfStrikeout = TRUE;     // [omit if lfStrikeout FALSE]    // REQ #045
     **************************************************************/// REQ #045
     CString code;                                                  // REQ #045
     code += _T("LOGFONT lf = {0}\r\n");                            // REQ #045
                                                                    // REQ #045
     if(c_GM_ADVANCED.GetCheck() == BST_CHECKED)                    // REQ #045
        { /* checked */                                             // REQ #045
         switch(language)                                           // REQ #045
            { /* language */                                        // REQ #045
             case LANGUAGE_C6:                                      // REQ #045
             case LANGUAGE_C2008:                                   // REQ #045
                code += _T("SetGraphicsMode(GM_ADVANCED)\r\n");     // REQ #045
                break;                                              // REQ #045
             case LANGUAGE_MFC6:                                    // REQ #045
             case LANGUAGE_MFC2008:                                 // REQ #045
                code += _T("::SetGraphicsMode(GM_ADVANCED)\r\n");   // REQ #045
                break;                                              // REQ #045
             } /* language */                                       // REQ #045
        } /* checked */                                             // REQ #045
                                                                    // REQ #045
     CString s;                                                     // REQ #045
     //*************************************************************// REQ #045
     // lf.lfHeight                                                 // REQ #045
     //*************************************************************// REQ #045
     c_lfHeight.GetWindowText(s);                                   // REQ #045
     s.Trim();                                                      // REQ #045
     if(!s.IsEmpty())                                               // REQ #045
        code += ToString(_T("lf.lfHeight = %d;\r\n"), _ttoi(s));    // REQ #045
     else                                                           // REQ #045
     if(ShowZero)                                                   // REQ #045
        code += _T("lf.lfHeight = 0;\r\n");                         // REQ #045
                                                                    // REQ #045
     //*************************************************************// REQ #045
     // lf.lfWidth                                                  // REQ #045
     //*************************************************************// REQ #045
     c_lfWidth.GetWindowText(s);                                    // REQ #045
     s.Trim();                                                      // REQ #045
     if(!s.IsEmpty())                                               // REQ #045
        code += ToString(_T("lf.lfWidth = %d;\r\n"), _ttoi(s));     // REQ #045
     else                                                           // REQ #045
     if(ShowZero)                                                   // REQ #045
        code += _T("lf.lfWidth = 0;\r\n");                          // REQ #045
                                                                    // REQ #045
     //*************************************************************// REQ #045
     // lf.lfEscapement                                             // REQ #045
     //*************************************************************// REQ #045
     if(c_SpinEscapement.GetPos32() != 0 || ShowZero)               // REQ #045
        code += ToString(_T("lf.lfEscapement = %d;\r\n"), c_SpinEscapement.GetPos32());// REQ #045
                                                                    // REQ #045
     //*************************************************************// REQ #045
     // lf.lfOrientation                                            // REQ #045
     //*************************************************************// REQ #045
     if(c_GM_ADVANCED.GetCheck() == BST_CHECKED)                    // REQ #045
        { /* advanced mode */                                       // REQ #045
         if(c_SpinOrientation.GetPos32() != 0 || ShowZero)          // REQ #045
            { /* orientation */                                     // REQ #045
             code += ToString(_T("lf.lfOrientation = %d;\r\n"), c_SpinOrientation.GetPos32());// REQ #045
            } /* orientation */                                     // REQ #045
        } /* advanced mode */                                       // REQ #045
     else                                                           // REQ #045
        { /* Same as escapement */                                  // REQ #045
         if(c_SpinEscapement.GetPos32() != 0 || ShowZero)           // REQ #045
            code += _T("lf.lfOrientation = lf.lfEscapement;\r\n");  // REQ #045
        } /* Same as escapement */                                  // REQ #045
                                                                    // REQ #045
     //*************************************************************// REQ #045
     // lf.lfWeight                                                 // REQ #045
     //*************************************************************// REQ #045
     DWORD weight = (DWORD)c_lfWeight.GetItemData(c_lfWeight.GetCurSel());// REQ #045
     if(weight != 0 || ShowZero)                                    // REQ #045
        { /* has weight */                                          // REQ #045
         c_lfWeight.GetLBText(c_lfWeight.GetCurSel(), s);           // REQ #045
         code += ToString(_T("lf.lfWeight = %s;\r\n"), s);          // REQ #045
        } /* has weight */                                          // REQ #045
                                                                    // REQ #045
     //*************************************************************// REQ #045
     // lf.lfItalic                                                 // REQ #045
     //*************************************************************// REQ #045
     if(c_lfItalic.GetCheck() == BST_CHECKED)                       // REQ #045
        code += _T("lf.lfItalic = TRUE;\r\n");                      // REQ #045
     else                                                           // REQ #045
     if(ShowZero)                                                   // REQ #045
        code += _T("lf.lfItalic = FALSE;\r\n");                     // REQ #045
                                                                    // REQ #045
     //*************************************************************// REQ #045
     // lf.lfUnderline                                              // REQ #045
     //*************************************************************// REQ #045
     if(c_lfUnderline.GetCheck() == BST_CHECKED)                    // REQ #045
        code += _T("lf.lfUnderline = TRUE;\r\n");                   // REQ #045
     else                                                           // REQ #045
     if(ShowZero)                                                   // REQ #045
        code += _T("lf.lfUnderline = FALSE;\r\n");                  // REQ #045
                                                                    // REQ #045
     //*************************************************************// REQ #045
     // lf.lfStrikeout                                              // REQ #045
     //*************************************************************// REQ #045
     if(c_lfStrikeOut.GetCheck() == BST_CHECKED)                    // REQ #045
        code += _T("lf.lfStrikeOut = TRUE;\r\n");                   // REQ #045
     else                                                           // REQ #045
     if(ShowZero)                                                   // REQ #045
        code += _T("lf.lfStrikeOut = FALSE;\r\n");                  // REQ #045
                                                                    // REQ #045
     //*************************************************************// REQ #045
     // lf.lfCharSet                                                // REQ #045
     //*************************************************************// REQ #045
     DWORD charset = (DWORD)c_lfCharSet.GetItemData(c_lfCharSet.GetCurSel());// REQ #045
     c_lfCharSet.GetLBText(c_lfCharSet.GetCurSel(), s);             // REQ #045
     if(charset != 0 || ShowZero)                                   // REQ #045
        code += ToString(_T("lf.lfCharSet = %s;\r\n"), s);          // REQ #045
                                                                    // REQ #045
     //*************************************************************// REQ #045
     // lf.lfOutPrecision                                           // REQ #045
     //*************************************************************// REQ #045
     DWORD out = (DWORD)c_lfOutPrecision.GetItemData(c_lfOutPrecision.GetCurSel());// REQ #045
     if(out != 0 || ShowZero)                                       // REQ #045
        { /* out precsion */                                        // REQ #045
         c_lfOutPrecision.GetLBText(c_lfOutPrecision.GetCurSel(), s);// REQ #045
         code += ToString(_T("lf.lfOutPrecision = %s;\r\n"), s);    // REQ #045
        } /* out precsion */                                        // REQ #045
                                                                    // REQ #045
     //*************************************************************// REQ #045
     // lf.lfClipPrecsion                                           // REQ #045
     //*************************************************************// REQ #045
     DWORD clip = (DWORD)c_lfClipPrecision.GetItemData(c_lfClipPrecision.GetCurSel());// REQ #045
     if(clip != 0 || ShowZero)                                      // REQ #045
        { /* clip precsion */                                       // REQ #045
         c_lfClipPrecision.GetLBText(c_lfClipPrecision.GetCurSel(), s);// REQ #045
         code += ToString(_T("lf.lfClipPrecision = %s;\r\n"), s);   // REQ #045
        } /* clip precsion */                                       // REQ #045
                                                                    // REQ #045
     //*************************************************************// REQ #045
     // lf.lfQuality                                                // REQ #045
     //*************************************************************// REQ #045
     DWORD quality = (DWORD)c_lfQuality.GetItemData(c_lfQuality.GetCurSel());// REQ #045
     if(quality != 0 || ShowZero)                                   // REQ #045
        { /* quality */                                             // REQ #045
         c_lfQuality.GetLBText(c_lfQuality.GetCurSel(), s);         // REQ #045
         code += ToString(_T("lf.lfQuaity = %s\r\n"), s);           // REQ #045
        } /* quality */                                             // REQ #045
                                                                    // REQ #045
     //*************************************************************// REQ #045
     // lf.lfPitchAndFamily                                         // REQ #045
     //*************************************************************// REQ #045
     CString paf;                                                   // REQ #045
                                                                    // REQ #045
     DWORD pitch = (DWORD)c_lfPitch.GetItemData(c_lfPitch.GetCurSel());// REQ #045
     if(pitch != 0 || ShowZero)                                     // REQ #045
        { /* show pitch */                                          // REQ #045
         c_lfPitch.GetLBText(c_lfPitch.GetCurSel(), s);             // REQ #045
         paf += s;                                                  // REQ #045
        } /* show pitch */                                          // REQ #045
                                                                    // REQ #045
     DWORD family = (DWORD)c_lfFamily.GetItemData(c_lfFamily.GetCurSel());// REQ #045
     if(family != 0 || ShowZero)                                    // REQ #045
        { /* show family */                                         // REQ #045
         c_lfFamily.GetLBText(c_lfFamily.GetCurSel(), s);           // REQ #045
         if(!paf.IsEmpty())                                         // REQ #045
            paf += _T(" | ");                                       // REQ #045
         paf += s;                                                  // REQ #045
        } /* show family */                                         // REQ #045
                                                                    // REQ #045
     if(!paf.IsEmpty())                                             // REQ #045
        code += ToString(_T("lf.lfPitchAndFamily = %s;\r\n"), paf); // REQ #045
                                                                    // REQ #045
     //*************************************************************// REQ #045
     // lf.lfFaceName                                               // REQ #045
     //*************************************************************// REQ #045
     CString facename;                                              // REQ #045
     c_lfFaceName.GetLBText(c_lfFaceName.GetCurSel(), facename);    // REQ #045
                                                                    // REQ #045
     facename.Trim();                                               // REQ #045
     if(!facename.IsEmpty())                                        // REQ #045
        { /* has facename */                                        // REQ #045
         switch(language)                                           // REQ #045
            { /* facename */                                        // REQ #045
             case LANGUAGE_C6:                                      // REQ #045
                code += ToString(_T("lstrcpyn(lf.lfFaceName, _T(\"%s\"), LF_FACESIZE);\r\n"), facename);// REQ #045
                break;                                              // REQ #045
             case LANGUAGE_C2008:                                   // REQ #045
                code += ToString(_T("_tcscpy_s(lf.lfFaceName, _T(\"%s\"), _countof(lf.lfFaceName));\r\n"), facename);// REQ #045
                break;                                              // REQ #045
             case LANGUAGE_MFC6:                                    // REQ #045
                code += ToString(_T("lstrcpyn(lf.lfFaceName, _T(\"%s\"), LF_FACESIZE);\r\n"), facename);// REQ #045
                break;                                              // REQ #045
             case LANGUAGE_MFC2008:                                 // REQ #045
                code += ToString(_T("_tcscpy_s(lf.lfFaceName, _T(\"%s\"), _countof(lf.lfFaceName));\r\n"), facename);// REQ #045
                break;                                              // REQ #045
            } /* facename */                                        // REQ #045
        } /* has facename */                                        // REQ #045
                                                                    // REQ #045
     CString textalign;                                             // REQ #060
     DWORD align = (DWORD)c_Vert.GetItemData(c_Vert.GetCurSel());   // REQ #060
     if(ShowZero || align != 0)                                     // REQ #060
        { /* has vert alignment */                                  // REQ #060
         CString s;                                                 // REQ #060
         c_Vert.GetLBText(c_Vert.GetCurSel(), s);                   // REQ #060
         textalign = s;                                             // REQ #060
        } /* has vert alignment */                                  // REQ #060
                                                                    // REQ #060
     align = (DWORD)c_Horz.GetItemData(c_Horz.GetCurSel());         // REQ #060
     if(ShowZero || align != 0)                                     // REQ #060
        { /* has horz alignment */                                  // REQ #060
         CString s;                                                 // REQ #060
         c_Horz.GetLBText(c_Horz.GetCurSel(), s);                   // REQ #060
         if(!textalign.IsEmpty())                                   // REQ #060
            textalign += _T(" | ");                                 // REQ #060
         textalign += s;                                            // REQ #060
        } /* has horz alignment */                                  // REQ #060
                                                                    // REQ #060
     code += _T("\r\n");                                            // REQ #060
     code += _T("if(!CreateFontIndirect(&lf))\r\n");                // REQ #060
     code += _T("   { /* failed */\r\n");                           // REQ #060
     code += _T("    // deal with error here\r\n");                 // REQ #060
     code += _T("   } /* failed */\r\n");                           // REQ #060
     code += _T("else\r\n");                                        // REQ #060
     code += _T("   { /* font created */\r\n");                     // REQ #060
     code += _T("    dc.SelectObject(&font);\r\n");                 // REQ #060
     if(!textalign.IsEmpty())                                       // REQ #060
        code += ToString(_T("    dc.SetTextAlign(%s)\r\n"), textalign);// REQ #060
     code += _T("    dc.TextOut(x, y, s)\r\n");                     // REQ #060
     code += _T("   } /* font created */\r\n");                     // REQ #060
                                                                    // REQ #060
     c_Code.SetWindowText(code);                                    // REQ #045
    } // CLogFontExplorer::updateCode                               // REQ #045

/****************************************************************************
*                    CLogFontExplorer::OnEnChangelfHeight
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnEnChangelfHeight()                         // REQ #045
    {                                                               // REQ #045
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnEnChangelfHeight                       // REQ #045

/****************************************************************************
*                     CLogFontExplorer::OnEnChangelfWidth
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnEnChangelfWidth()                          // REQ #045
    {                                                               // REQ #045
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnEnChangelfWidth                        // REQ #045

/****************************************************************************
*                  CLogFontExplorer::OnEnChangelfEscapement
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnEnChangelfEscapement()                     // REQ #045
    {                                                               // REQ #045
     if(AvoidLockedControlRecursion)                                // REQ #090
        return;                                                     // REQ #090
     if(c_Locked.GetLockState())                                    // REQ #090
        { /* has locked */                                          // REQ #090
         AvoidLockedControlRecursion = TRUE;                        // REQ #090
         c_SpinOrientation.SetPos32(c_SpinEscapement.GetPos32());   // REQ #090
         AvoidLockedControlRecursion = FALSE;                       // REQ #090
        } /* has locked */                                          // REQ #090
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnEnChangelfEscapement                   // REQ #045

/****************************************************************************
*                    CLogFontExplorer::OnEnChangelfOrientation
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnEnChangelfOrientation()                    // REQ #045
    {                                                               // REQ #045
     if(AvoidLockedControlRecursion)                                // REQ #090
        return;                                                     // REQ #090
     if(c_Locked.GetLockState())                                    // REQ #090
        { /* has locked */                                          // REQ #090
         AvoidLockedControlRecursion = TRUE;                        // REQ #090
         c_SpinEscapement.SetPos32(c_SpinOrientation.GetPos32());   // REQ #090
         AvoidLockedControlRecursion = FALSE;                       // REQ #090
        } /* has locked */                                          // REQ #090
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnEnChangelfOrientation                  // REQ #045

/****************************************************************************
*                    CLogFontExplorer::OnBnClickedlfItalic
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnBnClickedlfItalic()                        // REQ #045
    {                                                               // REQ #045
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnBnClickedlfItalic                      // REQ #045

/****************************************************************************
*                  CLogFontExplorer::OnBnClickedlfUnderline
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnBnClickedlfUnderline()                     // REQ #045
    {                                                               // REQ #045
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnBnClickedlfUnderline                   // REQ #045

/****************************************************************************
*                  CLogFontExplorer::OnBnClickedlfStrikeout
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnBnClickedlfStrikeout()                     // REQ #045
    {                                                               // REQ #045
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnBnClickedlfStrikeout                   // REQ #045

/****************************************************************************
*                   CLogFontExplorer::OnCbnSelendOkLanguage
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnCbnSelendOkLanguage()                      // REQ #045
    {                                                               // REQ #045
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnCbnSelendOkLanguage                    // REQ #045

/****************************************************************************
*                    CLogFontExplorer::OnCbnSelendOkWeight
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnCbnSelendOkWeight()
    {
     updateFont();                                                  // REQ #057
     updateCode();
    } // CLogFontExplorer::OnCbnSelendOkWeight

/****************************************************************************
*                   CLogFontExplorer::OnCbnSelendOkCharSet
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnCbnSelendOkCharSet()                       // REQ #045
    {                                                               // REQ #045
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnCbnSelendOkCharSet                     // REQ #045

/****************************************************************************
*                 CLogFontExplorer::OnCbnSelendOkOutPrecision
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnCbnSelendOkOutPrecision()                  // REQ #045
    {                                                               // REQ #045
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnCbnSelendOkOutPrecision                // REQ #045

/****************************************************************************
*                 CLogFontExplorer::OnCbnSelendOkClipPrecision
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnCbnSelendOkClipPrecision()                 // REQ #045
    {                                                               // REQ #045
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnCbnSelendOkClipPrecision               // REQ #045

/****************************************************************************
*                   CLogFontExplorer::OnCbnSelendOkQuality
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnCbnSelendOkQuality()                       // REQ #045
    {                                                               // REQ #045
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnCbnSelendOkQuality                     // REQ #045

/****************************************************************************
*                   CLogFontExplorer::OnCbnSelendOkFaceName
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnCbnSelendOkFaceName()                      // REQ #045
    {                                                               // REQ #045
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnCbnSelendOkFaceName                    // REQ #045

/****************************************************************************
*                    CLogFontExplorer::OnCbnSelendOkFamily
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnCbnSelendOkFamily()                        // REQ #045
    {                                                               // REQ #045
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnCbnSelendOkFamily                      // REQ #045

/****************************************************************************
*                    CLogFontExplorer::OnCbnSelendOkPitch
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CLogFontExplorer::OnCbnSelendOkPitch()                         // REQ #045
    {                                                               // REQ #045
     updateFont();                                                  // REQ #057
     updateCode();                                                  // REQ #045
    } // CLogFontExplorer::OnCbnSelendOkPitch                       // REQ #045

/****************************************************************************
*                    CLogFontExplorer::OnBnClickedShowZero
* Result: void
*       
* Effect: 
*       Updates controls
****************************************************************************/

void CLogFontExplorer::OnBnClickedShowZero()
    {
     updateCode();
    } // CLogFontExplorer::OnBnClickedShowZero

/****************************************************************************
*                      CLogFontExplorer::OnEnChangeText
* Result: void
*       
* Effect: 
*       Changes the text
****************************************************************************/

void CLogFontExplorer::OnEnChangeText()                             // REQ #058
    {                                                               // REQ #058
     CString s;                                                     // REQ #058
     c_Text.GetWindowText(s);                                       // REQ #058
     c_Sample.SetWindowText(s);                                     // REQ #058
     c_Sample.Invalidate();                                         // REQ #058
    } // CLogFontExplorer::OnEnChangeText                           // REQ #058

/****************************************************************************
*                    CLogFontExplorer::OnBnClickedShowGrid
* Result: void
*       
* Effect: 
*       Shows the grid state
****************************************************************************/

void CLogFontExplorer::OnBnClickedShowGrid()                        // REQ #059
    {                                                               // REQ #059
     updateControls();                                              // REQ #059
    } // CLogFontExplorer::OnBnClickedShowGrid                      // REQ #059

/****************************************************************************
*                      CLogFontExplorer::OnCbnSelendOkHorz
* Result: void
*       
* Effect: 
*       Updates the code
****************************************************************************/

void CLogFontExplorer::OnCbnSelendOkHorz()                          // REQ #060
    {                                                               // REQ #060
     updateControls();                                              // REQ #060
     updateCode();                                                  // REQ #060
    } // CLogFontExplorer::OnCbnSelendOkHorz                        // REQ #060

/****************************************************************************
*                      CLogFontExplorer::OnSelendOkVert
* Result: void
*       
* Effect: 
*       Updates the code
****************************************************************************/

void CLogFontExplorer::OnCbnSelendOkVert()                          // REQ #060
    {                                                               // REQ #060
     updateControls();                                              // REQ #060
     updateCode();                                                  // REQ #060
    } // CLogFontExplorer::OnCbnSelendOkVert                        // REQ #060

/****************************************************************************
*                      CLogFontExplorer::OnBnClickedCopy
* Result: void
*       
* Effect: 
*       Copies the text to the clipboard
****************************************************************************/

void CLogFontExplorer::OnBnClickedCopy()                            // REQ #083
    {                                                               // REQ #083
     c_Code.SetRedraw(FALSE);                                       // REQ #083
     int low;                                                       // REQ #083
     int high;                                                      // REQ #083
     c_Code.GetSel(low, high);                                      // REQ #083
     c_Code.SetSel(0, -1);                                          // REQ #083
     c_Code.SendMessage(WM_COPY);                                   // REQ #083
     c_Code.SetSel(low, high);                                      // REQ #083
     c_Code.SetRedraw(TRUE);                                        // REQ #083
    } // CLogFontExplorer::OnBnClickedCopy                          // REQ #083

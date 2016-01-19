/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 23-Apr-08 | Created
* 23-Apr-08 | REQ #006: Changes required for 64-bit compatibility
* 24-Apr-08 | REQ #008: Removed fontexplorer.h
* 17-Oct-08 | REQ #049: Handle font failure problem
* 17-Oct-08 | REQ #050: Make resizeable
* 17-Oct-08 | REQ #051: Static CALLBACK methods are now static class methods
* 18-Oct-08 | REQ #052: Handle magnification properly
* 18-Oct-08 | REQ #054: Converted to view
* 19-Oct-08 | REQ #061: Set caption
* 20-Oct-08 | REQ #062: ResizeParentToFit
* 28-Oct-08 | REQ #071: Handle font smoothing
*****************************************************************************/
// Raster.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"                                               // REQ #008
#include "intedit.h"
#include "Raster.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RASTER_MAX_MULTIPLIER 50
#define VECTOR_MAX_MULTIPLIER 256
#define TRUETYPE_MAX_MULTIPLIER 256

IMPLEMENT_DYNCREATE(CRaster, CFormView)                             // REQ #054

/////////////////////////////////////////////////////////////////////////////
// CRaster dialog


static const IDData qualities[] ={                                  // REQ #071
   { IDS_DEFAULT_QUALITY, DEFAULT_QUALITY},                         // REQ #071
   { IDS_ANTIALIASED_QUALITY, ANTIALIASED_QUALITY},                 // REQ #071
   { IDS_CLEARTYPE_QUALITY, CLEARTYPE_QUALITY},                     // REQ #071
   { IDS_CLEARTYPE_NATURAL_QUALITY, CLEARTYPE_QUALITY},             // REQ #071
   { IDS_DRAFT_QUALITY,   DRAFT_QUALITY},                           // REQ #071
   { IDS_NONANTIALIASED_QUALITY, NONANTIALIASED_QUALITY},           // REQ #071
   { IDS_PROOF_QUALITY,   PROOF_QUALITY},                           // REQ #071
   { 0, 0 } // EOT                                                  // REQ #071
};                                                                  // REQ #071


/****************************************************************************
*                              CRaster::CRaster
* Inputs:
*       CWnd * pParent:
* Effect: 
*       Constructor
****************************************************************************/

CRaster::CRaster()                                                  // REQ #054
        : CFormView(CRaster::IDD)                                   // REQ #054
{
        initialized = FALSE;
        //{{AFX_DATA_INIT(CRaster)
        //}}AFX_DATA_INIT
}

/****************************************************************************
*                           CRaster::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CRaster::DoDataExchange(CDataExchange* pDX)
{
CFormView::DoDataExchange(pDX);                             // REQ #054
//{{AFX_DATA_MAP(CRaster)
DDX_Control(pDX, IDC_MULTIPLIER_CAPTION, c_c_Multiplier);
DDX_Control(pDX, IDC_HEIGHT_CAPTION, c_c_Height);
DDX_Control(pDX, IDC_VECTOR, c_Vector);
DDX_Control(pDX, IDC_TRUETYPE, c_TrueType);
DDX_Control(pDX, IDC_RASTER, c_Raster);
DDX_Control(pDX, IDC_MULTIPLIER, c_Multiplier);
DDX_Control(pDX, IDC_FONT_SIZE, c_FontSize);
DDX_Control(pDX, IDC_FONTS, c_Fonts);
DDX_Control(pDX, IDC_TEXT, c_Text);
DDX_Control(pDX, IDC_SPINMULTIPLIER, c_SpinMultiplier);     // REQ #052
DDX_Control(pDX, IDC_SAMPLE, c_Sample);
DDX_Control(pDX, IDC_FRAME, c_Frame);                       // REQ #050
DDX_Control(pDX, IDC_SHOW_GRID, c_ShowGrid);                // REQ #052
DDX_Control(pDX, IDC_ENABLE_SCALING, c_EnableScaling);      // REQ #052
DDX_Control(pDX, IDC_SAMPLE_UNMAGNIFIED, c_Unmagnified);    // REQ #052
DDX_Control(pDX, IDC_SPIN_SCALED_HEIGHT, c_SpinScaledHeight);// REQ #052
DDX_Control(pDX, IDC_SCALED_HEIGHT, c_ScaledHeight);        // REQ #052
DDX_Control(pDX, IDC_QUALITY, c_Quality);                   // REQ #071
DDX_Control(pDX, IDC_COPY, c_Copy);
    }

/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CRaster, CFormView)                               // REQ #054
        //{{AFX_MSG_MAP(CRaster)
        ON_EN_CHANGE(IDC_TEXT, OnChangeText)
        ON_CBN_SELENDOK(IDC_FONTS, OnSelendokFonts)
        ON_EN_CHANGE(IDC_MULTIPLIER, OnChangeMultiplier)
        ON_CBN_SELENDOK(IDC_FONT_SIZE, OnSelendokFontSize)
        ON_BN_CLICKED(IDC_COPY, OnCopy)
        ON_BN_CLICKED(IDC_RASTER, OnRaster)
        ON_BN_CLICKED(IDC_TRUETYPE, OnTruetype)
        ON_BN_CLICKED(IDC_ENABLE_SCALING, OnBnClickedEnableScaling) // REQ #052
        ON_BN_CLICKED(IDC_SHOW_GRID, OnBnClickedShowGrid)           // REQ #052
        ON_BN_CLICKED(IDC_VECTOR, OnVector)
        ON_WM_GETMINMAXINFO()                                       // REQ #050
        ON_WM_SIZE()                                                // REQ #050
        ON_EN_CHANGE(IDC_SCALED_HEIGHT, OnChangeScaledHeight)       // REQ #052
        ON_CBN_SELENDOK(IDC_QUALITY, OnSelendOkQuality)             // REQ #071
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRaster message handlers

/****************************************************************************
*                            CRaster::OnChangeText
* Result: void
*       
* Effect: 
*       There is a change in the sample text; reflect it to the sample control
****************************************************************************/

void CRaster::OnChangeText() 
{
 CString s;
 c_Text.GetWindowText(s);
 c_Sample.SetWindowText(s);
 c_Unmagnified.SetWindowText(s);                                    // REQ #052
}

/****************************************************************************
*                                loadFontProc
* Inputs:
*       ENUMLOGFONT * elf:
*       NEWTEXTMETRIC * ntm:
*       int type:
*       LPARAM lParam: (LPARAM)CRaster *
* Result: int
*       
* Effect: 
*       Loads the control
****************************************************************************/

int CALLBACK CRaster::loadFontProc(const LOGFONT * lf,              // REQ #051
                                 const TEXTMETRIC * ntm, 
                                 DWORD type, 
                                 LPARAM lParam)
    {
     CRaster * t = (CRaster *)lParam;

     if((t->fontmask == (DWORD)-1 && type == 0) ||
        (t->fontmask != (DWORD)-1 && (type & t->fontmask)))
        { /* add to list */
         int index = t->c_Fonts.AddString(lf->lfFaceName);
         t->c_Fonts.SetItemData(index, type);
        } /* add to list */

     return TRUE; // continue enumeration
    }

/****************************************************************************
*                            CRaster::OnInitialUpdate
* Result: BOOL
*       
* Effect: 
*       Initializes controls
****************************************************************************/

void CRaster::OnInitialUpdate()                                 // REQ #054
   {
    CFormView::OnInitialUpdate();                               // REQ #054
        
    CheckRadioButton(IDC_RASTER, IDC_TRUETYPE, IDC_RASTER);

    c_Text.SetWindowText(_T("Wx"));
        
    f.CreatePointFont(80, _T("MS Sans Serif"));                 // REQ #049

    //for(CWnd * wnd = GetWindow(GW_CHILD); wnd != NULL; wnd = GetWindow(GW_HWNDNEXT)) // REQ #049
    //   wnd->SetFont(&f);                                        // REQ #049
    CWnd * wnd = GetWindow(GW_CHILD);
    wnd->SetFont(&f);

    CRect r;
    GetClientRect(&r);
    CRect sample;
    sample.right = r.right;
    sample.bottom = r.bottom;
    c_Sample.SetWindowPos(NULL, 0, 0, r.Width(), r.Height(), SWP_NOMOVE | SWP_NOZORDER);

    CString s;                                                      // REQ #052
    s.LoadString(IDS_RASTER_EXPLORER_CAPTION);                      // REQ #061
    GetParentFrame()->SetWindowText(s);                             // REQ #061

    c_Text.GetWindowText(s);                                        // REQ #052
    c_Sample.SetWindowText(s);                                      // REQ #052

    c_SpinScaledHeight.SetRange(1,512);                             // REQ #052
    c_SpinScaledHeight.SetPos(8);                                   // REQ #052

    /***************************************************************
                  +--- c_FontSize
                  |
                  V
      +----------++---------+-+
      |  Height  || dropdown|V|
      +----------++---------+-+

                  +----------------- c_ScaledHeight
                  |        +-------- c_SpinScaledHeight
                  |        |
                  V        V
      +----------++--------+-+
      |  Height  || edit   |^|
      +----------++--------+-+

    ***************************************************************/
    CRect fontsize;
    c_FontSize.GetWindowRect(&fontsize);
    ScreenToClient(&fontsize);

    CRect scaledheight;
    c_ScaledHeight.GetWindowRect(&scaledheight);
    ScreenToClient(&scaledheight);

    CRect spinscaledheight;
    c_SpinScaledHeight.GetWindowRect(&spinscaledheight);
    ScreenToClient(&spinscaledheight);

    CRect newscaledheight;
    CPoint newscaledpos;
    newscaledpos.x = fontsize.left;
    newscaledpos.y = fontsize.top;

    c_ScaledHeight.SetWindowPos(NULL, newscaledpos.x, newscaledpos.y,
                                0, 0,
                                SWP_NOZORDER | SWP_NOSIZE);

    CPoint newspinscaledpos;
    newspinscaledpos.x = fontsize.left + fontsize.Width(); // + (spinscaledheight.left - scaledheight.right);
    newspinscaledpos.y = newscaledpos.y;

    c_SpinScaledHeight.SetWindowPos(NULL, newspinscaledpos.x, newspinscaledpos.y,
                                    0, 0,
                                    SWP_NOZORDER | SWP_NOSIZE);

    c_SpinMultiplier.SetPos(1);                                     // REQ #052

    c_Quality.AddStrings(qualities, DEFAULT_QUALITY);               // REQ #071

    c_Copy.LoadBitmaps(IDB_COPY);                                   

    initialized = TRUE;

    GetParentFrame()->RecalcLayout();                               // REQ #062
    ResizeParentToFit(FALSE);                                       // REQ #062
    
    updateControls();                                               // REQ #052

    OnRaster();
   }

/****************************************************************************
*                               ::loadFontSizes
* Inputs:
*       const LOGFONT * lf: LOGFONT for current font
*       const TEXTMETRIC * tm: TEXTMETRIC
*       DWORD type:
*       LPARAM lParam: (LPARAM)(CRaster *)
* Result: int
*       TRUE to continue enumeration
*       FALSE to stop enumeration
* Effect: 
*       Loads up the size combo given the font has been selected
****************************************************************************/

int CALLBACK CRaster::loadFontSizes(const LOGFONT * lf, const TEXTMETRIC * tm, DWORD type, LPARAM lParam ) // REQ #051
    {
     CRaster * wnd = (CRaster *)lParam;

     CString s;
     s.Format(_T("%3d"), lf->lfHeight);
     int index = wnd->c_FontSize.AddString(s);
     wnd->c_FontSize.SetItemData(index, lf->lfHeight);

     return TRUE;
    }


/****************************************************************************
*                           CRaster::OnSelendokFonts
* Result: void
*       
* Effect: 
*       THe font changed; reflect this to the controls
****************************************************************************/

void CRaster::OnSelendokFonts() 
{
 loadFontSizes();

 setNewFont();
}

/****************************************************************************
*                             CRaster::loadFontSizes
* Result: void
*       
* Effect: 
*       Loads the font size dropdown
****************************************************************************/

void CRaster::loadFontSizes()
    {
     // load the font size control

     CString s;
     c_Fonts.GetWindowText(s);

     c_FontSize.ResetContent();

     CClientDC dc(this);
     EnumFonts(dc.m_hDC, s, &CRaster::loadFontSizes, (LPARAM)this); // REQ #051

     c_FontSize.SetCurSel(0);
     
    }

/****************************************************************************
*                             CRaster::setNewFont
* Result: void
*       
* Effect: 
*       Creates a new font and sets it in the display window
****************************************************************************/

void CRaster::setNewFont()
    {
     if(!initialized)
        return;

     CString newname;

     c_Fonts.GetWindowText(newname);  // get new font name

     CFont * font = c_Sample.GetFont();

     if(font == NULL)                                               // REQ #052
         font = CFont::FromHandle((HFONT)::GetStockObject(SYSTEM_FONT));// REQ #052
                                                                    // REQ #052
     LOGFONT lf;                                                    // REQ #052
     font->GetLogFont(&lf);                                         // REQ #052
     lf.lfWidth = 0;                                                // REQ #052

     int size;
     if(c_Raster.GetCheck() == BST_CHECKED)                         // REQ #052
        { /* raster */                                              // REQ #052
         size = (int)c_FontSize.GetItemData(c_FontSize.GetCurSel());// REQ #006// REQ #052
        } /* raster */                                              // REQ #052
     else                                                           // REQ #052
        { /* scaled */                                              // REQ #052
         size = (int)c_SpinScaledHeight.GetPos32();                 // REQ #052
        } /* scaled */                                              // REQ #052

     BYTE newquality = (BYTE)c_Quality.GetItemData(c_Quality.GetCurSel());// REQ #071

     if(lstrcmp(lf.lfFaceName, newname) != 0 || size != lf.lfHeight ||
        lf.lfQuality != newquality)                                 // REQ #071
        { /* need new font */
         lf.lfHeight = size;
         lstrcpy(lf.lfFaceName, newname);

         lf.lfQuality = newquality;                                 // REQ #071

         CFont newfont;
         if(newfont.CreateFontIndirect(&lf))
            { /* success */
             c_Sample.SetFont(&newfont);
             c_Unmagnified.SetFont(&newfont);                       // REQ #052
             c_Sample.Invalidate();                                 // REQ #071
             c_Unmagnified.Invalidate();                            // REQ #071
             TRACE(_T(__FUNCTION__) _T(": DeleteObject(font=%p)\n"), font->m_hObject);// REQ #021
             font->DeleteObject();
             newfont.Detach();

             CRect client;                                          // REQ #050
             GetClientRect(&client);                                // REQ #050
             AdjustWindowSize(client.Width(), client.Height());     // REQ #050
            } /* success */
        } /* need new font */
    }

/****************************************************************************
*                         CRaster::OnChangeMultiplier
* Result: void
*       
* Effect: 
*       Sets the multiplier in the display container
****************************************************************************/

void CRaster::OnChangeMultiplier() 
   {
    if(!initialized)                                                // REQ #052
        return;                                                     // REQ #052
    int x = c_SpinMultiplier.GetPos32();                            // REQ #052
    c_Sample.SetMultiplier(x);                                      // REQ #052
   }

/****************************************************************************
*                         CRaster::OnSelendokFontSize
* Result: void
*       
* Effect: 
*       Updates the font
****************************************************************************/

void CRaster::OnSelendokFontSize() 
   {
    setNewFont();
   }

/****************************************************************************
*                               CRaster::OnCopy
* Result: void
*       
* Effect: 
*       Copies the sample bitmap to the clipboard
****************************************************************************/

void CRaster::OnCopy() 
   {
    CClientDC wdc(&c_Sample);  // get static control that surrounds example

    CDC memDC;

    memDC.CreateCompatibleDC(&wdc);

    CBitmap bm;
    CRect r;
 
    c_Sample.GetClientRect(&r);

    CString s;
    c_Sample.GetWindowText(s);

    CFont * font = c_Sample.GetFont();

    wdc.SelectObject(font);

    CSize sz = wdc.GetTextExtent(s);

    int scale = 1;                                                  // REQ #050
    if(c_EnableScaling.GetCheck() == BST_CHECKED)                   // REQ #050
       { /* scaled */                                               // REQ #050
        scale = c_SpinMultiplier.GetPos32();                        // REQ #050
       } /* scaled */                                               // REQ #050

    sz.cx *= scale;                                                 // REQ #050
    sz.cy *= scale;                                                 // REQ #050

    bm.CreateCompatibleBitmap(&wdc, sz.cx, sz.cy);
 
    CBitmap * oldbm = memDC.SelectObject(&bm);
 
    memDC.BitBlt(0, 0, sz.cx * scale, sz.cy * scale, &wdc, 0, 0, SRCCOPY);// REQ #050

    OpenClipboard();
    ::EmptyClipboard();
    ::SetClipboardData(CF_BITMAP, bm.m_hObject);
    CloseClipboard();

    memDC.SelectObject(oldbm);
    bm.Detach();  // make sure bitmap not deleted with CBitmap object
   }

/****************************************************************************
*                            CRaster::loadFontSet
* Result: void
*       
* Effect: 
*       Loads the font set based on the current radio button selection
****************************************************************************/

void CRaster::loadFontSet()
   {
    if(c_Raster.GetCheck())
       fontmask = RASTER_FONTTYPE;
    else
    if(c_Vector.GetCheck())
       fontmask = (DWORD)-1;
    else
       fontmask = TRUETYPE_FONTTYPE;


    c_Fonts.ResetContent();

    CClientDC dc(&c_Sample);
    ::EnumFontFamilies(dc.m_hDC, NULL, &CRaster::loadFontProc, (LPARAM)this); // REQ #051
     
    c_Fonts.SetCurSel(0);

//    
        
    c_FontSize.SetCurSel(0);

    loadFontSizes();

    setNewFont();
   }

/****************************************************************************
*                              CRaster::OnRaster
* Result: void
*       
* Effect: 
*       Updates the window
****************************************************************************/

void CRaster::OnRaster() 
{
 CString s;
 s.LoadString(IDS_RASTERFONTS);
 SetWindowText(s);

 c_SpinMultiplier.SetRange(1, RASTER_MAX_MULTIPLIER);

 loadFontSet();

 updateControls();
}

/****************************************************************************
*                             CRaster::OnTruetype
* Result: void
*       
* Effect: 
*       Updates the controls
****************************************************************************/

void CRaster::OnTruetype() 
   {
    CString s;
    s.LoadString(IDS_TRUETYPEFONTS);
    SetWindowText(s);

    c_SpinMultiplier.SetRange(1, TRUETYPE_MAX_MULTIPLIER);
    c_SpinMultiplier.SetPos(14);

    loadFontSet();

    updateControls();
   }

/****************************************************************************
*                              CRaster::OnVector
* Result: void
*       
* Effect: 
*       Updates the controls
****************************************************************************/

void CRaster::OnVector() 
   {
    CString s;
    s.LoadString(IDS_VECTORFONTS);
    SetWindowText(s);

    c_SpinMultiplier.SetRange(1, VECTOR_MAX_MULTIPLIER);

    updateControls();

    loadFontSet();
   }

/****************************************************************************
*                      CRaster::OnGetMinMaxInfo
* Inputs:
*       MINMAXINFO * lpMMI:
* Result: void
*       
* Effect: 
*       Prevents resizing the dialog to hide any controls
****************************************************************************/

void CRaster::OnGetMinMaxInfo(MINMAXINFO* lpMMI)                    // REQ #050
   {                                                                // REQ #050
    if(c_Frame.GetSafeHwnd() != NULL)                               // REQ #050
       { /* can limit */                                            // REQ #050
        CRect r;                                                    // REQ #050
        c_Frame.GetWindowRect(&r);                                  // REQ #050
        ScreenToClient(&r);                                         // REQ #050
        CalcWindowRect(&r);                                         // REQ #050
        lpMMI->ptMinTrackSize.x = r.Width();                        // REQ #050
        lpMMI->ptMinTrackSize.y = r.Height();                       // REQ #050
        return;                                                     // REQ #050
       } /* can limit */                                            // REQ #050
    CFormView::OnGetMinMaxInfo(lpMMI);                              // REQ #050// REQ #054
   } // CRaster::OnGetMinMaxInfo                                    // REQ #050

/****************************************************************************
*                          CRaster::OnSize
* Inputs:
*       UINT nType: Sizing type
*       int cx: New client width
*       int cy: New client height
* Result: void
*       
* Effect: 
*       Resizes the child controls
****************************************************************************/

void CRaster::OnSize(UINT nType, int cx, int cy)                    // REQ #050
   {                                                                // REQ #050
    CFormView::OnSize(nType, cx, cy);                               // REQ #050// REQ #054
                                                                    // REQ #050
    if(c_Unmagnified.GetSafeHwnd() != NULL &&                       // REQ #050
       c_Sample.GetSafeHwnd() != NULL)                              // REQ #050
       { /* resize sample */                                        // REQ #050
        AdjustWindowSize(cx, cy);                                   // REQ #052
       } /* resize sample */                                        // REQ #050
   }                                                                // REQ #050

/****************************************************************************
*                          CRaster::AdjustWindowSize
* Inputs:
*       int cx: Client width
*       int cy: Client height
* Result: void
*       
* Effect: 
*       Resizes the font windows
****************************************************************************/

void CRaster::AdjustWindowSize(int cx, int cy)                      // REQ #050
    {                                                               // REQ #050
     CRect unmag;                                                   // REQ #050
     c_Unmagnified.GetWindowRect(&unmag);                           // REQ #050
     ScreenToClient(&unmag);                                        // REQ #050
                                                                    // REQ #050
     CClientDC dc(&c_Unmagnified);                                  // REQ #050
     CFont * f = c_Unmagnified.GetFont();                           // REQ #050
     dc.SelectObject(f);                                            // REQ #050
     CSize sz = dc.GetTextExtent(_T("Xy"));                         // REQ #050
                                                                    // REQ #050
     int h = sz.cy + 2 * ::GetSystemMetrics(SM_CXBORDER);           // REQ #050
                                                                    // REQ #050
     c_Unmagnified.SetWindowPos(NULL,                               // REQ #050
                                0, 0,                               // REQ #050
                                cx - unmag.left,                    // REQ #050
                                h,                                  // REQ #050
                                SWP_NOMOVE | SWP_NOZORDER);         // REQ #050
                                                                    // REQ #050
     CRect r;                                                       // REQ #050
     c_Sample.GetWindowRect(&r);                                    // REQ #050
     ScreenToClient(&r);                                            // REQ #050
                                                                    // REQ #050
     c_Sample.SetWindowPos(NULL,                                    // REQ #050
                           r.left,                                  // REQ #050
                           h,                                       // REQ #050
                           cx - r.left,                             // REQ #050
                           cy - h,                                  // REQ #050
                           SWP_NOZORDER);                           // REQ #050
    } // CRaster::AdjustWindowSize                                  // REQ #050

/****************************************************************************
*                           CRaster::updateControls
* Result: void
*       
* Effect: 
*       Update contols
****************************************************************************/

void CRaster::updateControls()                                                 // REQ #052
    {                                                                          // REQ #052
     c_SpinMultiplier.EnableWindow(c_EnableScaling.GetCheck() == BST_CHECKED); // REQ #052
     c_Multiplier.EnableWindow(c_EnableScaling.GetCheck() == BST_CHECKED);     // REQ #052
     c_c_Multiplier.EnableWindow(c_EnableScaling.GetCheck() == BST_CHECKED);   // REQ #052
     c_Sample.SetGrid(c_ShowGrid.GetCheck() == BST_CHECKED);                   // REQ #052
                                                                    // REQ #052
     if(c_Raster.GetCheck() == BST_CHECKED)                         // REQ #052
        { /* raster */                                              // REQ #052
         c_FontSize.ShowWindow(SW_SHOW);                            // REQ #052
         c_ScaledHeight.ShowWindow(SW_HIDE);                        // REQ #052
         c_SpinScaledHeight.ShowWindow(SW_HIDE);                    // REQ #052
        } /* raster */                                              // REQ #052
     else                                                           // REQ #052
        { /* scaled */                                              // REQ #052
         c_FontSize.ShowWindow(SW_HIDE);                            // REQ #052
         c_ScaledHeight.ShowWindow(SW_SHOW);                        // REQ #052
         c_SpinScaledHeight.ShowWindow(SW_SHOW);                    // REQ #052
        } /* scaled */                                              // REQ #052
     c_Quality.EnableWindow(c_TrueType.GetCheck() == BST_CHECKED);  // REQ #071
    } // CRaster::updateControls                                    // REQ #052

/****************************************************************************
*                      CRaster::OnBnClickedEnableScaling
* Result: void
*       
* Effect: 
*       Updates controls
****************************************************************************/

void CRaster::OnBnClickedEnableScaling()                            // REQ #052
    {                                                               // REQ #052
     updateControls();                                              // REQ #052
     if(c_EnableScaling.GetCheck() == BST_CHECKED)                  // REQ #052
        { /* scaling */                                             // REQ #052
         c_Sample.SetMultiplier(c_SpinMultiplier.GetPos32());       // REQ #052
        } /* scaling */                                             // REQ #052
     else                                                           // REQ #052
        { /* no scaling */                                          // REQ #052
         c_Sample.SetMultiplier(1);                                 // REQ #052
        } /* no scaling */                                          // REQ #052
    } // CRaster::OnBnClickedEnableScaling                          // REQ #052

/****************************************************************************
*                        CRaster::OnBnClickedShowGrid
* Result: void
*       
* Effect: 
*       Updates the controls
****************************************************************************/

void CRaster::OnBnClickedShowGrid()                                 // REQ #052
    {                                                               // REQ #052
     updateControls();                                              // REQ #052
    } // CRaster::OnBnClickedShowGrid                               // REQ #052

/****************************************************************************
*                        CRaster::OnChangeScaledHeight
* Result: void
*       
* Effect: 
*       Updates the display
****************************************************************************/

void CRaster::OnChangeScaledHeight()                                // REQ #052
    {                                                               // REQ #052
     setNewFont();                                                  // REQ #052
    } // CRaster::OnChangeScaledHeight                              // REQ #052

/****************************************************************************
*                      CRaster::OnSelendOkQuality
* Result: void
*       
* Effect: 
*       Updates font display
****************************************************************************/

void CRaster::OnSelendOkQuality()                                   // REQ #071
    {                                                               // REQ #071
     setNewFont();                                                  // REQ #071
    } // CRaster::OnSelendOkQuality                                 // REQ #071

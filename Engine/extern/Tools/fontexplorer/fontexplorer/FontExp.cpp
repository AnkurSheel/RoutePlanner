/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 23-Apr-08 | Created
* 23-Apr-08 | REQ #006: Changes required for 64-bit compatibility
* 24-Apr-08 | REQ #008: Removed fontexplorer.h
* 24-Apr-08 | REQ #010: Made options a protected member of CFontDisplay
* 24-Apr-08 | REQ #042: Unicode conversion
* 15-Oct-08 | REQ #043: Replace CDC * with CDC & for cleaner code
* 22-Oct-08 | REQ #070: Moved all options onto this dialog, eliminated Options dialog
* 22-Oct-08 | REQ #071: Handle font smoothing
* 22-Oct-08 | REQ #073: Allow pair kerning only for fonts with kerning pairs
*  1-Nov-08 | REQ #080: FontDisp.h => FontDisplay.h
*  2-Nov-08 | REQ #081: Changed name from TEXTOUTEX to EXTTEXTOUT_
*  2-Nov-08 | REQ #082: Update font information from OnInitDialog
*****************************************************************************/
// FontExp.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"                                               // REQ #008
#include "dlgs.h"
#include "fontdesc.h"
#include "legendi.h"
#include "legend.h"
#include "dispopts.h"
#include "poplist.h"
//#include "fontmet.h"  // REQ #088
#include "fontdisplay.h"                                            // REQ #080
#include "fontexp.h"
#include "logfont.h"
#include "tm.h"
#include "kp.h"
#include "otm.h"
#include "chformat.h"
#include "abc.h"
#include "toclip.h"
#include "subclass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFontExplorer

CFontExplorer * CFontExplorer::self;

IMPLEMENT_DYNAMIC(CFontExplorer, CFontDialog)

#define LOWKERN  -20                                                // REQ #001// REQ #070
#define HIKERN   20                                                 // REQ #001// REQ #070


/****************************************************************************
*                        CFontExplorer::CFontExplorer
* Inputs:
*       LPLOGFONT lplfInitial:
*       DWORD dwFlags:
*       CDC * pdcPrinter:
*       CWnd * pParentWnd:
* Effect: 
*       Constructor of subclass of CFontDialog
****************************************************************************/

CFontExplorer::CFontExplorer(LPLOGFONT lplfInitial, DWORD dwFlags, CDC* pdcPrinter, CWnd* pParentWnd) : 
        CFontDialog(lplfInitial, dwFlags, pdcPrinter, pParentWnd)
{
 self = this;
 hook = NULL;
 debug = FALSE;
 initialized = FALSE;                                               // REQ #066
        //{{AFX_DATA_INIT(CFontExplorer)
        //}}AFX_DATA_INIT
}


/****************************************************************************
*                        CFontExplorer::DoDataExchange
* Inputs:
*       CDataExchnage * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CFontExplorer::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CFontExplorer)
        DDX_Control(pDX, IDC_TREEMETRICS, c_TreeMetrics);
        DDX_Control(pDX, IDC_c_LEGEND, c_c_Legend);
        DDX_Control(pDX, IDC_LEGEND, c_Legend);
        DDX_Control(pDX, stc5, c_SmallSample);
        DDX_Control(pDX, IDC_CHARDISPLAY, c_CharDisplay);
        DDX_Control(pDX, IDC_CHAR, c_Char);
        DDX_Control(pDX, IDC_INFO, c_Info);
        DDX_Control(pDX, IDC_GM_ADVANCED, c_Advanced);              // REQ #035
        DDX_Control(pDX, IDC_SAMPLE_BORDER, c_Border);              // REQ #036
        DDX_Control(pDX, IDC_DISPLAY_FRAME, c_Frame);               // REQ #036
        DDX_Control(pDX, IDC_MINMAXINFO_FRAME, c_MinMaxInfoFrame);  // REQ #036
        DDX_Control(pDX, IDC_DEBUG, c_Debug);                       // REQ #035
        DDX_Control(pDX, IDC_SHOW_KERNING_MAP, c_ShowKerningMap);   // REQ #041
        DDX_Control(pDX, IDC_KERNMAP, c_KerningMap);                // REQ #041
        DDX_Control(pDX, IDC_OVERLAY_X, c_OverlayX);                // REQ #066
        DDX_Control(pDX, IDC_OVERLAY_Y, c_OverlayY);                // REQ #066
        DDX_Control(pDX, IDC_SPIN_OVERLAY_X, c_SpinOverlayX);       // REQ #066
        DDX_Control(pDX, IDC_SPIN_OVERLAY_Y, c_SpinOverlayY);       // REQ #066
        DDX_Control(pDX, IDC_SHOW_PIXELS, c_ShowPixels);            // REQ #066
        DDX_Control(pDX, IDC_SHOW_OVERLAY, c_ShowOverlay);          // REQ #066
        DDX_Control(pDX, IDC_OVERLAY_CAPTION, x_Overlay);           // REQ #066
        DDX_Control(pDX, IDC_SPIN_TRACK_KERN, c_SpinTrackKern);     // REQ #070
        DDX_Control(pDX, IDC_TRACK_KERN, c_TrackKern);              // REQ #070
                                                                    //        DDX_Control(pDX, IDC_SAMPLE, c_Sample);                     // REQ #070
                                                                    //        DDX_Control(pDX, IDC_SMALLSAMPLE, c_SmallSample);           // REQ #042// REQ #070
        DDX_Control(pDX, IDC_NONE, c_None);                         // REQ #011// REQ #070
        DDX_Control(pDX, IDC_TEXTOUT, c_TextOut);                   // REQ #011// REQ #070
        DDX_Control(pDX, IDC_EXTTEXTOUT, c_ExtTextOut);             // REQ #011// REQ #070
        DDX_Control(pDX, IDC_IGNOREABC, c_IgnoreABC);               // REQ #031// REQ #070
        DDX_Control(pDX, IDC_HRULE, c_HRule);                       // REQ #070
        DDX_Control(pDX, IDC_VRULE, c_VRule);                       // REQ #070
        DDX_Control(pDX, IDC_CHRULE, c_CHRule);                     // REQ #070
        DDX_Control(pDX, IDC_TRACK, c_Track);                       // REQ #070
        DDX_Control(pDX, IDC_FONT_SMOOTHING, c_Smoothing);          // REQ #071
        DDX_Control(pDX, IDC_PAIR, c_Pair);                         // REQ #070
        DDX_Control(pDX, IDC_WHITE, c_White);                       // REQ #070
        DDX_Control(pDX, IDC_COLORS, c_Colors);                     // REQ #070
        DDX_Control(pDX, IDC_SAMPLE, c_Sample);                     // REQ #070
        //}}AFX_DATA_MAP
}

/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CFontExplorer, CFontDialog)
        ON_BN_CLICKED(IDC_NONE, OnBnClickedNone)                    // REQ #070
        ON_BN_CLICKED(IDC_TEXTOUT, OnBnClickedTextOut)              // REQ #070
        ON_BN_CLICKED(IDC_EXTTEXTOUT, OnBnClickedExtTextOut)        // REQ #070
        ON_BN_CLICKED(IDC_IGNOREABC, OnBnClickedIgnoreABC)          // REQ #070
        ON_BN_CLICKED(IDC_HRULE, OnBnClickedHRule)                  // REQ #070
        ON_BN_CLICKED(IDC_VRULE, OnBnClickedVRule)                  // REQ #070
        ON_BN_CLICKED(IDC_CHRULE, OnBnClickedCHRule)                // REQ #070
        ON_BN_CLICKED(IDC_TRACK, OnBnClickedTrack)                  // REQ #070
        ON_BN_CLICKED(IDC_PAIR, OnBnClickedPair)                    // REQ #070
        ON_BN_CLICKED(IDC_FONT_SMOOTHING, OnBnClickedFontSmoothing) // REQ #071
        ON_BN_CLICKED(IDC_DEBUG, OnBnClickedDebug)                  // REQ #035
        ON_BN_CLICKED(IDC_INFO, OnInfo)
        ON_BN_CLICKED(IDC_CHAR, OnChar)
        ON_BN_CLICKED(IDC_COPY, OnCopy)
        ON_WM_DESTROY()
        ON_BN_CLICKED(IDC_GM_ADVANCED, OnBnClickedAdvanced)         // REQ #035
        ON_BN_CLICKED(IDC_SHOW_KERNING_MAP, OnShowKerningMap)       // REQ #041
        ON_WM_GETMINMAXINFO()                                       // REQ #036
        ON_WM_SIZE()                                                // REQ #036
        ON_WM_CLOSE()                                               // REQ #068
        ON_MESSAGE(UWM_UPDATE_FONTS, OnUpdateFonts)
        ON_BN_CLICKED(IDOK, OnBnClickedOK)                          // REQ #068
        ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)                  // REQ #068
        ON_BN_CLICKED(IDC_SHOW_OVERLAY, OnBnClickedShowOverlay)     // REQ #066
        ON_BN_CLICKED(IDC_SHOW_PIXELS, OnBnClickedShowPixels)       // REQ #066
        ON_EN_CHANGE(IDC_OVERLAY_X, OnChangeOverlayX)               // REQ #066
        ON_EN_CHANGE(IDC_OVERLAY_Y, OnChangeOverlayY)               // REQ #066
        ON_EN_CHANGE(IDC_TRACK_KERN, OnChangeTrackKern)             // REQ #070
        ON_BN_CLICKED(IDC_WHITE, OnBnClickedWhite)                  // REQ #070
        ON_BN_CLICKED(IDC_COLORS, OnBnClickedColors)                // REQ #070
        ON_EN_CHANGE(IDC_SAMPLE, OnChangeSample)                    // REQ #070
END_MESSAGE_MAP()

// Ideally, we would like to have these handlers enabled.  But because
// Microsoft cannot read their own documentation, they carefully designed
// MFC so that it cannot be used to subclass common dialogs effectively.
// If we process these messages, then the common dialog handler will NOT do
// its proper handling, so we can't actually "subclass" the common dialog
// as we want to! 
//
// Take as given that we are *really* trying to implement the following
// message map entries in spite of Microsoft's inability to get their design
// right! (Caused, apparently, by a failure to read their own documentation
// and realize that the return value MUST be specifiable by the programmer!)

// Unfortunately, the common dialogs in Win95 and WinNT4.0 do not actually
// send the undocumented message that WinNT3.51 versions sent, indicating
// that the font selection had changed.  This design error, failing to provide
// the subclass with such a notification, is a serious design oversight on
// the part of Microsoft and necessitates all this ugly hackery.

// See the file subclass.cpp in which we subclass the window in a fairly
// primitive way.

        // ON_CBN_SELCHANGE(cmb1, OnSelchangecmb1)
        // ON_CBN_SELCHANGE(cmb2, OnSelchangecmb2)
        // ON_CBN_SELCHANGE(cmb3, OnSelchangecmb3)
        // ON_CBN_SELCHANGE(cmb4, OnSelchangecmb4)
        // ON_CBN_SELCHANGE(cmb5, OnSelchangecmb5)
        // ON_BN_CLICKED(chx1, Onchx1)
        // ON_BN_CLICKED(chx2, Onchx2)

/****************************************************************************
*                        CFontExplorer::loadWidths
* Result: void
*       
* Effect: 
*       Adds the ABCWidths info to the dropdown list
****************************************************************************/

void CFontExplorer::loadWidths(CFontDescriptor * desc)
    {
     CString s;
     CString smp;
     int i;

     c_CharDisplay.GetWindowText(smp);
     s.LoadString(IDS_WIDTHS);

     HTREEITEM wd = c_TreeMetrics.InsertItem(s);

     s.Format(_T("GetTextExtentPoint32"));
     HTREEITEM te = c_TreeMetrics.InsertItem(s, wd);

     SIZE sz = desc->dc->GetTextExtent(smp);
     s.Format(_T("cx %d"), sz.cx);
     c_TreeMetrics.InsertItem(s, te);
     s.Format(_T("cy %d"), sz.cy);
     c_TreeMetrics.InsertItem(s, te);

     for(i = 0; i < smp.GetLength(); i++)
        { /* add each */
         charFormat(s, smp[i]);
         HTREEITEM charwd = c_TreeMetrics.InsertItem(s, te);

         // Note the following clumsy construction because &smp[i]
         // gets a compilation error:
         TCHAR c[2];
         c[0] = smp[i];
         c[1] = _T('\0');
         sz = desc->dc->GetTextExtent(c, 1);
         s.Format(_T("cx %d"), sz.cx);
         c_TreeMetrics.InsertItem(s, charwd);
         s.Format(_T("cy %d"), sz.cy);
         c_TreeMetrics.InsertItem(s, charwd);
        } /* add each */

     loadABCWidths(*desc->dc, smp, &c_TreeMetrics, wd);// REQ #043
    }

/****************************************************************************
*                        CFontExplorer::updateFontInfo
* Result: void
*       
* Effect: 
*       Updates all the font info
****************************************************************************/

void CFontExplorer::updateFontInfo()
    {
     if(!initialized)                                               // REQ #070
         return;                                                    // REQ #070
     display_options opts = c_CharDisplay.GetOpts();                // REQ #070

     CFontDescriptor desc(this, this, c_Advanced.GetCheck() == BST_CHECKED, opts.quality);// REQ #035// REQ #071
     c_TreeMetrics.DeleteAllItems();

     // We can't subclass the control because it must be handled
     // as an owner-draw control by the common dialog.
     int sel = (int)GetDlgItem(cmb4)->SendMessage(CB_GETCURSEL);    // REQ #006
     COLORREF c = (COLORREF)GetDlgItem(cmb4)->SendMessage(CB_GETITEMDATA, sel); // REQ #006
     c_CharDisplay.color = c;
     
     if(c_Advanced.GetCheck() == BST_CHECKED)                       // REQ #035
        c_TreeMetrics.InsertItem(_T("GM_ADVANCED"));                // REQ #035
     else                                                           // REQ #035
        c_TreeMetrics.InsertItem(_T("GM_COMPATIBLE"));              // REQ #035
     
     loadTextMetrics(&desc.tm, &c_TreeMetrics);
     if(desc.otm != NULL)
        loadOutlineTextMetrics(desc.otm, &c_TreeMetrics);
     loadLogFont(&desc.lf, &c_TreeMetrics, FALSE);
     loadWidths(&desc);
     loadKerningPairs(*desc.dc, &c_TreeMetrics);
     c_CharDisplay.InvalidateRect(NULL, TRUE);
     c_KerningMap.SetFontInfo(desc);                                // REQ #041


     DWORD flags = desc.GetFontLanguageInfo();                      // REQ #073
     c_Pair.EnableWindow( (flags & GCP_USEKERNING) != 0);           // REQ #073
    }                                                               // REQ #070

/****************************************************************************
*                        CFontExplorer::OnFontChanged
* Inputs:
*       WPARAM wParam: ignored but sent to parent
*       LPARAM lParam: ignored but sent to parent
* Result: LRESULT
*       FALSE, always, indicating that the parent should process this
* Effect: 
*       Allows us to intercept all font changes and change the display
****************************************************************************/

//LRESULT CFontExplorer::OnFontChanged(WPARAM wParam, LPARAM lParam)
//    {
//     updateFontInfo();
//     return FALSE;
//    }

/****************************************************************************
*                        CFontExplorer::updateOptions
* Result: void
*       
* Effect: 
*       Updates the display options
****************************************************************************/

void CFontExplorer::updateOptions()                                 // REQ #070
    {                                                               // REQ #070
     if(!initialized)                                               // REQ #070
        return;                                                     // REQ #070
     display_options opts = c_CharDisplay.GetOpts();                // REQ #066
     opts.ShowPixels = c_ShowPixels.GetCheck() == BST_CHECKED;      // REQ #066
     opts.ShowOverlay = c_ShowOverlay.GetCheck() == BST_CHECKED;    // REQ #066
     opts.OverlayX = c_SpinOverlayX.GetPos32();                     // REQ #066
     opts.OverlayY = c_SpinOverlayY.GetPos32();                     // REQ #066
                                                                    // REQ #070
     opts.track = c_Track.GetCheck() == BST_CHECKED;                // REQ #070
     opts.trackval = c_SpinTrackKern.GetPos32();                    // REQ #070
                                                                    // REQ #070
     opts.quality = c_Smoothing.GetCheck() == BST_CHECKED ? DEFAULT_QUALITY : NONANTIALIASED_QUALITY;// REQ #071
                                                                    // REQ #070
     opts.vrule = c_VRule.GetCheck() == BST_CHECKED;                // REQ #070
     opts.hrule = c_HRule.GetCheck() == BST_CHECKED;                // REQ #070
     opts.chrule = c_CHRule.GetCheck() == BST_CHECKED;              // REQ #070
                                                                    // REQ #070
     if(c_None.GetCheck() == BST_CHECKED)                           // REQ #070
        opts.output = display_options::NONE;                        // REQ #070
     else                                                           // REQ #070
     if(c_TextOut.GetCheck() == BST_CHECKED)                        // REQ #070
        opts.output = display_options::TEXTOUT;                     // REQ #070
     else                                                           // REQ #070
     if(c_ExtTextOut.GetCheck() == BST_CHECKED)                     // REQ #070
        opts.output = display_options::EXTTEXTOUT_;                 // REQ #070// REQ #081
     else                                                           // REQ #070
     if(c_IgnoreABC.GetCheck() == BST_CHECKED)                      // REQ #070
        opts.output = display_options::IGNOREABC;                   // REQ #070
     else                                                           // REQ #070
        { /* unknown */                                             // REQ #070
         opts.output = display_options::TEXTOUT;                    // REQ #070
         CheckRadioButton(IDC_NONE, IDC_IGNOREABC, IDC_TEXTOUT);    // REQ #070
        } /* unknown */                                             // REQ #070
                                                                    // REQ #070
     opts.ShowOverlay = c_ShowOverlay.GetCheck() == BST_CHECKED;    // REQ #066
     opts.ShowPixels = c_ShowPixels.GetCheck() == BST_CHECKED;      // REQ #066
                                                                    // REQ #066
     opts.colors = c_Colors.GetCheck() == BST_CHECKED;              // REQ #070
     opts.white  = c_White.GetCheck() == BST_CHECKED;               // REQ #070

     opts.kerning = c_Pair.IsWindowEnabled() && c_Pair.GetCheck() == BST_CHECKED; // REQ #070

     c_CharDisplay.SetOpts(opts);                                   // REQ #066
    } // CFontExplorer::updateOptions                               // REQ #070

/****************************************************************************
*                        CFontExplorer.updateControls
* Result: void
*       
* Effect: 
*       Updates all the controls
****************************************************************************/

void CFontExplorer::updateControls()
    {
     if(!initialized)                                               // REQ #066
        return;                                                     // REQ #066

     if(c_Info.GetCheck() == BST_CHECKED)                           // REQ #037
        { /* info display */
         c_TreeMetrics.ShowWindow(SW_SHOW);
         c_CharDisplay.ShowWindow(SW_HIDE);
         c_KerningMap.ShowWindow(SW_HIDE);                          // REQ #041
         c_Legend.ShowWindow(SW_HIDE);
         c_c_Legend.ShowWindow(SW_HIDE);
        } /* info display */
     else
     if(c_Char.GetCheck() == BST_CHECKED)                           // REQ #037
        { /* char display */
         c_TreeMetrics.ShowWindow(SW_HIDE);
         c_CharDisplay.ShowWindow(SW_SHOW);
         c_KerningMap.ShowWindow(SW_HIDE);                          // REQ #041
         c_Legend.ShowWindow((c_CharDisplay.GetUseColors() ? SW_SHOW : SW_HIDE));   // REQ #010
         c_c_Legend.ShowWindow((c_CharDisplay.GetUseColors() ? SW_SHOW : SW_HIDE)); // REQ #010
        } /* char display */
     else                                                           // REQ #041
     if(c_ShowKerningMap.GetCheck() == BST_CHECKED)                 // REQ #041
        { /* kern map */                                            // REQ #041
         c_TreeMetrics.ShowWindow(SW_HIDE);                         // REQ #041
         c_CharDisplay.ShowWindow(SW_HIDE);                         // REQ #041
         c_KerningMap.ShowWindow(SW_SHOW);                          // REQ #041
        } /* kern map */                                            // REQ #041
                                                                    // REQ #066
     updateOptions();                                               // REQ #070
                                                                    // REQ #066
     display_options opts = c_CharDisplay.GetOpts();                // REQ #066
     BOOL overlay = opts.output == display_options::TEXTOUT ||      // REQ #066
                    opts.output == display_options::EXTTEXTOUT_;    // REQ #066// REQ #081
     overlay = TRUE;                                                // REQ #066
     x_Overlay.EnableWindow(overlay);                               // REQ #066
     c_SpinOverlayX.EnableWindow(overlay);                          // REQ #066
     c_SpinOverlayY.EnableWindow(overlay);                          // REQ #066
     c_OverlayX.EnableWindow(overlay);                              // REQ #066
     c_OverlayY.EnableWindow(overlay);                              // REQ #066
     c_ShowPixels.EnableWindow(overlay);                            // REQ #066
     c_ShowOverlay.EnableWindow(overlay);                           // REQ #066

     c_SpinTrackKern.EnableWindow(c_Track.GetCheck() == BST_CHECKED); // REQ #070
     c_TrackKern.EnableWindow(c_Track.GetCheck() == BST_CHECKED);   // REQ #070
    } // CFontExplorer::updateControls

/****************************************************************************
*                               simulateMsgMap
* Inputs:
*       int code: WC_ACTION, or value < 0
*       WPARAM wParam: Current-process flag (ignored)
*       LPARAM lParam: Pointer to CWPSTRUCT structure
* Result: LRESULT
*       Whatever is returned by CallNextHookEx
* Effect: 
*       In the case of several notification messages, we simulate the
*       message map entries by sending our own message.  Since in all
*       cases all we want to do is force the data to update by posting
*       a UWM_UPDATE_FONTS message, this is actually quite easy.
* Notes:
*       It does seem odd to specify the values as WPARAM and LPARAM types
*       since it is obvious they are BOOL and CWPSTRUCT *, but Microsoft
*       requires this spec (they were never very good at understanding
*       data types)
*
*       This is also grotesque in that it forces us to use two static
*       global variables to hold the hook and the current window handle
*       because MFC can't actually deliver the correct "CFontExplorer *"
*       refernce even using CWnd::FromHandle!
*
*       We can ignore the wParam because we set the hook to be a per-thread
*       hook and therefore we will never see messages other than the 
*       current thread.
****************************************************************************/

LRESULT CALLBACK simulateMsgMap(int code, WPARAM wParam, LPARAM lParam)
    {
#ifdef _DEBUG
     static int counter;
     counter++;  // see why we are so slow...
#endif

     CWPSTRUCT * cwp = (CWPSTRUCT *)lParam;

     if(code >= 0 && 
        cwp->hwnd == CFontExplorer::self->m_hWnd &&
        cwp->message == WM_COMMAND)
        { /* valid */
         // It is destined for our window.  We only care about WM_COMMAND
         // messages

         // It is a WM_COMMAND message.  If it is one of the controls that
         // would affect the information we are displaying we post a message
         // requesting an update

         // Note that this code critically depends on some information we
         // would be better off not having to code here, such as the fact
         // that the LOWORD of the wParam is the control ID
         // Such are the ugly hacks required by the MFC design problems

         switch(LOWORD(cwp->wParam))
            { /* which control */
             case cmb1:
             case cmb2:
             case cmb3:
             case cmb4:
             case cmb5:
             case chx1:
             case chx2:
                     CFontExplorer::self->PostMessage(UWM_UPDATE_FONTS);
                     break;
            } /* which control */
        } /* valid */

     // No matter what we saw, pass it on
     return CallNextHookEx(CFontExplorer::self->hook, code, wParam, lParam);
    }

/****************************************************************************
*                         CFontExplorer::OnInitDialog
* Result: BOOL
*       TRUE, always (leave focus alone)
* Effect: 
*       Fairly straightforword with one major exception: We install a
*       "hook" procedure to simulate the effect of the message map.  This
*       is required because MFC deliberately and with malice aforethought
*       goes out of its way to improperly implement the handling of 
*       WM_COMMAND messages, always returning a value that says "message
*       completely handled", instead of giving the programmer the option.
*       This makes it impossible to subclass a common dialog properly.
****************************************************************************/

BOOL CFontExplorer::OnInitDialog() 
{
        CFontDialog::OnInitDialog();
        
        c_Legend.AddLegends(CFontDisplay::GetLegend());
        CheckRadioButton(IDC_INFO, IDC_SHOW_KERNING_MAP, IDC_INFO); // REQ #041
        updateControls();

        // This seems a bit weird, but I want to get these
        // events BEFORE they go to the regular font control!
        
        subclassCommand(this, cmb1, CBN_SELCHANGE);
        subclassCommand(this, cmb2, CBN_SELCHANGE);
        subclassCommand(this, cmb3, CBN_SELCHANGE);
        subclassCommand(this, cmb4, CBN_SELCHANGE);
        subclassCommand(this, cmb5, CBN_SELCHANGE);
        subclassCommand(this, chx1, BN_CLICKED);
        subclassCommand(this, chx2, BN_CLICKED);

        // Compute the borders                                      // REQ #036
        //      +-Font info----------------------+<--- c_Border     // REQ #036
        //      |           margins.top          |                  // REQ #036
        //      | +----------------------------+<+---- c_Frame      // REQ #036
        //      |m|                            |m|   |              // REQ #036
        //      |a|                            |a|   |              // REQ #036
        //      |r|   +--------------------+   |r|   |              // REQ #036
        //      |g|   |Ap                  |   |g| i |              // REQ #036
        //      |i|   |   c_CharDisplay    |   |i| n |              // REQ #036
        //      |n|   |                    |   |n| s |              // REQ #036
        //      |s|   +--------------------+   |s| e |              // REQ #036
        //      |.|                            |.| t |              // REQ #036
        //      |l|   +--------------------+   |r| . |              // REQ #036
        //      |e|   |                    |   |i| c |              // REQ #036
        //      |f|   |   c_TreeMetrics    |   |g| x |              // REQ #036
        //      |t|   |                    |   |h|   |              // REQ #036
        //      | |   +--------------------+   |t|   |              // REQ #036
        //      | |                            | |   |              // REQ #036
        //      | +----------------------------+ |   |              // REQ #036
        //      |         margins.bottom         |   |              // REQ #036
        //      +--------------------------------+   |              // REQ #036
        //                 inset.cy                  |              // REQ #036
        //------------------------------------------ +              // REQ #036
        CRect client;                                               // REQ #036
        GetClientRect(&client);                                     // REQ #036
                                                                    // REQ #036
        CRect border;                                               // REQ #036
        c_Border.GetWindowRect(&border);                            // REQ #036
        ScreenToClient(&border);                                    // REQ #036
                                                                    // REQ #036
        CRect frame;                                                // REQ #036
        c_Frame.GetWindowRect(&frame);                              // REQ #036
        ScreenToClient(&frame);                                     // REQ #036
                                                                    // REQ #036
        margins.top = frame.top - border.top;                       // REQ #036
        margins.left = frame.left - border.left;                    // REQ #036
        margins.right = frame.right - border.right;                 // REQ #036
        margins.bottom = frame.bottom - border.bottom;              // REQ #036
                                                                    // REQ #036
        inset.cx = client.right - border.right;                     // REQ #036
        inset.cy = client.bottom - border.bottom;                   // REQ #036
                                                                    // REQ #036
        UINT id = c_KerningMap.GetDlgCtrlID();                      // REQ #041
        CRect w;                                                    // REQ #041
        c_KerningMap.GetWindowRect(&w);                             // REQ #041
        ScreenToClient(&w);                                         // REQ #041
        c_KerningMap.DestroyWindow();                               // REQ #041
        c_KerningMap.Create(w, id, this);                           // REQ #041
        c_KerningMap.SetWindowPos(&c_CharDisplay, 0, 0, 0, 0,       // REQ #041
                               SWP_NOMOVE | SWP_NOSIZE);            // REQ #041

        ResizeControls();                                           // REQ #036

        c_SpinOverlayX.SetRange(-1024, 1024);                       // REQ #066
        c_SpinOverlayX.SetPos(0);                                   // REQ #066
        c_SpinOverlayY.SetRange(-1024, 1024);                       // REQ #066
        c_SpinOverlayY.SetPos(0);                                   // REQ #066
        c_ShowPixels.SetCheck(BST_CHECKED);                         // REQ #066
        c_ShowOverlay.SetCheck(BST_CHECKED);                        // REQ #066

        c_HRule.SetCheck(BST_CHECKED);                              // REQ #070
        c_VRule.SetCheck(BST_CHECKED);                              // REQ #070
        c_CHRule.SetCheck(BST_CHECKED);                             // REQ #070
        c_SpinTrackKern.SetRange(LOWKERN, HIKERN);                  // REQ #070

        c_Smoothing.SetCheck(BST_CHECKED);                          // REQ #071
        CheckRadioButton(IDC_NONE, IDC_IGNOREABC, IDC_TEXTOUT);     // REQ #011// REQ #070
        c_Colors.SetCheck(BST_CHECKED);                             // REQ #070

        CString s;                                                  // REQ #066
        c_CharDisplay.GetWindowText(s);                             // REQ #066
        c_Sample.SetWindowText(s);                                  // REQ #066

        initialized = TRUE;                                         // REQ #066
        updateFontInfo();                                           // REQ #082
        updateControls();                                           // REQ #041
#ifndef _DEBUG                                                      // REQ #035
        c_Debug.ShowWindow(SW_HIDE);                                // REQ #035
#endif                                                              // REQ #035

        //hook = SetWindowsHookEx(WH_CALLWNDPROC, (HOOKPROC)simulateMsgMap,
        //                      AfxGetInstanceHandle(), GetCurrentThreadId());
        
        return TRUE;  // return TRUE unless you set the focus to a control
                      // EXCEPTION: OCX Property Pages should return FALSE
} // CFontExplorer::OnInitDialog

/****************************************************************************
*                            CFontExplorer::OnInfo
* Result: void
*       
* Effect: 
*       Selects the font info display
****************************************************************************/

void CFontExplorer::OnInfo() 
   {
    updateControls();
   } // CFontExplorer::OnInfo

/****************************************************************************
*                            CFontExplorer::OnChar
* Result: void
*       
* Effect: 
*       Sets the character display
****************************************************************************/

void CFontExplorer::OnChar() 
   {
    updateControls();
   }

/****************************************************************************
*                       CFontExplorer::OnShowKerningMap
* Result: void
*       
* Effect: 
*       Selects the kerning map display
****************************************************************************/

void CFontExplorer::OnShowKerningMap()
   {
    updateControls();
   }

// If we actually were able to use the message map, whose usage is defeated
// by a serious design flaw in MFC, we would use these handlers.

//void CFontExplorer::OnSelchangecmb1() 
//{
// PostMessage(UWM_UPDATE_FONTS);
//}

//void CFontExplorer::OnSelchangecmb2() 
//{
// PostMessage(UWM_UPDATE_FONTS);
//}

//void CFontExplorer::OnSelchangecmb3() 
//{
// PostMessage(UWM_UPDATE_FONTS);
//}

//void CFontExplorer::OnSelchangecmb4() 
//{
// PostMessage(UWM_UPDATE_FONTS);
//}

//void CFontExplorer::OnSelchangecmb5() 
//{
// PostMessage(UWM_UPDATE_FONTS);
//}

//void CFontExplorer::Onchx1() 
//{
// PostMessage(UWM_UPDATE_FONTS);
//}

//void CFontExplorer::Onchx2() 
//{
// PostMessage(UWM_UPDATE_FONTS);
//}

/****************************************************************************
*                        CFontExplorer::OnUpdateFonts
* Inputs:
*       ignored
* Result: LRESULT
*       0, always
* Effect: 
*       Updates the font information.  This must be deferred.
****************************************************************************/

LRESULT CFontExplorer::OnUpdateFonts(WPARAM, LPARAM)
    {
     updateOptions();                                               // REQ #070
     updateFontInfo();
     return 0;
    }

/****************************************************************************
*                        CFontExplorer::ResizeControls
* Result: void
*       
* Effect: 
*       Resizes the controls to fit
****************************************************************************/

void CFontExplorer::ResizeControls()
    {
     if(c_CharDisplay.GetSafeHwnd() == NULL ||                      // REQ #036
        c_TreeMetrics.GetSafeHwnd() == NULL ||                      // REQ #036
        c_KerningMap.GetSafeHwnd() == NULL ||                       // REQ #041
        c_Border.GetSafeHwnd() == NULL)                             // REQ #036
        { /* can't resize it */                                     // REQ #036
         return;                                                    // REQ #036
        } /* can't resize it */                                     // REQ #036
     //                                                             // REQ #036
     //      +-Font info----------------------+<--- c_Border        // REQ #036
     //      |           margins.top          |                     // REQ #036
     //      | +----------------------------+<+---- c_Frame         // REQ #036
     //      |m|                            |m|   |                 // REQ #036
     //      |a|                            |a|   |                 // REQ #036
     //      |r|   +--------------------+   |r|   |                 // REQ #036
     //      |g|   |Ap                  |   |g| i |                 // REQ #036
     //      |i|   |   c_CharDisplay    |   |i| n |                 // REQ #036
     //      |n|   |                    |   |n| s |                 // REQ #036
     //      |s|   +--------------------+   |s| e |                 // REQ #036
     //      |.|                            |.| t |                 // REQ #036
     //      |l|   +--------------------+   |r| . |                 // REQ #036
     //      |e|   |                    |   |i| c |                 // REQ #036
     //      |f|   |   c_TreeMetrics    |   |g| x |                 // REQ #036
     //      |t|   |                    |   |h|   |                 // REQ #036
     //      | |   +--------------------+   |t|   |                 // REQ #036
     //      | |                            | |   |                 // REQ #036
     //      | +----------------------------+ |   |                 // REQ #036
     //      |         margins.bottom         |   |                 // REQ #036
     //      +--------------------------------+   |                 // REQ #036
     //                 inset.cy                  |                 // REQ #036
     //------------------------------------------ +                 // REQ #036
                                                                    // REQ #036
     CRect client;                                                  // REQ #036
     GetClientRect(&client);                                        // REQ #036
                                                                    // REQ #036
     if(c_Debug.GetCheck() == BST_CHECKED)                          // REQ #036
        { /* debug */                                               // REQ #036
         TRACE(_T(__FUNCTION__) _T(": margins [%d %d %d %d]\n"),    // REQ #036
                                margins.left, margins.top,          // REQ #036
                                margins.right, margins.bottom);     // REQ #036
         TRACE(_T(__FUNCTION__) _T(": inset [%d %d]\n"),            // REQ #036
                               inset.cx, inset.cy);                 // REQ #036
        } /* debug */                                               // REQ #036
     CRect border; // outer caption border                          // REQ #036
     c_Border.GetWindowRect(&border);                               // REQ #036
     ScreenToClient(&border);                                       // REQ #036
                                                                    // REQ #036
     c_Border.SetWindowPos(NULL,                                    // REQ #036
                           0, 0,                                    // REQ #036
                           (client.right - inset.cx) - border.left, // REQ #036
                           client.bottom - inset.cy - border.top,   // REQ #036
                           SWP_NOMOVE | SWP_NOZORDER);              // REQ #036
                                                                    // REQ #036
     c_Border.GetWindowRect(&border);                               // REQ #036
     ScreenToClient(&border);                                       // REQ #036
                                                                    // REQ #036
     CRect frame;  // inner enclosing frame                         // REQ #036
     c_Frame.GetWindowRect(&frame);                                 // REQ #036
     ScreenToClient(&frame);                                        // REQ #036
                                                                    // REQ #036
     c_Frame.SetWindowPos(NULL, 0, 0,                               // REQ #036
                          (border.right + margins.right) - frame.left,  // REQ #036
                          (border.bottom + margins.bottom) - frame.top, // REQ #036
                          SWP_NOMOVE | SWP_NOZORDER);               // REQ #036
                                                                    // REQ #036
     c_Frame.GetWindowRect(&frame);                                 // REQ #036
     ScreenToClient(&frame);                                        // REQ #036
                                                                    // REQ #036
     c_TreeMetrics.SetWindowPos(NULL, frame.left, frame.top,        // REQ #036
                                frame.Width(),                      // REQ #036
                                frame.Height(),                     // REQ #036
                                SWP_NOZORDER);                      // REQ #036
                                                                    // REQ #036
     c_CharDisplay.SetWindowPos(NULL, frame.left, frame.top,        // REQ #036
                                frame.Width(),                      // REQ #036
                                frame.Height(),                     // REQ #036
                                SWP_NOZORDER);                      // REQ #036
                                                                    // REQ #036
     c_KerningMap.SetWindowPos(NULL, frame.left, frame.top,         // REQ #041
                                frame.Width(),                      // REQ #041
                                frame.Height(),                     // REQ #041
                                SWP_NOZORDER);                      // REQ #041
    } // CFontExplorer::ResizeControls                              // REQ #036

/****************************************************************************
*                            CFontExplorer::OnSize
* Inputs:
*       UINT nType:
*       int cx:
*       int cy:
* Result: void
*       
* Effect: 
*       Resizes the control
****************************************************************************/

void CFontExplorer::OnSize(UINT nType, int cx, int cy)              // REQ #036
    {                                                               // REQ #036
     CFontDialog::OnSize(nType, cx, cy);                            // REQ #036
                                                                    // REQ #036
     ResizeControls();                                              // REQ #036
    } // CFontExplorer::OnSize                                      // REQ #036

/****************************************************************************
*                       CFontExplorer::OnGetMinMaxInfo
* Inputs:
*       MINMAXINFO * lpMMI:
* Result: void
*       
* Effect: 
*       Limits the size
****************************************************************************/

void CFontExplorer::OnGetMinMaxInfo(MINMAXINFO * lpMMI)
    {
     if(c_MinMaxInfoFrame.GetSafeHwnd() != NULL)
        { /* has frame */
         CRect r;
         c_MinMaxInfoFrame.GetWindowRect(&r);
         ScreenToClient(&r);
         CalcWindowRect(&r);
         lpMMI->ptMinTrackSize.x = r.Width();
         lpMMI->ptMinTrackSize.y = r.Height();
        } /* has frame */        
     else
        CDialog::OnGetMinMaxInfo(lpMMI);
    } // CFontExplorer::OnGetMinMaxInfo

/****************************************************************************
*                            CFontExplorer::OnCopy
* Result: void
*       
* Effect: 
*       Copies the contents of the character display or font info to the
*       clipboard
****************************************************************************/

void CFontExplorer::OnCopy() 
{
 CRect bb;                                                          // REQ #041
 if(c_Char.GetCheck() == BST_CHECKED)                               // REQ #041
    bb = c_CharDisplay.GetBB();                                     // REQ #041
 else                                                               // REQ #041
 if(c_Info.GetCheck() == BST_CHECKED)                               // REQ #041
    c_TreeMetrics.GetClientRect(&bb); // too much; TODO: fix this   // REQ #041
 else                                                               // REQ #041
 if(c_ShowKerningMap.GetCheck() == BST_CHECKED)                     // REQ #041
    bb = c_KerningMap.GetBB();                                      // REQ #041
                                                                    // REQ #041
 toClipboard(&c_CharDisplay, bb);                                   // REQ #041
}


/****************************************************************************
*                       CFontExplorer::OnBnClickedDebug
* Result: void
*       
* Effect: 
*       Toggles debug mode
****************************************************************************/

void CFontExplorer::OnBnClickedDebug()                              // REQ #035
    {                                                               // REQ #035
     c_CharDisplay.SetDebug(c_Debug.GetCheck() == BST_CHECKED);     // REQ #035
    } // CFontExplorer::OnBnClickedDebug                            // REQ #035

/****************************************************************************
*                     CFontExplorer::OnBnClickedAdvanced
* Result: void
*       
* Effect: 
*       Switches to GM_ADVANCED mode
****************************************************************************/

void CFontExplorer::OnBnClickedAdvanced()                           // REQ #035
    {                                                               // REQ #035
     c_CharDisplay.SetGMAdvanced(c_Advanced.GetCheck() == BST_CHECKED);// REQ #035
     updateFontInfo();                                              // REQ #035
    } // CFontExplorer::OnBnClickedAdvanced                         // REQ #035

/****************************************************************************
*                           CFontExplorer::OnDestroy
* Result: void
*       
* Effect: 
*       Removes specialized subclassing
****************************************************************************/

void CFontExplorer::OnDestroy() 
   {
    CFontDialog::OnDestroy();
        
    unsubclassCommand(this, cmb1);
    unsubclassCommand(this, cmb2);
    unsubclassCommand(this, cmb3);
    unsubclassCommand(this, cmb4);
    unsubclassCommand(this, cmb4);
    unsubclassCommand(this, chx1);
    unsubclassCommand(this, chx2);

    // if(hook != NULL)
    //   UnhookWindowsHookEx(hook);
   }

/****************************************************************************
*                             CFontExplorer::OnOK
* Result: void
*       
* Effect: 
*       Avoids closing on <CR>
****************************************************************************/

void CFontExplorer::OnOK()                                          // REQ #068
    {                                                               // REQ #068
     // does nothing                                                // REQ #068
    } // CFontExplorer::OnOK                                        // REQ #068

/****************************************************************************
*                           CFontExplorer::OnCancel
* Result: void
*       
* Effect: 
*       Does nothing, avoids closing on <ESC>
****************************************************************************/

void CFontExplorer::OnCancel()                                      // REQ #068
    {                                                               // REQ #068
     // does nothing                                                // REQ #068
    } // CFontExplorer::OnCancel                                    // REQ #068

/****************************************************************************
*                           CFontExplorer::OnClose
* Result: void
*       
* Effect: 
*       ¶
****************************************************************************/

void CFontExplorer::OnClose()                                       // REQ #068
    {                                                               // REQ #068
     CFontDialog::OnCancel();                                       // REQ #068
    } // CFontExplorer::OnClose                                     // REQ #068

/****************************************************************************
*                        CFontExplorer::OnBnClickedOK
* Result: void
*       
* Effect: 
*       Closes the dialog
****************************************************************************/

void CFontExplorer::OnBnClickedOK()                                 // REQ #068
    {                                                               // REQ #068
     CFontDialog::OnOK();                                           // REQ #068
    } // CFontExplorer::OnBnClickedOK                               // REQ #068

/****************************************************************************
*                      CFontExplorer::OnBnClickedCancel
* Result: void
*       
* Effect: 
*       Closes the dialog
****************************************************************************/

void CFontExplorer::OnBnClickedCancel()                             // REQ #068
    {                                                               // REQ #068
     CFontDialog::OnCancel();                                       // REQ #068
    } // CFontExplorer::OnBnClickedCancel                           // REQ #068

/****************************************************************************
*                    CFontExplorer::OnBnClickedShowPixels
* Result: void
*       
* Effect: 
*       Toggles the pixels state
****************************************************************************/

void CFontExplorer::OnBnClickedShowPixels()                         // REQ #066
    {                                                               // REQ #066
     updateControls();                                              // REQ #066
    } // CFontExplorer::OnBnClickedShowPixels                       // REQ #066

/****************************************************************************
*                    CFontExplorer::OnBnClickedShowOverlay
* Result: void
*       
* Effect: 
*       Toggles the Overlay state
****************************************************************************/

void CFontExplorer::OnBnClickedShowOverlay()                        // REQ #066
    {                                                               // REQ #066
     updateControls();                                              // REQ #066
    } // CFontExplorer::OnBnClickedShowOverlay                      // REQ #066

/****************************************************************************
*                       CFontExplorer::OnChangeOverlayX
* Result: void
*       
* Effect: 
*       Updates the horizontal offset
****************************************************************************/

void CFontExplorer::OnChangeOverlayX()                              // REQ #066
    {                                                               // REQ #066
     updateControls();                                              // REQ #066
    } // CFontExplorer::OnChangeOverlayX                            // REQ #066

/****************************************************************************
*                       CFontExplorer::OnChangeOverlayY
* Result: void
*       
* Effect: 
*       Updates the horizontal offset
****************************************************************************/

void CFontExplorer::OnChangeOverlayY()                              // REQ #066
    {                                                               // REQ #066
     updateControls();                                              // REQ #066
    } // CFontExplorer::OnChangeOverlayY                            // REQ #066

/****************************************************************************
*                       CFontExplorer::OnBnClickedNone
* Result: void
*       
* Effect: 
*       Sets the display options to "None"
****************************************************************************/

void CFontExplorer::OnBnClickedNone()                               // REQ #070
    {                                                               // REQ #070
     updateControls();                                              // REQ #070
    } // CFontExplorer::OnBnClickedNone                             // REQ #070

/****************************************************************************
*                      CFontExplorer::OnBnClickedTextOut
* Result: void
*       
* Effect: 
*       Sets the output mode to "TextOut"
****************************************************************************/

void CFontExplorer::OnBnClickedTextOut()                            // REQ #070
    {                                                               // REQ #070
     updateControls();                                              // REQ #070
    } // CFontExplorer::OnBnClickedTextOut                          // REQ #070

/****************************************************************************
*                    CFontExplorer::OnBnClickedExtTextOut
* Result: void
*       
* Effect: 
*       Sets the output mode to ExtTextOut
****************************************************************************/

void CFontExplorer::OnBnClickedExtTextOut()                         // REQ #070
    {                                                               // REQ #070
     updateControls();                                              // REQ #070
    } // CFontExplorer::OnBnClickedExtTextOut                       // REQ #070

/****************************************************************************
*                     CFontExplorer::OnBnClickedIgnoreABC
* Result: void
*       
* Effect: 
*       Uses the special "Ignore ABC" mode
****************************************************************************/

void CFontExplorer::OnBnClickedIgnoreABC()                          // REQ #070
    {                                                               // REQ #070
     updateControls();                                              // REQ #070
    } // CFontExplorer::OnBnClickedIgnoreABC                        // REQ #070

/****************************************************************************
*                       CFontExplorer::OnBnClickedHRule
* Result: void
*       
* Effect: 
*       Toggles the Rules mode
****************************************************************************/

void CFontExplorer::OnBnClickedHRule()                              // REQ #070
    {                                                               // REQ #070
     updateControls();                                              // REQ #070
    } // CFontExplorer::OnBnClickedHRule                            // REQ #070

/****************************************************************************
*                       CFontExplorer::OnBnClickedCHRule
* Result: void
*       
* Effect: 
*       Toggles the Rules mode
****************************************************************************/

void CFontExplorer::OnBnClickedCHRule()                             // REQ #070
    {                                                               // REQ #070
     updateControls();                                              // REQ #070
    } // CFontExplorer::OnBnClickedCHRule                           // REQ #070

/****************************************************************************
*                       CFontExplorer::OnBnClickedVRule
* Result: void
*       
* Effect: 
*       Toggles the Rules mode
****************************************************************************/

void CFontExplorer::OnBnClickedVRule()                              // REQ #070
    {                                                               // REQ #070
     updateControls();                                              // REQ #070
    } // CFontExplorer::OnBnClickedVRule                            // REQ #070

/****************************************************************************
*                       CFontExplorer::OnBnClickedTrack
* Result: void
*       
* Effect: 
*       Enables/disables track kerning
****************************************************************************/

void CFontExplorer::OnBnClickedTrack()                              // REQ #070
    {                                                               // REQ #070
     updateControls();                                              // REQ #070
    } // CFontExplorer::OnBnClickedTrack                            // REQ #070

/****************************************************************************
*                   CFontExplorer::OnBnClickedFontSmoothing
* Result: void
*       
* Effect: 
*       Updates the font information
****************************************************************************/

void CFontExplorer::OnBnClickedFontSmoothing()                      // REQ #071
    {                                                               // REQ #071
     updateOptions();                                               // REQ #071
     updateFontInfo();                                              // REQ #071
    } // CFontExplorer::OnBnClickedFontSmoothing                    // REQ #071

/****************************************************************************
*                     CFontExplorer::OnChangeTrackKern
* Result: void
*       
* Effect: 
*       Updates the font information
****************************************************************************/

void CFontExplorer::OnChangeTrackKern()                             // REQ #070
    {                                                               // REQ #070
     updateOptions();                                               // REQ #070
     updateFontInfo();                                              // REQ #070
    } // CFontExplorer::OnChangeTrackKern                           // REQ #070

/****************************************************************************
*                       CFontExplorer::OnBnClickedPair
* Result: void
*       
* Effect: 
*       Sets pair kerning
****************************************************************************/

void CFontExplorer::OnBnClickedPair()                               // REQ #070
    {                                                               // REQ #070
     updateOptions();                                               // REQ #070
     updateFontInfo();                                              // REQ #070
    } // CFontExplorer::OnBnClickedPair                             // REQ #070

/****************************************************************************
*                      CFontExplorer::OnBnClickedColors
* Result: void
*       
* Effect: 
*       Toggles the Use Colors
****************************************************************************/

void CFontExplorer::OnBnClickedColors()                             // REQ #070
    {                                                               // REQ #070
     updateOptions();                                               // REQ #070
    } // CFontExplorer::OnBnClickedColors                           // REQ #070

/****************************************************************************
*                       CFontExplorer::OnBnClickedWhite
* Result: void
*       
* Effect: 
*       Updates the background
****************************************************************************/

void CFontExplorer::OnBnClickedWhite()                              // REQ #070
    {                                                               // REQ #070
     updateOptions();                                               // REQ #070
    } // CFontExplorer::OnBnClickedWhite                            // REQ #070

/****************************************************************************
*                        CFontExplorer::OnChangeSample
* Result: void
*       
* Effect: 
*       Updates the sample
****************************************************************************/

void CFontExplorer::OnChangeSample()                                // REQ #070
    {                                                               // REQ #070
     CString s;                                                     // REQ #070
     c_Sample.GetWindowText(s);                                     // REQ #070
     c_CharDisplay.SetWindowText(s);                                // REQ #070
    } // CFontExplorer::OnChangeSample                              // REQ #070

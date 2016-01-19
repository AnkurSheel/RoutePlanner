/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 31-Oct-08 | REQ #078: Created
*****************************************************************************/
// FontDialogExplorer.cpp : implementation file
//

#include "stdafx.h"                                                 // REQ #078
#include "resource.h"                                               // REQ #078
#include "FontDialogExplorer.h"                                     // REQ #078
#include "Language.h"                                               // REQ #078
#include "ToString.h"                                               // REQ #078
#include "ErrorString.h"                                            // REQ #078
                                                                    // REQ #078
// CFontDialogExplorer                                              // REQ #078
                                                                    // REQ #078
IMPLEMENT_DYNCREATE(CFontDialogExplorer, CFormView)                 // REQ #078
                                                                    // REQ #078
static const UINT MAX_STYLE_BUFFER= 256;                            // REQ #078

/****************************************************************************
*                  CFontDialogExplorer::CFontDialogExplorer
*                  CFontDialogExplorer::~CFontDialogExplorer
* Effect: 
*       Constructor/destructor
****************************************************************************/

CFontDialogExplorer::CFontDialogExplorer()                          // REQ #078
        : CFormView(CFontDialogExplorer::IDD)                       // REQ #078
   {                                                                // REQ #078
    initialized = FALSE;                                            // REQ #078
   }                                                                // REQ #078

CFontDialogExplorer::~CFontDialogExplorer()                         // REQ #078
{                                                                   // REQ #078
}                                                                   // REQ #078

/****************************************************************************
*                     CFontDialogExplorer::DoDataExchange
* Inputs:
*       CDataExchange * pDX:
* Result: void
*       
* Effect: 
*       Binds controls to variables
****************************************************************************/

void CFontDialogExplorer::DoDataExchange(CDataExchange* pDX)        // REQ #078
   {                                                                // REQ #078
   CFormView::DoDataExchange(pDX);                                  // REQ #078
   DDX_Control(pDX, IDC_LOGFONT_CAPTION, x_LOGFONT);                // REQ #078
   DDX_Control(pDX, IDC_FACENAME, c_lfFaceName);                    // REQ #078
   DDX_Control(pDX, IDC_LFWIDTH, c_lfWidth);                        // REQ #078
   DDX_Control(pDX, IDC_LFHEIGHT, c_lfHeight);                      // REQ #078
   DDX_Control(pDX, IDC_LFESCAPEMENT, c_lfEscapement);              // REQ #078
   DDX_Control(pDX, IDC_LFORIENTATION, c_lfOrientation);            // REQ #078
   DDX_Control(pDX, IDC_SPINORIENTATION, c_SpinOrientation);        // REQ #078
   DDX_Control(pDX, IDC_SPINESCAPEMENT, c_SpinEscapement);          // REQ #078
   DDX_Control(pDX, IDC_LFORIENTATION_CAPTION, x_lfOrientation);    // REQ #078
   DDX_Control(pDX, IDC_LFFAMILY, c_lfFamily);                      // REQ #078
   DDX_Control(pDX, IDC_LFPITCH, c_lfPitch);                        // REQ #078
   DDX_Control(pDX, IDC_LFWEIGHT, c_lfWeight);                      // REQ #078
   DDX_Control(pDX, IDC_LFQUALITY, c_lfQuality);                    // REQ #078
   DDX_Control(pDX, IDC_LFOUTPRECISION, c_lfOutPrecision);          // REQ #078
   DDX_Control(pDX, IDC_LFCHARSET, c_lfCharSet);                    // REQ #078
   DDX_Control(pDX, IDC_LFCLIPPRECISION, c_lfClipPrecision);        // REQ #078
   DDX_Control(pDX, IDC_LFUNDERLINE, c_lfUnderline);                // REQ #078
   DDX_Control(pDX, IDC_LFITALIC, c_lfItalic);                      // REQ #078
   DDX_Control(pDX, IDC_LFSTRIKEOUT, c_lfStrikeOut);                // REQ #078
   DDX_Control(pDX, IDC_R, c_Red);                                  // REQ #078
   DDX_Control(pDX, IDC_G, c_Green);                                // REQ #078
   DDX_Control(pDX, IDC_B, c_Blue);                                 // REQ #078
   DDX_Control(pDX, IDC_SPIN_R, c_SpinRed);                         // REQ #078
   DDX_Control(pDX, IDC_SPIN_G, c_SpinGreen);                       // REQ #078
   DDX_Control(pDX, IDC_SPIN_B, c_SpinBlue);                        // REQ #078
   DDX_Control(pDX, IDC_SPIN_POINTSIZE, c_SpinPointSize);           // REQ #078
   DDX_Control(pDX, IDC_IPOINTSIZE, c_PointSize);                   // REQ #078
   DDX_Control(pDX, IDC_LANGUAGE, c_Language);                      // REQ #078
                                                                    // REQ #078
   DDX_Control(pDX, IDC_CF_APPLY, c_CF_APPLY);                      // REQ #078
   DDX_Control(pDX, IDC_CF_ANSIONLY, c_CF_ANSIONLY);                // REQ #078
   DDX_Control(pDX, IDC_CF_BOTH, c_CF_BOTH);                        // REQ #078
   DDX_Control(pDX, IDC_CF_PRINTERFONTS, c_CF_PRINTERFONTS);        // REQ #078
   DDX_Control(pDX, IDC_CF_SCREENFONTS, c_CF_SCREENFONTS);          // REQ #078
   DDX_Control(pDX, IDC_CF_TTONLY, c_CF_TTONLY);                    // REQ #078
   DDX_Control(pDX, IDC_CF_EFFECTS, c_CF_EFFECTS);                  // REQ #078
   DDX_Control(pDX, IDC_CF_FIXEDPITCHONLY, c_CF_FIXEDPITCHONLY);    // REQ #078
   DDX_Control(pDX, IDC_CF_FORCEFONTEXIST, c_CF_FORCEFONTEXIST);    // REQ #078
   DDX_Control(pDX, IDC_CF_INITTOLOGFONTSTRUCT, c_CF_INITTOLOGFONTSTRUCT);// REQ #078
   DDX_Control(pDX, IDC_CF_LIMITSIZE, c_CF_LIMITSIZE);              // REQ #078
   DDX_Control(pDX, IDC_CF_NOVECTORFONTS, c_CF_NOVECTORFONTS);      // REQ #078
   DDX_Control(pDX, IDC_CF_NOFACESEL, c_CF_NOFACESEL);              // REQ #078
   DDX_Control(pDX, IDC_CF_NOSCRIPTSEL, c_CF_NOSCRIPTSEL);          // REQ #078
   DDX_Control(pDX, IDC_CF_NOSTYLESEL, c_CF_NOSTYLESEL);            // REQ #078
   DDX_Control(pDX, IDC_CF_NOSIZESEL, c_CF_NOSIZESEL);              // REQ #078
   DDX_Control(pDX, IDC_CF_NOSIMULATIONS, c_CF_NOSIMULATIONS);      // REQ #078
   DDX_Control(pDX, IDC_CF_NOVERTFONTS, c_CF_NOVERTFONTS);          // REQ #078
   DDX_Control(pDX, IDC_CF_SCALABLEONLY, c_CF_SCALABLEONLY);        // REQ #078
   DDX_Control(pDX, IDC_CF_SCRIPTSONLY, c_CF_SCRIPTSONLY);          // REQ #078
   DDX_Control(pDX, IDC_CF_SELECTSCRIPT, c_CF_SELECTSCRIPT);        // REQ #078
   DDX_Control(pDX, IDC_CF_SHOWHELP, c_CF_SHOWHELP);                // REQ #078
   DDX_Control(pDX, IDC_CF_USESTYLE, c_CF_USESTYLE);                // REQ #078
   DDX_Control(pDX, IDC_CF_WYSIWYG, c_CF_WYSIWYG);                  // REQ #078
   DDX_Control(pDX, IDC_CODE, c_Code);                              // REQ #078
   DDX_Control(pDX, IDC_STATUS, c_Status);                          // REQ #078
   DDX_Control(pDX, IDC_NSIZEMIN, c_nSizeMin);                      // REQ #078
   DDX_Control(pDX, IDC_SPIN_SIZEMIN, c_SpinSizeMin);               // REQ #078
   DDX_Control(pDX, IDC_NSIZEMAX, c_nSizeMax);                      // REQ #078
   DDX_Control(pDX, IDC_SPIN_SIZEMAX, c_SpinSizeMax);               // REQ #078
   DDX_Control(pDX, IDC_NSIZEMIN_CAPTION, x_nSizeMin);              // REQ #078
   DDX_Control(pDX, IDC_NSIZEMAX_CAPTION, x_nSizeMax);              // REQ #078
   DDX_Control(pDX, IDC_LFHEIGHT_CAPTION, x_lfHeight);              // REQ #078
   DDX_Control(pDX, IDC_LFFACENAME_CAPTION, x_lfFaceName);          // REQ #078
   DDX_Control(pDX, IDC_LFWEIGHT_CAPTION, x_lfWeight);              // REQ #078
   DDX_Control(pDX, IDC_LSTRUCTSIZE, c_lStructSize);                // REQ #078
   DDX_Control(pDX, IDC_LPLOGFONT, c_hDC);                          // REQ #078
   DDX_Control(pDX, IDC_HWNDOWNER, c_hwndOwner);                    // REQ #078
   DDX_Control(pDX, IDC_LPSZSTYLE_CAPTION, x_lpszStyle);            // REQ #078
   DDX_Control(pDX, IDC_LPSZSTYLE_IN_CAPTION, x_lpszStyleIn);       // REQ #078
   DDX_Control(pDX, IDC_LPSZSTYLE_OUT_CAPTION, x_lpszStyleOut);     // REQ #078
   DDX_Control(pDX, IDC_LPSZSTYLE_IN, c_lpszStyleIn);               // REQ #078
   DDX_Control(pDX, IDC_LPSZSTYLE_OUT, c_lpszStyleOut);             // REQ #078
   DDX_Control(pDX, IDC_BOLD_FONTTYPE, c_BOLD_FONTTYPE);            // REQ #078
   DDX_Control(pDX, IDC_ITALIC_FONTTYPE, c_ITALIC_FONTTYPE);        // REQ #078
   DDX_Control(pDX, IDC_PRINTER_FONTTYPE, c_PRINTER_FONTTYPE);      // REQ #078
   DDX_Control(pDX, IDC_REGULAR_FONTTYPE, c_REGULAR_FONTTYPE);      // REQ #078
   DDX_Control(pDX, IDC_SCREEN_FONTTYPE, c_SCREEN_FONTTYPE);        // REQ #078
   DDX_Control(pDX, IDC_SIMULATED_FONTTYPE, c_SIMULATED_FONTTYPE);  // REQ #078
   DDX_Control(pDX, IDC_RGBCOLORS_CAPTION, x_rgbColors);            // REQ #078
   DDX_Control(pDX, IDC_COLOR, c_Colors);                           // REQ #078
   DDX_Control(pDX, IDC_USE_PRINTER_DC, c_UsePrinterDC);            // REQ #078
   DDX_Control(pDX, IDC_SET_POINTHEIGHT, c_SetPointHeight);         // REQ #078
   DDX_Control(pDX, IDC_POINTFONT, c_PointFont);                    // REQ #078
   DDX_Control(pDX, IDC_SHOW_CODE, c_ShowPointFontCode);            // REQ #078
   DDX_Control(pDX, IDC_COPY, c_Copy);                              // REQ #078
   DDX_Control(pDX, IDC_LFCHARSET_CAPTION, x_lfCharSet);            // REQ #078
   DDX_Control(pDX, IDC_LFOUTPRECISION_CAPTION, x_lfOutPrecision);  // REQ #078
   DDX_Control(pDX, IDC_LFCLIPPRECSION_CAPTION, x_lfClipPrecision); // REQ #078
   DDX_Control(pDX, IDC_LFQUALITY_CAPTION, x_lfQuality);            // REQ #078
   DDX_Control(pDX, IDC_LFPITCHANDFAMILY_CAPTION, x_lfPitchAndFamily);// REQ #078
   DDX_Control(pDX, IDC_LFWIDTH_CAPTION, x_lfWidth);                // REQ #078
   DDX_Control(pDX, IDC_LFESCAPEMENT_CAPTION, x_lfEscapement);      // REQ #078
   DDX_Control(pDX, IDC_POINTSIZE_CAPTION, x_PointSize);            // REQ #078
   DDX_Control(pDX, IDC_POINTSIZE_MULTIPLIER, x_PointSizeMultiplier);// REQ #078
   DDX_Control(pDX, IDC_POINTFONT_CAPTION, x_PointFont);            // REQ #078
   DDX_Control(pDX, IDC_POINTSIZE, c_PointFontSize);                // REQ #078
   DDX_Control(pDX, IDC_FONTSAMPLE, c_FontSample);                  // REQ #078
   DDX_Control(pDX, IDC_DISPLAY_TEXT, c_DisplayText);               // REQ #078
   DDX_Control(pDX, IDC_SHOW_PIXELS, c_ShowPixels);                 // REQ #078
   DDX_Control(pDX, IDC_SHOW_OVERLAY, c_ShowOverlay);               // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CFontDialogExplorer, CFormView)                                                    // REQ #078
    ON_EN_CHANGE(IDC_G, &CFontDialogExplorer::OnEnChangeG)                                           // REQ #078
    ON_EN_CHANGE(IDC_R, &CFontDialogExplorer::OnEnChangeR)                                           // REQ #078
    ON_EN_CHANGE(IDC_B, &CFontDialogExplorer::OnEnChangeB)                                           // REQ #078
    ON_BN_CLICKED(IDC_COLOR, &CFontDialogExplorer::OnBnClickedColor)                                 // REQ #078
    ON_CBN_SELENDOK(IDC_LANGUAGE, OnCbnSelendOkLanguage)                                             // REQ #078
    ON_BN_CLICKED(IDC_CF_APPLY, &CFontDialogExplorer::OnBnClickedCfApply)                            // REQ #078
    ON_BN_CLICKED(IDC_CF_ANSIONLY, &CFontDialogExplorer::OnBnClickedCfAnsionly)                      // REQ #078
    ON_BN_CLICKED(IDC_CF_BOTH, &CFontDialogExplorer::OnBnClickedCfBoth)                              // REQ #078
    ON_BN_CLICKED(IDC_CF_PRINTERFONTS, &CFontDialogExplorer::OnBnClickedCfPrinterfonts)              // REQ #078
    ON_BN_CLICKED(IDC_CF_SCREENFONTS, &CFontDialogExplorer::OnBnClickedCfScreenfonts)                // REQ #078
    ON_BN_CLICKED(IDC_CF_TTONLY, &CFontDialogExplorer::OnBnClickedCfTtonly)                          // REQ #078
    ON_BN_CLICKED(IDC_CF_EFFECTS, &CFontDialogExplorer::OnBnClickedCfEffects)                        // REQ #078
    ON_BN_CLICKED(IDC_CF_FIXEDPITCHONLY, &CFontDialogExplorer::OnBnClickedCfFixedpitchonly)          // REQ #078
    ON_BN_CLICKED(IDC_CF_FORCEFONTEXIST, &CFontDialogExplorer::OnBnClickedCfForcefontexist)          // REQ #078
    ON_BN_CLICKED(IDC_CF_INITTOLOGFONTSTRUCT, &CFontDialogExplorer::OnBnClickedCfInittologfontstruct)// REQ #078
    ON_BN_CLICKED(IDC_CF_LIMITSIZE, &CFontDialogExplorer::OnBnClickedCfLimitsize)                    // REQ #078
    ON_BN_CLICKED(IDC_CF_NOVECTORFONTS, &CFontDialogExplorer::OnBnClickedCfNovectorfonts)            // REQ #078
    ON_BN_CLICKED(IDC_CF_NOFACESEL, &CFontDialogExplorer::OnBnClickedCfNofacesel)                    // REQ #078
    ON_BN_CLICKED(IDC_CF_NOSCRIPTSEL, &CFontDialogExplorer::OnBnClickedCfNoscriptsel)                // REQ #078
    ON_BN_CLICKED(IDC_CF_NOSTYLESEL, &CFontDialogExplorer::OnBnClickedCfNostylesel)                  // REQ #078
    ON_BN_CLICKED(IDC_CF_NOSIZESEL, &CFontDialogExplorer::OnBnClickedCfNosizesel)                    // REQ #078
    ON_BN_CLICKED(IDC_CF_NOSIMULATIONS, &CFontDialogExplorer::OnBnClickedCfNosimulations)            // REQ #078
    ON_BN_CLICKED(IDC_CF_NOVERTFONTS, &CFontDialogExplorer::OnBnClickedCfNovertfonts)                // REQ #078
    ON_BN_CLICKED(IDC_CF_SCALABLEONLY, &CFontDialogExplorer::OnBnClickedCfScalableonly)              // REQ #078
    ON_BN_CLICKED(IDC_CF_SCRIPTSONLY, &CFontDialogExplorer::OnBnClickedCfScriptsonly)                // REQ #078
    ON_BN_CLICKED(IDC_CF_SELECTSCRIPT, &CFontDialogExplorer::OnBnClickedCfSelectscript)              // REQ #078
    ON_BN_CLICKED(IDC_CF_SHOWHELP, &CFontDialogExplorer::OnBnClickedCfShowhelp)                      // REQ #078
    ON_BN_CLICKED(IDC_CF_USESTYLE, &CFontDialogExplorer::OnBnClickedCfUsestyle)                      // REQ #078
    ON_BN_CLICKED(IDC_CF_WYSIWYG, &CFontDialogExplorer::OnBnClickedCfWysiwyg)                        // REQ #078
    ON_BN_CLICKED(IDC_FONT_DIALOG, &CFontDialogExplorer::OnBnClickedFontDialog)                      // REQ #078
    ON_BN_CLICKED(IDC_LFITALIC, &CFontDialogExplorer::OnBnClickedLfitalic)                           // REQ #078
    ON_BN_CLICKED(IDC_LFUNDERLINE, &CFontDialogExplorer::OnBnClickedLfunderline)                     // REQ #078
    ON_BN_CLICKED(IDC_LFSTRIKEOUT, &CFontDialogExplorer::OnBnClickedLfstrikeout)                     // REQ #078
    ON_CBN_SELENDOK(IDC_LFCHARSET, &CFontDialogExplorer::OnCbnSelendokLfcharset)                     // REQ #078
    ON_CBN_SELCHANGE(IDC_LFOUTPRECISION, &CFontDialogExplorer::OnCbnSelchangeLfoutprecision)         // REQ #078
    ON_CBN_SELENDOK(IDC_LFCLIPPRECISION, &CFontDialogExplorer::OnCbnSelendokLfclipprecision)         // REQ #078
    ON_CBN_SELENDOK(IDC_LFQUALITY, &CFontDialogExplorer::OnCbnSelendokLfquality)                     // REQ #078
    ON_CBN_SELENDOK(IDC_LFPITCH, &CFontDialogExplorer::OnCbnSelendokLfpitch)                         // REQ #078
    ON_CBN_SELENDOK(IDC_LFFAMILY, &CFontDialogExplorer::OnCbnSelendokLffamily)                       // REQ #078
    ON_CBN_SELENDOK(IDC_FACENAME, &CFontDialogExplorer::OnCbnSelendokFacename)                       // REQ #078
    ON_EN_CHANGE(IDC_LFORIENTATION, &CFontDialogExplorer::OnEnChangeLforientation)                   // REQ #078
    ON_EN_CHANGE(IDC_LFESCAPEMENT, &CFontDialogExplorer::OnEnChangeLfescapement)                     // REQ #078
    ON_EN_CHANGE(IDC_LFHEIGHT, &CFontDialogExplorer::OnEnChangeLfheight)                             // REQ #078
    ON_EN_CHANGE(IDC_LFWIDTH, &CFontDialogExplorer::OnEnChangeLfwidth)                               // REQ #078
    ON_BN_CLICKED(IDC_USE_PRINTER_DC, &CFontDialogExplorer::OnBnClickedUsePrinterDc)                 // REQ #078
    ON_BN_CLICKED(IDC_PRINTER, &CFontDialogExplorer::OnBnClickedPrinter)                             // REQ #078
    ON_EN_CHANGE(IDC_POINTSIZE, &CFontDialogExplorer::OnEnChangePointsize)                           // REQ #078
    ON_BN_CLICKED(IDC_SET_POINTHEIGHT, &CFontDialogExplorer::OnBnClickedSetPointheight)              // REQ #078
    ON_BN_CLICKED(IDC_SHOW_CODE, &CFontDialogExplorer::OnBnClickedShowCode)                          // REQ #078
    ON_BN_CLICKED(IDC_COPY, &CFontDialogExplorer::OnBnClickedCopy)                                   // REQ #078
    ON_WM_SIZE()                                                                                     // REQ #078
    ON_EN_CHANGE(IDC_LPSZSTYLE_IN, &CFontDialogExplorer::OnEnChangeLpszstyleIn)                      // REQ #078
    ON_EN_CHANGE(IDC_DISPLAY_TEXT, &CFontDialogExplorer::OnEnChangeDisplayText)                      // REQ #078
    ON_BN_CLICKED(IDC_SHOW_PIXELS, &CFontDialogExplorer::OnBnClickedShowPixels)                      // REQ #078
    ON_BN_CLICKED(IDC_SHOW_OVERLAY, &CFontDialogExplorer::OnBnClickedShowOverlay)                    // REQ #078
    ON_WM_VSCROLL()                                                                                  // REQ #078
END_MESSAGE_MAP()                                                                                    // REQ #078

// CFontDialogExplorer diagnostics                                  // REQ #078
                                                                    // REQ #078
#ifdef _DEBUG                                                       // REQ #078
void CFontDialogExplorer::AssertValid() const                       // REQ #078
{                                                                   // REQ #078
        CFormView::AssertValid();                                   // REQ #078
}                                                                   // REQ #078
                                                                    // REQ #078
#ifndef _WIN32_WCE                                                  // REQ #078
void CFontDialogExplorer::Dump(CDumpContext& dc) const              // REQ #078
{                                                                   // REQ #078
        CFormView::Dump(dc);                                        // REQ #078
}                                                                   // REQ #078
#endif                                                              // REQ #078
#endif //_DEBUG                                                     // REQ #078
                                                                    // REQ #078
static const IDData t_Weight[] = {                                  // REQ #078
   { IDS_FW_DONTCARE,     0},                                       // REQ #078
   { IDS_FW_THIN,       100},                                       // REQ #078
   { IDS_FW_EXTRALIGHT, 200},                                       // REQ #078
   { IDS_FW_ULTRALIGHT, 200},                                       // REQ #078
   { IDS_FW_LIGHT,      300},                                       // REQ #078
   { IDS_FW_NORMAL,     400},                                       // REQ #078
   { IDS_FW_REGULAR,    400},                                       // REQ #078
   { IDS_FW_MEDIUM,     500},                                       // REQ #078
   { IDS_FW_SEMIBOLD,   600},                                       // REQ #078
   { IDS_FW_DEMIBOLD,   600},                                       // REQ #078
   { IDS_FW_BOLD,       700},                                       // REQ #078
   { IDS_FW_EXTRABOLD,  800},                                       // REQ #078
   { IDS_FW_ULTRABOLD,  800},                                       // REQ #078
   { IDS_FW_HEAVY,      900},                                       // REQ #078
   { IDS_FW_BLACK,      900},                                       // REQ #078
   { 0, 0} // EOT                                                   // REQ #078
};                                                                  // REQ #078
                                                                    // REQ #078
// This encompasses the character sets for Windows 2000             // REQ #078
static const IDData t_CharSet[] = {                                 // REQ #078
   { IDS_ANSI_CHARSET, ANSI_CHARSET},                               // REQ #078
   { IDS_BALTIC_CHARSET,   BALTIC_CHARSET},                         // REQ #078
   { IDS_CHINESEBIG5_CHARSET, CHINESEBIG5_CHARSET},                 // REQ #078
   { IDS_DEFAULT_CHARSET, DEFAULT_CHARSET},                         // REQ #078
   { IDS_EASTEUROPE_CHARSET,       EASTEUROPE_CHARSET},             // REQ #078
   { IDS_GB2312_CHARSET, GB2312_CHARSET},                           // REQ #078
   { IDS_GREEK_CHARSET,    GREEK_CHARSET},                          // REQ #078
   { IDS_HANGEUL_CHARSET, HANGEUL_CHARSET},                         // REQ #078
   { IDS_MAC_CHARSET,      MAC_CHARSET},                            // REQ #078
   { IDS_OEM_CHARSET, OEM_CHARSET},                                 // REQ #078
   { IDS_RUSSIAN_CHARSET,  RUSSIAN_CHARSET},                        // REQ #078
   { IDS_SHIFTJIS_CHARSET, SHIFTJIS_CHARSET},                       // REQ #078
   { IDS_SYMBOL_CHARSET, SYMBOL_CHARSET},                           // REQ #078
   { IDS_TURKISH_CHARSET,  TURKISH_CHARSET},                        // REQ #078
   { 0, 0}, // EOT                                                  // REQ #078
};                                                                  // REQ #078
                                                                    // REQ #078
static const IDData t_CharSet95[] = {                               // REQ #078
   { IDS_JOHAB_CHARSET, JOHAB_CHARSET},                             // REQ #078
   { IDS_HEBREW_CHARSET, HEBREW_CHARSET},                           // REQ #078
   { IDS_ARABIC_CHARSET, ARABIC_CHARSET},                           // REQ #078
   { IDS_GREEK_CHARSET, GREEK_CHARSET},                             // REQ #078
   { IDS_TURKISH_CHARSET, TURKISH_CHARSET},                         // REQ #078
   { IDS_THAI_CHARSET, THAI_CHARSET},                               // REQ #078
   { IDS_EASTEUROPE_CHARSET, EASTEUROPE_CHARSET},                   // REQ #078
   { IDS_RUSSIAN_CHARSET, RUSSIAN_CHARSET},                         // REQ #078
   { IDS_MAC_CHARSET, MAC_CHARSET},                                 // REQ #078
   { IDS_BALTIC_CHARSET, BALTIC_CHARSET},                           // REQ #078
   { 0, 0 } // EOT                                                  // REQ #078
};                                                                  // REQ #078
                                                                    // REQ #078
static const IDData t_OutPrecision[] = {                            // REQ #078
   { IDS_OUT_CHARACTER_PRECIS, OUT_CHARACTER_PRECIS},               // REQ #078
   { IDS_OUT_DEFAULT_PRECIS, OUT_DEFAULT_PRECIS},                   // REQ #078
   { IDS_OUT_DEVICE_PRECIS, OUT_DEVICE_PRECIS},                     // REQ #078
   { IDS_OUT_OUTLINE_PRECIS, OUT_OUTLINE_PRECIS},                   // REQ #078
   { IDS_OUT_RASTER_PRECIS, OUT_RASTER_PRECIS},                     // REQ #078
   { IDS_OUT_STRING_PRECIS, OUT_STRING_PRECIS},                     // REQ #078
   { IDS_OUT_STROKE_PRECIS, OUT_STROKE_PRECIS},                     // REQ #078
   { IDS_OUT_TT_ONLY_PRECIS, OUT_TT_ONLY_PRECIS},                   // REQ #078
   { IDS_OUT_TT_PRECIS, OUT_TT_PRECIS},                             // REQ #078
   { 0, 0 } // EOT                                                  // REQ #078
};                                                                  // REQ #078
                                                                    // REQ #078
static const IDData t_ClipPrecision[] = {                           // REQ #078
//        { IDS_CLIP_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS},      // REQ #078
   { IDS_CLIP_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS},                 // REQ #078
   { IDS_CLIP_STROKE_PRECIS, CLIP_STROKE_PRECIS},                   // REQ #078
//        { IDS_CLIP_MASK, CLIP_MASK},                              // REQ #078
   { IDS_CLIP_EMBEDDED, CLIP_EMBEDDED},                             // REQ #078
   { IDS_CLIP_LH_ANGLES, CLIP_LH_ANGLES},                           // REQ #078
//      { IDS_CLIP_TT_ALWAYS, CLIP_TT_ALWAYS},                      // REQ #078
   { 0, 0} // EOT                                                   // REQ #078
};                                                                  // REQ #078
                                                                    // REQ #078
static const IDData t_Pitch[] = {                                   // REQ #078
   { IDS_DEFAULT_PITCH, DEFAULT_PITCH},                             // REQ #078
   { IDS_FIXED_PITCH, FIXED_PITCH},                                 // REQ #078
   { IDS_VARIABLE_PITCH, VARIABLE_PITCH},                           // REQ #078
   { 0, 0 } // EOT                                                  // REQ #078
};                                                                  // REQ #078
                                                                    // REQ #078
static const IDData t_Family[] = {                                  // REQ #078
   { IDS_FF_DECORATIVE, FF_DECORATIVE},                             // REQ #078
   { IDS_FF_DONTCARE,   FF_DONTCARE},                               // REQ #078
   { IDS_FF_MODERN,     FF_MODERN},                                 // REQ #078
   { IDS_FF_ROMAN,      FF_ROMAN},                                  // REQ #078
   { IDS_FF_SCRIPT,     FF_SCRIPT},                                 // REQ #078
   { IDS_FF_SWISS,      FF_SWISS},                                  // REQ #078
   { 0, 0} // EOT                                                   // REQ #078
};                                                                  // REQ #078
                                                                    // REQ #078
static const IDData t_Quality[] = {                                 // REQ #078
   { IDS_DEFAULT_QUALITY, DEFAULT_QUALITY},                         // REQ #078
   { IDS_ANTIALIASED_QUALITY, ANTIALIASED_QUALITY},                 // REQ #078
   { IDS_CLEARTYPE_QUALITY, CLEARTYPE_QUALITY},                     // REQ #078
   { IDS_CLEARTYPE_NATURAL_QUALITY, CLEARTYPE_QUALITY},             // REQ #078
   { IDS_DRAFT_QUALITY,   DRAFT_QUALITY},                           // REQ #078
   { IDS_NONANTIALIASED_QUALITY, NONANTIALIASED_QUALITY},           // REQ #078
   { IDS_PROOF_QUALITY,   PROOF_QUALITY},                           // REQ #078
   { 0, 0 } // EOT                                                  // REQ #078
};                                                                  // REQ #078
                                                                    // REQ #078
static const IDData Languages[] = {                                 // REQ #078
   { IDS_C6, LANGUAGE_C6},                                          // REQ #078
   { IDS_C2008, LANGUAGE_C2008},                                    // REQ #078
   { IDS_MFC6, LANGUAGE_MFC6},                                      // REQ #078
   { IDS_MFC2008, LANGUAGE_MFC2008},                                // REQ #078
   { 0, 0} // EOT                                                   // REQ #078
};                                                                  // REQ #078
                                                                    // REQ #078
// CFontDialogExplorer message handlers                             // REQ #078

/****************************************************************************
*                     CFontDialogExplorer::OnInitialUpdate
* Result: void
*       
* Effect: 
*       Initializes the controls
****************************************************************************/

void CFontDialogExplorer::OnInitialUpdate()                         // REQ #078
    {                                                               // REQ #078
     CFormView::OnInitialUpdate();                                  // REQ #078
                                                                    // REQ #078
     CString s;                                                     // REQ #078
     s.LoadString(IDS_CFONTDIALOG_EXPLORER_CAPTION);                // REQ #078
     GetParentFrame()->SetWindowText(s);                            // REQ #078
                                                                    // REQ #078
     c_lfWeight.AddStrings(t_Weight, FW_DONTCARE);                  // REQ #078
                                                                    // REQ #078
     c_lfCharSet.AddStrings(t_CharSet, ANSI_CHARSET);               // REQ #078
                                                                    // REQ #078
     c_lfOrientation.ShowWindow(SW_HIDE);                           // REQ #078
     x_lfOrientation.EnableWindow(FALSE);                           // REQ #078
     c_SpinOrientation.EnableWindow(FALSE);                         // REQ #078
                                                                    // REQ #078
     c_SpinOrientation.SetBuddy(&c_lfOrientation);                  // REQ #078
     c_SpinOrientation.SetRange(-3600, 3600);                       // REQ #078
     c_SpinOrientation.SetPos(0);                                   // REQ #078
                                                                    // REQ #078
     c_SpinEscapement.SetBuddy(&c_lfEscapement);                    // REQ #078
     c_SpinEscapement.SetRange(-3600, 3600);                        // REQ #078
     c_SpinEscapement.SetPos(0);                                    // REQ #078
                                                                    // REQ #078
     c_lfOutPrecision.AddStrings(t_OutPrecision, OUT_DEFAULT_PRECIS);// REQ #078
     c_lfClipPrecision.AddStrings(t_ClipPrecision, CLIP_DEFAULT_PRECIS);// REQ #078
     c_lfPitch.AddStrings(t_Pitch, DEFAULT_PITCH);                  // REQ #078
     c_lfFamily.AddStrings(t_Family, FF_DONTCARE);                  // REQ #078
     c_lfQuality.AddStrings(t_Quality, DEFAULT_QUALITY);            // REQ #078
                                                                    // REQ #078
     c_Language.AddStrings(Languages, LANGUAGE_MFC2008);            // REQ #078
                                                                    // REQ #078
     c_SpinRed.SetRange(0, 255);                                    // REQ #078
     c_SpinRed.SetPos(0);                                           // REQ #078
     c_SpinGreen.SetRange(0, 255);                                  // REQ #078
     c_SpinGreen.SetPos(0);                                         // REQ #078
     c_SpinBlue.SetRange(0, 255);                                   // REQ #078
     c_SpinBlue.SetPos(0);                                          // REQ #078
                                                                    // REQ #078
     c_SpinPointSize.SetRange(0, 10240);                            // REQ #078
     c_SpinPointSize.SetPos(100); // 10pt                           // REQ #078
                                                                    // REQ #078
     c_SpinSizeMin.SetRange(0, 1024);                               // REQ #078
     c_SpinSizeMin.SetPos(0);                                       // REQ #078
     c_SpinSizeMax.SetRange(0, 1024);                               // REQ #078
     c_SpinSizeMax.SetPos(24);                                      // REQ #078
                                                                    // REQ #078
     CodeFont.CreatePointFont(90, _T("Courier New"));               // REQ #078
     c_Code.SetFont(&CodeFont);                                     // REQ #078
                                                                    // REQ #078
     c_lStructSize.SetWindowText(ToString(_T("%d"), sizeof(CHOOSEFONT)));// REQ #078
     c_hwndOwner.SetWindowText(_T("this"));                         // REQ #078
     c_hDC.SetWindowText(_T("NULL"));                               // REQ #078
                                                                    // REQ #078
     c_SetPointHeight.SetDirection(DrawArrow::ARROW_W);             // REQ #078
     c_Copy.LoadBitmaps(IDB_COPY);                                  // REQ #078
                                                                    // REQ #078
     CRect left;                                                    // REQ #078
     c_Status.GetWindowRect(&left);                                 // REQ #078
     ScreenToClient(&left);                                         // REQ #078
                                                                    // REQ #078
     CRect right;                                                   // REQ #078
     c_FontSample.GetWindowRect(&right);                            // REQ #078
     ScreenToClient(&right);                                        // REQ #078
                                                                    // REQ #078
     gap = right.left - left.right;                                 // REQ #078
                                                                    // REQ #078
     c_SpinOrientation.SetBuddy(&c_lfOrientation);                  // REQ #078
     c_SpinOrientation.SetRange(-3600, 3600);                       // REQ #078
     c_SpinOrientation.SetPos(0);                                   // REQ #078
                                                                    // REQ #078
     c_SpinEscapement.SetBuddy(&c_lfEscapement);                    // REQ #078
     c_SpinEscapement.SetRange(-3600, 3600);                        // REQ #078
     c_SpinEscapement.SetPos(0);                                    // REQ #078
                                                                    // REQ #078
                                                                    // REQ #078
     s.LoadString(IDS_FONTDIALOG_SAMPLE);                           // REQ #078
     c_FontSample.SetWindowText(s);                                 // REQ #078
     c_DisplayText.SetWindowText(s);                                // REQ #078
     display_options opts = c_FontSample.GetOpts();                 // REQ #078
     opts.output = display_options::TEXTOUT;                        // REQ #078
     c_FontSample.SetOpts(opts);                                    // REQ #078
     c_ShowPixels.SetCheck(opts.ShowPixels ? BST_CHECKED : BST_UNCHECKED);// REQ #078
     c_ShowOverlay.SetCheck(opts.ShowOverlay ? BST_CHECKED : BST_UNCHECKED);// REQ #078
                                                                    // REQ #078
     initialized = TRUE;                                            // REQ #078
     updateControls();                                              // REQ #078
     updateCode();                                                  // REQ #078
     updateStatus();                                                // REQ #078
    } // CFontDialogExplorer::OnInitialUpdate                       // REQ #078

/****************************************************************************
*                       CFontDialogExplorer::OnEnChangeG
* Result: void
*       
* Effect: 
*       Green color changed
****************************************************************************/

void CFontDialogExplorer::OnEnChangeG()                             // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078


/****************************************************************************
*                       CFontDialogExplorer::OnEnChangeR
* Result: void
*       
* Effect: 
*       Changes red color
****************************************************************************/

void CFontDialogExplorer::OnEnChangeR()                             // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078


/****************************************************************************
*                       CFontDialogExplorer::OnEnChangeB
* Result: void
*       
* Effect: 
*       Changes blue color
****************************************************************************/

void CFontDialogExplorer::OnEnChangeB()                             // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                    CFontDialogExplorer::OnBnClickedColor
* Result: void
*       
* Effect: 
*       Chooses color
****************************************************************************/

void CFontDialogExplorer::OnBnClickedColor()                        // REQ #078
    {                                                               // REQ #078
     COLORREF rgb = RGB((BYTE)c_SpinRed.GetPos32(),                 // REQ #078
                        (BYTE)c_SpinGreen.GetPos32(),               // REQ #078
                        (BYTE)c_SpinBlue.GetPos32());               // REQ #078
     CColorDialog dlg(rgb, CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT); // REQ #078
     if(dlg.DoModal() != IDOK)                                      // REQ #078
        return;                                                     // REQ #078
                                                                    // REQ #078
     rgb = dlg.GetColor();                                          // REQ #078
     c_SpinRed.SetPos32(GetRValue(rgb));                            // REQ #078
     c_SpinGreen.SetPos32(GetGValue(rgb));                          // REQ #078
     c_SpinBlue.SetPos32(GetBValue(rgb));                           // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                   CFontDialogExplorer::OnCbnSelendOkLanguage
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnCbnSelendOkLanguage()                   // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    } // CFontDialogExplorer::OnCbnSelendOkLanguage                 // REQ #078

/****************************************************************************
*                       CFontDialogExplorer::updateCode
* Result: void
*       
* Effect: 
*       Updates the code
****************************************************************************/

void CFontDialogExplorer::updateCode()                              // REQ #078
    {                                                               // REQ #078
     if(!initialized)                                               // REQ #078
         return;                                                    // REQ #078
                                                                    // REQ #078
     int language = (int)c_Language.GetItemData(c_Language.GetCurSel());// REQ #078
                                                                    // REQ #078
     CString code;                                                  // REQ #078
                                                                    // REQ #078
                                                                    // REQ #078
     switch(language)                                               // REQ #078
        { /* language */                                            // REQ #078
         case LANGUAGE_C6:                                          // REQ #078
         case LANGUAGE_C2008:                                       // REQ #078
            if(c_CF_USESTYLE.GetCheck() == BST_CHECKED)             // REQ #078
               { /* use style */                                    // REQ #078
                code += _T("#define MAX_BUFFER_LENGTH 256\r\n");    // REQ #078
                code += _T("   TCHAR style[MAX_BUFFER_LENGTH];\r\n");// REQ #078
               } /* use style */                                    // REQ #078
                                                                    // REQ #078
            if(c_UsePrinterDC.GetCheck() == BST_CHECKED)            // REQ #078
               { /* use printer DC */                               // REQ #078
                code += _T("   HDC DC;\r\n");                       // REQ #078
               } /* use printer DC */                               // REQ #078
            code += _T("   CHOOSEFONT cf = { sizeof(CHOOSEFONT) }\r\n");// REQ #078
            break;                                                  // REQ #078
        } /* language */                                            // REQ #078
                                                                    // REQ #078
     code += _T("   LOGFONT lf = {0};\r\n");                        // REQ #078
                                                                    // REQ #078
     CString initlogfont;                                           // REQ #078
     if(c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED)         // REQ #078
        { /* use logfont */                                         // REQ #078
         CString s;                                                 // REQ #078
                                                                    // REQ #078
         initlogfont = _T("&lf");                                   // REQ #078
                                                                    // REQ #078
         if((c_UsePrinterDC.GetCheck() == BST_CHECKED &&            // REQ #078
             PrinterDC.m_hDC != NULL) ||                            // REQ #078
            c_ShowPointFontCode.GetCheck() == BST_CHECKED)          // REQ #078
            { /* use DC */                                          // REQ #078
             switch(language)                                       // REQ #078
                { /* language */                                    // REQ #078
                 case LANGUAGE_MFC6:                                // REQ #078
                 case LANGUAGE_MFC2008:                             // REQ #078
                    code += _T("   CDC DC;\r\n");                   // REQ #078
                    CString t;                                      // REQ #078
                    t.LoadString(IDS_SETUP_DC);                     // REQ #078
                    code += ToString(_T("   // %s\r\n"), t);        // REQ #078
                    break;                                          // REQ #078
                } /* language */                                    // REQ #078
            } /* use DC */                                          // REQ #078
                                                                    // REQ #078
         if(c_ShowPointFontCode.GetCheck() == BST_CHECKED)          // REQ #078
            { /* show font height code */                           // REQ #078
             CString t = ToString(_T("   CPoint pt(0, ::MulDiv(DC.GetDeviceCaps(LOGPIXELSY), %d, 720));\r\n"), c_SpinPointSize.GetPos32());// REQ #078
             t += _T("   DC.DPtoLP(&pt)\r\n");                      // REQ #078
             t += _T("   CPoint org(0, 0);\r\n");                   // REQ #078
             t += _T("   DC.DPtoLP(&org);\r\n");                    // REQ #078
             t += _T("   lf.lfHeight = -abs(pt.y - org.y);\r\n");   // REQ #078
             code += t;                                             // REQ #078
            } /* show font height code */                           // REQ #078
         else                                                       // REQ #078
            { /* just set height */                                 // REQ #078
             c_lfHeight.GetWindowText(s);                           // REQ #078
             if(_ttoi(s) != 0)                                      // REQ #078
                code += ToString(_T("   lf.lfHeight = %s;\r\n"), s);// REQ #078
            } /* just set height */                                 // REQ #078
                                                                    // REQ #078
         c_lfWidth.GetWindowText(s);                                // REQ #078
         if(_ttoi(s) != 0)                                          // REQ #078
            code += ToString(_T("   lf.lfWidth = %s;\r\n"), s);     // REQ #078
                                                                    // REQ #078
         if(c_SpinEscapement.GetPos32() != 0)                       // REQ #078
            code += ToString(_T("   lf.lfEscapement = %d;\r\n"), c_SpinEscapement.GetPos32());// REQ #078
                                                                    // REQ #078
         if(c_lfWeight.GetItemData(c_lfWeight.GetCurSel()) != 0)    // REQ #078
            { /* has weight */                                      // REQ #078
             c_lfWeight.GetLBText(c_lfWeight.GetCurSel(), s);       // REQ #078
             code += ToString(_T("   lf.lfWeight = %s;\r\n"), s);   // REQ #078
            } /* has weight */                                      // REQ #078
                                                                    // REQ #078
         if(c_lfItalic.GetCheck() == BST_CHECKED)                   // REQ #078
            code += _T("   lf.lfItalic = TRUE;\r\n");               // REQ #078
                                                                    // REQ #078
         if(c_lfUnderline.GetCheck() == BST_CHECKED)                // REQ #078
            code += _T("   lf.lfUnderline = TRUE;\r\n");            // REQ #078
                                                                    // REQ #078
         if(c_lfStrikeOut.GetCheck() == BST_CHECKED)                // REQ #078
            code += _T("   lf.lfStrikeOut = TRUE;\r\n");            // REQ #078
                                                                    // REQ #078
         if(c_lfCharSet.GetItemData(c_lfCharSet.GetCurSel()) != 0)  // REQ #078
            { /* charset */                                         // REQ #078
             c_lfCharSet.GetLBText(c_lfCharSet.GetCurSel(), s);     // REQ #078
             code += ToString(_T("   lf.lfCharSet = %s;\r\n"), s);  // REQ #078
            } /* charset */                                         // REQ #078
                                                                    // REQ #078
         if(c_lfOutPrecision.GetItemData(c_lfOutPrecision.GetCurSel()) != 0)// REQ #078
            { /* precision */                                       // REQ #078
             c_lfOutPrecision.GetLBText(c_lfOutPrecision.GetCurSel(), s);// REQ #078
             code += ToString(_T("   lf.lfOutPrecision = %s;\r\n"), s);// REQ #078
            } /* precision */                                       // REQ #078
                                                                    // REQ #078
         if(c_lfQuality.GetItemData(c_lfQuality.GetCurSel()) != 0)  // REQ #078
            { /* quality */                                         // REQ #078
             c_lfQuality.GetLBText(c_lfQuality.GetCurSel(), s);     // REQ #078
             code += ToString(_T("   lf.lfQuality = %s;\r\n"), s);  // REQ #078
            } /* quality */                                         // REQ #078
                                                                    // REQ #078
         CString pitch;                                             // REQ #078
         if(c_lfPitch.GetItemData(c_lfPitch.GetCurSel()) != 0)      // REQ #078
            c_lfPitch.GetLBText(c_lfPitch.GetCurSel(), pitch);      // REQ #078
                                                                    // REQ #078
         CString family;                                            // REQ #078
         if(c_lfFamily.GetItemData(c_lfFamily.GetCurSel()) != 0)    // REQ #078
            c_lfFamily.GetLBText(c_lfFamily.GetCurSel(), family);   // REQ #078
                                                                    // REQ #078
         if(!pitch.IsEmpty() || !family.IsEmpty())                  // REQ #078
            { /* has pitch or family */                             // REQ #078
             s = pitch;                                             // REQ #078
             if(!s.IsEmpty() && !family.IsEmpty())                  // REQ #078
                s += _T(" | ");                                     // REQ #078
             s += family;                                           // REQ #078
             code += ToString(_T("   lf.lfPitchAndFamily = %s;\r\n"), s);// REQ #078
            } /* has pitch or family */                             // REQ #078
                                                                    // REQ #078
         if(c_lfFaceName.GetCurSel() >= 0)                          // REQ #078
            { /* has font */                                        // REQ #078
             c_lfFaceName.GetLBText(c_lfFaceName.GetCurSel(), s);   // REQ #078
             switch(language)                                       // REQ #078
                { /* language facename */                           // REQ #078
                 case LANGUAGE_C6:                                  // REQ #078
                 case LANGUAGE_MFC6:                                // REQ #078
                    code += ToString(_T("   lstrcpyn(lf.lfFaceName, _T(\"%s\"), LF_FACESIZE;\r\n"), s);// REQ #078
                    break;                                          // REQ #078
                 case LANGUAGE_C2008:                               // REQ #078
                 case LANGUAGE_MFC2008:                             // REQ #078
                    code += ToString(_T("   _tcscpy_s(lf.lfFaceName, _countof(lf.lfFaceName), _T(\"%s\");\r\n"), s);// REQ #078
                    break;                                          // REQ #078
                } /* language facename */                           // REQ #078
            } /* has font */                                        // REQ #078
         code += _T("\r\n");                                        // REQ #078
        } /* use logfont */                                         // REQ #078
     else                                                           // REQ #078
        { /* no logfont */                                          // REQ #078
         initlogfont = _T("NULL");                                  // REQ #078
        } /* no logfont */                                          // REQ #078
                                                                    // REQ #078
     CString flags;                                                 // REQ #078
     static const UINT MFCindent = 21; // based on where we want indentation// REQ #078
     static const UINT Cindent = 14;                                // REQ #078
     UINT indent = 0;                                               // REQ #078
     switch(language)                                               // REQ #078
        { /* language */                                            // REQ #078
         case LANGUAGE_C6:                                          // REQ #078
         case LANGUAGE_C2008:                                       // REQ #078
            indent = Cindent;                                       // REQ #078
            break;                                                  // REQ #078
         case LANGUAGE_MFC6:                                        // REQ #078
         case LANGUAGE_MFC2008:                                     // REQ #078
            indent = MFCindent;                                     // REQ #078
            indent += initlogfont.GetLength();                      // REQ #078
            break;                                                  // REQ #078
        } /* language */                                            // REQ #078

#define AddFlag(x) {if(c_##x.GetCheck() == BST_CHECKED)                      \
                      {                                                      \
                       if(!flags.IsEmpty())                                  \
                          flags += _T(" |\r\n") + CString(_T(' '), indent);  \
                       flags += _T(#x);                                      \
                      }                                                      \
                   }
                                                                    // REQ #078
     AddFlag(CF_APPLY);                                             // REQ #078
     AddFlag(CF_ANSIONLY);                                          // REQ #078
     AddFlag(CF_BOTH);                                              // REQ #078
                                                                    // REQ #078
     if(c_CF_BOTH.GetCheck() != BST_CHECKED)                        // REQ #078
        { /* not both */                                            // REQ #078
         AddFlag(CF_PRINTERFONTS);                                  // REQ #078
         AddFlag(CF_SCREENFONTS);                                   // REQ #078
        } /* not both */                                            // REQ #078
                                                                    // REQ #078
     AddFlag(CF_TTONLY);                                            // REQ #078
     AddFlag(CF_EFFECTS);                                           // REQ #078
     AddFlag(CF_FIXEDPITCHONLY);                                    // REQ #078
     AddFlag(CF_FORCEFONTEXIST);                                    // REQ #078
     AddFlag(CF_INITTOLOGFONTSTRUCT);                               // REQ #078
     AddFlag(CF_LIMITSIZE);                                         // REQ #078
     AddFlag(CF_NOVECTORFONTS);                                     // REQ #078
     AddFlag(CF_NOFACESEL);                                         // REQ #078
     AddFlag(CF_NOSCRIPTSEL);                                       // REQ #078
     AddFlag(CF_NOSTYLESEL);                                        // REQ #078
     AddFlag(CF_NOSIZESEL);                                         // REQ #078
     AddFlag(CF_NOSIMULATIONS);                                     // REQ #078
     AddFlag(CF_NOVERTFONTS);                                       // REQ #078
     AddFlag(CF_SCALABLEONLY);                                      // REQ #078
     AddFlag(CF_SCRIPTSONLY);                                       // REQ #078
     AddFlag(CF_SELECTSCRIPT);                                      // REQ #078
     AddFlag(CF_SHOWHELP);                                          // REQ #078
     AddFlag(CF_USESTYLE);                                          // REQ #078
     AddFlag(CF_WYSIWYG);                                           // REQ #078
                                                                    // REQ #078
     if(flags.IsEmpty())                                            // REQ #078
        flags = _T("0");                                            // REQ #078
#undef AddFlag                                                      // REQ #078
                                                                    // REQ #078
     switch(language)                                               // REQ #078
        { /* language */                                            // REQ #078
         case LANGUAGE_C6:                                          // REQ #078
         case LANGUAGE_C2008:                                       // REQ #078
            { /* C */                                               // REQ #078
             CString owner;                                         // REQ #078
             c_hwndOwner.GetWindowText(owner);                      // REQ #078
             CString dc;                                            // REQ #078
             if(c_UsePrinterDC.GetCheck() == BST_CHECKED && PrinterDC.m_hDC != NULL)// REQ #078
                { /* use printer DC */                              // REQ #078
                 CString t;                                         // REQ #078
                 t.LoadString(IDS_SETUP_DC);                        // REQ #078
                 code += ToString(_T("   // %s\r\n"), t);           // REQ #078
                 dc = _T("   cf.hDC = DC;\r\n");                    // REQ #078
                } /* use printer DC */                              // REQ #078
                                                                    // REQ #078
             int pointsize = c_SpinPointSize.GetPos32();            // REQ #078
                                                                    // REQ #078
             CString rgbColors;                                     // REQ #078
             if(c_CF_EFFECTS.GetCheck() == BST_CHECKED)             // REQ #078
                { /* use colors */                                  // REQ #078
                 rgbColors.Format(_T("   cf.rgbColors = RGB(%d, %d, %d);\r\n"),// REQ #078
                                  c_SpinRed.GetPos32(),             // REQ #078
                                  c_SpinGreen.GetPos32(),           // REQ #078
                                  c_SpinBlue.GetPos32());           // REQ #078
                } /* use colors */                                  // REQ #078
                                                                    // REQ #078
             CString maxsize;                                       // REQ #078
             CString minsize;                                       // REQ #078
             if(c_CF_LIMITSIZE.GetCheck() == BST_CHECKED)           // REQ #078
                { /* limits */                                      // REQ #078
                 minsize.Format(_T("   cf.nSizeMin = %d\r\n"), c_SpinSizeMin.GetPos32());// REQ #078
                 maxsize.Format(_T("   cf.nSizeMax = %d\r\n"), c_SpinSizeMax.GetPos32());// REQ #078
                 } /* limits */                                     // REQ #078
                                                                    // REQ #078
             CString usestyle;                                      // REQ #078
                                                                    // REQ #078
             if(c_CF_USESTYLE.GetCheck() == BST_CHECKED)            // REQ #078
                { /* use style */                                   // REQ #078
                 CString style;                                     // REQ #078
                 c_lpszStyleIn.GetWindowText(style);                // REQ #078
                 switch(language)                                   // REQ #078
                    { /* C6/C2008 */                                // REQ #078
                     case LANGUAGE_C6:                              // REQ #078
                        if(!style.IsEmpty())                        // REQ #078
                           usestyle += ToString(_T("   lstrcpyn(style, _T(\"%s\"), MAX_BUFFER_LENGTH)\r\n"), style);// REQ #078
                        break;                                      // REQ #078
                     case LANGUAGE_C2008:                           // REQ #078
                        if(!style.IsEmpty())                        // REQ #078
                           usestyle += ToString(_T("   _tcscpy_s(style, MAX_BUFFER_LENGTH, _T(\"%s\"))\r\n"), style);// REQ #078
                        break;                                      // REQ #078
                    } /* C6/C2008 */                                // REQ #078
                } /* use style */                                   // REQ #078
                                                                    // REQ #078
             CString s;                                             // REQ #078
             s.Format(                                              // REQ #078
                      _T("   cf.hwndOwner = %s;\r\n")               // REQ #078
                      _T("%s")                                      // REQ #078
                      _T("   cf.lpLogFont = %s;\r\n")               // REQ #078
                      _T("   cf.Flags = %s;\r\n")                   // REQ #078
                      _T("%s")                                      // REQ #078
                      _T("%s")                                      // REQ #078
                      _T("%s")                                      // REQ #078
                      _T("%s")                                      // REQ #078
                      _T("\r\n"),                                   // REQ #078
                      owner,                                        // REQ #078
                      dc,                                           // REQ #078
                      _T("&lf"),                                    // REQ #078
                      flags,                                        // REQ #078
                      rgbColors,                                    // REQ #078
                      minsize,                                      // REQ #078
                      maxsize,                                      // REQ #078
                      usestyle);                                    // REQ #078
             code += s;                                             // REQ #078
                                                                    // REQ #078
             CString action;                                        // REQ #078
             action.LoadString(IDS_APPROPRIATE_ACTION);             // REQ #078
                                                                    // REQ #078
             s.Format(_T("   if(!ChooseFont(&cf))\r\n")             // REQ #078
                      _T("      return; // %s\r\n"),                // REQ #078
                     action);                                       // REQ #078
             code += s;                                             // REQ #078
            } /* C */                                               // REQ #078
            break;                                                  // REQ #078
         //*********************************************************// REQ #078
         // MFC                                                     // REQ #078
         //*********************************************************// REQ #078
         case LANGUAGE_MFC6:                                        // REQ #078
         case LANGUAGE_MFC2008:                                     // REQ #078
            { /* MFC */                                             // REQ #078
             CString s;                                             // REQ #078
                                                                    // REQ #078
             if((c_UsePrinterDC.GetCheck() == BST_CHECKED &&        // REQ #078
                 PrinterDC.m_hDC != NULL))                          // REQ #078
                { /* use DC */                                      // REQ #078
                 s.Format(_T("   CFontDialog dlg(%s, %s, &DC);\r\n"),// REQ #078
                          initlogfont,                              // REQ #078
                          flags);                                   // REQ #078
                } /* use DC */                                      // REQ #078
             else                                                   // REQ #078
                { /* no DC */                                       // REQ #078
                 s.Format(_T("   CFontDialog dlg(%s, %s);\r\n"),    // REQ #078
                          initlogfont,                              // REQ #078
                          flags);                                   // REQ #078
                } /* no DC */                                       // REQ #078
                                                                    // REQ #078
             if(c_CF_EFFECTS.GetCheck() == BST_CHECKED)             // REQ #078
                { /* set colors */                                  // REQ #078
                 s += ToString(_T("   dlg.m_cf.rgbColors = RGB(%d, %d, %d);\r\n"),// REQ #078
                                c_SpinRed.GetPos32(),               // REQ #078
                                c_SpinGreen.GetPos32(),             // REQ #078
                                c_SpinBlue.GetPos32());             // REQ #078
                } /* set colors */                                  // REQ #078
                                                                    // REQ #078
             if(c_CF_USESTYLE.GetCheck() == BST_CHECKED)            // REQ #078
                { /* use style */                                   // REQ #078
                 CString style;                                     // REQ #078
                 c_lpszStyleIn.GetWindowText(style);                // REQ #078
                                                                    // REQ #078
                 s += _T("   static const int MAX_BUFFER_LENGTH = 256;\r\n");// REQ #078
                 if(!style.IsEmpty())                               // REQ #078
                    s += ToString(_T("   CString style(\"%s\");\r\n"), style);// REQ #078
                 s += _T("   dlg.m_cf.lpszStyle = style.GetBuffer(MAX_BUFFER_LENGTH);\r\n");// REQ #078
                } /* use style */                                   // REQ #078
             CString action;                                        // REQ #078
             action.LoadString(IDS_APPROPRIATE_ACTION);             // REQ #078
                                                                    // REQ #078
             s += ToString(_T("   if(dlg.DoModal() != IDOK)\r\n")); // REQ #078
             s += _T("      {\r\n");                                // REQ #078
             if(c_CF_USESTYLE.GetCheck() == BST_CHECKED)            // REQ #078
                { /* release style buffer */                        // REQ #078
                 s += _T("       style.ReleaseBuffer();\r\n");      // REQ #078
                } /* release style buffer */                        // REQ #078
             s += ToString(_T("       return; // %s\r\n"), action); // REQ #078
             s += _T("      }\r\n");                                // REQ #078
                                                                    // REQ #078
             if(c_CF_USESTYLE.GetCheck() == BST_CHECKED)            // REQ #078
                s += _T("   style.ReleaseBuffer();\r\n");           // REQ #078
                                                                    // REQ #078
             s += _T("   dlg.GetCurrentFont(&lf);\r\n");            // REQ #078
             code += s;                                             // REQ #078
            } /* MFC */                                             // REQ #078
            break;                                                  // REQ #078
        } /* language */                                            // REQ #078
                                                                    // REQ #078
     c_Code.SetWindowText(code);                                    // REQ #078
     c_Copy.EnableWindow(c_Code.GetWindowTextLength() > 0);         // REQ #078
    } // CFontDialogExplorer::updateCode                            // REQ #078

/****************************************************************************
*                     CFontDialogExplorer::updateControls
* Result: void
*       
* Effect: 
*       Updates the controls
****************************************************************************/

void CFontDialogExplorer::updateControls()                          // REQ #078
    {                                                               // REQ #078
     if(!initialized)                                               // REQ #078
        return;                                                     // REQ #078
                                                                    // REQ #078
     ComputePointSize();                                            // REQ #078
                                                                    // REQ #078
     BOOL enable;                                                   // REQ #078
                                                                    // REQ #078
     //-------------------------------------------------------------// REQ #078
     // CHOOSEFONT                                                  // REQ #078
     //-------------------------------------------------------------// REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lStructSize                                                 // REQ #078
     //----------------                                             // REQ #078
     // nothing to do                                               // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // hWndOwner                                                   // REQ #078
     //----------------                                             // REQ #078
     // nothing to do                                               // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // hDC                                                         // REQ #078
     //----------------                                             // REQ #078
     if(c_UsePrinterDC.GetCheck() == BST_CHECKED)                   // REQ #078
        { /* use printer DC */                                      // REQ #078
         if(PrinterDC.m_hDC == NULL)                                // REQ #078
            c_hDC.SetWindowText(_T("NULL"));                        // REQ #078
         else                                                       // REQ #078
            { /* has DC */                                          // REQ #078
             c_hDC.SetWindowText(ToString(_T("0x%p"), PrinterDC.m_hDC));// REQ #078
            } /* has DC */                                          // REQ #078
        } /* use printer DC */                                      // REQ #078
     else                                                           // REQ #078
        { /* no printer DC */                                       // REQ #078
         c_hDC.SetWindowText(_T("NULL"));                           // REQ #078
        } /* no printer DC */                                       // REQ #078
                                                                    // REQ #078
     c_UsePrinterDC.EnableWindow(PrinterDC.m_hDC != NULL);          // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // iPointSize                                                  // REQ #078
     //----------------                                             // REQ #078
     // nothing to do                                               // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // Flags                                                       // REQ #078
     //----------------                                             // REQ #078
     // flag enabling distributed                                   // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // rgbColors                                                   // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_EFFECTS.GetCheck() == BST_CHECKED;               // REQ #078
     x_rgbColors.EnableWindow(enable);                              // REQ #078
     c_Red.EnableWindow(enable);                                    // REQ #078
     c_SpinRed.EnableWindow(enable);                                // REQ #078
     c_Blue.EnableWindow(enable);                                   // REQ #078
     c_SpinBlue.EnableWindow(enable);                               // REQ #078
     c_Green.EnableWindow(enable);                                  // REQ #078
     c_SpinGreen.EnableWindow(enable);                              // REQ #078
     c_Colors.EnableWindow(enable);                                 // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lpszStyle                                                   // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_USESTYLE.GetCheck() == BST_CHECKED;              // REQ #078
     x_lpszStyle.EnableWindow(enable);                              // REQ #078
     x_lpszStyleIn.EnableWindow(enable);                            // REQ #078
     x_lpszStyleOut.EnableWindow(enable);                           // REQ #078
     c_lpszStyleIn.EnableWindow(enable);                            // REQ #078
     c_lpszStyleOut.EnableWindow(enable);                           // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // nSizeMin                                                    // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_LIMITSIZE.GetCheck() == BST_CHECKED &&           // REQ #078
              c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     x_nSizeMin.EnableWindow(enable);                               // REQ #078
     c_nSizeMin.EnableWindow(enable);                               // REQ #078
     c_SpinSizeMin.EnableWindow(enable);                            // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // nSizeMax                                                    // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_LIMITSIZE.GetCheck() == BST_CHECKED &&           // REQ #078
              c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     x_nSizeMax.EnableWindow(enable);                               // REQ #078
     c_nSizeMax.EnableWindow(enable);                               // REQ #078
     c_SpinSizeMax.EnableWindow(enable);                            // REQ #078
                                                                    // REQ #078
     //-------------------------------------------------------------// REQ #078
     // LOGFONT                                                     // REQ #078
     //-------------------------------------------------------------// REQ #078
     //----------------                                             // REQ #078
     // lfHeight                                                    // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_NOSIZESEL.GetCheck() == BST_UNCHECKED &&         // REQ #078
              c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     x_lfHeight.EnableWindow(enable);                               // REQ #078
     c_lfHeight.EnableWindow(enable);                               // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfWidth                                                     // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     x_lfWidth.EnableWindow(enable);                                // REQ #078
     c_lfWidth.EnableWindow(enable);                                // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfEscapement                                                // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     x_lfEscapement.EnableWindow(enable);                           // REQ #078
     c_lfEscapement.EnableWindow(enable);                           // REQ #078
     c_SpinEscapement.EnableWindow(enable);                         // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfOrientation                                               // REQ #078
     //----------------                                             // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfWeight                                                    // REQ #078
     //----------------                                             // REQ #078
                                                                    // REQ #078
     enable = c_CF_NOSTYLESEL.GetCheck() == BST_UNCHECKED &&        // REQ #078
              c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     x_lfWeight.EnableWindow(enable);                               // REQ #078
     c_lfWeight.EnableWindow(enable);                               // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfItalic                                                    // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_NOFACESEL.GetCheck() == BST_UNCHECKED &&         // REQ #078
              c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     c_lfItalic.EnableWindow(enable);                               // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfUnderline                                                 // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_EFFECTS.GetCheck() == BST_CHECKED &&             // REQ #078
              c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     c_lfUnderline.EnableWindow(enable);                            // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfStrikeOut                                                 // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_EFFECTS.GetCheck() == BST_CHECKED &&             // REQ #078
              c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     c_lfStrikeOut.EnableWindow(enable);                            // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfCharSet                                                   // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     x_lfCharSet.EnableWindow(enable);                              // REQ #078
     c_lfCharSet.EnableWindow(enable);                              // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfOutPrecision                                              // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     x_lfOutPrecision.EnableWindow(enable);                         // REQ #078
     c_lfOutPrecision.EnableWindow(enable);                         // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfClipPrecision                                             // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     x_lfClipPrecision.EnableWindow(enable);                        // REQ #078
     c_lfClipPrecision.EnableWindow(enable);                        // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfQuality                                                   // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     x_lfQuality.EnableWindow(enable);                              // REQ #078
     c_lfQuality.EnableWindow(enable);                              // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfPitchAndFamily                                            // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     x_lfPitchAndFamily.EnableWindow(enable);                       // REQ #078
     c_lfPitch.EnableWindow(enable);                                // REQ #078
     c_lfFamily.EnableWindow(enable);                               // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfFaceName                                                  // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_NOFACESEL.GetCheck() == BST_UNCHECKED &&         // REQ #078
              c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     x_lfFaceName.EnableWindow(enable);                             // REQ #078
     c_lfFaceName.EnableWindow(enable);                             // REQ #078
                                                                    // REQ #078
     //-------------------------------------------------------------// REQ #078
     // end of LOGFONT                                              // REQ #078
     //-------------------------------------------------------------// REQ #078
     // Point font                                                  // REQ #078
     //----------------                                             // REQ #078
     enable = c_CF_INITTOLOGFONTSTRUCT.GetCheck() == BST_CHECKED;   // REQ #078
     c_SetPointHeight.EnableWindow(enable);                         // REQ #078
     c_ShowPointFontCode.EnableWindow(enable);                      // REQ #078
     c_SpinPointSize.EnableWindow(enable);                          // REQ #078
     c_PointFont.EnableWindow(enable);                              // REQ #078
     x_PointSize.EnableWindow(enable);                              // REQ #078
     x_PointSizeMultiplier.EnableWindow(enable);                    // REQ #078
     x_PointFont.EnableWindow(enable);                              // REQ #078
     c_PointFontSize.EnableWindow(enable);                          // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // [Copy]                                                      // REQ #078
     //----------------                                             // REQ #078
     c_Copy.EnableWindow(c_Code.GetWindowTextLength() > 0);         // REQ #078
    } // CFontDialogExplorer::updateControls                        // REQ #078

/****************************************************************************
*                   CFontDialogExplorer::OnBnClickedCfApply
* Result: void
*       
* Effect: 
*       Updates flags
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfApply()                      // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                  CFontDialogExplorer::OnBnClickedCfAnsionly
* Result: void
*       
* Effect: 
*       Updates flags
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfAnsionly()                   // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                    CFontDialogExplorer::OnBnClickedCfBoth
* Result: void
*       
* Effect: 
*       Updates flags, and mkes the selected bits be consistent
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfBoth()                       // REQ #078
    {                                                               // REQ #078
     c_CF_PRINTERFONTS.SetCheck(c_CF_BOTH.GetCheck());              // REQ #078
     c_CF_SCREENFONTS.SetCheck(c_CF_BOTH.GetCheck());               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078


/****************************************************************************
*                CFontDialogExplorer::OnBnClickedCfPrinterfonts
* Result: void
*       
* Effect: 
*       Updates flags, and makes the selected bits be consistent
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfPrinterfonts()               // REQ #078
    {                                                               // REQ #078
     if(c_CF_PRINTERFONTS.GetCheck() == BST_CHECKED &&              // REQ #078
        c_CF_SCREENFONTS.GetCheck() == BST_CHECKED)                 // REQ #078
        { /* both checked */                                        // REQ #078
         c_CF_BOTH.SetCheck(BST_CHECKED);                           // REQ #078
        } /* both checked */                                        // REQ #078
     else                                                           // REQ #078
        { /* not both */                                            // REQ #078
         c_CF_BOTH.SetCheck(BST_UNCHECKED);                         // REQ #078
        } /* not both */                                            // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                CFontDialogExplorer::OnBnClickedCfScreenfonts
* Result: void
*       
* Effect: 
*       Updates flags, and makes the selected bits be consistent
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfScreenfonts()                // REQ #078
    {                                                               // REQ #078
     if(c_CF_PRINTERFONTS.GetCheck() == BST_CHECKED &&              // REQ #078
        c_CF_SCREENFONTS.GetCheck() == BST_CHECKED)                 // REQ #078
        { /* both checked */                                        // REQ #078
         c_CF_BOTH.SetCheck(BST_CHECKED);                           // REQ #078
        } /* both checked */                                        // REQ #078
     else                                                           // REQ #078
        { /* not both */                                            // REQ #078
         c_CF_BOTH.SetCheck(BST_UNCHECKED);                         // REQ #078
        } /* not both */                                            // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                   CFontDialogExplorer::OnBnClickedCfTtonly
* Result: void
*       
* Effect: 
*       updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfTtonly()                     // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                  CFontDialogExplorer::OnBnClickedCfEffects
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfEffects()                    // REQ #078
    {                                                               // REQ #078
     updateControls();                                              // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*               CFontDialogExplorer::OnBnClickedCfFixedpitchonly
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfFixedpitchonly()             // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*               CFontDialogExplorer::OnBnClickedCfForcefontexist
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfForcefontexist()             // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*            CFontDialogExplorer::OnBnClickedCfInittologfontstruct
* Result: void
*       
* Effect: 
*       Updtes code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfInittologfontstruct()        // REQ #078
    {                                                               // REQ #078
     updateControls();                                              // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                 CFontDialogExplorer::OnBnClickedCfLimitsize
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfLimitsize()                  // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
     updateControls();                                              // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*               CFontDialogExplorer::OnBnClickedCfNovectorfonts
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfNovectorfonts()              // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                 CFontDialogExplorer::OnBnClickedCfNofacesel
* Result: void
*       
* Effect: 
*       Updates code and enables controls
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfNofacesel()                  // REQ #078
    {                                                               // REQ #078
     updateControls();                                              // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                 CFontDialogExplorer::OnBnClickedCfNostylesel
* Result: void
*       
* Effect: 
*       Updates code and enables controls
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfNostylesel()                 // REQ #078
    {                                                               // REQ #078
     updateControls();                                              // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                CFontDialogExplorer::OnBnClickedCfNoscriptsel
* Result: void
*       
* Effect: 
*       Updates code and enables controls
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfNoscriptsel()                // REQ #078
    {                                                               // REQ #078
     updateControls();                                              // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                 CFontDialogExplorer::OnBnClickedCfNosizesel
* Result: void
*       
* Effect: 
*       Updates code and enables controls
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfNosizesel()                  // REQ #078
    {                                                               // REQ #078
     updateControls();                                              // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*               CFontDialogExplorer::OnBnClickedCfNosimulations
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfNosimulations()              // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                CFontDialogExplorer::OnBnClickedCfNovertfonts
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfNovertfonts()                // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                CFontDialogExplorer::OnBnClickedCfScalableonly
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfScalableonly()               // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                CFontDialogExplorer::OnBnClickedCfScriptsonly
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfScriptsonly()                // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                CFontDialogExplorer::OnBnClickedCfSelectscript
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfSelectscript()               // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                  CFontDialogExplorer::OnBnClickedCfShowhelp
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfShowhelp()                   // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                  CFontDialogExplorer::OnBnClickedCfUsestyle
* Result: void
*       
* Effect: 
*       Updates code and controls
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfUsestyle()                   // REQ #078
    {                                                               // REQ #078
     updateControls();                                              // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                  CFontDialogExplorer::OnBnClickedCfWysiwyg
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCfWysiwyg()                    // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                    CFontDialogExplorer::ControlsToFlags
* Result: DWORD
*       Flags
****************************************************************************/

DWORD CFontDialogExplorer::ControlsToFlags()                        // REQ #078
    {                                                               // REQ #078
     DWORD flags = 0;                                               // REQ #078
#define AddFlag(x) flags |= c_##x.GetCheck() == BST_CHECKED ? x : 0 // REQ #078
     AddFlag(CF_APPLY);                                             // REQ #078
     AddFlag(CF_ANSIONLY);                                          // REQ #078
     AddFlag(CF_BOTH);                                              // REQ #078
     AddFlag(CF_PRINTERFONTS);                                      // REQ #078
     AddFlag(CF_SCREENFONTS);                                       // REQ #078
     AddFlag(CF_TTONLY);                                            // REQ #078
     AddFlag(CF_EFFECTS);                                           // REQ #078
     AddFlag(CF_FIXEDPITCHONLY);                                    // REQ #078
     AddFlag(CF_FORCEFONTEXIST);                                    // REQ #078
     AddFlag(CF_INITTOLOGFONTSTRUCT);                               // REQ #078
     AddFlag(CF_LIMITSIZE);                                         // REQ #078
     AddFlag(CF_NOVECTORFONTS);                                     // REQ #078
     AddFlag(CF_NOFACESEL);                                         // REQ #078
     AddFlag(CF_NOSCRIPTSEL);                                       // REQ #078
     AddFlag(CF_NOSTYLESEL);                                        // REQ #078
     AddFlag(CF_NOSIZESEL);                                         // REQ #078
     AddFlag(CF_NOSIMULATIONS);                                     // REQ #078
     AddFlag(CF_NOVERTFONTS);                                       // REQ #078
     AddFlag(CF_SCALABLEONLY);                                      // REQ #078
     AddFlag(CF_SCRIPTSONLY);                                       // REQ #078
     AddFlag(CF_SELECTSCRIPT);                                      // REQ #078
     AddFlag(CF_SHOWHELP);                                          // REQ #078
     AddFlag(CF_USESTYLE);                                          // REQ #078
     AddFlag(CF_WYSIWYG);                                           // REQ #078
#undef AddFlag                                                      // REQ #078
     return flags;                                                  // REQ #078
    } // CFontDialogExplorer::ControlsToFlags                       // REQ #078

/****************************************************************************
*                      CFontDialogExplorer::updateStatus
* Result: void
*       
* Effect: 
*       Updates the status window
****************************************************************************/

void CFontDialogExplorer::updateStatus()                            // REQ #078
    {                                                               // REQ #078
     CString status = CFontDialogResult;                            // REQ #078
     if(c_UsePrinterDC.GetCheck() == BST_CHECKED &&                 // REQ #078
        PrinterDC.m_hDC != NULL)                                    // REQ #078
        { /* show printer DC */                                     // REQ #078
         status += _T("\r\n");                                      // REQ #078
         status += PrinterName;                                     // REQ #078
         status += _T("\r\n");                                      // REQ #078
         status += ToString(_T("GetDeviceCaps(LOGPIXELSY) => %d"), PrinterDC.GetDeviceCaps(LOGPIXELSY));// REQ #078
        } /* show printer DC */                                     // REQ #078
     if(!FontCreationStatus.IsEmpty())                              // REQ #078
        { /* has font status */                                     // REQ #078
         status += _T("\r\n");                                      // REQ #078
         status += FontCreationStatus;                              // REQ #078
        } /* has font status */                                     // REQ #078
     c_Status.SetWindowText(status);                                // REQ #078
    } // CFontDialogExplorer::updateStatus                          // REQ #078

/****************************************************************************
*                   CFontDialogExplorer::ControlsToLogFont
* Inputs:
*       LOGFONT & lf: LOGFONT structure
* Result: void
*       
* Effect: 
*       Grabs the control information from the LOGFONT structure
****************************************************************************/

void CFontDialogExplorer::ControlsToLogFont(LOGFONT & lf)           // REQ #078
    {                                                               // REQ #078
     ::ZeroMemory(&lf, sizeof(LOGFONT));                            // REQ #078
                                                                    // REQ #078
     CString s;                                                     // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfHeight                                                    // REQ #078
     //----------------                                             // REQ #078
     c_lfHeight.GetWindowText(s);                                   // REQ #078
     lf.lfHeight = _ttoi(s);                                        // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfWidth                                                     // REQ #078
     //----------------                                             // REQ #078
     c_lfWidth.GetWindowText(s);                                    // REQ #078
     lf.lfWidth = _ttoi(s);                                         // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfEscapement                                                // REQ #078
     //----------------                                             // REQ #078
     lf.lfEscapement = c_SpinEscapement.GetPos32();                 // REQ #078
     // ignored                                                     // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfOrientation                                               // REQ #078
     //----------------                                             // REQ #078
     lf.lfOrientation = lf.lfEscapement;                            // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfWeight                                                    // REQ #078
     //----------------                                             // REQ #078
     lf.lfWeight = (LONG)c_lfWeight.GetItemData(c_lfWeight.GetCurSel());// REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfItalic                                                    // REQ #078
     // lfUnderline                                                 // REQ #078
     // lfStrikeOut                                                 // REQ #078
     //----------------                                             // REQ #078
     lf.lfItalic = c_lfItalic.GetCheck() == BST_CHECKED;            // REQ #078
     lf.lfUnderline = c_lfUnderline.IsWindowEnabled() ? c_lfUnderline.GetCheck() == BST_CHECKED : FALSE;// REQ #078
     lf.lfStrikeOut = c_lfStrikeOut.IsWindowEnabled() ? c_lfStrikeOut.GetCheck() == BST_CHECKED : FALSE;// REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfCharSet                                                   // REQ #078
     //----------------                                             // REQ #078
     lf.lfCharSet = (BYTE)c_lfCharSet.GetItemData(c_lfCharSet.GetCurSel());// REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfOutPrecision                                              // REQ #078
     //----------------                                             // REQ #078
     lf.lfOutPrecision = (BYTE)c_lfOutPrecision.GetItemData(c_lfOutPrecision.GetCurSel());// REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfClipPrecision                                             // REQ #078
     //----------------                                             // REQ #078
     lf.lfClipPrecision = (BYTE)c_lfClipPrecision.GetItemData(c_lfClipPrecision.GetCurSel());// REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfQuality                                                   // REQ #078
     //----------------                                             // REQ #078
     lf.lfQuality = (BYTE)c_lfQuality.GetItemData(c_lfQuality.GetCurSel());// REQ #078
                                                                    // REQ #078
     //-----------------                                            // REQ #078
     // lfPitchAndFamily                                            // REQ #078
     //-----------------                                            // REQ #078
     lf.lfPitchAndFamily = (BYTE)c_lfPitch.GetItemData(c_lfPitch.GetCurSel()) |   // REQ #078
                           (BYTE)c_lfFamily.GetItemData(c_lfFamily.GetCurSel());  // REQ #078
                                                                    // REQ #078
     //----------------                                             // REQ #078
     // lfFaceName                                                  // REQ #078
     //----------------                                             // REQ #078
     if(c_lfFaceName.GetCurSel() >= 0)                              // REQ #078
        { /* has font */                                            // REQ #078
         c_lfFaceName.GetLBText(c_lfFaceName.GetCurSel(), s);       // REQ #078
         _tcscpy_s(lf.lfFaceName, _countof(lf.lfFaceName), s);      // REQ #078
        } /* has font */                                            // REQ #078
    } // CFontDialogExplorer::ControlsToLogFont                     // REQ #078

/****************************************************************************
*                       CFontDialogExplorer::updateFont
* Result: void
*       
* Effect: 
*       From the LOGFONT controls, creates a new font
****************************************************************************/

void CFontDialogExplorer::updateFont()                              // REQ #078
    {                                                               // REQ #078
     LOGFONT lf;                                                    // REQ #078
     ControlsToLogFont(lf);                                         // REQ #078
                                                                    // REQ #078
     CFont newfont;                                                 // REQ #078
     if(newfont.CreateFontIndirect(&lf))                            // REQ #078
        { /* created new font */                                    // REQ #078
         FontCreationStatus = _T("");                               // REQ #078
         SampleFont.DeleteObject();                                 // REQ #078
         SampleFont.Attach(newfont.Detach());                       // REQ #078
         c_FontSample.SetFont(&SampleFont);                         // REQ #078
        } /* created new font */                                    // REQ #078
     else                                                           // REQ #078
        { /* font creation failed */                                // REQ #078
         DWORD err = ::GetLastError();                              // REQ #078
         FontCreationStatus.LoadString(IDS_FONT_CREATION_FAILED);   // REQ #078
         FontCreationStatus += ErrorString(err);                    // REQ #078
        } /* font creation failed */                                // REQ #078
    } // CFontDialogExplorer::updateFont                            // REQ #078

/****************************************************************************
*                  CFontDialogExplorer::OnBnClickedFontDialog
* Result: void
*       
* Effect: 
*       Pops up a font dialog box
****************************************************************************/

void CFontDialogExplorer::OnBnClickedFontDialog()                   // REQ #078
    {                                                               // REQ #078
                                                                    // REQ #078
     DWORD flags = ControlsToFlags();                               // REQ #078
     LOGFONT lf = {0};                                              // REQ #078
     CString s;                                                     // REQ #078
                                                                    // REQ #078
     ControlsToLogFont(lf);                                         // REQ #078
                                                                    // REQ #078
     CDC * dc = NULL;                                               // REQ #078
     if(c_UsePrinterDC.GetCheck() == BST_CHECKED &&                 // REQ #078
        PrinterDC.m_hDC != NULL)                                    // REQ #078
        dc = &PrinterDC;                                            // REQ #078
                                                                    // REQ #078
     CFontDialog dlg(&lf, flags, dc);                               // REQ #078
                                                                    // REQ #078
     dlg.m_cf.nSizeMin = c_SpinSizeMin.GetPos32();                  // REQ #078
     dlg.m_cf.nSizeMax = c_SpinSizeMax.GetPos32();                  // REQ #078
                                                                    // REQ #078
     CString style;                                                 // REQ #078
     LPTSTR p = NULL;                                               // REQ #078
     if(c_CF_USESTYLE.GetCheck() == BST_CHECKED)                    // REQ #078
        { /* use style */                                           // REQ #078
         c_lpszStyleIn.GetWindowText(style);                        // REQ #078
         p = style.GetBuffer(MAX_STYLE_BUFFER);                     // REQ #078
        } /* use style */                                           // REQ #078
                                                                    // REQ #078
     dlg.m_cf.lpszStyle = p;                                        // REQ #078
                                                                    // REQ #078
     //-----------------------                                      // REQ #078
     // Launch the CFontDialog                                      // REQ #078
     //-----------------------                                      // REQ #078
                                                                    // REQ #078
     if(dlg.DoModal() == IDOK)                                      // REQ #078
        { /* success */                                             // REQ #078
         dlg.GetCurrentFont(&lf);                                   // REQ #078
         CFontDialogResult.LoadString(IDS_CFONTDIALOG_SUCCEEDED);   // REQ #078
         updateStatus();                                            // REQ #078
        } /* success */                                             // REQ #078
     else                                                           // REQ #078
        { /* failure */                                             // REQ #078
         CFontDialogResult.LoadString(IDS_CFONTDIALOG_FAILED);      // REQ #078
         CString reason;                                            // REQ #078
         static const UINT COMMBASE = 10000;                        // REQ #078
         reason.LoadString(COMMBASE + CommDlgExtendedError());      // REQ #078
         CFontDialogResult += _T("\r\n") + reason;                  // REQ #078
                                                                    // REQ #078
         c_lpszStyleOut.SetWindowText(_T(""));                      // REQ #078
#define ClearFlag(x) c_##x.SetCheck(BST_UNCHECKED)                  // REQ #078
         ClearFlag(BOLD_FONTTYPE);                                  // REQ #078
         ClearFlag(ITALIC_FONTTYPE);                                // REQ #078
         ClearFlag(PRINTER_FONTTYPE);                               // REQ #078
         ClearFlag(REGULAR_FONTTYPE);                               // REQ #078
         ClearFlag(SCREEN_FONTTYPE);                                // REQ #078
         ClearFlag(SIMULATED_FONTTYPE);                             // REQ #078
         updateStatus();                                            // REQ #078
#undef ClearFlag                                                    // REQ #078
         return;                                                    // REQ #078
        } /* failure */                                             // REQ #078
                                                                    // REQ #078
     if(_tcslen(lf.lfFaceName) > 0 && c_lfFaceName.FindStringExact(-1, lf.lfFaceName) < 0)// REQ #078
        { /* add facename */                                        // REQ #078
         int n = c_lfFaceName.AddString(lf.lfFaceName);             // REQ #078
         c_lfFaceName.SetCurSel(n);                                 // REQ #078
        } /* add facename */                                        // REQ #078
                                                                    // REQ #078
     c_PointSize.SetWindowText(ToString(_T("%d"), dlg.m_cf.iPointSize));// REQ #078
                                                                    // REQ #078
     if(c_CF_USESTYLE.GetCheck() == BST_CHECKED)                    // REQ #078
        { /* report style */                                        // REQ #078
         style.ReleaseBuffer();                                     // REQ #078
         c_lpszStyleOut.SetWindowText(style);                       // REQ #078
        } /* report style */                                        // REQ #078
     else                                                           // REQ #078
        c_lpszStyleOut.SetWindowText(_T(""));                       // REQ #078
                                                                    // REQ #078
     dlg.GetCurrentFont(&lf);                                       // REQ #078
     c_lfHeight.SetWindowText(ToString(_T("%d"), lf.lfHeight));     // REQ #078
     c_lfWidth.SetWindowText(ToString(_T("%d"), lf.lfWidth));       // REQ #078
     c_SpinEscapement.SetPos(lf.lfEscapement);                      // REQ #078
     c_SpinOrientation.SetPos(lf.lfOrientation);                    // REQ #078
     c_lfWeight.Select(lf.lfWeight);                                // REQ #078
     c_lfItalic.SetCheck(lf.lfItalic ? BST_CHECKED : BST_UNCHECKED);// REQ #078
     c_lfUnderline.SetCheck(lf.lfUnderline ? BST_CHECKED : BST_UNCHECKED);// REQ #078
     c_lfStrikeOut.SetCheck(lf.lfStrikeOut ? BST_CHECKED : BST_UNCHECKED);// REQ #078
     c_lfCharSet.Select(lf.lfCharSet);                              // REQ #078
     c_lfOutPrecision.Select(lf.lfOutPrecision);                    // REQ #078
     c_lfClipPrecision.Select(lf.lfClipPrecision);                  // REQ #078
     c_lfQuality.Select(lf.lfQuality);                              // REQ #078
     c_lfPitch.Select(lf.lfPitchAndFamily & 0xF);                   // REQ #078
     c_lfFamily.Select(lf.lfPitchAndFamily & 0xF0);                 // REQ #078
     c_lfFaceName.SetWindowText(lf.lfFaceName);                     // REQ #078
                                                                    // REQ #078
                                                                    // REQ #078
#define SetFlag(x) c_##x.SetCheck(dlg.m_cf.nFontType & x ? BST_CHECKED : BST_UNCHECKED)// REQ #078
     SetFlag(BOLD_FONTTYPE);                                        // REQ #078
     SetFlag(ITALIC_FONTTYPE);                                      // REQ #078
     SetFlag(PRINTER_FONTTYPE);                                     // REQ #078
     SetFlag(REGULAR_FONTTYPE);                                     // REQ #078
     SetFlag(SCREEN_FONTTYPE);                                      // REQ #078
     SetFlag(SIMULATED_FONTTYPE);                                   // REQ #078
#undef SetFlag                                                      // REQ #078
                                                                    // REQ #078
     updateFont();                                                  // REQ #078
     updateStatus();                                                // REQ #078
     updateCode();                                                  // REQ #078
    } // CFontDialogExplorer::OnBnClickedFontDialog                 // REQ #078

/****************************************************************************
*                   CFontDialogExplorer::OnBnClickedLfitalic
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedLfitalic()                     // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
     updateFont();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                 CFontDialogExplorer::OnBnClickedLfunderline
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedLfunderline()                  // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
     updateFont();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                 CFontDialogExplorer::OnBnClickedLfstrikeout
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedLfstrikeout()                  // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
     updateFont();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                 CFontDialogExplorer::OnCbnSelendokLfcharset
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnCbnSelendokLfcharset()                  // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
     updateFont();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*              CFontDialogExplorer::OnCbnSelchangeLfoutprecision
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnCbnSelchangeLfoutprecision()            // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
     updateFont();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*              CFontDialogExplorer::OnCbnSelendokLfclipprecision
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnCbnSelendokLfclipprecision()            // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
     updateFont();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                 CFontDialogExplorer::OnCbnSelendokLfquality
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnCbnSelendokLfquality()                  // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
     updateFont();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                  CFontDialogExplorer::OnCbnSelendokLfpitch
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnCbnSelendokLfpitch()                    // REQ #078
   {                                                                // REQ #078
    updateCode();                                                   // REQ #078
    updateFont();                                                   // REQ #078
   }                                                                // REQ #078

/****************************************************************************
*                  CFontDialogExplorer::OnCbnSelendokLffamily
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnCbnSelendokLffamily()                   // REQ #078
   {                                                                // REQ #078
    updateCode();                                                   // REQ #078
    updateFont();                                                   // REQ #078
   }                                                                // REQ #078

/****************************************************************************
*                  CFontDialogExplorer::OnCbnSelendokFacename
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnCbnSelendokFacename()                   // REQ #078
   {                                                                // REQ #078
    updateCode();                                                   // REQ #078
    updateFont();                                                   // REQ #078
   }                                                                // REQ #078

/****************************************************************************
*                 CFontDialogExplorer::OnEnChangeLforientation
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnEnChangeLforientation()                 // REQ #078
   {                                                                // REQ #078
    updateCode();                                                   // REQ #078
    updateFont();                                                   // REQ #078
   }                                                                // REQ #078

/****************************************************************************
*                 CFontDialogExplorer::OnEnChangeLfescapement
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnEnChangeLfescapement()                  // REQ #078
   {                                                                // REQ #078
    updateCode();                                                   // REQ #078
    updateFont();                                                   // REQ #078
   }                                                                // REQ #078

/****************************************************************************
*                   CFontDialogExplorer::OnEnChangeLfheight
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnEnChangeLfheight()                      // REQ #078
   {                                                                // REQ #078
    updateCode();                                                   // REQ #078
   }                                                                // REQ #078

/****************************************************************************
*                    CFontDialogExplorer::OnEnChangeLfwidth
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnEnChangeLfwidth()                       // REQ #078
   {                                                                // REQ #078
    updateCode();                                                   // REQ #078
   }                                                                // REQ #078

/****************************************************************************
*                 CFontDialogExplorer::OnBnClickedUsePrinterDc
* Result: void
*       
* Effect: 
*       Updates the code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedUsePrinterDc()                 // REQ #078
    {                                                               // REQ #078
     updateStatus();                                                // REQ #078
     updateControls();                                              // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                   CFontDialogExplorer::OnBnClickedPrinter
* Result: void
*       
* Effect: 
*       Updates the DC
****************************************************************************/

void CFontDialogExplorer::OnBnClickedPrinter()                      // REQ #078
    {                                                               // REQ #078
     CPrintDialog dlg(TRUE, PD_RETURNDC);                           // REQ #078
     if(dlg.DoModal() != IDOK)                                      // REQ #078
        return;                                                     // REQ #078
     if(dlg.m_pd.hDC != NULL)                                       // REQ #078
        { /* has DC */                                              // REQ #078
         if(PrinterDC.m_hDC != NULL)                                // REQ #078
            PrinterDC.DeleteDC();                                   // REQ #078
         PrinterDC.Attach(dlg.m_pd.hDC);                            // REQ #078
         PrinterName = dlg.GetDeviceName();                         // REQ #078
        } /* has DC */                                              // REQ #078
     else                                                           // REQ #078
        { /* no DC */                                               // REQ #078
         PrinterDC.DeleteDC();                                      // REQ #078
        } /* no DC */                                               // REQ #078
                                                                    // REQ #078
     updateStatus();                                                // REQ #078
     updateControls();                                              // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                    CFontDialogExplorer::ComputePointSize
* Result: void
*       
* Effect: 
*       Computes the point size
****************************************************************************/

void CFontDialogExplorer::ComputePointSize()                        // REQ #078
    {                                                               // REQ #078
     CDC * dc;                                                      // REQ #078
     CClientDC wdc(this);                                           // REQ #078
                                                                    // REQ #078
     if(c_UsePrinterDC.GetCheck() == BST_CHECKED &&                 // REQ #078
        PrinterDC.m_hDC != NULL)                                    // REQ #078
        dc = &PrinterDC;                                            // REQ #078
     else                                                           // REQ #078
        dc = &wdc;                                                  // REQ #078
                                                                    // REQ #078
     CPoint pt(0,0);                                                // REQ #078
     int h = c_SpinPointSize.GetPos32();                            // REQ #078
                                                                    // REQ #078
     pt.y = ::MulDiv(dc->GetDeviceCaps(LOGPIXELSY), h, 720);        // REQ #078
     dc->DPtoLP(&pt);                                               // REQ #078
                                                                    // REQ #078
     CPoint org(0, 0);                                              // REQ #078
     dc->DPtoLP(&org);                                              // REQ #078
     int height = -abs(pt.y - org.y);                               // REQ #078
                                                                    // REQ #078
     c_PointFont.SetWindowText(ToString(_T("%d"), height));         // REQ #078
    } // CFontDialogExplorer::ComputePointSize                      // REQ #078

/****************************************************************************
*                   CFontDialogExplorer::OnEnChangePointsize
* Result: void
*       
* Effect: 
*       Computes the point size
****************************************************************************/

void CFontDialogExplorer::OnEnChangePointsize()                     // REQ #078
    {                                                               // REQ #078
     updateControls();                                              // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                CFontDialogExplorer::OnBnClickedSetPointheight
* Result: void
*       
* Effect: 
*       Sets the point size as a pixel size
****************************************************************************/

void CFontDialogExplorer::OnBnClickedSetPointheight()               // REQ #078
    {                                                               // REQ #078
     CString s;                                                     // REQ #078
     c_PointFont.GetWindowText(s);                                  // REQ #078
     c_lfHeight.SetWindowText(s);                                   // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                   CFontDialogExplorer::OnBnClickedShowCode
* Result: void
*       
* Effect: 
*       Updates code
****************************************************************************/

void CFontDialogExplorer::OnBnClickedShowCode()                     // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                     CFontDialogExplorer::OnBnClickedCopy
* Result: void
*       
* Effect: 
*       Copies text to clipboard
****************************************************************************/

void CFontDialogExplorer::OnBnClickedCopy()                         // REQ #078
    {                                                               // REQ #078
     c_Code.SetRedraw(FALSE);                                       // REQ #078
     int low;                                                       // REQ #078
     int high;                                                      // REQ #078
     c_Code.GetSel(low, high);                                      // REQ #078
     c_Code.SetSel(0, -1);                                          // REQ #078
     c_Code.SendMessage(WM_COPY);                                   // REQ #078
     c_Code.SetSel(low, high);                                      // REQ #078
     c_Code.SetRedraw(TRUE);                                        // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                         CFontDialogExplorer::OnSize
* Inputs:
*       UINT nType:
*       int cx:
*       int cy:
* Result: void
*       
* Effect: 
*       Resizes controls
****************************************************************************/

void CFontDialogExplorer::OnSize(UINT nType, int cx, int cy)        // REQ #078
    {                                                               // REQ #078
     CFormView::OnSize(nType, cx, cy);                              // REQ #078
                                                                    // REQ #078
     if(c_Code.GetSafeHwnd() != NULL)                               // REQ #078
        { /* resize code */                                         // REQ #078
         CRect r;                                                   // REQ #078
         c_Code.GetWindowRect(&r);                                  // REQ #078
         ScreenToClient(&r);                                        // REQ #078
         c_Code.SetWindowPos(NULL, 0, 0, cx - r.left, cy - r.top, SWP_NOMOVE | SWP_NOZORDER);// REQ #078
        } /* resize code */                                         // REQ #078
                                                                    // REQ #078
     if(c_Status.GetSafeHwnd() != NULL &&                           // REQ #078
        c_FontSample.GetSafeHwnd() != NULL)                         // REQ #078
        { /* resize status and sample */                            // REQ #078
         CRect left;                                                // REQ #078
         c_Status.GetWindowRect(&left);                             // REQ #078
         ScreenToClient(&left);                                     // REQ #078
                                                                    // REQ #078
         CRect right;                                               // REQ #078
         c_FontSample.GetWindowRect(&right);                        // REQ #078
         ScreenToClient(&right);                                    // REQ #078
         HDWP wp = ::BeginDeferWindowPos(2);                        // REQ #078
                                                                    // REQ #078
         int width = (cx - left.left) / 2 - gap / 2;                // REQ #078
                                                                    // REQ #078
         ::DeferWindowPos(wp, c_Status.m_hWnd, NULL, 0, 0, width, left.Height(), SWP_NOMOVE | SWP_NOZORDER);// REQ #078
                                                                    // REQ #078
         int x = left.left + width + gap;                           // REQ #078
         ::DeferWindowPos(wp, c_FontSample.m_hWnd, NULL, x, right.top,// REQ #078
                                     cx - x, right.Height(),        // REQ #078
                                     SWP_NOZORDER);                 // REQ #078
                                                                    // REQ #078
         ::EndDeferWindowPos(wp);                                   // REQ #078
        } /* resize status and sample */                            // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                  CFontDialogExplorer::OnEnChangeLpszstyleIn
* Result: void
*       
* Effect: 
*       Updates the code
****************************************************************************/

void CFontDialogExplorer::OnEnChangeLpszstyleIn()                   // REQ #078
    {                                                               // REQ #078
     updateCode();                                                  // REQ #078
    }                                                               // REQ #078


/****************************************************************************
*                  CFontDialogExplorer::OnEnChangeDisplayText
* Result: void
*       
* Effect: 
*       Updates the display
****************************************************************************/

void CFontDialogExplorer::OnEnChangeDisplayText()                   // REQ #078
    {                                                               // REQ #078
     CString s;                                                     // REQ #078
     c_DisplayText.GetWindowText(s);                                // REQ #078
     c_FontSample.SetWindowText(s);                                 // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                  CFontDialogExplorer::OnBnClickedShowPixels
* Result: void
*       
* Effect: 
*       Updates the display
****************************************************************************/

void CFontDialogExplorer::OnBnClickedShowPixels()                   // REQ #078
    {                                                               // REQ #078
     display_options opts = c_FontSample.GetOpts();                 // REQ #078
     opts.ShowPixels = c_ShowPixels.GetCheck() == BST_CHECKED;      // REQ #078
     c_FontSample.SetOpts(opts);                                    // REQ #078
    }                                                               // REQ #078


/****************************************************************************
*                 CFontDialogExplorer::OnBnClickedShowOverlay
* Result: void
*       
* Effect: 
*       Updates the display
****************************************************************************/

void CFontDialogExplorer::OnBnClickedShowOverlay()                  // REQ #078
    {                                                               // REQ #078
     display_options opts = c_FontSample.GetOpts();                 // REQ #078
     opts.ShowOverlay = c_ShowOverlay.GetCheck() == BST_CHECKED;    // REQ #078
     c_FontSample.SetOpts(opts);                                    // REQ #078
    }                                                               // REQ #078

/****************************************************************************
*                      CFontDialogExplorer::OnVScroll
* Inputs:
*       UINT nSBCode:
*       UINT nPos:
*       CScrollBar * pScrollBar
* Result: void
*       
* Effect: 
*       Updates the rotation
****************************************************************************/

void CFontDialogExplorer::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)// REQ #078
    {                                                               // REQ #078
     if(pScrollBar != NULL)                                         // REQ #078
        {                                                           // REQ #078
         if(pScrollBar->m_hWnd == c_SpinOrientation.m_hWnd)         // REQ #078
            c_SpinOrientation.OnVScroll(nSBCode, nPos, pScrollBar); // REQ #078
         else                                                       // REQ #078
            if(pScrollBar->m_hWnd == c_SpinEscapement.m_hWnd)       // REQ #078
               c_SpinEscapement.OnVScroll(nSBCode, nPos, pScrollBar);// REQ #078
        }                                                           // REQ #078
     else                                                           // REQ #078
        CFormView::OnVScroll(nSBCode, nPos, pScrollBar);            // REQ #078
    }                                                               // REQ #078

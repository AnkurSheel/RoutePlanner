/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  1-Nov-08 | Created change log
*  1-Nov-08 | REQ #080: FontDisp.h => FontDisplay.h
*  1-Nov-08 | REQ #078: Added ChooseFont/CFontDialog explorer
*****************************************************************************/
#pragma once
#include "afxwin.h"

#include "IDCombo.h"
#include "degrees.h"
#include "rotation.h"
#include "fontname.h"
#include "afxcmn.h"
#include "ArrowButton.h"
#include "ImageButton.h"
#include "FontDisplay.h"                                            // REQ #080

// CFontDialogExplorer form view

class CFontDialogExplorer : public CFormView
{
        DECLARE_DYNCREATE(CFontDialogExplorer)

protected:
        CFontDialogExplorer();           // protected constructor used by dynamic creation
        virtual ~CFontDialogExplorer();

public:
        enum { IDD = IDD_FONTDIALOG };
#ifdef _DEBUG
        virtual void AssertValid() const;
#ifndef _WIN32_WCE
        virtual void Dump(CDumpContext& dc) const;
#endif
#endif
protected:
        BOOL initialized;
        CFont CodeFont;
        CDC PrinterDC;
        CString PrinterName;
        CString CFontDialogResult;
        CString FontCreationStatus;
        int gap;
        CFont SampleFont;
protected:
        void updateCode();
        void updateControls();
        void updateStatus();
        void updateFont();

        DWORD ControlsToFlags();
        void ComputePointSize();
        void ControlsToLogFont(LOGFONT & lf);

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual void OnInitialUpdate();                             // REQ #078

        DECLARE_MESSAGE_MAP()
        CButton c_CF_APPLY;
        CButton c_CF_ANSIONLY;
        CButton c_CF_BOTH;
        CButton c_CF_PRINTERFONTS;
        CButton c_CF_SCREENFONTS;
        CButton c_CF_TTONLY;
        CButton c_CF_EFFECTS;
        CButton c_CF_FIXEDPITCHONLY;
        CButton c_CF_FORCEFONTEXIST;
        CButton c_CF_INITTOLOGFONTSTRUCT;
        CButton c_CF_LIMITSIZE;
        CButton c_CF_NOVECTORFONTS;
        CButton c_CF_NOFACESEL;
        CButton c_CF_NOSCRIPTSEL;
        CButton c_CF_NOSTYLESEL;
        CButton c_CF_NOSIZESEL;
        CButton c_CF_NOSIMULATIONS;
        CButton c_CF_NOVERTFONTS;
        CButton c_CF_SCALABLEONLY;
        CButton c_CF_SCRIPTSONLY;
        CButton c_CF_SELECTSCRIPT;
        CButton c_CF_SHOWHELP;
        CButton c_CF_USESTYLE;
        CButton c_CF_WYSIWYG;

        
        CStatic x_LOGFONT;
        CEdit   c_lfWidth;
        CEdit   c_lfHeight;
        CFontName       c_lfFaceName;
        CDegrees        c_lfEscapement;
        CDegrees        c_lfOrientation;
        CRotation       c_SpinOrientation;
        CRotation       c_SpinEscapement;
        CStatic x_lfOrientation;
        CIDCombo        c_lfFamily;
        CIDCombo        c_lfPitch;
        CIDCombo        c_lfWeight;
        CIDCombo        c_lfQuality;
        CIDCombo        c_lfOutPrecision;
        CIDCombo        c_lfCharSet;
        CIDCombo        c_lfClipPrecision;
        CButton c_lfUnderline;
        CButton c_lfItalic;
        CButton c_lfStrikeOut;
        CEdit c_Red;
        CSpinButtonCtrl c_SpinPointSize;
        CEdit c_PointSize;
        CEdit c_Green;
        CEdit c_Blue;
        CSpinButtonCtrl c_SpinRed;
        CSpinButtonCtrl c_SpinGreen;
        CSpinButtonCtrl c_SpinBlue;
        CIDCombo        c_Language;
        CEdit c_Code;
        CEdit c_Status;
        CEdit c_nSizeMin;
        CSpinButtonCtrl c_SpinSizeMin;
        CEdit c_nSizeMax;
        CSpinButtonCtrl c_SpinSizeMax;
        CStatic x_nSizeMin;
        CStatic x_nSizeMax;
        CStatic x_lfHeight;
        CStatic x_lfFaceName;
        CStatic x_lfWeight;
        CEdit c_lStructSize;
        CEdit c_hDC;
        CEdit c_hwndOwner;
        CStatic x_lpszStyle;
        CStatic x_lpszStyleIn;
        CStatic x_lpszStyleOut;
        CEdit c_lpszStyleIn;
        CEdit c_lpszStyleOut;
        CButton c_BOLD_FONTTYPE;
        CButton c_ITALIC_FONTTYPE;
        CButton c_PRINTER_FONTTYPE;
        CButton c_REGULAR_FONTTYPE;
        CButton c_SCREEN_FONTTYPE;
        CButton c_SIMULATED_FONTTYPE;
        CStatic x_rgbColors;
        CButton c_Colors;
        CButton c_UsePrinterDC;
        CArrowButton c_SetPointHeight;
        CEdit c_PointFont;
        CButton c_ShowPointFontCode;
        CImageButton c_Copy;
        CStatic x_lfCharSet;
        CStatic x_lfOutPrecision;
        CStatic x_lfClipPrecision;
        CStatic x_lfQuality;
        CStatic x_lfPitchAndFamily;
        CStatic x_lfWidth;
        CStatic x_lfEscapement;
        CStatic x_PointSize;
        CStatic x_PointSizeMultiplier;
        CStatic x_PointFont;
        CEdit c_PointFontSize;
        CFontDisplay c_FontSample;
        CEdit c_DisplayText;
        CButton c_ShowPixels;
        CButton c_ShowOverlay;

protected:
   afx_msg void OnBnClickedCfAnsionly();
   afx_msg void OnBnClickedCfApply();
   afx_msg void OnBnClickedCfBoth();
   afx_msg void OnBnClickedCfEffects();
   afx_msg void OnBnClickedCfFixedpitchonly();
   afx_msg void OnBnClickedCfForcefontexist();
   afx_msg void OnBnClickedCfInittologfontstruct();
   afx_msg void OnBnClickedCfLimitsize();
   afx_msg void OnBnClickedCfNofacesel();
   afx_msg void OnBnClickedCfNoscriptsel();
   afx_msg void OnBnClickedCfNosimulations();
   afx_msg void OnBnClickedCfNosizesel();
   afx_msg void OnBnClickedCfNostylesel();
   afx_msg void OnBnClickedCfNovectorfonts();
   afx_msg void OnBnClickedCfNovertfonts();
   afx_msg void OnBnClickedCfPrinterfonts();
   afx_msg void OnBnClickedCfScalableonly();
   afx_msg void OnBnClickedCfScreenfonts();
   afx_msg void OnBnClickedCfScriptsonly();
   afx_msg void OnBnClickedCfSelectscript();
   afx_msg void OnBnClickedCfShowhelp();
   afx_msg void OnBnClickedCfTtonly();
   afx_msg void OnBnClickedCfUsestyle();
   afx_msg void OnBnClickedCfWysiwyg();
   afx_msg void OnBnClickedColor();
   afx_msg void OnBnClickedFontDialog();
   afx_msg void OnBnClickedLfitalic();
   afx_msg void OnBnClickedLfstrikeout();
   afx_msg void OnBnClickedLfunderline();
   afx_msg void OnCbnSelchangeLfoutprecision();
   afx_msg void OnCbnSelendokFacename();
   afx_msg void OnCbnSelendOkLanguage();
   afx_msg void OnCbnSelendokLfcharset();
   afx_msg void OnCbnSelendokLfclipprecision();
   afx_msg void OnCbnSelendokLffamily();
   afx_msg void OnCbnSelendokLfpitch();
   afx_msg void OnCbnSelendokLfquality();
   afx_msg void OnEnChangeB();
   afx_msg void OnEnChangeG();
   afx_msg void OnEnChangeLfescapement();
   afx_msg void OnEnChangeLfheight();
   afx_msg void OnEnChangeLforientation();
   afx_msg void OnEnChangeLfwidth();
   afx_msg void OnEnChangeR();
   afx_msg void OnBnClickedUsePrinterDc();
   afx_msg void OnBnClickedPrinter();
   afx_msg void OnEnChangePointsize();
   afx_msg void OnBnClickedSetPointheight();
   afx_msg void OnBnClickedShowCode();
   afx_msg void OnBnClickedCopy();
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnEnChangeLpszstyleIn();
   afx_msg void OnEnChangeDisplayText();
   afx_msg void OnBnClickedShowPixels();
   afx_msg void OnBnClickedShowOverlay();
   afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);// REQ #045
};



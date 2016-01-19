/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 23-Apr-08 | Created change log
* 23-Apr-08 | REQ #011: Support ExtTextOut as a native output mode
* 27-Apr-08 | REQ #017: Added detect-pair-kerning option
* 28-Apr-08 | REQ #022: Support vertical offset
* 29-Apr-08 | REQ #026: Retain settings
* 29-Apr-08 | REQ #029: Support copy-only-images
* 15-Oct-08 | REQ #042: Converted to VS2005
* 29-Oct-08 | REQ #066: Use bitmap layout for font display
* 29-Oct-08 | REQ #076: Finally implemented presets for tests
*  1-Nov-08 | REQ #080: FontDisp.h => FontDisplay.h
*****************************************************************************/
#pragma once

#include "fontdisplay.h"                                            // REQ #080
#include "afxwin.h"
#include "IDCombo.h"                                                // REQ #066


// CKerningExplorer form view

class CKerningExplorer : public CFormView
{
        DECLARE_DYNCREATE(CKerningExplorer)

protected:
        CKerningExplorer();           // protected constructor used by dynamic creation
        virtual ~CKerningExplorer();

public:
        enum { IDD = IDD_KERNING };
#ifdef _DEBUG
        virtual void AssertValid() const;
        virtual void Dump(CDumpContext& dc) const;
#endif

protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

        BOOL kernedonly;

        void Resize();
        void updateControls();
        void enableTracking(BOOL mode);
        void SetOutputMode();                                       // REQ #011
        display_options::OutputOptions GetOutputMode();             // REQ #011
        int FindEntry(const CString & s);                           // REQ #076
        void UpdateFont(CFont * oldFont, LOGFONT & lf);             // REQ #066

#ifdef _DEBUGFONT                                                   // REQ #019
        void FontTrace(LPCTSTR s);                                  // REQ #019
#else                                                               // REQ #019
        __inline void FontTrace(LPCTSTR s) {}                       // REQ #019// REQ #042
#endif                                                              // REQ #019
        
protected:
        CEdit   c_TrackVal;
        CSpinButtonCtrl c_SpinTrack;
        CEdit   c_Sample;
        CFontDisplay    c_Kerned;
        CFontDisplay    c_Unkerned;
        CButton c_Basal;
        CButton c_Pair;
        CButton c_KernedOnly;
        CButton c_HorizontalRule;
        CButton c_VerticalRule;
        CButton c_CharacterRule;
        CButton c_White;
        CButton c_Debug;
        CButton c_UseTrack;
        CButton c_UseColors;
        CButton c_None;                                             // REQ #011
        CButton c_TextOut;                                          // REQ #011
        CButton c_ExtTextOut;                                       // REQ #011
        CButton c_DetectPairKerning;                                // REQ #017
        CButton c_Advanced;                                         // REQ #018
        CSpinButtonCtrl c_SpinVerticalOffset;                       // REQ #022
        CSpinButtonCtrl c_SpinHorizontalOffset;                     // REQ #066
        CEdit c_VerticalOffset;                                     // REQ #022
        CEdit c_HorizontalOffset;                                   // REQ #066
        CIDCombo c_Quality;                                         // REQ #066
        CButton c_Copy;                                             // REQ #027
        CButton c_Add;                                              // REQ #026
        CButton c_Delete;                                           // REQ #026
        CButton c_CopyImage;                                        // REQ #029
        CButton c_IgnoreABC;                                        // REQ #031
        CButton c_ShowPixels;                                       // REQ #066
        CButton c_ShowOverlay;                                      // REQ #066
        CComboBox c_Presets;                                        // REQ #076

        DECLARE_MESSAGE_MAP()

        afx_msg void OnChangeSample();
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
        afx_msg void OnFont();
        virtual void OnInitialUpdate();
        afx_msg void OnOptions();
        afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        afx_msg void OnCopy();
        afx_msg LRESULT OnGetLogFont(WPARAM, LPARAM);
        afx_msg LRESULT OnGetColor(WPARAM, LPARAM);
        afx_msg void OnBnClickedColors();
        afx_msg void OnBnClickedWhite();
        afx_msg void OnBnClickedDebug();
        afx_msg void OnBnClickedKernedOnly();
        afx_msg void OnBnClickedPair();
        afx_msg void OnBnClickedHrule();
        afx_msg void OnBnClickedVrule();
        afx_msg void OnBnClickedChrule();
        afx_msg void OnBnClickedTrack();
        afx_msg void OnBnClickedNone();
        afx_msg void OnBnClickedTextout();
        afx_msg void OnBnClickedExttextout();
        afx_msg void OnBnClickedAdvanced();                         // REQ #018
        afx_msg void OnEnChangeVoffset();                           // REQ #022
        afx_msg void OnBnClickedAdd();                              // REQ #026
        afx_msg void OnBnClickedDelete();                           // REQ #026
        afx_msg void OnBnClickedCopyimage();                        // REQ #029
        afx_msg void OnBnClickedIgnoreABC();                        // REQ #031
        afx_msg void OnEnChangeHoffset();                           // REQ #066
        afx_msg void OnSelendOkQuality();                           // REQ #066
        afx_msg void OnBnClickedShowOverlay();                      // REQ #066
        afx_msg void OnBnClickedShowPixels();                       // REQ #066
        afx_msg void OnSelendOkPresets();                           // REQ #076
    };




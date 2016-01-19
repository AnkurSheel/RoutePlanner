/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  3-May-08 | Created
*  3-May-08 | REQ #035: Support GM_ADVANCED mode
*  3-May-08 | REQ #036: Allow control to be resized
*  4-May-08 | REQ #032: Support debug tracing
*  6-May-08 | REQ #041: Added kerning map support
* 21-Oct-08 | REQ #068: Avoid accidental close on OK button
*  2-Nov-08 | REQ #088: Removed FontMetrics
*****************************************************************************/
// fontexp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFontExplorer dialog
#include "KerningMap.h"                                             // REQ #041

class CFontExplorer : public CFontDialog
{
        DECLARE_DYNAMIC(CFontExplorer)

public:
        CFontExplorer(LPLOGFONT lplfInitial = NULL,
                DWORD dwFlags = CF_EFFECTS | CF_SCREENFONTS,
                CDC* pdcPrinter = NULL,
                CWnd* pParentWnd = NULL);
#ifndef _AFX_NO_RICHEDIT_SUPPORT
        CFontExplorer(const CHARFORMAT& charformat,
                DWORD dwFlags = CF_SCREENFONTS,
                CDC* pdcPrinter = NULL,
                CWnd* pParentWnd = NULL);
#endif

// Dialog Data
        //{{AFX_DATA(CFontExplorer)
        enum { IDD = FORMATDLGORD31 };
//        CFontMetrics    c_TreeMetrics;                            // REQ #088
        CTreeCtrl c_TreeMetrics;                                    // REQ #088
        CStatic c_c_Legend;
        BOOL debug;
        CLegend c_Legend;
        CStatic c_SmallSample;
        CFontDisplay    c_CharDisplay;
        CButton c_Char;
        CButton c_Info;
        CButton c_ShowKerningMap;                                   // REQ #041
        CComboBox       c_Metrics;
        //}}AFX_DATA

public:
        HHOOK hook;  // hook procedure to simulate message map entries due
                     // to improper implementation of MFC. 

        // This ugly hack is due to MFC not being able to find the
        // correct CFontExplorer * object in the map...and no, we don't
        // understand why!
        static CFontExplorer * self;  // grotesque and ugly hack

protected:
        void updateControls();
        void updateOptions();                                       // REQ #070
        void DoDataExchange(CDataExchange* pDX);
        // CDC * getFontDC(CWnd * wnd, CWnd * fontwnd = NULL);
        void updateFontInfo();
        void loadWidths(CFontDescriptor * desc);
        void ResizeControls();                                      // REQ #036

        BOOL initialized;                                           // REQ #066

protected: // Controls        
        CButton c_Advanced;                                         // REQ #035
        CButton c_Border; // yes, it's a CButton!  (Group Box)      // REQ #036
        CButton c_Frame;  // internal frame                         // REQ #036
        CStatic c_MinMaxInfoFrame;                                  // REQ #036
        CButton c_Debug;                                            // REQ #032
        CKerningMap c_KerningMap;                                   // REQ #041

        CRect margins;                                              // REQ #036
        CSize inset;                                                // REQ #036
        CEdit c_OverlayX;                                           // REQ #066
        CEdit c_OverlayY;                                           // REQ #066
        CSpinButtonCtrl c_SpinOverlayX;                             // REQ #066
        CSpinButtonCtrl c_SpinOverlayY;                             // REQ #066
        CButton c_ShowPixels;                                       // REQ #066
        CButton c_ShowOverlay;                                      // REQ #066
        CButton x_Overlay;                                          // REQ #066
        CSpinButtonCtrl c_SpinTrackKern;                            // REQ #070
        CEdit c_TrackKern;                                          // REQ #070
        CButton c_None;                                             // REQ #070
        CButton c_TextOut;                                          // REQ #070
        CButton c_ExtTextOut;                                       // REQ #070
        CButton c_IgnoreABC;                                        // REQ #070
        CButton c_VRule;                                            // REQ #070
        CButton c_HRule;                                            // REQ #070
        CButton c_CHRule;                                           // REQ #070
        CButton c_Track;                                            // REQ #070
        CButton c_Smoothing;                                        // REQ #071
        CButton c_Pair;                                             // REQ #070
        CButton c_Colors;                                           // REQ #070
        CButton c_White;                                            // REQ #070
        CButton c_Sample;                                           // REQ #070

protected: // Virtual methods
        virtual void OnOK();                                        // REQ #068
        virtual void OnCancel();                                    // REQ #068
        virtual BOOL OnInitDialog();

protected: // Message handlers
        afx_msg void OnInfo();
        afx_msg void OnChar();
        afx_msg void OnCopy();
        afx_msg void OnDestroy();
        afx_msg void OnBnClickedAdvanced();                         // REQ #035
        afx_msg void OnSize(UINT nType, int cx, int cy);            // REQ #036
        afx_msg void OnGetMinMaxInfo(MINMAXINFO * lpMMI);           // REQ #036
        afx_msg void OnBnClickedDebug();                            // REQ #035
        afx_msg void OnShowKerningMap();                            // REQ #041
        afx_msg void OnClose();                                     // REQ #068
        afx_msg void OnBnClickedOK();                               // REQ #068
        afx_msg void OnBnClickedCancel();                           // REQ #068
        afx_msg void OnChangeOverlayX();                            // REQ #066
        afx_msg void OnChangeOverlayY();                            // REQ #066
        afx_msg void OnBnClickedShowPixels();                       // REQ #066
        afx_msg void OnBnClickedShowOverlay();                      // REQ #066
        afx_msg void OnBnClickedNone();                             // REQ #070
        afx_msg void OnBnClickedTextOut();                          // REQ #070
        afx_msg void OnBnClickedExtTextOut();                       // REQ #070
        afx_msg void OnBnClickedIgnoreABC();                        // REQ #070
        afx_msg void OnBnClickedVRule();                            // REQ #070
        afx_msg void OnBnClickedHRule();                            // REQ #070
        afx_msg void OnBnClickedCHRule();                           // REQ #070
        afx_msg void OnBnClickedTrack();                            // REQ #070
        afx_msg void OnBnClickedFontSmoothing();                    // REQ #071
        afx_msg void OnChangeTrackKern();                           // REQ #070
        afx_msg void OnBnClickedPair();                             // REQ #070
        afx_msg void OnBnClickedColors();                           // REQ #070
        afx_msg void OnBnClickedWhite();                            // REQ #070
        afx_msg void OnChangeSample();                              // REQ #070
        afx_msg LRESULT OnUpdateFonts(WPARAM, LPARAM);

        DECLARE_MESSAGE_MAP()
};

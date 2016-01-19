/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 17-Oct-08 | Created change log
* 17-Oct-08 | REQ #050: Added resizability
* 17-Oct-08 | REQ #051: Made callback a static method
* 18-Oct-08 | REQ #054: CHange from dialog to view
* 28-Oct-08 | REQ #071: Font smoothing
*****************************************************************************/
// Raster.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRaster dialog
#pragma once

#include "RasterSample.h"                                           // REQ #052
#include "IDCombo.h"                                                // REQ #071
#include "afxwin.h"
#include "ImageButton.h"

class CRaster : public CFormView                                    // REQ #054
{
 DECLARE_DYNCREATE(CRaster)                                         // REQ #054
// Construction
public:
        CRaster();   // standard constructor                        // REQ #054

// Dialog Data
        //{{AFX_DATA(CRaster)
        enum { IDD = IDD_RASTER };
protected:
        CStatic c_c_Multiplier;
        CStatic c_c_Height;
        CButton c_Vector;
        CButton c_TrueType;
        CButton c_Raster;
        CIntEdit        c_Multiplier;
        CComboBox       c_FontSize;
        CComboBox       c_Fonts;
        CEdit   c_Text;
        CSpinButtonCtrl c_SpinMultiplier;                           // REQ #052
        CRasterSample c_Sample;                                     // REQ #052
        CButton c_ShowGrid;                                         // REQ #052
        CButton c_EnableScaling;                                    // REQ #052
        CStatic c_Frame;                                            // REQ #050
        CStatic c_Unmagnified;                                      // REQ #052
        CSpinButtonCtrl c_SpinScaledHeight;                         // REQ #052
        CEdit  c_ScaledHeight;                                      // REQ #052
        CIDCombo c_Quality;                                         // REQ #071
        CImageButton c_Copy;

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CRaster)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

protected:
        DWORD fontmask;  // mask for font types

// Implementation
protected:
        void loadFontSet();
        void loadFontSizes();
        BOOL initialized;
        CFont f;                                                    // REQ #047
        static int CALLBACK loadFontProc(const LOGFONT * lf,        // REQ #051
                                         const TEXTMETRIC * ntm,    // REQ #051
                                         DWORD type,                // REQ #051
                                         LPARAM lParam);            // REQ #051

        static int CALLBACK loadFontSizes(const LOGFONT * lf, const TEXTMETRIC * tm, DWORD type, LPARAM lParam ); // REQ #051
        void AdjustWindowSize(int cx, int cy);                      // REQ #050
        void setNewFont();
        void updateControls();                                      // REQ #052
        // Generated message map functions
        //{{AFX_MSG(CRaster)
        afx_msg void OnChangeText();
        virtual void OnInitialUpdate();                             // REQ #054
        afx_msg void OnSelendokFonts();
        afx_msg void OnChangeMultiplier();
        afx_msg void OnBnClickedEnableScaling();                    // REQ #052
        afx_msg void OnBnClickedShowGrid();                         // REQ #052
        afx_msg void OnSelendokFontSize();
        afx_msg void OnCopy();
        afx_msg void OnRaster();
        afx_msg void OnTruetype();
        afx_msg void OnVector();
        afx_msg void OnSize(UINT nType, int cx, int cy);            // REQ #050
        afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);            // REQ #050
        afx_msg void OnChangeScaledHeight();                        // REQ #052
        afx_msg void OnSelendOkQuality();                           // REQ #071
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
    };

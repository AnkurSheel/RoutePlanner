/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  4-Nov-08 | REQ #089: Created
*****************************************************************************/
#pragma once                                                        // REQ #089
#include "afxwin.h"                                                 // REQ #089
                                                                    // REQ #089
#include "IDCombo.h"                                                // REQ #089
#include "ImageButton.h"                                            // REQ #089
#include "afxcmn.h"                                                 // REQ #089
#include "Rotation.h"                                               // REQ #089
#include "Degrees.h"                                                // REQ #089
                                                                    // REQ #089
// CGetCharacterPlacement form view                                 // REQ #089
                                                                    // REQ #089
class CGetCharacterPlacement : public CFormView                     // REQ #089
{                                                                   // REQ #089
        DECLARE_DYNCREATE(CGetCharacterPlacement)                   // REQ #089
                                                                    // REQ #089
protected:                                                          // REQ #089
        CGetCharacterPlacement();           // protected constructor used by dynamic creation// REQ #089
        virtual ~CGetCharacterPlacement();                          // REQ #089
                                                                    // REQ #089
public:                                                             // REQ #089
        enum { IDD = IDD_GETCHARACTERPLACEMENT };                   // REQ #089
#ifdef _DEBUG                                                       // REQ #089
        virtual void AssertValid() const;                           // REQ #089
        virtual void Dump(CDumpContext& dc) const;                  // REQ #089
#endif                                                              // REQ #089
                                                                    // REQ #089
protected:                                                          // REQ #089
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support// REQ #089
        virtual void OnInitialUpdate();                             // REQ #089
                                                                    // REQ #089
        DECLARE_MESSAGE_MAP()                                       // REQ #089
                                                                    // REQ #089
        void updateControls();                                      // REQ #089
        void updateCode();                                          // REQ #089
        void updateStatus();                                        // REQ #089
        DWORD ControlsToFlags();                                    // REQ #089
        CString ControlsToFlagsString(const CString & indent);      // REQ #089
        CString FontInfoToString(DWORD info);                       // REQ #089
        void GCPResultsToControls(GCP_RESULTS & results, DWORD retval, DWORD err);
        void DoGetCharacterPlacement();                             // REQ #089
        CString ClassToString(char Class);                          // REQ #089
protected:                                                          // REQ #089
        CFont CodeFont;                                             // REQ #089
        CFont Font;                                                 // REQ #089
        CString PrinterName;                                        // REQ #089
        CDC PrinterDC;                                              // REQ #089
        BOOL initialized;                                           // REQ #089
        CString ResultString;                                       // REQ #089
                                                                    // REQ #089
protected:                                                          // REQ #089
    CStatic c_FontName;                                             // REQ #089
    CButton c_GCP_CLASSIN;                                          // REQ #089
    CButton c_GCP_DIACRITIC;                                        // REQ #089
    CButton c_GCP_DISPLAYZWG;                                       // REQ #089
    CButton c_GCP_GLYPHSHAPE;                                       // REQ #089
    CButton c_GCP_JUSTIFY;                                          // REQ #089
    CButton c_GCP_KASHIDA;                                          // REQ #089
    CButton c_GCP_LIGATE;                                           // REQ #089
    CButton c_GCP_MAXEXTENT;                                        // REQ #089
    CButton c_GCP_NEUTRALOVERRIDE;                                  // REQ #089
    CButton c_GCP_NUMERICOVERRIDE;                                  // REQ #089
    CButton c_GCP_NUMERICSLATIN;                                    // REQ #089
    CButton c_GCP_NUMERICSLOCAL;                                    // REQ #089
    CButton c_GCP_REORDER;                                          // REQ #089
    CButton c_GCP_SYMSWAPOFF;                                       // REQ #089
    CButton c_GCP_USEKERNING;                                       // REQ #089
    CEdit c_Code;                                                   // REQ #089
    CImageButton c_Copy;                                            // REQ #089
    CIDCombo c_Language;                                            // REQ #089
    CButton c_UsePrinterDC;                                         // REQ #089
    CEdit c_PrinterName;                                            // REQ #089
    CTreeCtrl c_GCPResults;                                         // REQ #089
    CEdit c_Status;                                                 // REQ #089
    CButton c_UselpOutString;                                       // REQ #089
    CButton c_UselpOrder;                                           // REQ #089
    CButton c_UselpDx;                                              // REQ #089
    CButton c_UselpCaretPos;                                        // REQ #089
    CButton c_UselpClass;                                           // REQ #089
    CButton c_UselpGlyphs;                                          // REQ #089
    CStatic c_lpOutString;                                          // REQ #089
    CStatic c_lpOrder;                                              // REQ #089
    CStatic c_lpDx;                                                 // REQ #089
    CStatic c_lpCaretPos;                                           // REQ #089
    CStatic c_lpClass;                                              // REQ #089
    CStatic c_lpGlyphs;                                             // REQ #089
    CStatic c_lpStructSize;                                         // REQ #089
    CSpinButtonCtrl c_SpinMaxExtent;                                // REQ #089
    CStatic x_MaxExtent;                                            // REQ #089
    CEdit c_MaxExtent;                                              // REQ #089
    CEdit c_Str;                                                    // REQ #089
    CRotation       c_SpinOrientation;                              // REQ #089
    CRotation       c_SpinEscapement;                               // REQ #089
    CDegrees        c_lfEscapement;                                 // REQ #089
    CDegrees        c_lfOrientation;                                // REQ #089
protected:                                                          // REQ #089
    afx_msg void OnUpdateGetcharplacement(CCmdUI *pCmdUI);          // REQ #089
    afx_msg void OnBnClickedFont();                                 // REQ #089
    afx_msg void OnCbnSelendokLanguage();                           // REQ #089
    afx_msg void OnBnClickedGcpClassin();                           // REQ #089
    afx_msg void OnBnClickedGcpDiacritic();                         // REQ #089
    afx_msg void OnBnClickedGcpDisplayzwg();                        // REQ #089
    afx_msg void OnBnClickedGcpGlyphshape();                        // REQ #089
    afx_msg void OnBnClickedGcpJustify();                           // REQ #089
    afx_msg void OnBnClickedGcpKashida();                           // REQ #089
    afx_msg void OnBnClickedGcpLigate();                            // REQ #089
    afx_msg void OnBnClickedGcpMaxextent();                         // REQ #089
    afx_msg void OnBnClickedGcpNeutraloverride();                   // REQ #089
    afx_msg void OnBnClickedGcpNumericoverride();                   // REQ #089
    afx_msg void OnBnClickedGcpNumericslatin();                     // REQ #089
    afx_msg void OnBnClickedGcpNumericslocal();                     // REQ #089
    afx_msg void OnBnClickedGcpReorder();                           // REQ #089
    afx_msg void OnBnClickedGcpSymswapoff();                        // REQ #089
    afx_msg void OnBnClickedGcpUsekerning();                        // REQ #089
    afx_msg void OnBnClickedCopy();                                 // REQ #089
    afx_msg void OnBnClickedPrinter();                              // REQ #089
    afx_msg void OnSize(UINT nType, int cx, int cy);                // REQ #089
    afx_msg void OnBnClickedUseLpoutstring();                       // REQ #089
    afx_msg void OnBnClickedUseLporder();                           // REQ #089
    afx_msg void OnBnClickedUseLpdx();                              // REQ #089
    afx_msg void OnBnClickedUseCaretPos();                          // REQ #089
    afx_msg void OnBnClickedUseLpclass();                           // REQ #089
    afx_msg void OnBnClickedUseLpglyphs();                          // REQ #089
    afx_msg void OnChangeMaxExtent();                               // REQ #089
    afx_msg void OnChangeStr();                                     // REQ #089
};                                                                  // REQ #089



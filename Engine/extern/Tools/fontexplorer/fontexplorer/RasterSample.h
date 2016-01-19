/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 17-Oct-08 | REQ #052: Created
* 20-Oct-08 | REQ #063: Added flyover coordinates
*****************************************************************************/
#pragma once                                                        // REQ #052
                                                                    // REQ #052
                                                                    // REQ #052
// CRasterSample                                                    // REQ #052
#include "InfoDisplay.h"                                            // REQ #063
                                                                    // REQ #052
class CRasterSample : public CStatic                                // REQ #052
{                                                                   // REQ #052
        DECLARE_DYNAMIC(CRasterSample)                              // REQ #052
                                                                    // REQ #052
public:                                                             // REQ #052
        CRasterSample();                                            // REQ #052
        virtual ~CRasterSample();                                   // REQ #052
        void SetMultiplier(int x);                                  // REQ #052
        void SetGrid(BOOL mode);                                    // REQ #052
                                                                    // REQ #052
protected:                                                          // REQ #052
        int multiplier;                                             // REQ #052
        BOOL ShowGrid;                                              // REQ #052
        CString Text;                                               // REQ #052
        HFONT font;                                                 // REQ #052
        CInfoDisplay * FlyOver;                                     // REQ #063
                                                                    // REQ #052
        virtual void PreSubclassWindow();                           // REQ #063
        CRect VisibleGrid;                                          // REQ #063
        CBitmap ColorMap;                                           // REQ #063
                                                                    // REQ #063
        DECLARE_MESSAGE_MAP()                                       // REQ #052
        afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);               // REQ #063
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);        // REQ #063
        afx_msg LRESULT OnSetText(WPARAM, LPARAM);                  // REQ #052
        afx_msg LRESULT OnGetText(WPARAM, LPARAM);                  // REQ #052
        afx_msg LRESULT OnSetFont(WPARAM, LPARAM);                  // REQ #052
        afx_msg LRESULT OnGetFont(WPARAM, LPARAM);                  // REQ #052
        afx_msg LRESULT OnGetTextLength(WPARAM, LPARAM);            // REQ #052
        afx_msg BOOL OnEraseBkgnd(CDC * pDC);                       // REQ #052
        afx_msg void OnPaint();                                     // REQ #052
        afx_msg HBRUSH CtlColor(CDC * pDC, UINT);                   // REQ #052
};                                                                  // REQ #052



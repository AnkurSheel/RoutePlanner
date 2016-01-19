/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  6-May-08 | REQ #041: Created
*****************************************************************************/

#pragma once                                                        // REQ #041
                                                                    // REQ #041
#include "FontDesc.h"                                               // REQ #041
                                                                    // REQ #041
// CKerningMap                                                      // REQ #041
                                                                    // REQ #041
class CKerningMap : public CWnd                                     // REQ #041
{                                                                   // REQ #041
        DECLARE_DYNAMIC(CKerningMap)                                // REQ #041
                                                                    // REQ #041
public:                                                             // REQ #041
        CKerningMap();                                              // REQ #041
        virtual ~CKerningMap();                                     // REQ #041
        BOOL Create(const CRect & r, UINT id, CWnd * parent);       // REQ #041
        void SetFontInfo(CFontDescriptor & desc);                   // REQ #041
        __inline CRect GetBB() {return bb; }                        // REQ #041
                                                                    // REQ #041
protected:                                                          // REQ #041
                                                                    // REQ #041
   CRect bb;                                                        // REQ #041
   HFONT font;                                                      // REQ #041
   int hpage;                                                       // REQ #041
   int vpage;                                                       // REQ #041
   CString classname;                                               // REQ #041
   void GetMaxCharWidthInArray(CDC & dc, CArray<WORD> & ar, int & width); // REQ #041
        DECLARE_MESSAGE_MAP()                                       // REQ #041
    afx_msg LRESULT OnSetScrollRange(WPARAM, LPARAM);               // REQ #041
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);// REQ #041
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);// REQ #041
    afx_msg void OnPaint();                                         // REQ #041
    afx_msg LRESULT OnSetFont(WPARAM, LPARAM);                      // REQ #041
    afx_msg LRESULT OnGetFont(WPARAM, LPARAM);                      // REQ #041
public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};                                                                  // REQ #041



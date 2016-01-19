/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 24-Apr-08 | Created
* 24-Apr-08 | REQ #009: Moved various #include directives here
* 24-Apr-08 | REQ #010: Made options protected
* 25-Apr-08 | REQ #011: Support multiple output modes
* 27-Apr-08 | REQ #017: Support pair-kerning detection
* 27-Apr-08 | REQ #018: Allow transformation matrix for scaling
* 28-Apr-08 | REQ #022: Support vertical offset
* 29-Apr-08 | REQ #029: Add ability to copy only the image
*  4-May-08 | REQ #038: Handle hover-over
*  5-May-08 | REQ #041: Limit screen capture to used area
* 23-Oct-08 | REQ #072: Handle more general cases of options in DrawABCs
* 30-Oct-08 | REQ #077: Separate drawing and reference contexts for drawABCs
*  1-Nov-08 | REQ #080: FontDisp.h => FontDisplay.h
*****************************************************************************/
// FontDisplay.h : header file                                      // REQ #080
//
#pragma once

#include "dispopts.h"                                               // REQ #009
#include "legend.h"                                                 // REQ #009
#include "poplist.h"                                                // REQ #009
#include "fontdesc.h"                                               // REQ #009
#include "InfoDisplay.h"                                            // REQ #038
typedef struct {int win; int view; } iscale;


/////////////////////////////////////////////////////////////////////////////
// CFontDisplay window

class PosInfo {
    public:
        TCHAR ch;
        int pos;
               };


/****************************************************************************
*                             class CFontDisplay
****************************************************************************/

class CFontDisplay : public CStatic
{
    // Construction
    public:
       CFontDisplay(BOOL dokerning = FALSE);
       COLORREF color;
       void SetWindowText(LPCTSTR s);                               // REQ #011
       void SetFont(CFont * f);                                     // REQ #011
       __inline CRect GetBB() { return bb; }                        // REQ #041
// Attributes
public:
       void SetOpts(display_options & newopts);                     // REQ #010
       void SetWhite(BOOL mode);                                    // REQ #010
       __inline BOOL GetWhite() { return opts.white; }              // REQ #010
                                                                    // REQ #010
       void SetHorizontalRule(BOOL mode);                           // REQ #010
       __inline BOOL GetHorizontalRule() { return opts.hrule; }     // REQ #010
                                                                    // REQ #010
       void SetVerticalRule(BOOL mode);                             // REQ #010
       __inline BOOL GetVerticalRule() { return opts.vrule; }       // REQ #010
                                                                    // REQ #010
       void SetCharacterRule(BOOL mode);                            // REQ #010
       __inline BOOL GetCharacterRule() { return opts.chrule; }     // REQ #010
                                                                    // REQ #010
       void SetUseColors(BOOL mode);                                // REQ #010
       __inline BOOL GetUseColors() { return opts.colors; }         // REQ #010
                                                                    // REQ #010
       void SetTrackMode(BOOL mode);                                // REQ #010
       __inline BOOL GetTrackMode() { return opts.track; }          // REQ #010
                                                                    // REQ #010
       void SetUsePairKerning(BOOL mode);                           // REQ #010
       __inline BOOL GetUsePairKerning() { return opts.kerning; }   // REQ #010
                                                                    // REQ #010
       void SetOutputMode(display_options::OutputOptions mode);     // REQ #010
       __inline display_options::OutputOptions GetOutputMode() { return opts.output; } // REQ #010
                                                                    // REQ #010
       void SetVerticalOffset(int n);                               // REQ #022
       __inline int  GetVerticalOffset() { return opts.VerticalOffset; } // REQ #022
                                                                    // REQ #022
       void SetTrackValue(int val);                                 // REQ #010
       __inline int GetTrackValue() { return opts.trackval; }       // REQ #010

       void SetGMAdvanced(BOOL mode);                               // REQ #018
       __inline BOOL GetGMAdvanced() { return opts.advanced; }      // REQ #018

       __inline display_options & GetOpts() { return opts; }        // REQ #010

       void SetDebug(BOOL mode) { opts.debug = mode; }              // REQ #032
       __inline BOOL GetDebug() { return opts.debug; }              // REQ #032

       CSize GetImageSize();                                        // REQ #029
// Operations
public:
        static LegendInfo ** GetLegend();
// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CFontDisplay)
        protected:
        virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
        virtual void PreSubclassWindow();                           // REQ #038
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~CFontDisplay();

        // Generated message map functions
protected:
#ifdef _DEBUG
        PosInfo * pinfo;
#endif
        display_options opts;                                       // REQ #010
        int ImageWidth;                                             // REQ #029

        void SetBB(CDC & dc, CRect r);                              // REQ #041
        CRect bb;                                                   // REQ #041

        class CharInfo {                                            // REQ #038
            public:                                                 // REQ #038
               CharInfo() { r.SetRectEmpty(), ch = _T('\0'), ::ZeroMemory(&abc, sizeof(ABC)); pair = 0; } // REQ #038
               CharInfo(const CRect & rp, TCHAR chp, const ABC & abcp, int pairp)// REQ #038
                  {                                                 // REQ #038
                   r = rp;                                          // REQ #038
                   ch = chp;                                        // REQ #038
                   abc = abcp;                                      // REQ #038
                   pair = pairp;                                    // REQ #038
                  }                                                 // REQ #038
               CRect r;                                             // REQ #038
               TCHAR ch;                                            // REQ #038
               ABC abc;                                             // REQ #038
               int pair;                                            // REQ #038
#ifdef _DEBUG                                                       // REQ #038
               int drawcode;                                        // REQ #038
#endif                                                              // REQ #038
        };                                                          // REQ #038
                                                                    // REQ #038
        CArray<CharInfo> Hits;                                      // REQ #038
        CInfoDisplay * FlyOver;                                     // REQ #038

        CFont legendFont;
        int GetDisplayCode(CDC & dc, TCHAR ch);
        static inline int f(int x) { return (x == 0 ? 0 : 
                                        x < 0 ? 1 : 2); }
        void DrawOutline(CDC & dc, CFontDescriptor & desc, const display_options & opts, int x, const CString & Text, int i); // REQ #066
        int requiredHeight(CFontDescriptor & desc);
        static float limitScaling(TEXTMETRIC & tm, float scale);

        void DoExtTextOut(const CFontDescriptor & desc, CDC & dc, const CString & Text, int baseoffset, int & pos, int i); // REQ #066

        void drawABCs(CDC & dc, CDC & CharDC, int pos, TCHAR ch, TCHAR next, int top, int bottom, int parity, const display_options & opts); // BOOL ignore = FALSE);// REQ #031// REQ #038// REQ #072// REQ #077
        void drawDistance(CDC & dc, int from, int to, int ypos, LPCTSTR legend, int ylegend);
        void drawV(CDC & dc, int x, int top, int bottom);
        void writeRulerV(CDC & dc, int left, int top, int bottom);
        void writeRulerH(CDC & dc, int pos, int left, int right);
        void getABC(CDC & dc, TCHAR ch, ABC& abc);
        CPopupList * popup;
        BOOL dismissPopup(CPoint point);
        SIZE getOverhangTextExtent(CDC & dc, CString s);
        iscale normalizeScaling(float sx);
        COLORREF ComputePairKerningColor(CDC & pdc, COLORREF color, const CString & s, int i); // REQ #017// REQ #043
        //{{AFX_MSG(CFontDisplay)
        afx_msg void OnPaint();
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
#if _MSC_VER < 1300                                                 // REQ #042
        afx_msg UINT OnNcHitTest(CPoint point);
#else                                                               // REQ #042
        afx_msg LRESULT OnNcHitTest(CPoint point);                  // REQ #042
#endif                                                              // REQ #042
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnDestroy();
        afx_msg void OnCancelMode();
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);        // REQ #038
        //}}AFX_MSG
        afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);               // REQ #038

        DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

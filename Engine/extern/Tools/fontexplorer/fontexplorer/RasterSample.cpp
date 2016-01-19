/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 17-Oct-08 | REQ #052: Created
* 18-Oct-08 | REQ #052: Handle raster magnification
* 20-Oct-08 | REQ #063: Added flyover coordinates
*****************************************************************************/
// RasterSample.cpp : implementation file
//

#include "stdafx.h"                                                 // REQ #052
#include "Resource.h"                                               // REQ #063
#include "RasterSample.h"                                           // REQ #052
#include "ToString.h"                                               // REQ #063
                                                                    // REQ #052
                                                                    // REQ #052
// CRasterSample                                                    // REQ #052
                                                                    // REQ #052
IMPLEMENT_DYNAMIC(CRasterSample, CStatic)                           // REQ #052

/****************************************************************************
*                        CRasterSample::CRasterSample
*                        CRasterSample::~CRasterSample
* Effect: 
*       Constructor/destructor
****************************************************************************/
                                                                    // REQ #052
CRasterSample::CRasterSample()                                      // REQ #052
{                                                                   // REQ #052
 multiplier = 1;                                                    // REQ #052
 font = NULL;                                                       // REQ #052
 ShowGrid = TRUE;                                                   // REQ #052
 FlyOver = NULL;                                                    // REQ #063
}                                                                   // REQ #052
                                                                    // REQ #052
CRasterSample::~CRasterSample()                                     // REQ #052
{                                                                   // REQ #052
}                                                                   // REQ #052

/****************************************************************************
*                      CRasterSample::PreSubclassWindow
* Result: void
*       
* Effect: 
*       Creates the flyover help
****************************************************************************/

void CRasterSample::PreSubclassWindow()                             // REQ #063
    {                                                               // REQ #063
     CStatic::PreSubclassWindow();                                  // REQ #063
     FlyOver = new CInfoDisplay;                                    // REQ #063
     FlyOver->Create(0, 0, _T(""), this);                           // REQ #063
     CFont f;                                                       // REQ #063
     f.CreateStockObject(DEFAULT_GUI_FONT);                         // REQ #063
     FlyOver->SetFont(&f);                                          // REQ #063
     f.Detach();                                                    // REQ #063
    } // CRasterSample::PreSubclassWindow                           // REQ #063

/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CRasterSample, CStatic)                           // REQ #052
        ON_WM_PAINT()                                               // REQ #052
        ON_WM_CTLCOLOR_REFLECT()                                    // REQ #052
        ON_MESSAGE(WM_SETTEXT, OnSetText)                           // REQ #052
        ON_MESSAGE(WM_GETTEXT, OnGetText)                           // REQ #052
        ON_MESSAGE(WM_SETFONT, OnSetFont)                           // REQ #052
        ON_MESSAGE(WM_GETFONT, OnGetFont)                           // REQ #052
        ON_MESSAGE(WM_GETTEXTLENGTH, OnGetTextLength)               // REQ #052
        ON_WM_MOUSEMOVE()                                           // REQ #063
        ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)                     // REQ #063
        ON_WM_ERASEBKGND()                                          // REQ #052
END_MESSAGE_MAP()                                                   // REQ #052

/****************************************************************************
*                           CRasterSample::SetGrid
* Inputs:
*       BOOL mode: Mode to set
* Result: void
*       
* Effect: 
*       Sets the grid display mode
****************************************************************************/

void CRasterSample::SetGrid(BOOL mode)                              // REQ #052
    {                                                               // REQ #052
     if(ShowGrid == mode)                                           // REQ #052
        return;                                                     // REQ #052
     ShowGrid = mode;                                               // REQ #052
     Invalidate();                                                  // REQ #052
    } // CRasterSample::SetGrid                                     // REQ #052

/****************************************************************************
*                        CRasterSample::SetMultiplier
* Inputs:
*       int n: Multiplier
* Result: void
*       
* Effect: 
*       Sets the multiplier
****************************************************************************/

void CRasterSample::SetMultiplier(int n)                            // REQ #052
    {                                                               // REQ #052
     if(multiplier == n)                                            // REQ #052
        return;                                                     // REQ #052
     multiplier = n;                                                // REQ #052
     if(GetSafeHwnd() != NULL)                                      // REQ #052
        Invalidate();                                               // REQ #052
    } // CRasterSample::SetMultiplier                               // REQ #052

/****************************************************************************
*                           CRasterSample::OnPaint
* Result: void
*       
* Effect: 
*       Draws the sample
****************************************************************************/

void CRasterSample::OnPaint()                                       // REQ #052
    {                                                               // REQ #052
     CPaintDC dc(this);                                             // REQ #052
     CString s;                                                     // REQ #052
     GetWindowText(s);                                              // REQ #052
                                                                    // REQ #052
     CFont * f = GetFont();                                         // REQ #052
     dc.SelectObject(f);                                            // REQ #052
#ifdef _DEBUG                                                       // REQ #052
     LOGFONT lf;                                                    // REQ #052
     if(f != NULL)                                                  // REQ #052
        f->GetLogFont(&lf);                                         // REQ #052
#endif                                                              // REQ #052
     CSize sz = dc.GetTextExtent(s);                                // REQ #052
     CDC memDC;                                                     // REQ #052
     memDC.CreateCompatibleDC(&dc);                                 // REQ #052
     CBitmap bmp;                                                   // REQ #052
     bmp.CreateCompatibleBitmap(&dc, sz.cx, sz.cy);                 // REQ #052
                                                                    // REQ #052
     int memsave = memDC.SaveDC();                                  // REQ #052
     memDC.SelectObject(&bmp);                                      // REQ #052
     memDC.SelectObject(f);                                         // REQ #052
     memDC.SetBkMode(TRANSPARENT);                                  // REQ #052
     CRect r(0, 0, sz.cx, sz.cy);                                   // REQ #052
     memDC.FillSolidRect(&r, RGB(255, 255, 255));                   // REQ #052
                                                                    // REQ #052
     memDC.TextOut(0, 0, s);                                        // REQ #052
                                                                    // REQ #052
     dc.StretchBlt(0, 0, sz.cx * multiplier, sz.cy * multiplier, &memDC, 0, 0, sz.cx, sz.cy, SRCCOPY);// REQ #052
                                                                    // REQ #052
     if(ShowGrid)                                                   // REQ #052
        { /* show grid */                                           // REQ #052
         dc.SelectObject(CPen::FromHandle((HPEN)::GetStockObject(WHITE_PEN)));// REQ #052
         dc.SetROP2(R2_XORPEN);                                     // REQ #052
         VisibleGrid = CRect(0, 0, sz.cx * multiplier, sz.cy * multiplier);// REQ #063
         for(int x = 0; x < sz.cx * multiplier; x += multiplier)    // REQ #052
            { /* draw verticals */                                  // REQ #052
             dc.MoveTo(x, 0);                                       // REQ #052
             dc.LineTo(x, sz.cy * multiplier);                      // REQ #052
            } /* draw verticals */                                  // REQ #052
                                                                    // REQ #052
         for(int y = 0; y < sz.cy * multiplier; y += multiplier)    // REQ #052
            { /* draw horizonatals */                               // REQ #052
             dc.MoveTo(0, y);                                       // REQ #052
             dc.LineTo(sz.cx * multiplier, y);                      // REQ #052
            } /* draw horizonatals */                               // REQ #052
        } /* show grid */                                           // REQ #052
                                                                    // REQ #052
     memDC.RestoreDC(memsave);                                      // REQ #052
     ColorMap.DeleteObject();                                       // REQ #063
     ColorMap.Attach(bmp.Detach());                                 // REQ #063
    } // CRasterSample::OnPaint                                     // REQ #052

/****************************************************************************
*                           CRasterSample::CtlColor
* Inputs:
*       CDC * pDC: DC to use
*       UINT nCtlColor: ignored 
* Result: HBRUSH
*       Brush to use
* Effect: 
*       Returns a brush for the background
****************************************************************************/

HBRUSH CRasterSample::CtlColor(CDC * pDC, UINT)                     // REQ #052
    {                                                               // REQ #052
     pDC->SetBkMode(TRANSPARENT);                                   // REQ #052
     return (HBRUSH)::GetStockObject(WHITE_BRUSH);                  // REQ #052
    } // CRasterSample::CtlColor                                    // REQ #052

/****************************************************************************
*                          CRasterSample::OnSetText
* Inputs:
*       WPARAM: unused
*       LPARAM lParam: (LPARAM)(LPCTSTR) string
* Result: LRESULT
*       (LRESULT)TRUE, always
* Effect: 
*       Sets the text
****************************************************************************/

LRESULT CRasterSample::OnSetText(WPARAM, LPARAM lParam)             // REQ #052
    {                                                               // REQ #052
     Text = (LPCTSTR)lParam;                                        // REQ #052
     Invalidate();                                                  // REQ #052
     return TRUE;                                                   // REQ #052
    } // CRasterSample::OnSetText                                   // REQ #052

/****************************************************************************
*                          CRasterSample::OnGetText
* Inputs:
*       WPARAM: (WPARAM) Maximum character count
*       LPARAM: (LPARAM)(LPTSTR) Pointer to string buffer
* Result: LRESULT
*       Number of characters actually copied
* Effect: 
*       Copies the characters to the buffer
****************************************************************************/

LRESULT CRasterSample::OnGetText(WPARAM wParam, LPARAM lParam)      // REQ #052
    {                                                               // REQ #052
     LPTSTR p = (LPTSTR)lParam;                                     // REQ #052
     if(Text.GetLength() < (int)wParam)                             // REQ #052
        { /* can do it */                                           // REQ #052
         _tcscpy_s(p, Text.GetLength() + 1, (LPCTSTR)Text); // we know this is safe         // REQ #052
         return Text.GetLength();                                   // REQ #052
        } /* can do it */                                           // REQ #052
     else                                                           // REQ #052
        { /* truncate it */                                         // REQ #052
         lstrcpyn(p, (LPCTSTR)Text, (int)wParam);                   // REQ #052
         return wParam;                                             // REQ #052
        } /* truncate it */                                         // REQ #052
    } // CRasterSample::OnGetText                                   // REQ #052

/****************************************************************************
*                          CRasterSample::OnSetFont
* Inputs:
*       WPARAM: (WPARAM)(HFONT)
*       LPARAM: (LPARAM)(MAKELONG(redraw, 0)):
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Sets the font
****************************************************************************/

LRESULT CRasterSample::OnSetFont(WPARAM wParam, LPARAM lParam)      // REQ #052
    {                                                               // REQ #052
     font = (HFONT)wParam;                                          // REQ #052
     if(LOWORD(lParam))                                             // REQ #052
        { /* update window */                                       // REQ #052
         Invalidate();                                              // REQ #052
         UpdateWindow();                                            // REQ #052
        } /* update window */                                       // REQ #052
     return 0;                                                      // REQ #052
    } // CRasterSample::OnSetFont                                   // REQ #052

/****************************************************************************
*                          CRasterSample::OnGetFont
* Inputs:
*       WPARAM: unused
*       LPARAM: unused
* Result: LRESULT
*       (LRESULT)(HFONT)
****************************************************************************/

LRESULT CRasterSample::OnGetFont(WPARAM, LPARAM)                    // REQ #052
    {                                                               // REQ #052
     return (LPARAM)font;                                           // REQ #052
    } // CRasterSample::OnGetFont                                   // REQ #052

/****************************************************************************
*                       CRasterSample::OnGetTextLength
* Inputs:
*       WPARAM: unused
*       LPARAM: unused
* Result: LRESULT
*       Length of text
****************************************************************************/

LRESULT CRasterSample::OnGetTextLength(WPARAM, LPARAM)              // REQ #052
    {                                                               // REQ #052
     return Text.GetLength();                                       // REQ #052
    } // CRasterSample::OnGetTextLength                             // REQ #052

/****************************************************************************
*                         CRasterSample::OnEraseBkgnd
* Inputs:
*       CDC * pDC: DC
* Result: BOOL
*       TRUE, always
* Effect: 
*       Erases the background
****************************************************************************/

BOOL CRasterSample::OnEraseBkgnd(CDC * pDC)                         // REQ #052
    {                                                               // REQ #052
     CRect r;                                                       // REQ #052
     GetClientRect(&r);                                             // REQ #052
     pDC->FillSolidRect(&r, ::GetSysColor(COLOR_3DFACE));           // REQ #052
     return TRUE;                                                   // REQ #052
    } // CRasterSample::OnEraseBkgnd                                // REQ #052

/****************************************************************************
*                         CRasterSample::OnMouseMove
* Inputs:
*       UINT nFlags:
*       CPoint point:
* Result: void
*       
* Effect: 
*       Handles the flyover help
****************************************************************************/

void CRasterSample::OnMouseMove(UINT nFlags, CPoint point)          // REQ #063
    {                                                               // REQ #063
     if(ShowGrid)                                                   // REQ #063
        { /* show coordinates? */                                   // REQ #063
         if(VisibleGrid.PtInRect(point))                            // REQ #063
            { /* show coordinates */                                // REQ #063
             CPoint pt;  // normalized point                        // REQ #063
             pt.x = point.x / multiplier;                           // REQ #063
             pt.y = point.y / multiplier;                           // REQ #063
                                                                    // REQ #063
             COLORREF color;                                        // REQ #063
             CDC dc;                                                // REQ #063
             dc.CreateCompatibleDC(NULL);                           // REQ #063
             dc.SelectObject(&ColorMap);                            // REQ #063
             color = dc.GetPixel(pt.x, pt.y);                       // REQ #063
                                                                    // REQ #063
             CString colorString;                                   // REQ #063
                                                                    // REQ #063
             switch(color)                                          // REQ #063
                { /* color */                                       // REQ #063
                 case RGB(0, 0, 0):                                 // REQ #063
                    colorString.LoadString(IDS_BLACK);              // REQ #063
                    break;                                          // REQ #063
                 case RGB(255, 255, 255):                           // REQ #063
                    colorString.LoadString(IDS_WHITE);              // REQ #063
                    break;                                          // REQ #063
                 default:                                           // REQ #063
                    colorString  = ToString(_T("RGB(%d, %d, %d)"),  // REQ #063
                                            GetRValue(color),       // REQ #063
                                            GetGValue(color),       // REQ #063
                                            GetBValue(color));      // REQ #063
                } /* color */                                       // REQ #063
                                                                    // REQ #063
             FlyOver->SetWindowText(ToString(_T("%d, %d\n%s"),      // REQ #063
                                             pt.x, pt.y,            // REQ #063
                                             colorString));         // REQ #063
                                                                    // REQ #063
             CPoint ptd = point;                                    // REQ #063
             ClientToScreen(&ptd);                                  // REQ #063
             ptd.y += ::GetSystemMetrics(SM_CYCURSOR);              // REQ #063
             FlyOver->SetWindowPos(NULL, ptd.x, ptd.y, 0, 0,        // REQ #063
                                   SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);// REQ #063
             if(!FlyOver->IsWindowVisible())                        // REQ #063
                { /* show it */                                     // REQ #063
                 FlyOver->ShowWindow(SW_SHOWNA);                    // REQ #063
                 TRACKMOUSEEVENT tme = { sizeof(TRACKMOUSEEVENT),   // REQ #063
                                         TME_LEAVE, m_hWnd, 0};     // REQ #063
                 VERIFY(TrackMouseEvent(&tme));                     // REQ #063
                } /* show it */                                     // REQ #063
             return;                                                // REQ #063
            } /* show coordinates */                                // REQ #063
        } /* show coordinates? */                                   // REQ #063
     // If we get here, we have not shown the coordinates           // REQ #063
     if(FlyOver->IsWindowVisible())                                 // REQ #063
        FlyOver->ShowWindow(SW_HIDE);                               // REQ #063
    } // CRasterSample::OnMouseMove                                 // REQ #063

/****************************************************************************
*                         CRasterSample::OnMouseLeave
* Inputs:
*       WPARAM: ignored
*       LPARAM: ignored
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Hides the tracking window
****************************************************************************/

LRESULT CRasterSample::OnMouseLeave(WPARAM, LPARAM)                 // REQ #063
    {                                                               // REQ #063
     if(FlyOver->IsWindowVisible())                                 // REQ #063
        FlyOver->ShowWindow(SW_HIDE);                               // REQ #063
     return 0;                                                      // REQ #063
    } // CRasterSample::OnMouseLeave                                // REQ #063

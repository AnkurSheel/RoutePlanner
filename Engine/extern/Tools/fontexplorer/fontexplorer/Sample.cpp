/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 24-Apr-08 | Created
* 24-Apr-08 | REQ #008: Removed FontExplorer.h
* 19-Oct-08 | REQ #059: Show grid for font sample
* 19-Oct-08 | REQ #060: Support horizontal and vertical alignment selections
*****************************************************************************/
// Sample.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"                                               // REQ #008
#include "Sample.h"
#include "savedc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSample

CSample::CSample()
{
 GraphicsMode = GM_COMPATIBLE;
}

CSample::~CSample()
{
}


BEGIN_MESSAGE_MAP(CSample, CStatic)
        //{{AFX_MSG_MAP(CSample)
        ON_WM_PAINT()
        ON_WM_ERASEBKGND()
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSample message handlers


/****************************************************************************
*                            CSample::SetTextAlign
* Inputs:
*       DWORD align: Desired alignment
*               one of       |      one of
*               -------------+-----------------
*               TA_LEFT   \  |   /  TA_TOP
*               TA_CENTER  > |  <   TA_BOTTOM
*               TA_RIGHT  /  |   \  TA_BASELINE
* Result: void
*       
* Effect: 
*       Sets the text alignment
****************************************************************************/

void CSample::SetTextAlign(DWORD align)                             // REQ #060
    {                                                               // REQ #060
     if(TextAlign == align)                                         // REQ #060
        return;                                                     // REQ #060
     TextAlign = align;                                             // REQ #060
     if(GetSafeHwnd() != NULL)                                      // REQ #060
        Invalidate();                                               // REQ #060
    } // CSample::SetTextAlign                                      // REQ #060

/****************************************************************************
*                      CSample::SetGraphicsMode
* Inputs:
*       DWORD mode: GM_ADVANCED or GM_COMPATIBLE
* Result: void
*       
* Effect: 
*       Sets the graphics mode
****************************************************************************/

void CSample::SetGraphicsMode(DWORD mode)
    {
     if(GraphicsMode == mode)
        return;
     GraphicsMode = mode;
     if(GetSafeHwnd() != NULL)
        Invalidate();
    } // CSample::SetGraphicsMode

/****************************************************************************
*                              CSample::ShowGrid
* Inputs:
*       BOOL mode: Mode to set
* Result: void
*       
* Effect: 
*       Sets the grid mode
****************************************************************************/

void CSample::ShowGrid(BOOL mode)                                   // REQ #059
    {                                                               // REQ #059
     if(Grid == mode)                                               // REQ #059
        return;                                                     // REQ #059
     Grid = mode;                                                   // REQ #059
     Invalidate();                                                  // REQ #059
    } // CSample::ShowGrid                                          // REQ #059

/****************************************************************************
*                               CSample::OnPaint
* Result: void
*       
* Effect: 
*       Draws the text
****************************************************************************/

void CSample::OnPaint() 
    {
     CPaintDC dc(this); // device context for painting
     CRect r;
     CFont * font = GetFont();
        
     GetClientRect(&r);
        
     ::SetGraphicsMode(dc.m_hDC, GraphicsMode);

     dc.SelectObject(font);

     dc.SetBkMode(TRANSPARENT);
     dc.SetTextAlign(TextAlign);                                    // REQ #060

     CRgn rgn;                                                      // REQ #059
     rgn.CreateRectRgnIndirect(&r);                                 // REQ #059
     dc.SelectClipRgn(&rgn);                                        // REQ #059

     CString s;
     GetWindowText(s);

     CSize sz = dc.GetTextExtent(s);                                // REQ #059
     CPoint pt;                                                     // REQ #059
     //------------------------------------------------------------ // REQ #060
     // 0000 0000 0000  TA_LEFT                                     // REQ #060
     // 0000 0000 0001  TA_UPDATECP                                 // REQ #060
     // 0000 0000 0010  TA_RIGHT                                    // REQ #060
     // 0000 0000 0110  TA_CENTER                                   // REQ #060
     // 0000 0000 0000  TA_TOP                                      // REQ #060
     // 0000 0000 1000  TA_BOTTOM                                   // REQ #060
     // 0000 0011 0000  TA_BASELINE                                 // REQ #060
     // 0001 0000 0000  TA_RTLREADING                               // REQ #060
     //------------------------------------------------------------ // REQ #060
     pt.x = r.Width() / 2;                                          // REQ #059
     pt.y = r.Height() / 2;                                         // REQ #059
                                                                    // REQ #060
     switch(TextAlign & (TA_LEFT | TA_RIGHT | TA_CENTER))           // REQ #060
        { /* horizontal */                                          // REQ #060
         case TA_LEFT:                                              // REQ #060
            pt.x -= sz.cx / 2;                                      // REQ #059
            pt.y -= sz.cy / 2;                                      // REQ #059
            break;                                                  // REQ #060
         case TA_CENTER:                                            // REQ #060
            // Do nothing                                           // REQ #060
            break;                                                  // REQ #060
         case TA_RIGHT:                                             // REQ #060
            pt.x += sz.cx / 2;                                      // REQ #060
            pt.y += sz.cy / 2;                                      // REQ #060
            break;                                                  // REQ #060
        } /* horizontal */                                          // REQ #060
                                                                    // REQ #059
     if(Grid)                                                       // REQ #059
        { /* show grid */                                           // REQ #059
         CPen pen(PS_SOLID, 0, RGB(255, 0, 0));                     // REQ #059
         int save = dc.SaveDC();                                    // REQ #059
         dc.SelectObject(&pen);                                     // REQ #059
         dc.MoveTo(pt.x, r.top);                                    // REQ #059
         dc.LineTo(pt.x, r.bottom);                                 // REQ #059
         dc.MoveTo(r.left, pt.y);                                   // REQ #059
         dc.LineTo(r.right, pt.y);                                  // REQ #059
         dc.RestoreDC(save);                                        // REQ #059
        } /* show grid */                                           // REQ #059

     dc.TextOut(pt.x, pt.y, s);                                     // REQ #059

     
//     dc.DrawText(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  // REQ #059

    }


/****************************************************************************
*                            CSample::OnEraseBkgnd
* Inputs:
*       CDC * pDC:
* Result: BOOL
*       
* Effect: 
*       Erases the background
****************************************************************************/

BOOL CSample::OnEraseBkgnd(CDC* pDC) 
{
 CBrush bkg;
 CRect r;

 CSaveDC dc(pDC);

 bkg.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
 GetClientRect(&r);

 dc->SelectObject(&bkg);
 dc->PatBlt(r.left, r.top, r.Width(), r.Height(), PATCOPY);

 return CStatic::OnEraseBkgnd(pDC);
}

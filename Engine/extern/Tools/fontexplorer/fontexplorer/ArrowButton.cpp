// ArrowButton.cpp : implementation file
//

#include "stdafx.h"
#include "ArrowButton.h"
#include ".\arrowbutton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArrowButton

/****************************************************************************
*                         CArrowButton::CArrowButton
* Effect: 
*       Constructor
****************************************************************************/

CArrowButton::CArrowButton()
   {
    direction = DrawArrow::ARROW_NONE;
    LineColor = RGB(0,0,0);
    BodyColor = ::GetSysColor(COLOR_WINDOW);
    TextColor = ::GetSysColor(COLOR_WINDOWTEXT);
   }

/****************************************************************************
*                         CArrowButton::~CArrowButton
* Effect: 
*       Destructor
****************************************************************************/

CArrowButton::~CArrowButton()
   {
   }

/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CArrowButton, CButton)
        //{{AFX_MSG_MAP(CArrowButton)
                // NOTE - the ClassWizard will add and remove mapping macros here.
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArrowButton message handlers

/****************************************************************************
*                       CArrowButton::RecomputeFontSize
* Inputs:
*       CDC * dc: DC to work on
*       CFont * f: Original font
*       CFont & Font: New font
*       CSize & size: size of the current string
*       CSize AreaSize: Size of the area it can write into
*       const CString & text: The text that will be displayed
*       int depth: A depth limit to keep us from going into infinite recursion
* Result: void
*       
* Effect: 
*       Recomputes the font size
*       The Font is changed, and the new font is left selected into the dc
*       The size is updated to show the new text size
****************************************************************************/

void CArrowButton::RecomputeFontSize(CDC * dc, CFont * f, CFont & Font, CSize & size, CSize AreaSize, const CString & text, int depth)
    {
     LOGFONT lf;
     Font.GetLogFont(&lf);

     if(depth > 0)
        { /* fine-tune it */
         if(lf.lfHeight < 0)
            lf.lfHeight += depth;
         else
            lf.lfHeight -= depth;
        } /* fine-tune it */
     else
        { /* first-cut approximation */
         double ratio =  (double)AreaSize.cx / (double)size.cx ;
         double newsize = ((double)lf.lfHeight * ratio);

         lf.lfHeight = (int) newsize;
        } /* adjust */

     if(lf.lfHeight < 4)
         return;

     dc->SelectObject(f);
     Font.DeleteObject();
     Font.CreateFontIndirect(&lf);
     dc->SelectObject(&Font);
     size = dc->GetTextExtent(text);
     if(size.cx > AreaSize.cx)
        { /* still too large */
         RecomputeFontSize(dc, f, Font, size, AreaSize, text, depth + 1);
        } /* still too large */
    } // CArrowButton::RecomputeFontSize

/****************************************************************************
*                           CArrowButton::DrawItem
* Inputs:
*       LPDRAWITEMSTRUCT dis:
* Result: void
*       
* Effect: 
*       Draws the arrow and the text in it
****************************************************************************/

void CArrowButton::DrawItem(LPDRAWITEMSTRUCT dis) 
   {
    CDC * dc = CDC::FromHandle(dis->hDC);
    int save = dc->SaveDC();
    CRect r;
    GetClientRect(&r);

    dc->FillSolidRect(&r, ::GetSysColor(COLOR_3DFACE));
    dc->SelectStockObject(WHITE_BRUSH);
    UINT edge;
    CPoint pt(0,0);
    if(dis->itemState & ODS_SELECTED)
       { /* up */
        edge = EDGE_SUNKEN;
        pt = CPoint(1, 1);
       } /* up */
    else
       { /* down */
        edge = EDGE_RAISED;
       } /* down */

    dc->DrawEdge(&r, edge, BF_ADJUST | BF_RECT);
    r.InflateRect(-2, -2);
    r += pt;
    CBrush Body;
    CPen Line;
    CBitmap bmp;
    COLORREF Text;

    if(IsWindowEnabled())
       { /* enabled */
        Body.CreateSolidBrush(BodyColor);
        Line.CreatePen(PS_SOLID, 0, LineColor);
        Text = TextColor;
       } /* enabled */
    else
       { /* disabled */
        // This creates a bitmap which is an alternating-pattern
        // black-and-white bitmap, then it ANDs it into the existing
        // control
        Line.CreatePen(PS_SOLID, 0, ::GetSysColor(COLOR_3DSHADOW));
        CDC pattern;
        pattern.CreateCompatibleDC(dc);
        static const UINT BRUSH_WIDTH = 8;
        static const UINT BRUSH_HEIGHT = 8;
        bmp.CreateCompatibleBitmap(dc, BRUSH_WIDTH, BRUSH_HEIGHT);
        int save = pattern.SaveDC();
        pattern.SelectObject(&bmp);
        Text = ::GetSysColor(COLOR_GRAYTEXT);

        COLORREF graycolor = (BodyColor == ::GetSysColor(COLOR_3DFACE) ? ::GetSysColor(COLOR_3DSHADOW) : ::GetSysColor(COLOR_3DFACE));
        for(int x = 0; x < BRUSH_WIDTH; x++)
           for(int y = 0; y < BRUSH_HEIGHT; y++)
              pattern.SetPixel(x,y, (x & 1) ? ((y & 1) ? BodyColor : graycolor)
                                            : ((y & 1) ? graycolor : BodyColor));

        Body.CreatePatternBrush(&bmp);
        pattern.RestoreDC(save);
       } /* disabled */
    

    dc->SelectObject(&Body);
    dc->SelectObject(&Line);
    CRect textArea = DrawArrow::Draw(*dc, r, direction);

    CString text;
    CSize AreaSize;
    GetWindowText(text);
    CFont Font;
    //int width;
    if(!text.IsEmpty())
       { /* has text */
        CFont * f;
        f = GetFont();
        if(f != NULL)
           { /* has font */
            LOGFONT lf;
            f->GetLogFont(&lf);
            CPoint pt(0,0);

            switch(direction)
               { /* direction */
                case DrawArrow::ARROW_W:
                      // Normal text orientation
                      lf.lfHeight = textArea.Height();
                      AreaSize = CSize(textArea.Width(), textArea.Height());
                      break;
                case DrawArrow::ARROW_E:
                      // Normal text orientation
                      lf.lfHeight = textArea.Height();
                      AreaSize = CSize(textArea.Width(), textArea.Height());
                      break;
                case DrawArrow::ARROW_N:
                      // Vertical, up
                      lf.lfOrientation = 900;
                      lf.lfEscapement = 900;
                      lf.lfHeight = textArea.Width();
                      AreaSize = CSize(textArea.Height(), textArea.Width());
                      break;
                case DrawArrow::ARROW_S:
                      lf.lfOrientation = -900;
                      lf.lfEscapement = -900;
                      lf.lfHeight = textArea.Width();
                      AreaSize = CSize(textArea.Height(), textArea.Width());
                      break;
               } /* direction */

            VERIFY(Font.CreateFontIndirect(&lf));
            dc->SelectObject(&Font);
            dc->SetBkMode(TRANSPARENT);
            dc->SetTextColor(Text);

            CSize size = dc->GetTextExtent(text);
            
            if(size.cx > AreaSize.cx)
               { /* recompute font */
                RecomputeFontSize(dc, f, Font, size, AreaSize, text, 0);
               } /* recompute font */

            DWORD style = GetStyle();
            switch(style & (BS_LEFT | BS_RIGHT | BS_CENTER))
               { /* style */
                case BS_LEFT:
                      switch(direction)
                         { /* direction: LEFT */
                          case DrawArrow::ARROW_E:
                                dc->SetTextAlign(TA_LEFT);
                                pt.x = textArea.left + ::GetSystemMetrics(SM_CXBORDER);
                                pt.y = textArea.top + (textArea.Height() - size.cy) / 2;
                                break;
                          case DrawArrow::ARROW_W:
                                dc->SetTextAlign(TA_LEFT);
                                pt.x = textArea.left;
                                pt.y = textArea.top + (textArea.Height() - size.cy) / 2;
                                break;
                          case DrawArrow::ARROW_N:
                                dc->SetTextAlign(TA_LEFT);
                                pt.x = textArea.left + (textArea.Width() - size.cy) / 2;
                                pt.y = textArea.bottom;
                                break;
                          case DrawArrow::ARROW_S:
                                dc->SetTextAlign(TA_LEFT);
                                pt.x = textArea.right - (textArea.Width() - size.cy) / 2;
                                pt.y = textArea.top;
                                break;
                         } /* direction: LEFT */
                      break;
                case BS_RIGHT:
                      dc->SetTextAlign(TA_RIGHT);
                      switch(direction)
                         { /* direction: RIGHT */
                          case DrawArrow::ARROW_W:
                          case DrawArrow::ARROW_E:
                                dc->SetTextAlign(TA_RIGHT);
                                pt.x = textArea.right;
                                pt.y = textArea.top + (textArea.Height() - size.cy) / 2;
                                break;
                          case DrawArrow::ARROW_N:
                                dc->SetTextAlign(TA_LEFT);
                                pt.x = textArea.left + (textArea.Width() - size.cy) / 2;
                                pt.y = textArea.top + size.cx;
                                break;
                          case DrawArrow::ARROW_S:
                                dc->SetTextAlign(TA_LEFT);
                                pt.x = textArea.right - (textArea.Width() - size.cy) / 2;
                                pt.y = textArea.bottom - size.cx;
                                break;
                         } /* direction: RIGHT */
                      break;
                case BS_CENTER:
                      switch(direction)
                         { /* direction: CENTER */
                          case DrawArrow::ARROW_E:
                          case DrawArrow::ARROW_W:
                                dc->SetTextAlign(TA_CENTER);
                                pt.x = textArea.left + (textArea.Width() / 2);
                                pt.y = textArea.top + (textArea.Height() - size.cy) / 2;
                                break;
                          case DrawArrow::ARROW_N:
                                dc->SetTextAlign(TA_LEFT);
                                pt.x = textArea.left + (textArea.Width() - size.cy) / 2;
                                pt.y = textArea.bottom - (textArea.Height() - size.cx) / 2;
                                break;
                          case DrawArrow::ARROW_S:
                                pt.x = textArea.right - (textArea.Width() - size.cy) / 2;
                                pt.y = textArea.top + (textArea.Height() - size.cx) / 2;
                                break;
                         } /* direction: CENTER */
                      break;
               } /* style */
            dc->TextOut(pt.x, pt.y, text);
           } /* has font */
       } /* has text */
    
    dc->RestoreDC(save);
   }

/****************************************************************************
*                         CArrowButton::SetDirection
* Inputs:
*       DrawArrow::Direction dir: Direction to set
* Result: void
*       
* Effect: 
*       Sets the direction
****************************************************************************/

void CArrowButton::SetDirection(DrawArrow::Direction dir)
    {
     if(direction == dir)
        return; // ignore if already set
     direction = dir;
     if(GetSafeHwnd() != NULL)
        Invalidate();
    } // CArrowButton::SetDirection

/****************************************************************************
*                         CArrowButton::SetLineColor
* Inputs:
*       COLORREF c: Color
* Result: void
*       
* Effect: 
*       Sets the line color (and creates the pen used for it)
****************************************************************************/

void CArrowButton::SetLineColor(COLORREF c)
    {
     if(LineColor == c)
        return;
     LineColor = c;
     if(GetSafeHwnd() != NULL)
        Invalidate();
    } // CArrowButton::SetLineColor

/****************************************************************************
*                         CArrowButton::GetLineColor
* Result: COLORREF
*       Current pen color
****************************************************************************/

COLORREF CArrowButton::GetLineColor()
    {
     return LineColor;
    } // CArrowButton::GetLineColor

/****************************************************************************
*                         CArrowButton::SetBodyColor
* Inputs:
*       COLORREF c
* Result: void
*       
* Effect: 
*       Changes the body brush
****************************************************************************/

void CArrowButton::SetBodyColor(COLORREF c)
    {
     if(BodyColor == c)
        return;
     BodyColor = c;
     if(GetSafeHwnd() != NULL)
        Invalidate();
    } // CArrowButton::SetBodyColor

/****************************************************************************
*                         CArrowButton::GetBodyColor
* Result: COLORREF
*       Current body color
****************************************************************************/

COLORREF CArrowButton::GetBodyColor()
    {
     return BodyColor;
    } // CArrowButton::GetBodyColor

/****************************************************************************
*                         CArrowButton::SetTextColor
* Inputs:
*       COLORREF c: Color
* Result: void
*       
* Effect: 
*       Changes the text color
****************************************************************************/

void CArrowButton::SetTextColor(COLORREF c)
    {
     if(TextColor == c)
        return;
     TextColor = c;
     if(GetSafeHwnd() != NULL)
        Invalidate();
    } // CArrowButton::SetTextColor

/****************************************************************************
*                         CArrowButton::GetTextColor
* Result: COLORREF
*       Text color
****************************************************************************/

COLORREF CArrowButton::GetTextColor()
    {
     return TextColor;
    } // CArrowButton::GetTextColor

/****************************************************************************
*                       CArrowButton::PreSubclassWindow
* Result: void
*       
* Effect: 
*       Forces an ASSERT failure if the control is not owner-draw
****************************************************************************/

void CArrowButton::PreSubclassWindow()
    {
     ASSERT( (GetStyle() & BS_OWNERDRAW) != 0); // You must make this owner-draw!

     CButton::PreSubclassWindow();
    }

/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  5-May-08 | REQ #041: Created
* 21-Oct-08 | REQ #065: Indicate kerning map is empty
*****************************************************************************/
// KerningMap.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "KerningMap.h"
#include "Kern.h"
#include "ToString.h"
#include "SaveDC.h"

#ifndef _countof
#define _countof(x) ( sizeof(x) / sizeof( (x)[0]))
#endif

// CKerningMap

/****************************************************************************
*                            UWM_SET_SCROLL_RANGE
* Inputs:
*       WPARAM: Scroll bar, SB_VERT or SB_HORZ
*       LPARAM: upper bound of range (lower bound is always 0)
* Result: LPRESULT
*       Logically void, 0, always
* Effect: 
*       Sets the scroll range
* Notes:
*       A message must be posted, because if the OnPaint handler causes
*       the scrollbar to disappear, the uxtheme module will crash with
*       an access fault
****************************************************************************/

static const UINT UWM_SET_SCROLL_RANGE = ::RegisterWindowMessage(_T("UWM_SET_SCROLL_RANGE") _T(""));


/****************************************************************************
*                                SortByFirst
* Inputs:
*       const void * p1:
*       const void * p2:
* Result: int
*       <0 p1 < p2
*       =0 p1 == -2
*       >0 p1 > p2
****************************************************************************/

static int SortByFirst(const void * p1, const void * p2)            // REQ #041
    {                                                               // REQ #041
     const KERNINGPAIR * k1 = (const KERNINGPAIR *)p1;              // REQ #041
     const KERNINGPAIR * k2 = (const KERNINGPAIR *)p2;              // REQ #041
     return (int)k1->wFirst - (int)k2->wFirst;                      // REQ #041
    } // SortByFirst                                                // REQ #041

/****************************************************************************
*                                SortBySecond
* Inputs:
*       const void * p1:
*       const void * p2:
* Result: int
*       <0 p1 < p2
*       =0 p1 == -2
*       >0 p1 > p2
****************************************************************************/

static int SortBySecond(const void * p1, const void * p2)           // REQ #041
    {                                                               // REQ #041
     const KERNINGPAIR * k1 = (const KERNINGPAIR *)p1;              // REQ #041
     const KERNINGPAIR * k2 = (const KERNINGPAIR *)p2;              // REQ #041
     return (int)k1->wSecond - (int)k2->wSecond;                    // REQ #041
    } // SortBySecond                                               // REQ #041


IMPLEMENT_DYNAMIC(CKerningMap, CWnd)                                // REQ #041


/****************************************************************************
*                          CKerningMap::CKerningMap
* Effect: 
*       Constructor
****************************************************************************/

CKerningMap::CKerningMap()                                          // REQ #041
   {                                                                // REQ #041
    hpage = 5;                                                      // REQ #041
    vpage = 5;                                                      // REQ #041
   }                                                                // REQ #041

CKerningMap::~CKerningMap()                                         // REQ #041
{                                                                   // REQ #041
}                                                                   // REQ #041


/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CKerningMap, CWnd)                                // REQ #041
    ON_REGISTERED_MESSAGE(UWM_SET_SCROLL_RANGE, OnSetScrollRange)   // REQ #041
    ON_WM_HSCROLL()                                                 // REQ #041
    ON_WM_VSCROLL()                                                 // REQ #041
    ON_WM_PAINT()                                                   // REQ #041
    ON_MESSAGE(WM_SETFONT, OnSetFont)                               // REQ #041
    ON_MESSAGE(WM_GETFONT, OnGetFont)                               // REQ #041
    ON_WM_ERASEBKGND()                                              // REQ #041
END_MESSAGE_MAP()                                                   // REQ #041

/****************************************************************************
*                        CKerningMap::OnSetScrollRange
* Inputs:
*       WPARAM: SB_HORZ or SB_VERT
*       LPARAM: range to set
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Sets the scroll range to be 0..LPARAM
****************************************************************************/

LRESULT CKerningMap::OnSetScrollRange(WPARAM wParam, LPARAM lParam) // REQ #041
    {                                                               // REQ #041
     SetScrollRange((int)wParam, 0, (int)lParam);                   // REQ #041
     return 0;                                                      // REQ #041
    } // CKerningMap::OnSetScrollRange                              // REQ #041

/****************************************************************************
*                             CKerningMap::Create
* Inputs:
*       const CRect & r:
*       UINT id:
*       CWnd * parent:
* Result: BOOL
*       TRUE if successful
*       FALSE if error
* Effect: 
*       Creates a kerning explorer window
****************************************************************************/

BOOL CKerningMap::Create(const CRect & r, UINT id, CWnd * parent)   // REQ #041
    {                                                               // REQ #041
     if(classname.IsEmpty())                                        // REQ #041
        { /* register the class */                                  // REQ #041
         classname = AfxRegisterWndClass(0); // class styles        // REQ #041
        } /* register the class */                                  // REQ #041
     BOOL b = CWnd::CreateEx(0, // extended styles                  // REQ #041
                             classname,  // class name              // REQ #041
                             NULL,  // window name                  // REQ #041
                             WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_CHILD, // styles// REQ #041
                             r,                                     // REQ #041
                             parent,                                // REQ #041
                             id);                                   // REQ #041
     if(!b)                                                         // REQ #041
        return FALSE;                                               // REQ #041
     // TODO: more code here                                        // REQ #041
     return TRUE;                                                   // REQ #041
    } // CKerningMap::Create                                        // REQ #041

/****************************************************************************
*                            CKerningMap::OnHScroll
* Inputs:
*       UINT nSBCode: Scroll code
*       UINT nPos: Current position
*       CScrollBar * pScrollBar: NULL for window scrollbar
* Result: void
*       
* Effect: 
*       Scrolls the window horizontally
****************************************************************************/

void CKerningMap::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)// REQ #041
    {                                                               // REQ #041
     int current = GetScrollPos(SB_HORZ);                           // REQ #041
     int oldpos = current;                                          // REQ #041
     int low;                                                       // REQ #041
     int high;                                                      // REQ #041
     GetScrollRange(SB_HORZ, &low, &high);                          // REQ #041
     switch(nSBCode)                                                // REQ #041
        { /* code */                                                // REQ #041
         case SB_LINERIGHT:                                         // REQ #041
            current++;                                              // REQ #041
            if(current >= high)                                     // REQ #041
               current = high - 1;                                  // REQ #041
            break;                                                  // REQ #041
         case SB_LINELEFT:                                          // REQ #041
            current--;                                              // REQ #041
            if(current < low)                                       // REQ #041
               current = low;                                       // REQ #041
            break;                                                  // REQ #041
         case SB_PAGERIGHT:                                         // REQ #041
            // TODO: compute page size                              // REQ #041
            current += hpage;                                       // REQ #041
            if(current >= high)                                     // REQ #041
               current = high - 1;                                  // REQ #041
            break;                                                  // REQ #041
         case SB_PAGELEFT:                                          // REQ #041
            // TODO: compute page size                              // REQ #041
            current -= hpage;                                       // REQ #041
            if(current < low)                                       // REQ #041
               current = low;                                       // REQ #041
            break;                                                  // REQ #041
         case SB_THUMBTRACK:                                        // REQ #041
            current = nPos;                                         // REQ #041
            break;                                                  // REQ #041
        } /* code */                                                // REQ #041
                                                                    // REQ #041
     SetScrollPos(SB_HORZ, current);                                // REQ #041
                                                                    // REQ #041
     // TODO: use ScrollWindow here for efficiency and flicker reduction // REQ #041
     if(oldpos != current)                                          // REQ #041
        { /* redraw */                                              // REQ #041
         Invalidate();                                              // REQ #041
         UpdateWindow();                                            // REQ #041
        } /* redraw */                                              // REQ #041
                                                                    // REQ #041
     CWnd::OnHScroll(nSBCode, nPos, pScrollBar);                    // REQ #041
    }                                                               // REQ #041

/****************************************************************************
*                            CKerningMap::OnVScroll
* Inputs:
*       ¶
* Result: void
*       
* Effect: 
*       ¶
****************************************************************************/

void CKerningMap::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)// REQ #041
    {                                                               // REQ #041
     int current = GetScrollPos(SB_VERT);                           // REQ #041
     int oldpos = current;                                          // REQ #041
     int low;                                                       // REQ #041
     int high;                                                      // REQ #041
     GetScrollRange(SB_VERT, &low, &high);                          // REQ #041
     switch(nSBCode)                                                // REQ #041
        { /* code */                                                // REQ #041
         case SB_LINEDOWN:                                          // REQ #041
            current++;                                              // REQ #041
            if(current >= high)                                     // REQ #041
               current = high - 1;                                  // REQ #041
            break;                                                  // REQ #041
         case SB_LINEUP:                                            // REQ #041
            current--;                                              // REQ #041
            if(current < low)                                       // REQ #041
               current = low;                                       // REQ #041
            break;                                                  // REQ #041
         case SB_PAGEDOWN:                                          // REQ #041
            // TODO: compute page size                              // REQ #041
            current += vpage;                                       // REQ #041
            if(current >= high)                                     // REQ #041
               current = high - 1;                                  // REQ #041
            break;                                                  // REQ #041
         case SB_PAGEUP:                                            // REQ #041
            // TODO: compute page size                              // REQ #041
            current -= vpage;                                       // REQ #041
            if(current < low)                                       // REQ #041
               current = low;                                       // REQ #041
            break;                                                  // REQ #041
         case SB_THUMBTRACK:                                        // REQ #041
            current = nPos;                                         // REQ #041
            break;                                                  // REQ #041
        } /* code */                                                // REQ #041
                                                                    // REQ #041
     SetScrollPos(SB_VERT, current);                                // REQ #041
                                                                    // REQ #041
     // TODO: use ScrollWindow here for efficiency and flicker reduction // REQ #041
     if(oldpos != current)                                          // REQ #041
        { /* force redraw */                                        // REQ #041
         Invalidate();                                              // REQ #041
         UpdateWindow();                                            // REQ #041
        } /* force redraw */                                        // REQ #041
                                                                    // REQ #041
    CWnd::OnVScroll(nSBCode, nPos, pScrollBar);                     // REQ #041
    }                                                               // REQ #041

/****************************************************************************
*                           CKerningMap::OnSetFont
* Inputs:
*       WPARAM: (WPARAM)(HFONT)
*       LPARAM: (LPARAM)(BOOL): TRUE to force redraw
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Saves the font; forces a redraw if LOWORD(lParam) is non-zero
****************************************************************************/

LRESULT CKerningMap::OnSetFont(WPARAM wParam, LPARAM lParam)        // REQ #041
    {                                                               // REQ #041
     font = (HFONT)wParam;                                          // REQ #041
     if(LOWORD(lParam))                                             // REQ #041
        { /* force redraw */                                        // REQ #041
         Invalidate();                                              // REQ #041
         UpdateWindow();                                            // REQ #041
        } /* force redraw */                                        // REQ #041
     return 0;                                                      // REQ #041
    } // CKerningMap::OnSetFont                                     // REQ #041

/****************************************************************************
*                           CKerningMap::OnGetFont
* Inputs:
*       WPARAM: ignored
*       LPARAM: ignored
* Result: LRESULT
*       (LRESULT)(HFONT)
****************************************************************************/

LRESULT CKerningMap::OnGetFont(WPARAM, LPARAM)                      // REQ #041
    {                                                               // REQ #041
     return (LRESULT)font;                                          // REQ #041
    } // CKerningMap::OnGetFont                                     // REQ #041

/****************************************************************************
*                     CKerningMap::GetMaxCharWidthInArray
* Inputs:
*       CDC & dc: DC
*       CArray<WORD> & ar: Text array
*       int & width: Current width
* Result: void
*       
* Effect: 
*       Updates the width to be wide enough to hold the character
*       Notes: Uses the abbreviation 'sp' or its localized version
*       when a space character is found
****************************************************************************/

void CKerningMap::GetMaxCharWidthInArray(CDC & dc, CArray<WORD> & ar, int & width)// REQ #041
    {                                                               // REQ #041
     for(int i = 0; i < ar.GetSize(); i++)                          // REQ #041
        { /* compute x-width */                                     // REQ #041
         int w;                                                     // REQ #041
         if(ar[i] == _T(' '))                                       // REQ #041
            { /* space */                                           // REQ #041
             CString sp;                                            // REQ #041
             sp.LoadString(IDS_SPACE_ABBREV);                       // REQ #041
             w = dc.GetTextExtent(sp).cx;                           // REQ #041
            } /* space */                                           // REQ #041
         else                                                       // REQ #041
            w = dc.GetTextExtent((LPCTSTR)&ar[i], 1).cx;            // REQ #041
                                                                    // REQ #041
         if(w > width)                                              // REQ #041
            width = w;                                              // REQ #041
        } /* compute x-width */                                     // REQ #041
                                                                    // REQ #041
    } // CKerningMap::GetMaxCharWidthInArray                        // REQ #041

/****************************************************************************
*                             CKerningMap::OnPaint
* Result: void
*       
* Effect:   
*       Draws the contents 
****************************************************************************/

void CKerningMap::OnPaint()                                         // REQ #041
    {                                                               // REQ #041
     CPaintDC dc(this); // device context for painting              // REQ #041
                                                                    // REQ #041
     CRect client;                                                  // REQ #041
                                                                    // REQ #041
     GetClientRect(&client);                                        // REQ #041
                                                                    // REQ #041
     bb.SetRectEmpty();                                             // REQ #041
     CFont * f = GetFont();                                         // REQ #041
     if(f == NULL)                                                  // REQ #041
        return; // No font                                          // REQ #041
                                                                    // REQ #041
     dc.SelectObject(f);                                            // REQ #041
     KERNINFO ki(&dc);                                              // REQ #041
     if(ki.count == 0)                                              // REQ #041
        { /* empty */                                               // REQ #065
         CString s;                                                 // REQ #065
         s.LoadString(IDS_NO_KERNING_PAIRS);                        // REQ #065
         dc.SelectStockObject(DEFAULT_GUI_FONT);                    // REQ #065
         dc.SetTextColor(RGB(0, 0, 255));                           // REQ #065
         dc.SetBkMode(TRANSPARENT);                                 // REQ #065
         dc.TextOut(0, 0, s);                                       // REQ #065
         CSize sz;                                                  // REQ #065
         sz = dc.GetTextExtent(s);                                  // REQ #065
         PostMessage(UWM_SET_SCROLL_RANGE, (WPARAM)SB_HORZ, 0);     // REQ #065
         PostMessage(UWM_SET_SCROLL_RANGE, (WPARAM)SB_VERT, 0);     // REQ #065
         return; // no kerning pairs                                // REQ #041
        } /* empty */                                               // REQ #065
                                                                    // REQ #041
     /************************************************************* // REQ #041
       |A|H|I|J|                                                    // REQ #041
      -+-+-+-+-+                                                    // REQ #041
      V|X| | |X|                                                    // REQ #041
      -+-+-+-+-+                                                    // REQ #041
      Z| |X| | |                                                    // REQ #041
      -+-+-+-+-+                                                    // REQ #041
                                                                    // REQ #041
     *************************************************************/ // REQ #041
                                                                    // REQ #041
                                                                    // REQ #041
     CString sp;                                                    // REQ #041
     sp.LoadString(IDS_SPACE_ABBREV);                               // REQ #041
                                                                    // REQ #041
     // WORD wFirst                                                 // REQ #041
     // WORD wSecond                                                // REQ #041
     // int iKernAmount                                             // REQ #041
                                                                    // REQ #041
     // There is no guarantee the kerning pairs are sorted          // REQ #041
     // in order in the font, so sort them to make subsequent       // REQ #041
     // computations easier                                         // REQ #041
                                                                    // REQ #041
     qsort(ki.pairs, ki.count, sizeof(KERNINGPAIR), SortByFirst);   // REQ #041
                                                                    // REQ #041
     // Scan to find the unique set of first-characters             // REQ #041
     // These will be drawn down the left side of the display       // REQ #041
     CArray<WORD> yaxis;                                            // REQ #041
     WORD lasty = _T('\0');                                         // REQ #041
                                                                    // REQ #041
     for(int i = 0; i < ki.count; i++)                              // REQ #041
        { /* build y-axis */                                        // REQ #041
         if(ki.pairs[i].wFirst != lasty)                            // REQ #041
            { /* add y-axis */                                      // REQ #041
             yaxis.Add(ki.pairs[i].wFirst);                         // REQ #041
             lasty = ki.pairs[i].wFirst;                            // REQ #041
            } /* add y-axis */                                      // REQ #041
        } /* build y-axis */                                        // REQ #041
                                                                    // REQ #041
#ifdef _DEBUG                                                       // REQ #041
     TRACE(_T(__FUNCTION__) _T(": Y:"));                            // REQ #041
     for(int i = 0; i < yaxis.GetSize(); i++)                       // REQ #041
        { /* trace output */                                        // REQ #041
         TRACE(_T("%02x'%c' "), (WORD)yaxis[i], (WORD)yaxis[i]);    // REQ #041
        } /* trace output */                                        // REQ #041
     TRACE(_T("\n"));                                               // REQ #041
#endif                                                              // REQ #041
                                                                    // REQ #041
     qsort(ki.pairs, ki.count, sizeof(KERNINGPAIR), SortBySecond);  // REQ #041
                                                                    // REQ #041
     CArray<WORD> xaxis;                                            // REQ #041
                                                                    // REQ #041
     WORD lastx = _T('\0');                                         // REQ #041
     for(int i = 0; i < ki.count; i++)                              // REQ #041
        { /* build x-axis */                                        // REQ #041
         if(ki.pairs[i].wSecond != lastx)                           // REQ #041
            { /* add x-axis */                                      // REQ #041
             xaxis.Add(ki.pairs[i].wSecond);                        // REQ #041
             lastx = ki.pairs[i].wSecond;                           // REQ #041
            } /* add x-axis */                                      // REQ #041
        } /* build x-axis */                                        // REQ #041
                                                                    // REQ #041
#ifdef _DEBUG                                                       // REQ #041
     TRACE(_T(__FUNCTION__) _T(": X:"));                            // REQ #041
     for(int i = 0; i < xaxis.GetSize(); i++)                       // REQ #041
        { /* trace output */                                        // REQ #041
         TRACE(_T("%02x'%c' "), (WORD)xaxis[i], (WORD)xaxis[i]);    // REQ #041
        } /* trace output */                                        // REQ #041
     TRACE(_T("\n"));                                               // REQ #041
#endif                                                              // REQ #041
                                                                    // REQ #041
     int height = 0;                                                // REQ #041
     int width = 0;                                                 // REQ #041
     int xpos = 0;                                                  // REQ #041
     int ypos = 0;                                                  // REQ #041
                                                                    // REQ #041
     int hspace = ::GetSystemMetrics(SM_CXBORDER) * 2;              // REQ #041
     int vspace = hspace; // TODO: maybe change this?               // REQ #041
     { /* output text */                                            // REQ #041
      CFont text;                                                   // REQ #041
      CPen widepen(PS_SOLID, 2, ::GetSysColor(COLOR_WINDOWTEXT));   // REQ #041
                                                                    // REQ #041
      CSaveDC tdc(&dc);                                             // REQ #041
      text.CreatePointFont(100, _T("Arial"), &dc);                  // REQ #041
      // Note that beyond this point we only need the               // REQ #041
      // text font, not the font we are investigating               // REQ #041
      dc.SelectObject(&text);                                       // REQ #041
                                                                    // REQ #041
      // Make sure we can hold the widest character                 // REQ #041
      GetMaxCharWidthInArray(dc, xaxis, width);                     // REQ #041
      GetMaxCharWidthInArray(dc, yaxis, width);                     // REQ #041
                                                                    // REQ #041
     //*********************************************************    // REQ #041
     // Although it is clear that this could be done with any       // REQ #041
     // sort and combined with any other loop, we really can        // REQ #041
     // only do this if the correct font is selected into the       // REQ #041
     // DC, so we do it here                                        // REQ #041
     // The point here is that with large fonts, we could get       // REQ #041
     // kerning dimensions with values like -162, which might       // REQ #041
     // be wider than any character, so we are going to modify      // REQ #041
     // the width parameter to make sure we can hold the            // REQ #041
     // longest width string without crowding or overlapping        // REQ #041
     // adjacent fields                                             // REQ #041
                                                                    // REQ #041
      int kwidth = 0;                                               // REQ #041
      for(int i = 0; i < ki.count; i++)                             // REQ #041
         { /* compute text width */                                 // REQ #041
          CString s = ToString(_T("%d"), ki.pairs[i].iKernAmount);  // REQ #041
          int w = dc.GetTextExtent(s).cx;                           // REQ #041
          if(w > kwidth)                                            // REQ #041
             kwidth = w;                                            // REQ #041
         } /* compute text width */                                 // REQ #041
                                                                    // REQ #041
      kwidth += 2 * hspace;                                         // REQ #041
      if(kwidth > width)                                            // REQ #041
         width = kwidth;                                            // REQ #041
      //********************************************************    // REQ #041
                                                                    // REQ #041
      dc.SetTextAlign(TA_CENTER);                                   // REQ #041
      dc.SetBkMode(TRANSPARENT);                                    // REQ #041
                                                                    // REQ #041
      width += 2 * hspace;                                          // REQ #041
                                                                    // REQ #041
      // round to next reasonable multiple                          // REQ #041
      if((width & 1) == 0)                                          // REQ #041
         width++;                                                   // REQ #041
                                                                    // REQ #041
      height = dc.GetTextExtent(_T("X"), 1).cy;                     // REQ #041
      height += vspace;                                             // REQ #041
      xpos = GetScrollPos(SB_HORZ);                                 // REQ #041
      ypos = GetScrollPos(SB_VERT);                                 // REQ #041
                                                                    // REQ #041
      static const COLORREF colors[] = {                            // REQ #041
         RGB(192, 255, 192),                                        // REQ #041
         RGB(128, 255, 128) };                                      // REQ #041
                                                                    // REQ #041
      //********************************************************    // REQ #041
      // Output the header row                                      // REQ #041
      //********************************************************    // REQ #041
         int y = 0;                                                 // REQ #041
         int right = 0;                                             // REQ #041
         for(int i = xpos; i < xaxis.GetSize(); i++)                // REQ #041
            { /* draw x-axis */                                     // REQ #041
             int x = (i - xpos + 1) * width;                        // REQ #041
             if(x > client.right)                                   // REQ #041
                { /* fell off right end */                          // REQ #041
                 hpage = i - xpos;                                  // REQ #041
                 // stop drawing                                    // REQ #041
                 break;                                             // REQ #041
                } /* fell off right end */                          // REQ #041
             dc.FillSolidRect(CRect(x, y, x + width, y + height), colors[(i / 3) % _countof(colors)]);// REQ #041
                                                                    // REQ #041
             { /* draw left rule */                                 // REQ #041
              CSaveDC save(&dc);                                    // REQ #041
              if(i == xpos)                                         // REQ #041
                 dc.SelectObject(&widepen);                         // REQ #041
              dc.MoveTo(x, y);                                      // REQ #041
              dc.LineTo(x, y + height);                             // REQ #041
             } /* draw left rule */                                 // REQ #041
                                                                    // REQ #041
             dc.MoveTo(x + width, y);                               // REQ #041
             dc.LineTo(x + width, y + height);                      // REQ #041
             right = x + width;                                     // REQ #041
             if(xaxis[i] == _T(' '))                                // REQ #041
                dc.TextOut(x + width / 2, y, sp);                   // REQ #041
             else                                                   // REQ #041
                dc.TextOut(x + width / 2, y, (LPCTSTR)&xaxis[i], 1); // REQ #041
            } /* draw x-axis */                                     // REQ #041
                                                                    // REQ #041
         bb.right = right;                                          // REQ #041
         { /* draw top rule */                                      // REQ #041
          CSaveDC tmp(&dc);                                         // REQ #041
          dc.SelectObject(&widepen);                                // REQ #041
          dc.MoveTo(0, y + height - 1);                             // REQ #041
          dc.LineTo(right, y + height - 1);                         // REQ #041
         } /* draw top rule */                                      // REQ #041
                                                                    // REQ #041
        //******************************************************    // REQ #041
        // End of top rule output                                   // REQ #041
        //******************************************************    // REQ #041

        //******************************************************    // REQ #041
        // Draw the vertical rule                                   // REQ #041
        //******************************************************    // REQ #041
         y += height;                                               // REQ #041
                                                                    // REQ #041
         for(int i = ypos; i < yaxis.GetSize(); i++)                // REQ #041
            { /* draw y-axis values */                              // REQ #041
             if(y > client.bottom)                                  // REQ #041
                { /* done */                                        // REQ #041
                 vpage = i - ypos;                                  // REQ #041
                 // Stop drawing                                    // REQ #041
                 break;                                             // REQ #041
                } /* done */                                        // REQ #041
             if(yaxis[i] == _T(' '))                                // REQ #041
                dc.TextOut( width / 2, y, sp);                      // REQ #041
             else                                                   // REQ #041
                dc.TextOut( width / 2, y, (LPCTSTR)&yaxis[i], 1);   // REQ #041
                                                                    // REQ #041
             if(i % 3 == 0)                                         // REQ #041
                { /* every third */                                 // REQ #041
                 dc.MoveTo(0, y);                                   // REQ #041
                 dc.LineTo(width, y);                               // REQ #041
                } /* every third */                                 // REQ #041
                                                                    // REQ #041
             for(int j = xpos; j < xaxis.GetSize(); j++)            // REQ #041
                { /* draw x items */                                // REQ #041
                 int x = (j - xpos + 1) * width;                    // REQ #041
                 LPKERNINGPAIR p = ki.findPair(yaxis[i], xaxis[j]); // REQ #041
                 if(p == NULL)                                      // REQ #041
                    { /* no kerning pair */                         // REQ #041
                     dc.FillSolidRect(CRect(x,y,x + width, y + height), colors[(j / 3) % _countof(colors)]);// REQ #041// REQ #041
                    } /* no kerning pair */                         // REQ #041
                 else                                               // REQ #041
                    { /* has kerning pair */                        // REQ #041
                     dc.FillSolidRect(CRect(x, y, x + width, y + height), RGB(255, 255, 128));// REQ #041
                     CString s = ToString(_T("%d"), p->iKernAmount); // REQ #041
                     dc.TextOut(x + width / 2, y, s);               // REQ #041
                    } /* has kerning pair */                        // REQ #041
                                                                    // REQ #041
                 { /* draw left rule */                             // REQ #041
                  CSaveDC save(&dc);                                // REQ #041
                  if(j == xpos)                                     // REQ #041
                     dc.SelectObject(&widepen);                     // REQ #041
                  dc.MoveTo(x, y);                                  // REQ #041
                  dc.LineTo(x, y + height);                         // REQ #041
                 } /* draw left rule */                             // REQ #041
                 dc.MoveTo(x + width, y);                           // REQ #041
                 dc.LineTo(x + width, y + height);                  // REQ #041
                 if(i % 3 == 0)                                     // REQ #041
                    { /* every third */                             // REQ #041
                     dc.MoveTo(x, y);                               // REQ #041
                     dc.LineTo(x + width, y);                       // REQ #041
                    } /* every third */                             // REQ #041
#ifdef _DEBUG                                                       // REQ #041
                 ::GdiFlush();                                      // REQ #041
#endif                                                              // REQ #041
                } /* draw x items */                                // REQ #041
             y += height;                                           // REQ #041
             bb.bottom = y;                                         // REQ #041
            } /* draw y-axis values */                              // REQ #041
     } /* output text */                                            // REQ #041
                                                                    // REQ #041
     //*********************************************************    // REQ #041
     // Now, decide if we need scroll bars, and if so, set          // REQ #041
     // their ranges                                                // REQ #041
     // TODO: limit scrolling to moving the endmost to              // REQ #041
     // just-visible                                                // REQ #041
     if(client.right < bb.right)                                    // REQ #041
        bb.right = client.right;                                    // REQ #041
     if(client.bottom < bb.bottom)                                  // REQ #041
        bb.bottom = client.bottom;                                  // REQ #041
     if(xpos == 0 && client.right > bb.right + xpos * width)        // REQ #041
        PostMessage(UWM_SET_SCROLL_RANGE, (WPARAM)SB_HORZ, 0);      // REQ #041
     else                                                           // REQ #041
        PostMessage(UWM_SET_SCROLL_RANGE, (WPARAM)SB_HORZ, (LPARAM)xaxis.GetSize());// REQ #041
                                                                    // REQ #041
     if(ypos == 0 && client.bottom > bb.bottom + ypos * height)     // REQ #041
        PostMessage(UWM_SET_SCROLL_RANGE, (WPARAM)SB_VERT, 0);      // REQ #041
     else                                                           // REQ #041
        PostMessage(UWM_SET_SCROLL_RANGE, (WPARAM)SB_VERT, (LPARAM)yaxis.GetSize());// REQ #041
     // What we want to do here is set the ranges directly,         // REQ #041
     // but if we do so and it causes the scroll bar to disappear   // REQ #041
     // the uxtheme module which handles themes will crash with     // REQ #041
     // an acess fault.  Therefore, we have to defer actually       // REQ #041
     // setting the range in the OnPaint handler                    // REQ #041
     //*************************************************************// REQ #041
                                                                    // REQ #041
     // Do not call CWnd::OnPaint() for painting messages           // REQ #041
    }                                                               // REQ #041

/****************************************************************************
*                          CKerningMap::SetFontInfo
* Inputs:
*       CFontDescriptor & desc:
* Result: void
*       
* Effect: 
*       Sets the font
****************************************************************************/

void CKerningMap::SetFontInfo(CFontDescriptor & desc)               // REQ #041
    {                                                               // REQ #041
     ASSERT(desc.font != NULL);                                     // REQ #041
     if(desc.font == NULL)                                          // REQ #041
        return;                                                     // REQ #041
                                                                    // REQ #041
     CFont f;                                                       // REQ #041
     f.CreateFontIndirect(&desc.lf);                                // REQ #041
                                                                    // REQ #041
     CFont * oldfont = GetFont();                                   // REQ #041
     if(oldfont != NULL)                                            // REQ #041
        oldfont->DeleteObject();                                    // REQ #041
     SetFont(&f);                                                   // REQ #041
     f.Detach();                                                    // REQ #041
    } // CKerningMap::SetFontInfo                                   // REQ #041


/****************************************************************************
*                          CKerningMap::OnEraseBkgnd
* Inputs:
*       CDC * pDC:
* Result: BOOL
*       
* Effect: 
*       Erases the backgroun
****************************************************************************/

BOOL CKerningMap::OnEraseBkgnd(CDC* pDC)                            // REQ #041
    {                                                               // REQ #041
     CRect r;                                                       // REQ #041
     GetClientRect(&r);                                             // REQ #041
     pDC->FillSolidRect(&r, ::GetSysColor(COLOR_3DFACE));           // REQ #041
     return TRUE;                                                   // REQ #041
    }                                                               // REQ #041

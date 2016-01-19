/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 23-Apr-08 | Created
* 23-Apr-08 | REQ #001: Allow negative track kerning values
* 23-Apr-08 | REQ #010: Made display_options a protected member
* 24-Apr-08 | REQ #011: Support multiple output modes
* 24-Apr-08 | REQ #008: Removed fontexplorer.h
* 25-Apr-08 | REQ #014: Fixed layout bug in text display (overcompensation for A)
* 25-Apr-08 | REQ #015: Added more information to font display
* 25-Apr-08 | REQ #016: Changed GetTextExtent calls that want one character
* 27-Apr-08 | REQ #017: Added support to show detected pair-kerning
* 27-Apr-08 | REQ #018: Allow SetWorldTransform to get scaling
* 27-Apr-08 | REQ #019: Font-logic tracing added
* 27-Apr-08 | REQ #020: Use dialog font for popup display
* 28-May-08 | REQ #021: Trace font deletion
* 29-Apr-08 | REQ #025: Use alternating bands of colors for ABC
* 29-Apr-08 | REQ #028: Better listbox height computation
* 29-Apr-08 | REQ #029: Allow minimum image width copy
* 30-Apr-08 | REQ #032: Support GDI debugging
*  2-May-08 | REQ #034: Removed MS-DOS support
*  4-May-08 | REQ #035: Support for GM_ADVANCED metrics
*  4-May-08 | REQ #037: Code cleanup
*  4-May-08 | REQ #037: Use flyover help to display ABC widths
*  4-May-08 | REQ #038: Added mouse-hover capability
*  4-May-08 | REQ #039: Use 3-tier ABC display instead of 2-tier ABC display
*  5-May-08 | REQ #040: Handle OnCancelMode properly (set pointer to NULL)
*  5-May-08 | REQ #041: Support bounding box
*  8-May-08 | REQ #042: Unicode support
* 15-Oct-08 | REQ #043: Replace CDC * with CDC & for cleaner code
* 21-Oct-08 | REQ #066: Use bitmap rendering for fonts
* 22-Oct-08 | REQ #071: Support font smoothing option
* 23-Oct-08 | REQ #072: Deal with track kerning in ABC width display
* 30-Oct-08 | REQ #077: Separate drawing and reference contexts for drawABCs
*  1-Nov-08 | REQ #080: FontDisp.h => FontDisplay.h
*  2-Nov-08 | REQ #081: Changed name from TEXTOUTEX to EXTTEXTOUT_
*****************************************************************************/
// FontDisp.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"                                               // REQ #008
#include "poplist.h"
#include "legendi.h"
#include "legend.h"
#include "dispopts.h"
#include "fontdesc.h"
#include "FontDisplay.h"                                            // REQ #080
#include "savedc.h"
#include "kern.h"
#include "ErrorString.h"                                            // REQ #011
#include "DCState.h"                                                // REQ #033
#include "TraceABC.h"                                               // REQ #032
#include "ToString.h"                                               // REQ #032
#include "Bitmap.h"                                                 // REQ #066

#ifdef _DEBUG                                                       // REQ #032
#define GDI_FLUSH() ::GdiFlush()                                    // REQ #032
#else                                                               // REQ #032
#define GDI_FLUSH()                                                 // REQ #032
#endif                                                              // REQ #032


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define fontCOLOR_INTERNAL_LEADING RGB(255, 255,   0)
#define fontCOLOR_EXTERNAL_LEADING RGB(  0, 255, 255)
#define penCOLOR_BASELINE          RGB(  0, 255,   0)
#define fontCOLOR_ASCENT           RGB(192, 255, 192)   // 010
#define fontCOLOR_DESCENT          RGB(255, 192, 192)   // 100
#define fontCOLOR_ABC1             RGB(192, 192, 255)   // 001    // light magenta
#define fontCOLOR_ABC2             RGB(255, 192, 255)   // 101    // light blue
#define fontCOLOR_ABC3             RGB(128, 128, 255)             // dark magenta  // REQ #025
#define fontCOLOR_ABC4             RGB(255, 128, 255)             // dark blue     // REQ #025
#define fontCOLOR_PAIRKERNABLE     RGB(255,   0,   0)               // REQ #017

#define penCOLOR_ABC               RGB(127, 127, 127)

static CBrush internalLeadingBrush(fontCOLOR_INTERNAL_LEADING);
static CPen   internalLeadingPen(PS_SOLID, 0, fontCOLOR_INTERNAL_LEADING);

static CBrush externalLeadingBrush(fontCOLOR_EXTERNAL_LEADING);
static CPen   externalLeadingPen(PS_SOLID, 0, fontCOLOR_EXTERNAL_LEADING);

static CBrush ascentBrush(fontCOLOR_ASCENT);
static CPen   ascentPen(PS_SOLID, 0, fontCOLOR_ASCENT);

static CBrush descentBrush(fontCOLOR_DESCENT);
static CPen   descentPen(PS_SOLID, 0, fontCOLOR_DESCENT);

static CPen   baselinePen(PS_SOLID, 0, penCOLOR_BASELINE);

static CBrush abc1Brush(fontCOLOR_ABC1);
static CPen   abc1Pen(PS_SOLID, 0, fontCOLOR_ABC1);
static CBrush abc2Brush(fontCOLOR_ABC2);
static CPen   abc2Pen(PS_SOLID, 0, fontCOLOR_ABC2);
static CBrush abc3Brush(fontCOLOR_ABC3);                            // REQ #025
static CPen   abc3Pen(PS_SOLID, 0, fontCOLOR_ABC3);                 // REQ #025
static CBrush abc4Brush(fontCOLOR_ABC4);                            // REQ #025
static CPen   abc4Pen(PS_SOLID, 0, fontCOLOR_ABC4);                 // REQ #025

static CPen   abcPen(PS_SOLID, 0, penCOLOR_ABC);

#define BLINE  1
#define BLINEc 0
#define ACLINE 2
#define ACLINEc 2
#define LINEOFFSET 3

//#define ABCextra 5
#define ABCextra ((3 * LINEOFFSET) - 1)                             // REQ #040

typedef struct {float sx; float sy; } scaling;
static LegendInfo Legend_internalLeading(&internalLeadingBrush, &internalLeadingPen, IDS_INTERNAL_LEADING);
static LegendInfo Legend_externalLeading(&externalLeadingBrush, &externalLeadingPen, IDS_EXTERNAL_LEADING);
static LegendInfo Legend_ascent(&ascentBrush, &ascentPen, IDS_ASCENT);
static LegendInfo Legend_descent(&descentBrush, &descentPen, IDS_DESCENT);
static LegendInfo Legend_ABC1(&abc1Brush, &abc1Pen, IDS_ABC1);
static LegendInfo Legend_ABC2(&abc2Brush, &abc2Pen, IDS_ABC2);
static LegendInfo Legend_ABC3(&abc3Brush, &abc3Pen, IDS_ABC3);      // REQ #025
static LegendInfo Legend_ABC4(&abc4Brush, &abc4Pen, IDS_ABC4);      // REQ #025

static LegendInfo * legend[] = {
        &Legend_internalLeading,
        &Legend_ascent,
        &Legend_descent,
        &Legend_externalLeading,
        &Legend_ABC1,
        &Legend_ABC2,
        &Legend_ABC3,                                               // REQ #025
        &Legend_ABC4,                                               // REQ #025
        NULL                   };

/****************************************************************************
*                           CFontDisplay::GetLegend
* Result: LegendInfo **
*       Pointer to legend table
****************************************************************************/

LegendInfo ** CFontDisplay::GetLegend()
    {
     return &legend[0];
    }

/****************************************************************************
*                         CFontDisplay::CFontDisplay
* Inputs:
*       BOOL dokerning: Establishes initial kerning value
* Effect: 
*       Constructor
****************************************************************************/

CFontDisplay::CFontDisplay(BOOL dokerning /* = FALSE */ )
   {
    opts.debug = FALSE;

    opts.hrule = TRUE;
    opts.vrule = TRUE;
    opts.chrule = TRUE;

    opts.colors = TRUE;
    opts.white = FALSE; // stock background

    opts.track = FALSE;  // no track kerning
    opts.trackval = 0;

    opts.kerning = dokerning;

   // opts.basal = FALSE;                                           // REQ #011
    opts.output = display_options::NONE;                            // REQ #011

    FlyOver = NULL;                                                 // REQ #038
    bb.SetRectEmpty();                                              // REQ #041
#ifdef _DEBUG
    pinfo = NULL;
#endif
    ImageWidth = 0;                                                 // REQ #029
   }

/****************************************************************************
*                         CFontDisplay::~CFontDisplay
* Effect: 
*       Frees up any pinfo storage
****************************************************************************/

CFontDisplay::~CFontDisplay()
   {
#ifdef _DEBUG
    if(pinfo != NULL)
       delete [] pinfo;
#endif
   }

/****************************************************************************
*                       CFontDisplay::PreSubclassWindow
* Result: void
*       
* Effect: 
*       Creates the FlyOver display
****************************************************************************/

void CFontDisplay::PreSubclassWindow()                              // REQ #038
    {                                                               // REQ #038
     CStatic::PreSubclassWindow();                                  // REQ #038
     FlyOver = new CInfoDisplay;                                    // REQ #038
     FlyOver->Create(0, 0, _T(""), this);                           // REQ #038
    } // CFontDisplay::PreSubclassWindow                            // REQ #038

/****************************************************************************
*                                 Message Map
****************************************************************************/

BEGIN_MESSAGE_MAP(CFontDisplay, CStatic)
        //{{AFX_MSG_MAP(CFontDisplay)
        ON_WM_MOUSEMOVE()                                           // REQ #038
        ON_WM_PAINT()
        ON_WM_ERASEBKGND()
        ON_WM_RBUTTONDOWN()
        ON_WM_RBUTTONUP()
        ON_WM_LBUTTONDOWN()
        ON_WM_NCHITTEST()
        ON_WM_LBUTTONUP()
        ON_WM_LBUTTONDBLCLK()
        ON_WM_CREATE()
        ON_WM_DESTROY()
        ON_WM_CANCELMODE()
        ON_WM_SIZE()
        //}}AFX_MSG_MAP
        ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)                     // REQ #038
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontDisplay message handlers

/****************************************************************************
*                                   CFontDisplay::getABC
* Inputs:
*       CDC & dc: Display context, must be in MM_TEXT mode
*       TCHAR ch: Character whose ABC value is to be obtained
*       ABC& abc: ABC structure
* Result: void
*       
* Effect: 
*       Loads up ABC values.  If the font is not a TrueType font, sets
*       A = 0, C = 0, B = text extent
* Notes:
*       If the mapping mode is other than MM_TEXT, the pseudo-kerning data
*       will be an incorrect reflection of what MM_TEXT mode would produce
****************************************************************************/

void CFontDisplay::getABC(CDC & dc, TCHAR ch, ABC& abc)
    {
     ASSERT(dc.GetMapMode() == MM_TEXT);                              // REQ #033
     if(!dc.GetCharABCWidths(ch, ch, &abc))
        { /* not TrueType */
         abc.abcA = 0;
         abc.abcC = 0;
         SIZE sz = dc.GetTextExtent(&ch, 1);
         abc.abcB = sz.cx;
        } /* not TrueType */
     TraceABC(_T(__FUNCTION__), __LINE__, ch, dc, abc);
    } // CFontDisplay::getABC

/****************************************************************************
*                               CFontDisplay::normalizeScaling
* Inputs:
*       float sx: Scaling factor, expressed as floating point number
* Result: iscale
*       .win is window extent
*       .view is viewport extent
* Notes: 
*       This computes the two integer values needed to set the viewport extent
*       and the window extent.  These integers are ideally in the ratio 
*       expressed by the floating point number, but may be off by one unit
*       because of the need to dumb-down to the 16-bit Win95 GDI.
****************************************************************************/

iscale CFontDisplay::normalizeScaling(float sx)
    {
     iscale sc;
     sc.win = 1000;
     sc.view = (int)(1000.0f * sx);
#if 0                                                               // REQ #034
     while(sc.view > 32767)
        { /* dumb down */
         sc.view /= 2;
         sc.win /= 2;
        } /* dumb down */
#endif                                                              // REQ #034
     return sc;
    }

/****************************************************************************
*                               computeScaling
* Inputs:
*       CRect r: Rectangle defining container window
*       SIZE sz: width of string including overhangs
* Result: scaling
*       Floating point values giving scaling for x and y
* Effect: 
*       ²
****************************************************************************/

scaling computeScaling(CRect r, SIZE sz)
    {
     scaling sc;
     sc.sx = (float)r.Width() / (float)sz.cx;
     sc.sy = (float)r.Height() / (float)sz.cy;
     return sc;
    }

/****************************************************************************
*                     CFontDisplay::getOverhangTextExtent
* Inputs:
*       CDC & dc: DC to use for values.  Should be untransformed and use
*                       MM_TEXT mapping mode
*       CString s: String to compute width of
* Result: SIZE
*       Size of string
* Effect: 
*       ²
****************************************************************************/

SIZE CFontDisplay::getOverhangTextExtent(CDC & dc, CString s)
    {
     SIZE sz;
     CSaveDC pdc(&dc);
     dc.SetMapMode(MM_TEXT);

     sz = dc.GetTextExtent(s);

     if(s.IsEmpty())                                                // REQ #037
        return sz;

     // If we have overhang on the far left or far right
     // factor the overhang into the values
     // Add the overhang only for TrueType fonts

     if(opts.debug)                                                 // REQ #032
        ShowDCState(_HERE(_T("")), dc);                             // REQ #032// REQ #033

     ABC abc;
     if(opts.output == display_options::IGNOREABC)                  // REQ #031
        { /* ignore ABC */                                          // REQ #031
         sz.cx = 0;
         for(int i = 0; i < s.GetLength(); i++)
            { /* count each */
             if(dc.GetCharABCWidths(s[i], s[i], &abc))
                sz.cx += abc.abcB;
             TraceABC(_T(__FUNCTION__), __LINE__, s[i], dc, abc);   // REQ #032
            } /* count each */
        } /* ignore ABC */                                          // REQ #031
     else                                                           // REQ #031
        { /* use ABC */                                             // REQ #031
         if(dc.GetCharABCWidths(s[0], s[0], &abc))
            { /* has ABC:first */                                   // REQ #032
             if(abc.abcA < 0)
                sz.cx += -abc.abcA;
             TraceABC(_T(__FUNCTION__), __LINE__, s[0], dc, abc);   // REQ #032
            } /* has ABC:first */                                   // REQ #032
         else
            { /* not TrueType */
             DWORD err = ::GetLastError();
             TRACE(_T(__FUNCTION__) _T(": GetCharABCWidths('%c') failed (%d: %s)\n"), s[0], err, ErrorString(err));
            } /* not TrueType */

         if(dc.GetCharABCWidths(s[s.GetLength()- 1], s[s.GetLength() - 1], &abc))
            { /* has ABC:last */                                    // REQ #032
             if(abc.abcC < 0)                                       // REQ #032
                sz.cx += -abc.abcC;                                 // REQ #032
             TraceABC(_T(__FUNCTION__), __LINE__, s[s.GetLength() - 1], dc, abc); // REQ #032
            } /* has ABC:last */                                    // REQ #032
         else
            { /* not TrueType */                                    // REQ #032
             // Error already reported                              // REQ #032
            } /* not TrueType */                                    // REQ #032
        } /* use ABC */                                             // REQ #031

      if(opts.track && !s.IsEmpty())                                // REQ #037
         sz.cx += opts.trackval * (s.GetLength() - 1);

      if(opts.debug)                                                // REQ #032
         TRACE(_T(__FUNCTION__) _T(": sz = [%d, %d]\n"), sz.cx, sz.cy);// REQ #032
      return sz;
    }

/****************************************************************************
*                          CFontDisplay::writeRulerV
* Inputs:
*       CDC & dc: Display context
*       int left: Left edge
*       int top: Starting position
*       int bottom: Ending position
* Result: void
*       
* Effect: 
*       Draws a vertical ruler
****************************************************************************/

#define RULE5  2
#define RULE10 3
#define RULE1  1

void CFontDisplay::writeRulerV(CDC & idc, int left, int top, int bottom)
    {
     CSaveDC dc(&idc);
     dc->SetROP2(R2_NOTXORPEN);
     for(int i = top; i <= bottom; i++)
        { /* write rule */
         int width;

         if(i % 10 == 0)
            width = RULE10;
         else
         if(i % 5 == 0)
            width = RULE5;
         else
            width = RULE1;

         dc->MoveTo(left, i);
         dc->LineTo(left + width, i);
        } /* write rule */
    }

/****************************************************************************
*                          CFontDisplay::writeRulerH
* Inputs:
*       CDC & dc: DC
*       int left: 
* Result: void
*       
* Effect: 
*       Draws a horizontal rule along the bottom edge
* Notes:
*       Need to supply a sign eventually so we can have a scale going up
*       or down.  
****************************************************************************/

void CFontDisplay::writeRulerH(CDC & idc, int pos, int left, int right)
    {
     CSaveDC dc(&idc);
     dc->SetROP2(opts.white ? R2_COPYPEN : R2_NOTXORPEN);
     for(int i = left; i <= right; i++)
        { /* write rule */
         int height;

         if(i % 10 == 0)
            height = RULE10;
         else
         if(i % 5 == 0)
            height = RULE5;
         else
            height = RULE1;

         dc->MoveTo(i, pos);
         dc->LineTo(i, pos - height);
        } /* write rule */
    }

/****************************************************************************
*                             CFontDisplay::DrawV
* Inputs:
*       CDC & dc: DC
*       int x: Horizontal position
*       int top: Top of line
*       int bottom: Bottom of line
* Result: void
*       
* Effect: 
*       Draws a fiducial line
****************************************************************************/

void CFontDisplay::drawV(CDC & dc, int x, int top, int bottom)
    {
     CSaveDC pdc(&dc);
     pdc->SelectObject(&abcPen);
     pdc->MoveTo(x, top);
     pdc->LineTo(x, bottom);
    }

/****************************************************************************
*                         CFontDisplay::drawDistance
* Inputs:
*       CDC & dc: DC
*       int from: Horizontal starting position
*       int to: Horizontal ending position
*       int ypos: Vertical position of line
*       LPCTSTR legend: Legend to display
*       int ylegend: Position to display legend
* Result: void
*       
* Effect: 
*       Draws a horizontal line with a legend above or below it, centered
*       over it.
* Notes:
*
****************************************************************************/

void CFontDisplay::drawDistance(CDC & dc, int from, int to, int ypos, LPCTSTR legend, int ylegend)
    {
     CSaveDC pdc(&dc);

     pdc->MoveTo(from, ypos);
     pdc->LineTo(to, ypos);
     

#if 0 // debug later
     SIZE sz;
     pdc->SelectObject(&legendFont);
     sz = pdc->GetTextExtent(legend, lstrlen(legend));

     pdc->TextOut(from + (to - from - sz.cx) / 2, ylegend, legend, 
                                                        lstrlen(legend) );
#endif

    }

/****************************************************************************
*                        CFontDisplay::GetDisplayCode
* Inputs:
*       TCHAR ch: Character code
* Result: int
*       Display code
*       A       f(A)    C       f(C)    result
*       <0      1       <0      1       4
*       <0      1       ==0     0       1
*       <0      1       >0      2       7
*       ==0     0       <0      1       3
*       ==0     0       ==0     0       0
*       ==0     0       >0      2       6
*       >0      2       <0      1       5
*       >0      2       ==0     0       2
*       >0      2       >0      2       8
****************************************************************************/

int CFontDisplay::GetDisplayCode(CDC & dc, TCHAR ch)
    {
     ABC abc;

     // Get the ABC dimensions; since we are simulating MM_TEXT, we must
     // set MM_TEXT mode temporarily so the results are consistent
     // with the vision of MM_TEXT mode
     // In other mapping modes, the ABC dimensions may be different
     {
      CSaveDC pdc(&dc);
      dc.SetMapMode(MM_TEXT);
      getABC(dc, ch, abc);
     }

     int drawcode = (f(abc.abcA) + 3 * f(abc.abcC));

     TRACE(_T(__FUNCTION__) _T(": '%c' f(%d) + 3 * f(%d) => %d + 3 * %d = %d\n"),// REQ #032
           ch,                                                      // REQ #032
           abc.abcA, abc.abcC,                                      // REQ #032
           f(abc.abcA), f(abc.abcC),                                // REQ #032
           drawcode);                                               // REQ #032
     
     return drawcode;
    }

/****************************************************************************
*                             CFontDisplay::SetBB
* Inputs:
*       CRect r: Rectangle in logical coordinates
* Result: void
*       
* Effect: 
*       Sets the Bounding Box in device coordinates
****************************************************************************/

void CFontDisplay::SetBB(CDC & dc, CRect r)                         // REQ #041
    {                                                               // REQ #041
     dc.LPtoDP(&r);                                                 // REQ #041
     if(r.bottom > bb.bottom)                                       // REQ #041
        bb.bottom = r.bottom;                                       // REQ #041
     if(r.right > bb.right)                                         // REQ #041
        bb.right = r.right;                                         // REQ #041
    } // CFontDisplay::SetBB                                        // REQ #041

/****************************************************************************
*                            CFontDisplay::drawABCs
* Inputs:
*       CDC & DrawDC: Display context in which boxes are drawn
*       CDC & CharDC: Display context from which character widths are determined
*       int pos: Character starting position
*       TCHAR ch: Character code
*       TCHAR next: Next character (for pair-kerning data), '\0' if no character // REQ #038
*       int parity: A value selecting the color, 0, 1, 2, 3
*       BOOL ignore: TRUE to ignore ABC width values, FALSE otherwise // REQ #031
* Result: void
*       
* Effect: 
*       Draws the ABC fiducials and annotations
* Notes:
*       We encode the cases in a simple-minded way; we use the
*       encodings 0, 1, 2 to indicate the relationship to 0, and
*       a dense polynomial encoding according to the formula
*               f(A) + 3 * f(c) 
*
*       f(x) is defined as
*               x == 0 then 0
*               x <  0 then 1
*               x >  0 then 2
*               
*
*          0                              1  <= fiducial
*          |               B              |
*          |------------------------------|  A == 0, C == 0     0     
*          |                              |  
*          |                              |
*
*          0     1                        2  <= fiducial
*          |     |            B           |
*          |------------------------------|  A < 0, C == 0      
*          |-----|                        |    1    3 * 0       1
*          |  A  |                        |
*
*          0     1                        2  <= fiducial
*          |     |            B           |
*          |     |------------------------|  A > 0, C == 0      
*          |-----|                        |    2    3 * 0       2
*          |  A  |                        |
*
*          0                        1     2  <= fiducial
*          |           B            |     |
*          |------------------------------|  A == 0, C < 0
*          |                        |-----|    0     3 * 1      3
*          |                        |  C  |
*
*          0     1                  2     3  <= fiducial
*          |     |        B         |     |
*          |------------------------------|  A < 0, C < 0       
*          |-----|                  |-----|    1    3 * 1       4
*          |  A  |                  |  C  |
*
*          0     1                  2     3  <= fiducial
*          |     |            B     |     |
*          |     |------------------------|  A > 0, C < 0       
*          |-----|                  |-----|    2    3 * 1       5
*          |  A  |                  |  C  |     
*
*
*          0                        1     2  <= fiducial
*          |           B            |     |
*          |------------------------|  C  |  A == 0, C > 0
*          |                        |-----|    0     3 * 2      6
*          |                        |     |
*
*          0     1                  2     3  <= fiducial
*          |     |                  |     |
*          |-----------B------------|     |  A < 0, C > 0       
*          |--A--|                  |--C--|    1    3 * 2       7
*          |     |                  |     |
*
*          0     1                  2     3  <= fiducial        
*          |     |        B         |     |
*          |     |------------------|     |  A > 0, C > 0       
*          |-----|                  |-----|    2    3 * 2       8
*          |  A  |                  |  C  |
*
*
*
****************************************************************************/

void CFontDisplay::drawABCs(CDC & DrawDC, CDC & CharDC, int pos, TCHAR ch, TCHAR next, int top, int bottom, int parity, const display_options & opts) // BOOL ignore) // REQ #031// REQ #038// REQ #072// REQ #077
    {
     if(opts.debug)                                                                           // REQ #032
        TRACE(_T(__FUNCTION__) _T(": ch '%c', pos %d top %d, bottom %d, parity %d, ...\n"),    // REQ #032
              ch, pos, top, bottom, parity);                        // REQ #032// REQ #072
     ABC abc;
     int code;
     int botf = bottom + LINEOFFSET; // +  (LINEOFFSET * (parity)) + LINEOFFSET; //ABCextra - 2;  // REQ #038
     
     // Revert to MM_TEXT so we get correct kerning information as if this were text
     {
      CSaveDC pdc(&CharDC);                                         // REQ #077
      CharDC.SetMapMode(MM_TEXT);                                   // REQ #077
      getABC(CharDC, ch, abc);                                      // REQ #077
      TRACE(_T(__FUNCTION__) _T(": abc = [%d, %d, %d]\n"), abc.abcA, abc.abcB, abc.abcC); // REQ #032
     }

     code = opts.output == display_options::IGNOREABC ? 0 : GetDisplayCode(CharDC, ch); // REQ #031// REQ #077

     // Draw the rectangles (in alternating colors) that highlight the ABC
     // rulers
     if(opts.colors)
         { /* show colors */
          CSaveDC pdc(&DrawDC);                                     // REQ #077

          
//          pdc->SelectObject((parity ? abc1Pen   : abc2Pen));      // REQ #025
//          pdc->SelectObject((parity ? abc1Brush : abc2Brush));    // REQ #025
          switch(parity)                                            // REQ #025
             { /* parity */                                         // REQ #025
              case 0:                                               // REQ #025
                 DrawDC.SelectObject(abc1Pen);                      // REQ #025// REQ #077
                 DrawDC.SelectObject(abc1Brush);                    // REQ #025// REQ #077
                 break;                                             // REQ #025
              case 1:                                               // REQ #025
                 DrawDC.SelectObject(abc2Pen);                      // REQ #025// REQ #077
                 DrawDC.SelectObject(abc2Brush);                    // REQ #025// REQ #077
                 break;                                             // REQ #025
              case 2:                                               // REQ #025
                 DrawDC.SelectObject(abc3Pen);                      // REQ #025// REQ #077
                 DrawDC.SelectObject(abc3Brush);                    // REQ #025// REQ #077
                 break;                                             // REQ #025
              case 3:                                               // REQ #025
                 DrawDC.SelectObject(abc4Pen);                      // REQ #025// REQ #077
                 DrawDC.SelectObject(abc4Brush);                    // REQ #025// REQ #077
                 break;                                             // REQ #025
             } /* parity */                                         // REQ #025

          CRect r;
          r.left = pos;
          r.top = bottom;
          if(opts.output != display_options::IGNOREABC)             // REQ #031// REQ #072
              r.right = r.left + abc.abcB + (abc.abcA < 0 ? 0 : abc.abcA) +
                                        (abc.abcC < 0 ? 0 : abc.abcC);
          else                                                      // REQ #031
              r.right = r.left + abc.abcB;                          // REQ #031

          r.bottom = r.top + LINEOFFSET;

          if(opts.debug)                                            // REQ #038
             TRACE(_T(__FUNCTION__) _T("(%d): r = [%d %d %d %d]\n"),// REQ #038
                   __LINE__, r.left, r.top, r.right, r.bottom);     // REQ #038
 
          CRect dr = r;                                             // REQ #038
          DrawDC.LPtoDP(&dr);                                       // REQ #038
          if(opts.debug)                                            // REQ #038
             TRACE(_T(__FUNCTION__) _T("(%d): dr = [%d %d %d %d]\n"),// REQ #038
                   __LINE__, dr.left, dr.top, dr.right, dr.bottom); // REQ #038

          int pairkern = 0;                                         // REQ #038
          if(next != _T('\0'))                                      // REQ #038
             { /* has next */                                       // REQ #038
              KERNINFO ki(&CharDC);                                 // REQ #038// REQ #077
              LPKERNINGPAIR pair = NULL;                            // REQ #038
              pair = ki.findPair(ch, next);                         // REQ #038
              if(pair != NULL)                                      // REQ #038
                 pairkern = pair->iKernAmount;                      // REQ #038
             } /* has next */                                       // REQ #038

          Hits.Add(CharInfo(dr, ch, abc, pairkern));                // REQ #038
#ifdef _DEBUG                                                       // REQ #038
          Hits[Hits.GetSize() - 1].drawcode = GetDisplayCode(CharDC, ch); // Horrible kludge for debugging // REQ #038// REQ #077
#endif                                                              // REQ #038
          DrawDC.Rectangle(&r);                                     // REQ #077
          SetBB(pdc, r);                                            // REQ #041
         } /* show colors */
     
     switch(code)
        { /* code */
         case 0:  // A == 0, C == 0
                 drawV(DrawDC, pos, top, botf);             // 0                  // REQ #077
                 drawV(DrawDC, pos + abc.abcB, top, botf);  // 1                  // REQ #077
                 drawDistance(DrawDC, pos, pos+abc.abcB, bottom + BLINE, _T("B"), // REQ #077
                                                bottom + BLINEc);
                 break;
         case 1: // A < 0, C == 0
                 drawV(DrawDC, pos, top, botf);             // 0                 // REQ #077
                 drawV(DrawDC, pos - abc.abcA, top, botf);  // 1                 // REQ #077
                 drawV(DrawDC, pos + abc.abcB, top, botf);  // 2                 // REQ #077
                 drawDistance(DrawDC, pos, pos+ abc.abcB, bottom +BLINE, _T("B"),// REQ #077
                                                bottom + BLINEc);
                 drawDistance(DrawDC, pos, pos - abc.abcA, bottom+ACLINE, _T("A"),// REQ #077
                                                bottom + ACLINEc);
                 break;
         case 2: // A > 0, C == 0
                 drawV(DrawDC, pos, top, botf);                             // 0 // REQ #077
                 drawV(DrawDC, pos + abc.abcA, top, botf);                  // 1 // REQ #077
                 drawV(DrawDC, pos + abc.abcA + abc.abcB, top, botf);       // 2 // REQ #077
                 drawDistance(DrawDC, pos + abc.abcA, pos + abc.abcA + abc.abcB, // REQ #077
                                        bottom + BLINE,
                                        _T("B"), bottom + BLINEc);
                 drawDistance(DrawDC, pos, pos + abc.abcA, bottom + ACLINE,      // REQ #077
                                                _T("A"),
                                                bottom + ACLINEc);
                 break;
         case 3: // A == 0, C < 0
                 drawV(DrawDC, pos, top, botf);                                  // REQ #077
                 drawV(DrawDC, pos + abc.abcB, top, botf);                       // REQ #077
                 drawV(DrawDC, pos + abc.abcB + abc.abcC, top, botf);            // REQ #077
                 drawDistance(DrawDC, pos, pos + abc.abcB, bottom + BLINE,       // REQ #077
                                        _T("B"), bottom);
                 drawDistance(DrawDC, pos + abc.abcB + abc.abcC,                 // REQ #077
                                  pos + abc.abcB,
                                  bottom + ACLINE,
                                  _T("C"), bottom + ACLINEc);
                 break;
         case 4: // A < 0, C < 0
                 drawV(DrawDC, pos, top, botf);                                  // REQ #077
                 drawV(DrawDC, pos - abc.abcA, top, botf);                       // REQ #077
                 drawV(DrawDC, pos + abc.abcB, top, botf);                       // REQ #077
                 drawV(DrawDC, pos + abc.abcB + abc.abcC, top, botf);            // REQ #077
                 drawDistance(DrawDC, pos, pos + abc.abcB,                       // REQ #077
                                  bottom + 1,
                                  _T("B"), bottom);
                 drawDistance(DrawDC, pos, pos - abc.abcA,                       // REQ #077
                                  bottom + 2,
                                  _T("A"), bottom + 2);
                 drawDistance(DrawDC, pos + abc.abcB + abc.abcC, pos + abc.abcB, // REQ #077
                                  bottom + 2,
                                  _T("C"), bottom + 2);
                 break;
         case 5: // A > 0, C < 0
                 drawV(DrawDC, pos, top, botf);                                  // REQ #077
                 drawV(DrawDC, pos + abc.abcA, top, botf);                       // REQ #077
                 drawV(DrawDC, pos + abc.abcA + abc.abcB, top, botf);            // REQ #077
                 drawV(DrawDC, pos + abc.abcA + abc.abcB + abc.abcC, top, botf); // REQ #077
                 drawDistance(DrawDC, pos + abc.abcA, pos + abc.abcA + abc.abcB, // REQ #077
                                   bottom + 1,
                                   _T("B"), bottom);
                 drawDistance(DrawDC, pos, pos + abc.abcA, bottom + 2,           // REQ #077
                                   _T("A"), bottom + 2);
                 drawDistance(DrawDC, pos + abc.abcA + abc.abcB + abc.abcC,      // REQ #077
                                  pos + abc.abcA + abc.abcB,
                                  bottom + 2,
                                  _T("C"), bottom + 2);
                 break;
         case 6: // A == 0, C > 0
                 drawV(DrawDC, pos, top, botf);                                  // REQ #077
                 drawV(DrawDC, pos + abc.abcB, top, botf);                       // REQ #077
                 drawV(DrawDC, pos + abc.abcB + abc.abcC, top, botf);            // REQ #077
                 drawDistance(DrawDC, pos, pos + abc.abcB, bottom + 1,           // REQ #077
                                        _T("B"), bottom);
                 drawDistance(DrawDC, pos + abc.abcB, pos + abc.abcB + abc.abcC, // REQ #077
                                        bottom + 2,
                                        _T("C"), bottom + 2);
                 break;
         case 7: // A < 0, C > 0
                 drawV(DrawDC, pos, top, botf);                                  // REQ #077
                 drawV(DrawDC, pos - abc.abcA, top, botf);                       // REQ #077
                 drawV(DrawDC, pos + abc.abcB, top, botf);                       // REQ #077
                 drawV(DrawDC, pos + abc.abcB + abc.abcC, top, botf);            // REQ #077
                 drawDistance(DrawDC, pos, pos + abc.abcB, bottom + 1,           // REQ #077
                                        _T("B"), bottom);
                 drawDistance(DrawDC, pos, pos - abc.abcA, bottom + 2,           // REQ #077
                                        _T("A"), bottom + 2);
                 drawDistance(DrawDC, pos + abc.abcB, pos + abc.abcB + abc.abcC, // REQ #077
                                        bottom + 2,
                                        _T("C"), bottom + 2);
                 break;
         case 8: // A > 0, C > 0
                 drawV(DrawDC, pos, top, botf);                                  // REQ #077
                 drawV(DrawDC, pos + abc.abcA, top, botf);                       // REQ #077
                 drawV(DrawDC, pos + abc.abcA + abc.abcB, top, botf);            // REQ #077
                 drawV(DrawDC, pos + abc.abcA + abc.abcB + abc.abcC, top, botf); // REQ #077
                 drawDistance(DrawDC, pos + abc.abcA, pos + abc.abcA + abc.abcB, // REQ #077
                                bottom + 1,
                                _T("B"), bottom);
                 drawDistance(DrawDC, pos, pos + abc.abcA, bottom + 2,           // REQ #077
                                _T("A"), bottom + 2);
                 drawDistance(DrawDC, pos + abc.abcA + abc.abcB,                 // REQ #077
                                  pos + abc.abcA + abc.abcB + abc.abcC,
                                  bottom + 2,
                                  _T("C"), bottom + 2);
                 break;
        } /* code */
    } // CFontDisplay::drawABCs

/****************************************************************************
*                        CFontDisplay::requiredHeight
* Inputs:
*       CFontDescriptor & desc
* Result: int
*       Required height for display, including rulers and the space around
*       them
****************************************************************************/

int CFontDisplay::requiredHeight(CFontDescriptor & desc)
    {
     return (desc.tm.tmHeight + desc.tm.tmExternalLeading) + (opts.chrule ? ABCextra : 0) + 1;
    } // CFontDisplay::requiredHeight

/****************************************************************************
*                         CFontDisplay::limitScaling
* Inputs:
*       TEXTMETRIC & tm: Allows us to determine if raster font
*       int scale: Current scaling factor
* Result: float
*       if raster font, min(scale, 5)
*       if TrueType font, scale
****************************************************************************/

float CFontDisplay::limitScaling(TEXTMETRIC & tm, float scale)
    {
     if( (tm.tmPitchAndFamily & (TMPF_VECTOR | TMPF_TRUETYPE)) == 0)
        return min(5.0f, scale);
     else
        return scale;
    } // CFontDisplay::limitScaling

/****************************************************************************
*                    CFontDisplay::ComputePairKerningColor
* Inputs:
*       CDC & dc: Display context to use                            // REQ #043
*       COLORREF color: Current color
*       const CString & s: String to use
*       int i: offset of current character
* Result: COLORREF
*       Sample          predicate                               result
*       "A"             s.GetLength() < 2                       color
*       "AV"            i + 1 < s.GetLength()
****************************************************************************/

COLORREF CFontDisplay::ComputePairKerningColor(CDC & dc, COLORREF color, const CString & s, int i)// REQ #017// REQ #043
    {                                                               // REQ #017
     if(opts.DetectPairKerning)                                     // REQ #017
        return color;                                               // REQ #017
                                                                    // REQ #017
     if(s.GetLength() < 2)                                          // REQ #017
        return color;                                               // REQ #017
     KERNINFO ki(&dc);                                              // REQ #017// REQ #043
     // Compute pair kerning info                                   // REQ #017
     LPKERNINGPAIR pair = NULL;                                     // REQ #017
     if(i > 0)                                                      // REQ #017
        { /* match to prev */                                       // REQ #017
         pair = ki.findPair((UINT)s[i - 1], (UINT)s[i]);            // REQ #017
         if(pair != NULL)                                           // REQ #017
            return fontCOLOR_PAIRKERNABLE;                          // REQ #017
        } /* match to prev */                                       // REQ #017
     if(i < s.GetLength() - 1)                                      // REQ #017
        { /* match to next */                                       // REQ #017
         pair = ki.findPair((UINT)s[i], (UINT)s[i + 1]);            // REQ #017
         if(pair != NULL)                                           // REQ #017
            return fontCOLOR_PAIRKERNABLE;                          // REQ #017
        } /* match to next */                                       // REQ #017
     return color;                                                  // REQ #017
    } // CFontDisplay::ComputePairKerningColor                      // REQ #017

/****************************************************************************
*                         CFontDisplay::DoExtTextOut
* Inputs:
*       const CFontDescriptor & desc
*       CDC & dc:
*       const CString & Text:
*       int baseoffset:
*       int & pos:
*       int i: Index into string
* Result: void
*       
* Effect: 
*       Does an ExtTextOut
****************************************************************************/

void CFontDisplay::DoExtTextOut(const CFontDescriptor & desc, CDC & dc, const CString & Text, int baseoffset, int & pos, int i)
    {
     // Note we do not need to conditionalize this on               // REQ #022
     // opts.advanced because this display mode is ONLY             // REQ #022
     // available in opts.advanced                                  // REQ #022
     float dy = desc.tm.tmHeight * ((float)opts.VerticalOffset / 100.0f); // REQ #022
     XFORM xlat={1, 0, 0, 1, 0, dy};                                // REQ #022
     ::ModifyWorldTransform(dc, &xlat, MWT_RIGHTMULTIPLY);          // REQ #022
     GCP_RESULTS results = { sizeof(GCP_RESULTS) };                 // REQ #011
     // lStructSize: set                                            // REQ #011
     // lpOutString: NULL (not needed)                              // REQ #011
     // lpOrder: NULL (not needed)                                  // REQ #011
     results.lpDx = new int[Text.GetLength()];                      // REQ #011
     // lpCaretPos: NULL (not needed)                               // REQ #011
     // lpClass: NULL (not needed)                                  // REQ #011
     results.lpGlyphs = new WCHAR[Text.GetLength()];                // REQ #011
     results.nGlyphs = Text.GetLength();                            // REQ #011
     // nMaxFit: 0 (not used)                                       // REQ #011
     DWORD flags = 0;                                               // REQ #011
     if(opts.kerning)                                               // REQ #011
        flags |= GCP_USEKERNING;                                    // REQ #011
     DWORD gcp = ::GetCharacterPlacement(dc,                        // REQ #011// REQ #066
                                         Text,                      // REQ #011
                                         Text.GetLength(),          // REQ #011
                                         0, // not used             // REQ #011
                                         &results,                  // REQ #011
                                         flags);                    // REQ #011
     if(gcp == 0)                                                   // REQ #011
        { /* failed */                                              // REQ #011
         TRACE(_T(__FUNCTION__) _T("GetCharacterPlacement failed: %Text\n"), ErrorString(::GetLastError()));// REQ #011
        } /* failed */                                              // REQ #011
     else                                                           // REQ #077
        { /* succeeded */                                           // REQ #077
#if 1                                                               // REQ #077
         TRACE(_T("    *** GetCharacerPlacement\n"));               // REQ #077
         LOGFONT lf;                                                // REQ #077
         CFont * f = dc.GetCurrentFont();                           // REQ #077
         if(f != NULL)                                              // REQ #077
            { /* show font */                                       // REQ #077
             f->GetLogFont(&lf);                                    // REQ #077
             TRACE(_T("        \"%s\" %d\n"), lf.lfFaceName, lf.lfHeight);// REQ #077
            } /* show font */                                       // REQ #077
         for(UINT i = 0; i < results.nGlyphs; i++)                  // REQ #077
            { /* show each */                                       // REQ #077
             TRACE(_T("        [%2d] '%c' lpDx %2d\n"), i, ((LPCTSTR)Text)[i], results.lpDx[i]);// REQ #077
            } /* show each */                                       // REQ #077
#endif                                                              // REQ #077
        } /* succeeded */                                           // REQ #077
     dc.ExtTextOut(baseoffset, 0,                                   // REQ #011
                      0,   // nOptions = 0                          // REQ #011
                      NULL,  // no limited rectangle                // REQ #011
                      Text,                                         // REQ #011
                      results.lpDx);                                // REQ #011
     GDI_FLUSH();                                                   // REQ #032
     pos += results.lpDx[i];                                        // REQ #011
     if(opts.track)           // Modify by track kerning            // REQ #072
        pos += opts.trackval;                                       // REQ #072
     delete [] results.lpDx;                                        // REQ #011
     delete [] results.lpGlyphs;                                    // REQ #011
    } // CFontDisplay::DoExtTextOut

/****************************************************************************
*                          CFontDisplay::DrawOutline
* Inputs:
*       CDC & dc:
*       CFontDescriptor & desc:
*       const display_options & otps
*       int x: Offset in pixels
*       const CString & Text:
*       int i: Index into string
* Result: void
*       
* Effect: 
*       Draws the outline
****************************************************************************/

void CFontDisplay::DrawOutline(CDC & dc, CFontDescriptor & desc, const display_options & opts, int x, const CString & Text, int i) // REQ #066
    {                                                               // REQ #066
     CSaveDC save(&dc);                                             // REQ #066
     dc.SetWindowOrg(-opts.OverlayX, opts.OverlayY);                // REQ #066
     dc.BeginPath();                                                // REQ #066
     if(opts.track)                                                 // REQ #066
        dc.SetTextCharacterExtra(opts.trackval);                    // REQ #066
                                                                    // REQ #066
     if(opts.output == display_options::NONE || opts.output == display_options::IGNOREABC)// REQ #066
        dc.TextOut(x, 0, Text, Text.GetLength());                   // REQ #066
     if(opts.output == display_options::TEXTOUT)                    // REQ #066
        dc.TextOut(x, 0, Text, Text.GetLength());                   // REQ #066
     if(opts.output == display_options::EXTTEXTOUT_)                 // REQ #066// REQ #081
        DoExtTextOut(desc, dc, Text, x, i, 0);                      // REQ #066
                                                                    // REQ #066
     dc.EndPath();                                                  // REQ #066
     dc.SelectStockObject(BLACK_BRUSH);                             // REQ #066
     if(!opts.ShowPixels)                                           // REQ #066
        dc.StrokeAndFillPath();                                     // REQ #066
     else                                                           // REQ #066
        { /* draw outline */                                        // REQ #066
         dc.SetROP2(R2_NOT);                                        // REQ #066
         dc.StrokePath();                                           // REQ #066
        } /* draw outline */                                        // REQ #066
    } // CFontDisplay::DrawOutline                                  // REQ #066

/****************************************************************************
*                            CFontDisplay::OnPaint
* Result: void
*       
* Effect: 
*       Handles the painting
****************************************************************************/

void CFontDisplay::OnPaint() 
   {
    class Overlay {                                                 // REQ #066
        public:                                                     // REQ #066
           Overlay() { point = CPoint(0,0); ch = _T('\0'); }        // REQ #066
           Overlay(CPoint pt, TCHAR c) { point = pt; ch = c; }      // REQ #066
        public:                                                     // REQ #066
           CPoint point;                                            // REQ #066
           TCHAR ch;                                                // REQ #066
    };                                                              // REQ #066
    CArray<Overlay> Overlays;                                       // REQ #066
    
    CPaintDC dc(this); // device context for painting
        
    CFontDescriptor desc(this, this->GetParent(), opts.advanced, opts.quality); // REQ #035// REQ #071

    CRect r;
    GetClientRect(&r);

    Hits.RemoveAll();                                               // REQ #038
    bb.SetRectEmpty();                                              // REQ #041

    ImageWidth = 0;                                                 // REQ #029
    TRACE(_T("================") _T(__FUNCTION__) _T("================\n"));
#ifdef _DEBUG
    if(pinfo != NULL)
       { /* release info structure */
        delete [] pinfo;
        pinfo = NULL;
       } /* release info structure */
#endif
    // We have to set the clipping region because static controls
    // inherit the CS_PARENTDC style, which we don't want.  This
    // style sets the clipping region to be the region of the parent,
    // which seems intrinsically nonsensical, but that's how it is.
    // It does NOT, as the documentation states, share a DC with the
    // parent.  This is incorrect, and the error is pointed out in the
    // KB article Q111005.

    CRgn clip;
    clip.CreateRectRgnIndirect(&r);
    dc.SelectObject(clip);
 
    CString Text;
    GetWindowText(Text);

    // Note that the graphics mode must be set early                // REQ #018
    // Otherwise all font computations are erroneous because        // REQ #018
    // GM_COMPATIBLE and GM_ADVANCED return different ABC widths    // REQ #018
    // even when everything else is the same                        // REQ #018
                                                                    // REQ #018
    if(opts.advanced)                                               // REQ #018
       ::SetGraphicsMode(dc, GM_ADVANCED);                          // REQ #018
    else                                                            // REQ #018
       ::SetGraphicsMode(dc, GM_COMPATIBLE);                        // REQ #018

#ifdef _DEBUG
    if(!Text.IsEmpty())                                             // REQ #037
       pinfo = new PosInfo[Text.GetLength()];
#endif

#ifdef _DEBUG                                                       // REQ #077
    {                                                               // REQ #077
     LOGFONT lf = {0};                                              // REQ #077
     if(desc.font != NULL)                                          // REQ #077
        desc.font->GetLogFont(&lf);                                 // REQ #077
     TRACE(_T(__FUNCTION__) _T("(%d): lfHeight = %d lfFaceName = %s"), __LINE__,// REQ #077
           lf.lfHeight, lf.lfFaceName);                             // REQ #077
    }                                                               // REQ #077
#endif                                                              // REQ #077

    dc.SelectObject(desc.font);
    
    SIZE stringwidth = getOverhangTextExtent(dc, Text);

    stringwidth.cx += 1; // fudge factor to keep edge on screen

    if(opts.debug)
       TRACE(_T(__FUNCTION__) _T(": stringwidth = [%d, %d]\n"), stringwidth.cx, stringwidth.cy);
    // Compute ratios of horizontal and vertical, and scale the the
    // smaller one


    scaling sc;

    stringwidth.cy = requiredHeight(desc);
    sc = computeScaling(r, stringwidth);

    dc.SetBkMode(TRANSPARENT);                                      // REQ #018
                                                                    // REQ #018
    if(!opts.advanced)                                              // REQ #018
       { /* GM_COMPATIBLE */                                        // REQ #018
        // We need to convert the scaling factor from floating point to
        // integer for the SetWindowExtEx and SetViewPortExtEx calls.
        // We want the smallest scaling so that we don't exceed either the
        // width or the height

        float sx = min(sc.sx, sc.sy);

        // Note that a raster font can be scaled at most 5X horizontally and
        // 8X vertically, so if the font is a raster font we limit it
        // to 5X

        sx = limitScaling(desc.tm, sx);

        iscale scale = normalizeScaling(sx);

        dc.SetMapMode(MM_ISOTROPIC);

        // Note: MUST set WindowExt before ViewportExt
        // Scaling factor is ViewportExtent / WindowExtent
        dc.SetWindowExt(scale.win, scale.win);
        dc.SetViewportExt(scale.view, scale.view);
        if(opts.debug)                                                                                     // REQ #032
           { /* debug */                                                                                   // REQ #032
            TRACE(_T(__FUNCTION__) _T(": SetWindowExt(%d, %d)\n"), scale.win, scale.win);                  // REQ #032
            TRACE(_T(__FUNCTION__) _T(": SetViewportExt(%d, %d)\n"), scale.view, scale.view);              // REQ #032
            TRACE(_T(__FUNCTION__) _T(": ratio window/view %g\n"),  (double)scale.view / (double)scale.win);// REQ #032
           } /* debug */                                                                                   // REQ #032
                 
       } /* GM_COMPATIBLE */                                        // REQ #018
    else                                                            // REQ #018
       { /* GM_ADVANCED */                                          // REQ #018
        float sx = min(sc.sx, sc.sy);                               // REQ #018
        XFORM M={sx, 0.0f, 0.0f, sx, 0.0f, 0.0f};                   // REQ #018
        ::SetWorldTransform(dc, &M);                                // REQ #018
       } /* GM_ADVANCED */                                          // REQ #018

    int top = 0;
    int bottom = desc.tm.tmHeight + desc.tm.tmExternalLeading;
    int right = stringwidth.cx;

    //if(opts.track && !Text.IsEmpty())                             // REQ #001// REQ #037
    //   right += opts.trackval * (Text.GetLength() - 1);           // REQ #001

    CSaveDC pdc(&dc);

    if(opts.colors)
        { /* show colors */
         /*
            +------------------------------------------+
            |     internal leading                     |
            +------------------------------------------+
            |   *****                                  |
            |  *** ***                                 |
            | ***   ***                                |
            |***     ***  ** ****                      | ascent
            |***********  ********                     |
            |***********  ***   ***                    |
            |***     ***  ***    ***                   |
            |***     ***  ***   ***                    |
            |***     ***  ********                     |
            +------------------------------------------+ baseline
            |             ***                          |
            |             ***                          | descent
            |            ****                          |
            +------------------------------------------+
            |    external leading                      |
            +------------------------------------------+
            |-----------| 
            |-|       |-| 
                         | |-----| |
                         |-|     |-|
         */

         // Draw the Internal Leading dimension
         pdc->SelectObject(&internalLeadingBrush);
         pdc->SelectObject(&internalLeadingPen);
         pdc->Rectangle(0, top, right, top+desc.tm.tmInternalLeading);


         pdc->SelectObject(&ascentBrush);
         pdc->SelectObject(&ascentPen);
         pdc->Rectangle(0, top + desc.tm.tmInternalLeading,
                                right, 
                                top + desc.tm.tmHeight - desc.tm.tmDescent);

         pdc->SelectObject(&descentBrush);
         pdc->SelectObject(&descentPen);
         pdc->Rectangle(0, top + desc.tm.tmHeight - desc.tm.tmDescent,
                           right,
                           top + desc.tm.tmHeight);

         pdc->SelectObject(&externalLeadingBrush);
         pdc->SelectObject(&externalLeadingPen);
         pdc->Rectangle(0, top + desc.tm.tmHeight, right, 
                        top+desc.tm.tmHeight + desc.tm.tmExternalLeading);

        } /* show colors */

    KERNINFO ki(&dc);

    int pos = 0;
    int lead = 0;
    int baseoffset = 0;

    //****************************************************************
    // If the first character would have a negative A-offset, we
    // shift everything to the right by the amount of the A-offset so
    // we don't lose the character off the left edge
    //
    // This offset is referred to as the "base offset"
    //****************************************************************
    if(!Text.IsEmpty())                                             // REQ #037
       { /* compute base offset */
        CSaveDC pdc(&dc);
        pdc->SetMapMode(MM_TEXT);
        if(opts.debug)                                              // REQ #032
           { /* show trace */                                       // REQ #032
            TRACE(_HERE(_T("")));                                   // REQ #033
            ShowDCState(_T(""), dc);                                // REQ #032
           } /* show trace */                                       // REQ #032
#if 0        
        if(pdc->GetCharABCWidths(Text[0], Text[0], &abc))
           { /* TrueType */
            TraceABC(_T(__FUNCTION__), __LINE__, Text[0], dc, abc); // REQ #032

            if(abc.abcA < 0)
               baseoffset = -abc.abcA;
           } /* TrueType */
#endif
       } /* compute lead */

    //************************************************************* // REQ #066
    // Lay the text out as a bitmap                                 // REQ #066
    //************************************************************* // REQ #066
    { /* bitmap layout */                                           // REQ #066
     CDC memDC;                                                     // REQ #066
     memDC.CreateCompatibleDC(&dc);                                 // REQ #066
     CSaveDC memsave(&memDC);                                       // REQ #066
                                                                    // REQ #066
     if(opts.advanced)                                              // REQ #066
        { /* use GM_ADVANCED */                                     // REQ #066
         ::SetGraphicsMode(memDC, GM_ADVANCED);                     // REQ #066
        } /* use GM_ADVANCED */                                     // REQ #066
     else                                                           // REQ #066
        { /* use GM_COMPATIBLE */                                   // REQ #066
         ::SetGraphicsMode(memDC, GM_COMPATIBLE);                   // REQ #066
        } /* use GM_COMPATIBLE */                                   // REQ #066
                                                                    // REQ #066
     if(opts.track)                                                 // REQ #066
        memDC.SetTextCharacterExtra(opts.trackval);                 // REQ #066
                                                                    // REQ #066
     memDC.SelectObject(desc.font);                                 // REQ #066
                                                                    // REQ #066
     CSize sz = memDC.GetTextExtent(Text);                          // REQ #066
     sz.cx += 2; // fudge factor                                    // REQ #066
     // Create a bitmap which may be right, then adjust if          // REQ #066
     // necessary                                                   // REQ #066
     HBITMAP h = CreateBmp(dc, sz, TRUE);                           // REQ #066
     CBitmap bmp;                                                   // REQ #066
     bmp.Attach(h);                                                 // REQ #066
     memDC.SetBkMode(TRANSPARENT);                                  // REQ #066
                                                                    // REQ #066
     CSize newsz = sz;                                              // REQ #066
     if(opts.output == display_options::IGNOREABC)                  // REQ #066
        { /* add width back in */                                   // REQ #066
         CSaveDC tdc(&memDC);                                       // REQ #066
         memDC.SelectObject(&bmp);                                  // REQ #066
         memDC.SetMapMode(MM_TEXT);                                 // REQ #066
         for(int i = 0; i < Text.GetLength(); i++)                  // REQ #066
            { /* add extra */                                       // REQ #066
             ABC abc;                                               // REQ #066
             memDC.GetCharABCWidths(Text[i], Text[i], &abc);        // REQ #066
             TraceABC(_T(__FUNCTION__), __LINE__, Text[i], dc, abc); // REQ #066
             if(abc.abcA < 0)                                       // REQ #066
                newsz.cx -= abc.abcA;                               // REQ #066
             if(abc.abcC < 0)                                       // REQ #066
                newsz.cx -= abc.abcC;                               // REQ #066
            } /* add extra */                                       // REQ #066
        } /* add width back in */                                   // REQ #066
                                                                    // REQ #066
     if(newsz != sz)                                                // REQ #066
        { /* make larger */                                         // REQ #066
         bmp.DeleteObject();                                        // REQ #066
         sz = newsz;                                                // REQ #066
         HBITMAP h = CreateBmp(dc, sz, TRUE);                       // REQ #066
         bmp.Attach(h);                                             // REQ #066
        } /* make larger */                                         // REQ #066
                                                                    // REQ #066
     memDC.SelectObject(&bmp);                                      // REQ #066
     TRACE(_T("Bitmap: size [%d, %d]\n"), sz.cx, sz.cy);            // REQ #066
     //h = CreateBmp(dc, sz, TRUE);                                 // REQ #066
                                                                    // REQ #066
     CRect r(0, 0, sz.cx, sz.cy);                                   // REQ #066
     memDC.FillSolidRect(&r, RGB(255, 255, 255));                   // REQ #066

     ABC abc;                                                       // REQ #066
     if(memDC.GetCharABCWidths(Text[0], Text[0], &abc))             // REQ #066
        { /* TrueType */                                            // REQ #066
         TraceABC(_T(__FUNCTION__), __LINE__, Text[0], dc, abc);    // REQ #032

         if(abc.abcA < 0)                                           // REQ #066
            baseoffset = -abc.abcA;                                 // REQ #066
        } /* TrueType */                                            // REQ #066

     for(int i = 0; i < Text.GetLength(); i++)
        { /* draw ABCs */
         CSaveDC pdc(&dc);                                          // REQ #035
         ABC abc;
         int offset = 0;

         { 
          CSaveDC mem(&memDC);                                      // REQ #066
          memDC.SetMapMode(MM_TEXT);                                // REQ #066
          if(!memDC.GetCharABCWidths(Text[i], Text[i], &abc))       // REQ #066
             { /* failed for TrueType */
              //----------------------------------------------------------------
              // If it fails, for whatever reason, we treat it as
              // A=0, B=GetTextExtent, C=0
              //----------------------------------------------------------------
              TraceABC(_T(__FUNCTION__), __LINE__, Text[i], dc, abc); // REQ #066
              abc.abcA = abc.abcC = 0;

              LPCTSTR p = Text.GetBuffer();                         // REQ #016
              CSize sz = memDC.GetTextExtent(&p[i], 1);             // REQ #016// REQ #066
              Text.ReleaseBuffer();                                 // REQ #016

              abc.abcB = sz.cx;
             } /* failed for TrueType */
          else                                                       // REQ #032
             { /* valid for font */                                  // REQ #032
              TraceABC(_T(__FUNCTION__), __LINE__, Text[i], dc, abc);// REQ #032
             } /* valid for font */                                  // REQ #032

          // If the A-offset is negative, we compute the 
          // "layout offset" as the A-offset
          if(opts.output != display_options::IGNOREABC && abc.abcA < 0) // REQ #014
             offset = abc.abcA;                                         // REQ #014
         }

         TCHAR next = _T('\0');                                     // REQ #038
         if(i < Text.GetLength() - 1)                               // REQ #038
            next = Text[i + 1];                                     // REQ #038
        
         if(opts.chrule)
            drawABCs(dc,                               // CDC &
                     memDC,
                     pos + baseoffset + offset,        // pos
                     Text[i],                          // TCHAR
                     next,                             // next      // REQ #038
                     top,                              // top
                     bottom + (i % 3) * LINEOFFSET,    // bottom    // REQ #039
                     i % 3,                            // parity    // REQ #039
                     opts);                                         // REQ #072

//                     opts.output == display_options::IGNOREABC); // ignore   // 

         //*****************************************************************************
         // Hand-Layout
         //*****************************************************************************
         if(opts.output == display_options::NONE || opts.output == display_options::IGNOREABC) // REQ #011// REQ #031
            { /* hand-layout */
             CSaveDC memsave(&memDC);                               // REQ #066
             if(opts.advanced)
                { /* use xform to shift */                          // REQ #022
                 float dy = desc.tm.tmHeight * ((float)opts.VerticalOffset / 100.0f); // REQ #022
                 XFORM xlat={1, 0, 0, 1, 0, dy};                    // REQ #022
                 ::ModifyWorldTransform(memDC, &xlat, MWT_RIGHTMULTIPLY); // REQ #022// REQ #066
                } /* use xform to shift */                          // REQ #022

             // If this character has a pair-kerning with the next  // REQ #017
             // or previous character, we will want to change       // REQ #017
             // color to depend on the pair-kerning                 // REQ #017
             // color = ComputePairKerningColor(&dc, color, Text, i);// REQ #017

             memDC.SetTextColor(color);                             // REQ #066

             int target = baseoffset + pos;                         // REQ #031
             if(opts.output == display_options::IGNOREABC)          // REQ #031
                target -= abc.abcA;                                 // REQ #031

//            int outpos = pos + baseoffset + offset;               // REQ #014
             
             LPCTSTR p = Text.GetBuffer();                          // REQ #016

//            dc.TextOut(target, 0, &p[i], 1);                        // REQ #016// REQ #031
             memDC.TextOut(target, 0, &p[i], 1);                    // REQ #066

             Text.ReleaseBuffer();                                  // REQ #016
#ifdef _DEBUG
             pinfo[i].ch = Text[i];
             pinfo[i].pos = target;                                 // REQ #031
#endif          

             if(opts.output != display_options::IGNOREABC && opts.kerning && ki.count > 0) // REQ #031
                { /* modify by pair kerning */
                 if(i < Text.GetLength() - 1) // no pair at end of string
                    { /* still in range */
                     LPKERNINGPAIR pair;
                     pair = ki.findPair((UINT)Text[i], (UINT)Text[i+1]);
                     if(pair != NULL)
                        { /* kerned */
                         pos += pair->iKernAmount;
                        } /* kerned */
                    } /* still in range */
                } /* modify by pair kerning */

             if(opts.ShowOverlay)                                   // REQ #066
                Overlays.Add(Overlay(target, Text[i]));             // REQ #066
//                DrawOutline(dc, desc, opts, pos, CString(Text[i]), i); // REQ #066

             if(opts.track)           // Modify by track kerning
                pos += opts.trackval;

             if(opts.output == display_options::IGNOREABC)          // REQ #031
                pos += /* -abc.abcA + */ abc.abcB;                  // REQ #031
             else                                                   // REQ #031
                pos += abc.abcA + abc.abcB + abc.abcC ;
            } /* hand-layout */

         //*****************************************************************************
         // TextOut
         //*****************************************************************************

         if(opts.output == display_options::TEXTOUT)                // REQ #011
            { /* use base textout */
             CSaveDC memsave(&memDC);                               // REQ #066

             if(opts.advanced)                                      // REQ #022
                { /* adjust height */                               // REQ #022
                 float dy = desc.tm.tmHeight * ((float)opts.VerticalOffset / 100.0f); // REQ #022
                 XFORM xlat={1, 0, 0, 1, 0, dy};                    // REQ #022
                 ::ModifyWorldTransform(memDC, &xlat, MWT_RIGHTMULTIPLY); // REQ #022// REQ #066
                } /* adjust height */                               // REQ #022

             if(opts.track)
                memDC.SetTextCharacterExtra(opts.trackval);         // REQ #066
             memDC.SetTextColor(color);                             // REQ #066
#ifdef _DEBUG
             int p = baseoffset;

             for(int i = 0; i < Text.GetLength(); i++)
                { /* record data */
                 pinfo[i].ch = Text[i];
                 pinfo[i].pos = p;
                 SIZE sz = memDC.GetTextExtent(&pinfo[i].ch, 1);    // REQ #066
                 p += sz.cx;
                } /* record data */
#endif
             memDC.TextOut(0, 0, Text, Text.GetLength());           // REQ #066
             GDI_FLUSH();                                           // REQ #032
             
             if(opts.track) // Modify by track kerning
                pos += opts.trackval;
             pos += abc.abcA + abc.abcB + abc.abcC ;
           } /* use base textout */

         //*****************************************************************************
         // ExtTextOut
         //*****************************************************************************
         if(opts.output == display_options::EXTTEXTOUT_)            // REQ #011// REQ #081
            { /* use ExtTextOut */                                  // REQ #011
             CSaveDC memsze(&memDC);                                // REQ #066
             if(opts.track)                                         // REQ #066
                memDC.SetTextCharacterExtra(opts.trackval);         // REQ #066
             DoExtTextOut(desc, memDC, Text, baseoffset, pos, i);   // REQ #066
            } /* use ExtTextOut */                                  // REQ #011
        } /* draw ABCs */
                                                                    // REQ #066
     // Note that GdiFlush is mandatory to make sure all the        // REQ #066
     // bitmap operations have actually been written to the         // REQ #066
     // bitmap                                                      // REQ #066
     GdiFlush(); // sync memory buffer                              // REQ #066
                                                                    // REQ #066
     if(opts.ShowPixels)                                            // REQ #066
        dc.BitBlt(0, 0, sz.cx, sz.cy, &memDC, 0, 0, SRCAND);        // REQ #066
                                                                    // REQ #066
     if(opts.ShowOverlay)                                           // REQ #066
        { /* textout path */                                        // REQ #066
         switch(opts.output)                                        // REQ #066
            { /* draw final */                                      // REQ #066
             case display_options::NONE:                            // REQ #066
             case display_options::IGNOREABC:                       // REQ #066
                { /* show options */                                // REQ #066
                 for(int i = 0; i < Overlays.GetSize(); i++)        // REQ #066
                    { /* scan array */                              // REQ #066
                     DrawOutline(dc, desc, opts, Overlays[i].point.x, CString(Overlays[i].ch), i);// REQ #066
                    } /* scan array */                              // REQ #066
                } /* show options */                                // REQ #066
                break;
             case display_options::TEXTOUT:                         // REQ #066
             case display_options::EXTTEXTOUT_:                     // REQ #066// REQ #081
                   DrawOutline(dc, desc, opts, baseoffset, Text, 0);// REQ #066
                   break;                                           // REQ #066
            } /* draw final */                                      // REQ #066
        } /* textout path */                                        // REQ #066
    } /* bitmap layout */                                           // REQ #066

    {
     CSaveDC sdc(&dc);
     int y = desc.tm.tmHeight - desc.tm.tmDescent;
     dc.MoveTo(0, y);
     dc.LineTo(right, y);
    }

    if(opts.vrule)
       writeRulerV(dc, 0, top, 
                   top + desc.tm.tmHeight + desc.tm.tmExternalLeading);

    if(opts.hrule)
       writeRulerH(dc, top + desc.tm.tmHeight + desc.tm.tmExternalLeading, 
                    0, right);

    CPoint pt(right, 0);                                            // REQ #029
    dc.LPtoDP(&pt, 1);                                              // REQ #029
    ImageWidth = max(ImageWidth, pt.x);                             // REQ #029
    if(opts.debug)                                                  // REQ #032
       TRACE(_T(__FUNCTION__) _T(": ImageWidth=%d\n"), ImageWidth); // REQ #029
   } // CFontDisplay::OnPaint

/****************************************************************************
*                         CFontDisplay::OnEraseBkgnd
* Inputs:
*       CDC * pDC: Display context
* Result: BOOL
*       CStatic::OnEraseBkgnd
* Effect: 
*       Erases the background
****************************************************************************/

BOOL CFontDisplay::OnEraseBkgnd(CDC* pDC) 
   {
    CBrush bkg;
    CRect r;

    CSaveDC dc(pDC);

    bkg.CreateSolidBrush(opts.white ? RGB(255, 255, 255) 
                               : ::GetSysColor(COLOR_BTNFACE));
    GetClientRect(&r);

    pDC->SelectObject(&bkg);
    pDC->PatBlt(r.left, r.top, r.Width(), r.Height(), PATCOPY);

    return CStatic::OnEraseBkgnd(pDC);
   } // CFontDisplay::OnEraseBkgnd

/****************************************************************************
*                         CFontDisplay::OnRButtonDown
* Inputs:
*       UINT nFlags: ignored, except as passed to parent
*       CPoint point: Place where mouse click occurred
* Result: void
*       
* Effect: 
*       If not already popped up, pops up a window showing the parameters
*       used to compute the font display
****************************************************************************/

void CFontDisplay::OnRButtonDown(UINT nFlags, CPoint point) 
   {
    if(GetCapture() == this)
       { /* already captured */
        dismissPopup(point); // if rdown but outside window, dismiss it
        return;   
       } /* already captured */

    CFontDescriptor desc(this, GetParent(), opts.advanced, opts.quality); // REQ #035// REQ #071

    popup = new CPopupList();
    SetCapture();

    CRect r;
    GetClientRect(&r);
    popup->Create(WS_VISIBLE | WS_BORDER | WS_CHILD | LBS_NOINTEGRALHEIGHT, r, this, 0);

    CFont * f = GetParent()->GetFont();                             // REQ #020
    if(opts.debug)                                                  // REQ #032
       { /* debug */                                                // REQ #019
        LOGFONT lf;                                                 // REQ #019
        if(f == NULL)                                               // REQ #019
           TRACE(_T(__FUNCTION__) _T(": parent font is NULL\n"));   // REQ #019
        else                                                        // REQ #019
           { /* show font info */                                   // REQ #019
            TRACE(_T(__FUNCTION__) _T(": GetLogFont=>%p)\n"), f->m_hObject);// REQ #021
                                                                    // REQ #019
            if(!f->GetLogFont(&lf))                                 // REQ #019
               TRACE(_T(__FUNCTION__) _T(": GetLogFont failed\n"));
            else
               TRACE(_T(__FUNCTION__) _T(": parent font is %p \"%s\" %d\n"), f->m_hObject, lf.lfFaceName, lf.lfHeight);// REQ #019
           } /* show font info */                                   // REQ #019
       } /* debug */                                                // REQ #019
    popup->SetFont(f);

    CString t;
    GetWindowText(t);

    SIZE sz;

    CString s;
    CString fmt;
    CClientDC dc(this);

    dc.SelectObject(desc.font);

    GetClientRect(&r);

    if(opts.debug)
       { /* debug only */
        fmt.LoadString(IDS_RECT_EXTENT);
        s.Format(fmt, r.Width(), r.Height());
        popup->AddString(s);

        fmt.LoadString(IDS_TEXT_EXTENT);
        sz = dc.GetTextExtent(t);
        s.Format(fmt, sz.cx, sz.cy);
        popup->AddString(s);

        fmt.LoadString(IDS_TEXT_OVERHANG);
        sz = getOverhangTextExtent(dc, t);
        sz.cy = requiredHeight(desc);
        s.Format(fmt, sz.cx, sz.cy);
        popup->AddString(s);

        scaling sc = computeScaling(r, sz);
        fmt.LoadString(IDS_FSCALE);
        s.Format(fmt, sc.sx, sc.sy);
        popup->AddString(s);


        // Note that a raster font can be scaled at most 5X horizontally and
        // 8X vertically, so if the font is a raster font we limit it
        // to 5X

        if(!opts.advanced)                                          // REQ #018
           { /* GM_COMPATIBLE */                                    // REQ #018
            iscale scale = normalizeScaling(limitScaling(desc.tm, min(sc.sx, sc.sy)));

            fmt.LoadString(IDS_ISCALE);
            s.Format(fmt, scale.win, scale.view);
            popup->AddString(s);

            fmt.LoadString(IDS_SCALED_EXTENT);
            s.Format(fmt, (sz.cx * scale.view) / scale.win, (sz.cy * scale.view) / scale.win);
            popup->AddString(s);
           } /* GM_COMPATIBLE */                                    // REQ #018

        fmt.LoadString(IDS_DRAWCODE);

        for(int i = 0; i < t.GetLength(); i++)
           { /* list widths */
            TCHAR ch = t[i];

            int code = GetDisplayCode(dc, ch);

            s.Format(fmt, ch, ch, ch, code);
            popup->AddString(s);
           } /* list widths */

        { /* show hit rects */
         CString p;
         p.Format(_T("Mouse @ [%d, %d]"), point.x, point.y);
         popup->AddString(p);

         for(int i = 0; i < Hits.GetSize(); i++)
            { /* show each */
                  // [%d]: '%c' [%d, %d, %d, %d] ABC [%d %d %d]
             p.Format(_T("[%d]: '%c' [%d, %d, %d, %d] ABC [%d %d %d]"),
                      i,
                      Hits[i].ch,
                      Hits[i].r.left, Hits[i].r.top,
                      Hits[i].r.right, Hits[i].r.bottom,
                      Hits[i].abc.abcA,
                      Hits[i].abc.abcB,
                      Hits[i].abc.abcC);
             if(Hits[i].pair != 0)                                  // REQ #038
                { /* show pair */                                   // REQ #038
                 CString fmt;
                 fmt.LoadString(IDS_PAIR_TRACE);                    // REQ #038
                 CString pk = ToString(fmt, Hits[i].pair);          // REQ #038
                 p += pk;                                           // REQ #038
                } /* show pair */                                   // REQ #038

             popup->AddString(p);
            } /* show each */
        } /* show hit rects */
       } /* debug only */
    else
       { /* normal user mode */
        { /* protect DC */
         CSaveDC pdc(&dc);
         dc.SetMapMode(MM_TEXT);

         CString s;
         fmt.LoadString(IDS_TEXT_EXTENT);
         CSize sz = dc.GetTextExtent(t);
         s.Format(fmt, sz.cx, sz.cy);
         popup->AddString(s);                                       // REQ #015
         
         TEXTMETRIC tm;                                             // REQ #015
         dc.GetTextMetrics(&tm);                                    // REQ #015
         fmt.LoadString(IDS_TEXTMETRICS);                           // REQ #015
         // TEXTMETRIC tmHeight=%d, tmAscent=%d, tmDescent=%d, tmInternalLeading=%d, tmExternalLeading=%d// REQ #015
         s.Format(fmt, tm.tmHeight, tm.tmAscent, tm.tmDescent, tm.tmInternalLeading, tm.tmExternalLeading);// REQ #015
         popup->AddString(s);                                       // REQ #015

         fmt.LoadString(IDS_ABC_WIDTHS);
         for(int i = 0; i < t.GetLength(); i++)
            { /* format each ABC */
             TCHAR ch = t[i];
             ABC abc;

             getABC(dc, ch, abc);
             s.Format(fmt, ch, ch, ch, abc.abcA, abc.abcB, abc.abcC);

#ifdef _DEBUG
             {
              CString p;
              p.Format(_T(" @ %d"), pinfo[i].pos);
              s += p;
             }
#endif

             popup->AddString(s);
            } /* format each ABC */

         KERNINFO ki(&dc);

         if(ki.count > 0)
            { /* has kerning */

             for(int i = 0; i < t.GetLength() - 1; i++)
                { /* format kerning pairs */
                 LPKERNINGPAIR pair = ki.findPair((UINT)t[i], (UINT)t[i+1]);
                 if(pair != NULL)
                    { /* show it */
                     s.Format(_T("\"%c\" - \"%c\": %d"), t[i], t[i+1], 
                                                       pair->iKernAmount);
                     popup->AddString(s);
                    } /* show it */
                } /* format kerning pairs */
            } /* has kerning */
        } /* protect DC */     
       } /* normal user mode */

    //============================================================================
    // Having filled the box, we now shrink it to fit
    //============================================================================

    int n = popup->GetCount();  // get number of lines
    int ht = popup->GetItemHeight(0); // get a typical item height (fixed)
    CRect w;
    popup->GetClientRect(&w);                                       // REQ #028
    // If the list box is smaller than the area, anchor it to the bottom but
    // make it no higher than needed
    if(n * ht < w.Height())
       { /* shrink it */
        if(opts.debug)
           { /* show at bottom */
            w.top = w.bottom - (n * ht);
           } /* show at bottom */
        else
           { /* show at top */
            w.bottom = w.top + (n * ht);
           } /* show at top */
        popup->CalcWindowRect(&w);                                  // REQ #028
//      ScreenToClient(&w);
        popup->MoveWindow(&w, FALSE);
       } /* shrink it */
   } // CFontDisplay::OnRButtonDown

/****************************************************************************
*                          CFontDisplay::OnRButtonUp
* Inputs:
*       UINT nFlags: ignored, except as passed on
*       CPoint point: Place where mouse button click occurred
* Result: void
*       
* Effect: 
*       If the button goes up when we have capture, we pass it into the
*       popup.  We reestablish capture because it gets dismissed.
****************************************************************************/

void CFontDisplay::OnRButtonUp(UINT nFlags, CPoint point) 
   {
    if(GetCapture() == this)
       { /* pass it thru */
        MapWindowPoints(popup, &point, 1);
        popup->DoRButtonUp(nFlags, point);
        if(GetCapture() != this)
           SetCapture();  // make sure we restore capture
        return;
       } /* pass it thru */
        
    CStatic::OnRButtonUp(nFlags, point);
   } // CFontDisplay::OnRButtonUp

/****************************************************************************
*                         CFontDisplay::dismissPopup
* Inputs:
*       CPoint point: Point of mouse click
* Result: BOOL
*       TRUE if we have dismissed popup window, or there was none
*       FALSE if click was within popup
* Effect: 
*       If mouse click is outside popup window, dismisses the popup window
****************************************************************************/

BOOL CFontDisplay::dismissPopup(CPoint point)
    {
     if(GetCapture() != this)
        return TRUE;

     CRect r;
     popup->GetWindowRect(&r);
     popup->ScreenToClient(&r);
     if(r.PtInRect(point))
        return FALSE;  // ignore mouse clicks inside popup window

     // mouse click was outside window
     popup->DestroyWindow();  // get rid of popup
     ReleaseCapture();
     return TRUE;
    } // CFontDisplay::dismissPopup

/****************************************************************************
*                         CFontDisplay::OnLButtonDown
* Inputs:
*       UINT nFlags:
*       CPoint point:
* Result: void
*       
* Effect: 
*       If the button goes down outside the popup, the popup is dismissed
*       If inside, it is passed to the popup.
*       We have to re-establish capture because it is dismissed somehow
****************************************************************************/

void CFontDisplay::OnLButtonDown(UINT nFlags, CPoint point) 
   {
    if(!dismissPopup(point))
       { /* pass it in */
        MapWindowPoints(popup, &point, 1);
        popup->DoLButtonDown(nFlags, point);
        if(GetCapture() != this)
           SetCapture();  // make sure we restore capture
        return;
       } /* pass it in */

    CStatic::OnLButtonDown(nFlags, point);
   } // CFontDisplay::OnLButtonDown

/****************************************************************************
*                          CFontDisplay::OnNcHitTest
* Inputs:
*       CPoint point: Mouse position, expressed in screen coordinates (NC-
*               style handlers use screen coordinates)
* Result: UINT
*       HTCLIENT if mouse is in client area of window
*       CStatic::OnNcHitTest() otherwise
* Notes: 
*       The default appears to be HTTRANSPARENT, so if we expect to handle
*       any of the events such as mouse down, etc. we have to return HTCLIENT
****************************************************************************/
#if _MSC_VER < 1300  // REQ #042
UINT CFontDisplay::OnNcHitTest(CPoint point)
#else
LRESULT CFontDisplay::OnNcHitTest(CPoint point)
#endif
   {
    CRect r;
    GetClientRect(&r);
    ClientToScreen(&r);
 
    if(r.PtInRect(point))
       return HTCLIENT;
        
    return CStatic::OnNcHitTest(point);
   } // CFontDisplay::OnNcHitTest

/****************************************************************************
*                          CFontDisplay::OnLButtonUp
* Inputs:
*       UINT nFlags:
*       CPoint poitn:
* Result: void
*       
* Effect: 
*       Handles the LButtonUp
****************************************************************************/

void CFontDisplay::OnLButtonUp(UINT nFlags, CPoint point) 
   {
    if(!dismissPopup(point))
       { /* pass it thru */
        MapWindowPoints(popup, &point, 1);
        popup->DoLButtonUp(nFlags, point);
        if(GetCapture() != this)
           SetCapture();  // make sure we restore capture
        return;
       } /* pass it thru */
        
    CStatic::OnLButtonUp(nFlags, point);
   } // CFontDisplay::OnLButtonUp

/****************************************************************************
*                       CFontDisplay::OnLButtonDblClk
* Inputs:
*       UINT nFlags: ignored except to pass forward or upward
*       CPoint point: Place of mouse click
* Result: void
*       
* Effect: 
*       If the double click is outside the popup space, dismisses the
*       popup.  Otherwise passes the click into the popup.  Upon completion,
*       reasserts capture, which for some reason has been killed by the
*       window into which we pass the mouse click.  
****************************************************************************/

void CFontDisplay::OnLButtonDblClk(UINT nFlags, CPoint point) 
   {
    if(!dismissPopup(point))
       { /* pass it thru */
        MapWindowPoints(popup, &point, 1);
        popup->DoLButtonDblClk(nFlags, point);
        if(GetCapture() != this)
           SetCapture();  // make sure we restore capture
        return;
       } /* pass it thru */
        
    CStatic::OnLButtonDblClk(nFlags, point);
   } // CFontDisplay::OnLButtonDblClk

/****************************************************************************
*                        CFontDisplay::PreCreateWindow
* Inputs:
*       CREATESTRUCT & cs: creation structure
* Result: BOOL
*       Result of CStatic::PreCreateWindow
* Effect: 
*       Adds the WS_CLIPCHILDREN flag.  This is because we pop up a
*       display window on top of the window, and if we do anything that 
*       causes the app to redisplay (e.g., uncovering it) while the info
*       box is being displayed, the underlying window "shows through" the
*       text of the list box.
****************************************************************************/

BOOL CFontDisplay::PreCreateWindow(CREATESTRUCT& cs) 
   {
    cs.style |= WS_CLIPCHILDREN;
        
    return CStatic::PreCreateWindow(cs);
   } // CFontDisplay::PreCreateWindow

/****************************************************************************
*                           CFontDisplay::OnCreate
* Inputs:
*       LPCREATESTRUCT lpCreateStruct: ignored except as passed on
* Result: int
*       -1 if error
*       0 if success
* Effect: 
*       Creates the font used to show the captions for the character type
****************************************************************************/

int CFontDisplay::OnCreate(LPCREATESTRUCT lpCreateStruct) 
   {
    if (CStatic::OnCreate(lpCreateStruct) == -1)
       return -1;
        
    legendFont.CreateFont(-1, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE,
                          ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                          CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                          FF_DONTCARE,
                          _T("Arial"));
        
    return 0;
   } // CFontDisplay::OnCreate

/****************************************************************************
*                           CFontDisplay::OnDestroy
* Result: void
*       
* Effect: 
*       Handles font deletion
****************************************************************************/

void CFontDisplay::OnDestroy() 
   {
    CStatic::OnDestroy();
        
    if(opts.debug)                                                  // REQ #032
       TRACE(_T(__FUNCTION__) _T(": DeleteObject(font=%p)\n"), legendFont.m_hObject);// REQ #021
    legendFont.DeleteObject();
   } // CFontDisplay::OnDestroy

/****************************************************************************
*                         CFontDisplay::OnCancelMode
* Result: void
*       
* Effect: 
*       This is necessary because we can lose focus in ways outside our
*       control, and when we return, mouse clicking outside the popup
*       won't dismiss it because we don't have capture.  WM_CANCELMODE is
*       used, among other objectives, to cancel capture, so this is our
*       best intercept point to destroy the popup.
****************************************************************************/

void CFontDisplay::OnCancelMode() 
   {
    if(GetCapture() == this)
       { /* has capture */
        ReleaseCapture();
        if(popup != NULL)                                           // REQ #040
           popup->DestroyWindow();                   
        popup = NULL;                                               // REQ #040
       } /* has capture */

    CStatic::OnCancelMode();
   } // CFontDisplay::OnCancelMode

/****************************************************************************
*                             CFontDisplay::OnSize
* Inputs:
*       UINT nType:
*       int cx:
*       int cy:
* Result: void
*       
* Effect: 
*       Resizes the control by forcing a redraw
****************************************************************************/

void CFontDisplay::OnSize(UINT nType, int cx, int cy) 
   {
    CStatic::OnSize(nType, cx, cy);
        
    InvalidateRect(NULL);
   } // CFontDisplay::OnSize

/****************************************************************************
*                            CFontDisplay::SetOpts
* Inputs:
*       display_options & newopts: Desired options
* Result: void
*       
* Effect: 
*       Sets the display options
****************************************************************************/

void CFontDisplay::SetOpts(display_options & newopts)               // REQ #010
    {                                                               // REQ #010
     opts = newopts;                                                // REQ #010
     if(GetSafeHwnd() != NULL)                                      // REQ #010
        Invalidate();                                               // REQ #010
    } // CFontDisplay::SetOpts                                      // REQ #010

/****************************************************************************
*                           CFontDisplay::SetWhite
* Inputs:
*       BOOL mode: Mode to set
* Result: void
*       
* Effect: 
*       Sets the white-background mode
****************************************************************************/

void CFontDisplay::SetWhite(BOOL mode)                              // REQ #010
    {                                                               // REQ #010
     if(opts.white == mode)                                         // REQ #010
        return;                                                     // REQ #010
     opts.white = mode;                                             // REQ #010
     if(GetSafeHwnd() != NULL)                                      // REQ #010
        Invalidate();                                               // REQ #010
    } // CFontDisplay::SetWhite                                     // REQ #010

/****************************************************************************
*                       CFontDisplay::SetHorizontalRule
* Inputs:
*       BOOL mode:
* Result: void
*       
* Effect: 
*       Sets the horizontal-rule mode
****************************************************************************/

void CFontDisplay::SetHorizontalRule(BOOL mode)                     // REQ #010
    {                                                               // REQ #010
     if(opts.hrule == mode)                                         // REQ #010
        return;                                                     // REQ #010
     opts.hrule = mode;                                             // REQ #010
     if(GetSafeHwnd() != NULL)                                      // REQ #010
        Invalidate();                                               // REQ #010
    } // CFontDisplay::SetHorizontalRule                            // REQ #010

/****************************************************************************
*                        CFontDisplay::SetVerticalRule
* Inputs:
*       BOOL mode:
* Result: void
*       
* Effect: 
*       Sets the vertical-rule mode
****************************************************************************/

void CFontDisplay::SetVerticalRule(BOOL mode)                       // REQ #010
    {                                                               // REQ #010
     if(opts.vrule == mode)                                         // REQ #010
        return;                                                     // REQ #010
     opts.vrule = mode;                                             // REQ #010
     if(GetSafeHwnd() != NULL)                                      // REQ #010
        Invalidate();                                               // REQ #010
    } // CFontDisplay::SetVerticalRule                              // REQ #010

/****************************************************************************
*                       CFontDisplay::SetCharacterRule
* Inputs:
*       BOOL mode:
* Result: void
*       
* Effect: 
*       Sets the character-rule mode
****************************************************************************/

void CFontDisplay::SetCharacterRule(BOOL mode)                      // REQ #010
    {                                                               // REQ #010
     if(opts.chrule == mode)                                        // REQ #010
        return;                                                     // REQ #010
     opts.chrule = mode;                                            // REQ #010
     if(GetSafeHwnd() != NULL)                                      // REQ #010
        Invalidate();                                               // REQ #010
    } // CFontDisplay::SetCharacterRule                             // REQ #010

/****************************************************************************
*                         CFontDisplay::SetUseColors
* Inputs:
*       BOOL mode:
* Result: void
*       
* Effect: 
*       Sets the use-colors mode
****************************************************************************/

void CFontDisplay::SetUseColors(BOOL mode)                          // REQ #010
    {                                                               // REQ #010
     if(opts.colors == mode)                                        // REQ #010
        return;                                                     // REQ #010
     opts.colors = mode;                                            // REQ #010
     if(GetSafeHwnd() != NULL)                                      // REQ #010
        Invalidate();                                               // REQ #010
    } // CFontDisplay::SetUseColors                                 // REQ #010

/****************************************************************************
*                         CFontDisplay::SetTrackMode
* Inputs:
*       BOOL mode:
* Result: void
*       
* Effect: 
*       Sets tracking mode
****************************************************************************/

void CFontDisplay::SetTrackMode(BOOL mode)                          // REQ #010
    {                                                               // REQ #010
     if(opts.track == mode)                                         // REQ #010
        return;                                                     // REQ #010
     opts.track = mode;                                             // REQ #010
     if(GetSafeHwnd() != NULL)                                      // REQ #010
        Invalidate();                                               // REQ #010
    } // CFontDisplay::SetTrackMode                                 // REQ #010

/****************************************************************************
*                        CFontDisplay::SetUsePairKerning
* Inputs:
*       BOOL mode:
* Result: void
*       
* Effect: 
*       Sets pair-kerning mode
****************************************************************************/

void CFontDisplay::SetUsePairKerning(BOOL mode)                     // REQ #010
    {                                                               // REQ #010
     if(opts.kerning == mode)                                       // REQ #010
        return;                                                     // REQ #010
     opts.kerning = mode;                                           // REQ #010
     if(GetSafeHwnd() != NULL)                                      // REQ #010
        Invalidate();                                               // REQ #010
    } // CFontDisplay::SetUsePairKerning                            // REQ #010

/****************************************************************************
*                         CFontDisplay::SetOutputMode
* Inputs:
*       disply_options::OutputOptions:
* Result: void
*       
* Effect: 
*       Sets the output options mode
****************************************************************************/

void CFontDisplay::SetOutputMode(display_options::OutputOptions mode)// REQ #010
    {                                                               // REQ #010
     if(opts.output == mode)                                        // REQ #010
        return;                                                     // REQ #010
     opts.output = mode;                                            // REQ #010
     if(GetSafeHwnd() != NULL)                                      // REQ #010
        Invalidate();                                               // REQ #010
    } // CFontDisplay::SetOutputMode                                // REQ #010

/****************************************************************************
*                         CFontDisplay::SetGMAdvanced
* Inputs:
*       BOOL mode: TRUE for GM_ADVANCED, FALSE for GM_COMPATIBLE
* Result: void
*       
* Effect: 
*       Sets the graphics mode
****************************************************************************/

void CFontDisplay::SetGMAdvanced(BOOL mode)                         // REQ #018
    {                                                               // REQ #018
     if(opts.advanced == mode)                                      // REQ #018
        return;                                                     // REQ #018
     opts.advanced = mode;                                          // REQ #018
     if(GetSafeHwnd() != NULL)                                      // REQ #018
        Invalidate();                                               // REQ #018
    } // CFontDisplay::SetGMAdvanced                                // REQ #018

/****************************************************************************
*                         CFontDisplay::SetTrackValue
* Inputs:
*       int n: Amount of tracking
* Result: void
*       
* Effect: 
*       Sets the tracking value
****************************************************************************/

void CFontDisplay::SetTrackValue(int n)                             // REQ #010
    {                                                               // REQ #010
     if(opts.trackval == n)                                         // REQ #010
        return;                                                     // REQ #010
     opts.trackval = n;                                             // REQ #010
     if(GetSafeHwnd() != NULL)                                      // REQ #010
        Invalidate();                                               // REQ #010
    } // CFontDisplay::SetTrackValue                                // REQ #010

/****************************************************************************
*                         CFontDisplay::SetVerticalOffset
* Inputs:
*       int n: Percentage of vertical offset
* Result: void
*       
* Effect: 
*       Sets the vertical offset value
****************************************************************************/

void CFontDisplay::SetVerticalOffset(int n)                         // REQ #022
    {                                                               // REQ #022
     if(opts.VerticalOffset == n)                                   // REQ #022
        return;                                                     // REQ #022
     opts.VerticalOffset = n;                                       // REQ #022
     if(GetSafeHwnd() != NULL)                                      // REQ #022
        Invalidate();                                               // REQ #022
    } // CFontDisplay::SetVerticalOffset                            // REQ #022

/****************************************************************************
*                         CFontDisplay::SetWindowText
* Inputs:
*       LPCTSTR s: String to set
* Result: void
*       
* Effect: 
*       Sets the string
****************************************************************************/

void CFontDisplay::SetWindowText(LPCTSTR s)                         // REQ #011// REQ #042
    {                                                               // REQ #011
     CStatic::SetWindowText(s);                                     // REQ #011
     Invalidate();                                                  // REQ #011
    } // CFontDisplay::SetWindowText                                // REQ #011

/****************************************************************************
*                            CFontDisplay::SetFont
* Inputs:
*       CFont * f: Font to set
* Result: void
*       
* Effect: 
*       Sets the font
****************************************************************************/

void CFontDisplay::SetFont(CFont * f)                               // REQ #011
    {                                                               // REQ #011
     CStatic::SetFont(f);                                           // REQ #011
     Invalidate();                                                  // REQ #011
    } // CFontDisplay::SetFont

/****************************************************************************
*                         CFontDisplay::GetImageSize
* Result: CSize
*       The image size, in client coordinates of the current window
****************************************************************************/

CSize CFontDisplay::GetImageSize()                                  // REQ #029
    {                                                               // REQ #029
     CRect r;                                                       // REQ #029
     GetClientRect(&r);                                             // REQ #029
                                                                    // REQ #029
     CSize sz(ImageWidth, r.bottom);                                // REQ #029
     return sz;                                                     // REQ #029
    } // CFontDisplay::GetImageSize                                 // REQ #029

/****************************************************************************
*                          CFontDisplay::OnMouseMove
* Inputs:
*       UINT nFlags:
*       CPoint point:
* Result: void
*       
* Effect: 
*       Handles the flyover help
****************************************************************************/

void CFontDisplay::OnMouseMove(UINT nFlags, CPoint point)           // REQ #038
    {                                                               // REQ #038
     for(int i = 0; i < Hits.GetSize(); i++)                        // REQ #038
        { /* scan for hit */                                        // REQ #038
         CRect r = Hits[i].r;                                       // REQ #038
         if(r.PtInRect(point))                                      // REQ #038
            { /* found it */                                        // REQ #038
             CString s;                                             // REQ #038
             ABC abc = Hits[i].abc;                                 // REQ #038
             s.Format(_T("'%c': ABC = [%d, %d, %d]"),               // REQ #038
                                              Hits[i].ch,           // REQ #038
                                              abc.abcA,             // REQ #038
                                              abc.abcB,             // REQ #038
                                              abc.abcC);            // REQ #038
             TRACE(_T(__FUNCTION__) _T(" (%d): Hits[%d].abc [%d, %d, %d]\n"), __LINE__, i, abc.abcA, abc.abcB, abc.abcC); // REQ #038
             if(Hits[i].pair != 0)                                  // REQ #038
                { /* has kerning pair */                            // REQ #038
                 CString fmt;                                       // REQ #038
                 //             pair kern %d                        // REQ #038
                 fmt.LoadString(IDS_PAIR_INFO);                     // REQ #038
                 CString t = ToString(fmt, Hits[i].pair);           // REQ #038
                 s += t;                                            // REQ #038
                } /* has kerning pair */                            // REQ #038
                                                                    // REQ #038
#ifdef _DEBUG                                                       // REQ #038
             s += ToString(_T(" drawcode %d"), Hits[i].drawcode);   // REQ #038
#endif                                                              // REQ #038
                                                                    // REQ #038
             FlyOver->SetWindowText(s);                             // REQ #038
             CPoint pt = point;                                     // REQ #038
             ClientToScreen(&pt);                                   // REQ #038
             // TODO: Adjust by cursor size and other values        // REQ #038
             pt.y += ::GetSystemMetrics(SM_CYCURSOR);               // REQ #038
             FlyOver->SetWindowPos(NULL, pt.x, pt.y, 0, 0,          // REQ #038
                                  SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);       // REQ #038
             if(!FlyOver->IsWindowVisible())                        // REQ #038
                { /* show it */                                     // REQ #038
                 FlyOver->ShowWindow(SW_SHOWNA);                    // REQ #038
                 TRACKMOUSEEVENT tme = {sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_hWnd, 0};// REQ #038
                 VERIFY(TrackMouseEvent(&tme));                     // REQ #038
                } /* show it */                                     // REQ #038
             return;                                                // REQ #038
            } /* found it */                                        // REQ #038
        } /* scan for hit */                                        // REQ #038
                                                                    // REQ #038
     if(FlyOver->IsWindowVisible())                                 // REQ #038
        FlyOver->ShowWindow(SW_HIDE);                               // REQ #038
                                                                    // REQ #038
     CStatic::OnMouseMove(nFlags, point);                           // REQ #038
    } // CFontDisplay::OnMouseMove                                  // REQ #038

/****************************************************************************
*                         CFontDisplay::OnMouseLeave
* Inputs:
*       WPARAM: ignored
*       LPARAM: ignored
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Takes down the viewing window
****************************************************************************/

LRESULT CFontDisplay::OnMouseLeave(WPARAM, LPARAM)                  // REQ #038
    {                                                               // REQ #038
     if(FlyOver->IsWindowVisible())                                 // REQ #038
        FlyOver->ShowWindow(SW_HIDE);                               // REQ #038
     return 0;                                                      // REQ #038
    } // CFontDisplay::OnMouseLeave                                 // REQ #038

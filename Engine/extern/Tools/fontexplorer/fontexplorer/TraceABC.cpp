/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  5-May-08 | REQ #032: Created
*****************************************************************************/
#include "stdafx.h"
#include "traceABC.h"

/****************************************************************************
*                                  TraceABC
* Inputs:
*       LPCSTR fn: Function name
*       int line: Line # in source
*       TCHAR ch: Character whose width is being found
*       CDC & dc: Current DC
*       LPCTSTR abc: ABC width string
* Result: void
*       
* Effect: 
*       Displays the ABC widhts
****************************************************************************/

static void TraceABC(LPCTSTR fn, int line, TCHAR ch, CDC & dc, LPCTSTR abc)// REQ #032
    {                                                               // REQ #032
     CString gmode = ::GetGraphicsMode(dc) == GM_ADVANCED ? _T("GM_ADVANCED") : _T("GM_COMPATIBLE"); // REQ #032
     CFont * f = dc.GetCurrentFont();                               // REQ #032
     LOGFONT lf;                                                    // REQ #032
     f->GetLogFont(&lf);                                            // REQ #032
                                                                    // REQ #032     
     TRACE(_T("%s (%d): GetCharABCWidths('%c') [%s] %s \"%s\" %d\n"),// REQ #032
           fn, line, ch, gmode,                                     // REQ #032
           abc,                                                     // REQ #032
           lf.lfFaceName, lf.lfHeight);                             // REQ #032
    } // TraceABC                                                   // REQ #032


/****************************************************************************
*                                  TraceABC
* Inputs:
*       LPCSTR fn: Function name
*       int line: Line # in source
*       TCHAR ch: Character whose width is being found
*       CDC & dc: Current DC
*       ABC abc: ABC width 
* Result: void
*       
* Effect: 
*       Displays the ABC widhts
****************************************************************************/

void TraceABC(LPCTSTR fn, int line, TCHAR ch, CDC & dc, ABC abc)    // REQ #032
    {                                                               // REQ #032
     CString s;                                                     // REQ #032
     s.Format(_T("ABC [%d, %d, %d]"), abc.abcA, abc.abcB, abc.abcC);// REQ #032
     TraceABC(fn, line, ch, dc, s);                                 // REQ #032
    } // TraceABC                                                   // REQ #032

/****************************************************************************
*                                  TraceABC
* Inputs:
*       LPCSTR fn: Function name
*       int line: Line # in source
*       TCHAR ch: Character whose width is being found
*       CDC & dc: Current DC
*       ABCFLOAT abc: ABC width
* Result: void
*       
* Effect: 
*       Displays the ABC widhts
****************************************************************************/

void TraceABC(LPCTSTR fn, int line, TCHAR ch, CDC & dc, ABCFLOAT abc)// REQ #032
    {                                                               // REQ #032
     CString s;                                                     // REQ #032
     s.Format(_T("ABCFLOAT [%#0.3g, %#0.3g, %#0.3g]"), abc.abcfA, abc.abcfB, abc.abcfC);// REQ #032
     TraceABC(fn, line, ch, dc, s);                                 // REQ #032
    } // TraceABC                                                   // REQ #032

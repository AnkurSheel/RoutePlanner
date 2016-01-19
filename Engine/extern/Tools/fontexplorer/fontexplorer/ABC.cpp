/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  4-May-08 | Created
*  4-May-08 | REQ #032: Added debugging support
* 15-Oct-08 | REQ #043: Replace CDC * with CDC & for cleaner code
*****************************************************************************/
#include "stdafx.h"
#include "chformat.h"
#include "DCState.h"                                                // REQ #032
#include "TraceABC.h"                                               // REQ #032

/****************************************************************************
*                                loadABCWidths
* Inputs:
*       CDC & dc: DC to use for getting widths                      // REQ #043
*       CString smp: Sample string
*       CTreeCtrl * tc: Tree control into which to insert it
*       HTREEITEM wd: Parent node of width
* Result: void
*       
* Effect: 
*       Computes the ABC widths, in floating point if possible, and displays
*       the integer or integer and floating point versions of the widths.
****************************************************************************/

void loadABCWidths(CDC & dc, CString smp, CTreeCtrl * tc, HTREEITEM wd)// REQ #043
    {     
     HTREEITEM gabc = tc->InsertItem(_T("GetCharABCWidths"), wd);
     CString s;
//     ShowDCState(_T(__FUNCTION__), *dc);                            // REQ #032

     for(int i = 0; i < smp.GetLength(); i++) 
        { /* add ABC */
         ABC abc;
         ABCFLOAT abcf;
         BOOL flt;

         dc.GetCharABCWidths(smp[i], smp[i], &abc);                 // REQ #043
         flt = ::GetCharABCWidthsFloat(dc, smp[i], smp[i], &abcf);  // REQ #043

         TraceABC(_T(__FUNCTION__), __LINE__, smp[i], dc, abc);     // REQ #032// REQ #043

         charFormat(s, smp[i]);


         HTREEITEM iabc = tc->InsertItem(s, gabc);
         if(flt)
            { /* floating */
#define FloatFormat _T("%c %d   %#0.4g")
             s.Format(FloatFormat, _T('A'), abc.abcA, abcf.abcfA);
             tc->InsertItem(s, iabc);

             s.Format(FloatFormat, _T('B'), abc.abcB, abcf.abcfB);
             tc->InsertItem(s, iabc);

             s.Format(FloatFormat, _T('C'), abc.abcC, abcf.abcfC);
             tc->InsertItem(s, iabc);
             TraceABC(_T(__FUNCTION__), __LINE__, smp[i], dc, abcf);     // REQ #032// REQ #043
            } /* floating */
         else
            { /* fixed only */
             s.Format(_T("A %d"), abc.abcA);
             tc->InsertItem(s, iabc);

             s.Format(_T("B %d"), abc.abcB);
             tc->InsertItem(s, iabc);

             s.Format(_T("C %d"), abc.abcC);
             tc->InsertItem(s, iabc);
            } /* fixed only */
        } /* add ABC */
     
    }

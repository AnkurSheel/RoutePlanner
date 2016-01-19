/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  8-May-08 | Created change log
*  8-May-08 | REQ #042: Unicode conversion
*****************************************************************************/
#include "stdafx.h"
#include "fontstr.h"

/****************************************************************************
*                                FontToString
* Inputs:
*       CString & buffer: Place to write formatted font string
*       LOGFONT * lf: Logical font to convert to external form
*       CDC * dc: DC for display (used to convert height properly)
*       BOOL quotes: TRUE to put quotes around the font name, FALSE to omit
*                    quotes
* Result: void
*       
* Effect: 
*       Converts the logical font to a string that can be processed by
*       StringToFont (if quotes is TRUE) or used for display (if quotes
*       is FALSE)
****************************************************************************/

void FontToString(CString & buffer, LOGFONT * lf, CDC * dc, BOOL quotes)// REQ #042
    {
     // char style[50];                                             // REQ #042
     CString style;                                                 // REQ #042
     int height;
     int factor;

     if(lf->lfWeight == FW_EXTRABOLD && !lf->lfItalic)
        style = _T("ExtraBold");                                    // REQ #042
     else
     if(lf->lfWeight == FW_BOLD && !lf->lfItalic)
        style = _T("Bold");                                         // REQ #042
     else
     if(lf->lfWeight == FW_BOLD && lf->lfItalic)
        style = _T("BoldItalic");                                   // REQ #042
     else
     if(lf->lfWeight == FW_NORMAL && lf->lfItalic)
        style = _T("Italic");                                       // REQ #042
     else
     if(lf->lfWeight == FW_NORMAL && !lf->lfItalic)
        style = _T("Normal");                                       // REQ #042
     else
        style.Format(_T("Weight %d"), lf->lfWeight);                // REQ #042
     
     factor = dc->GetDeviceCaps(LOGPIXELSX);
     height = -MulDiv(lf->lfHeight, 72, factor);
     buffer.Format(_T("%s%s%s %d %s"),                              // REQ #042
                (quotes ? _T("\"") : _T("")),                       // REQ #042
                lf->lfFaceName, 
                (quotes ? _T("\"") : _T("")),                       // REQ #042
                height, style);
    }

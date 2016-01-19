/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 23-Apr-08 | Created
* 23-Apr-08 | REQ #006: Changes required for 64-bit compatibility
*  4-May-08 | REQ #037: Code cleanup
*  5-May-08 | REQ #041: Added kerning map
* 22-Oct-08 | REQ #071: Handle font smoothing options
* 22-Oct-08 | REQ #073: Allow pair kerning only for fonts with kerning pairs
*  2-Nov-08 | REQ #078: Handle case where window is not child of CFontDialog
*****************************************************************************/
#include "stdafx.h"
#include "fontdesc.h"
#include "color.h"

/****************************************************************************
*                              CFontDescriptor::CFontDescriptor
* Inputs:
*       CWnd * wnd: Window handle for window
* Effect: 
*       Creates a CFontDescriptor.  
****************************************************************************/

CFontDescriptor::CFontDescriptor(CWnd * wnd, CWnd * fontwnd /* = NULL */, BOOL advanced /* = FALSE */, DWORD quality /* = 0 */) // REQ #035// REQ #071
    {
     ::ZeroMemory(&abc, sizeof(abc)); // font-sample-specific       // REQ #037
     ::ZeroMemory(&tm, sizeof(tm));                                 // REQ #037
     ::ZeroMemory(&otm, sizeof(otm));                               // REQ #037
     otm = NULL;

     if(fontwnd != NULL)
        { /* has parent */
         // If it has a parent, the parent must process the UWM_GETCOLOR
         // message (default will return 0, that is RGB(0,0,0)
         color = (COLORREF)fontwnd->SendMessage(UWM_GETCOLOR); // REQ #006
        } /* has parent */
     else
        { /* no color */
         color = ::GetSysColor(COLOR_WINDOWTEXT);
        } /* no color */

     dc = new CClientDC(wnd);

     if(advanced)                                                   // REQ #035
        ::SetGraphicsMode(*dc, GM_ADVANCED);                        // REQ #035

     ::ZeroMemory(&lf, sizeof(LOGFONT));                            // REQ #037

     (fontwnd == NULL ? wnd : fontwnd)->SendMessage(WM_CHOOSEFONT_GETLOGFONT, 0, (LPARAM)&lf);

     if(lf.lfHeight == 0 &&                                         // REQ #078
        lf.lfWidth == 0 &&                                          // REQ #078
        lf.lfEscapement == 0 &&                                     // REQ #078
        lf.lfWeight == 0 &&                                         // REQ #078
        lf.lfItalic == 0 &&                                         // REQ #078
        lf.lfUnderline == 0 &&                                      // REQ #078
        lf.lfStrikeOut == 0 &&                                      // REQ #078
        lf.lfCharSet == 0 &&                                        // REQ #078
        lf.lfOutPrecision == 0 &&                                   // REQ #078
        lf.lfClipPrecision == 0 &&                                  // REQ #078
        lf.lfQuality == 0 &&                                        // REQ #078
        lf.lfPitchAndFamily == 0 &&                                 // REQ #078
        _tcslen(lf.lfFaceName) == 0)                                // REQ #078
        { /* not child of CFontDialog */                            // REQ #078
         CFont * f = wnd->GetFont();                                // REQ #078
         if(f != NULL)                                              // REQ #078
            f->GetLogFont(&lf);                                     // REQ #078
        } /* not child of CFontDialog */                            // REQ #078
     
     if(quality != 0)                                               // REQ #071
        lf.lfQuality = (BYTE)quality;                               // REQ #071

     saved = dc->SaveDC();
     font = new CFont();

     if(font->CreateFontIndirect(&lf))
        { /* successful creation */
         dc->SelectObject(font);
         dc->GetTextMetrics(&tm);
         int n = dc->GetOutlineTextMetrics(0, NULL);
         if(n > 0)
            { /* load it */
             otm = (OUTLINETEXTMETRIC *)new BYTE[n];
             dc->GetOutlineTextMetrics(n, otm);
            } /* load it */
         // The DC is left in its currently-pushed state
         return;
        } /* successful creation */

     // If unsuccessful in creating the font, restore the DC and delete it
     delete font;                                                   // REQ #041
     font = NULL;                                                   // REQ #041
     dc->RestoreDC(saved);
     delete dc;
     dc = NULL;
     saved = -1;
    }

/****************************************************************************
*                              CFontDescriptor::~CFontDescriptor
* Effect: 
*       Destructor.  Releases the DC, deletes the font, if any
****************************************************************************/

CFontDescriptor::~CFontDescriptor()
    {
     if(saved >= 0)
        { /* restore DC */
         dc->RestoreDC(saved);
        } /* restore DC */

     delete font;
     delete dc;
     delete [] (LPBYTE)otm;
    }

/****************************************************************************
*                    CFontDescriptor::GetFontLanguageInfo
* Result: DWORD
*       Flags; see ::GetFontLanguageInfo
****************************************************************************/

DWORD CFontDescriptor::GetFontLanguageInfo()                        // REQ #073
    {                                                               // REQ #073
     DWORD result = ::GetFontLanguageInfo(dc->m_hDC);               // REQ #073
     if(result == GCP_ERROR)                                        // REQ #073
        return 0;                                                   // REQ #073
     return result;                                                 // REQ #073
    } // CFontDescriptor::GetFontLanguageInfo                       // REQ #073

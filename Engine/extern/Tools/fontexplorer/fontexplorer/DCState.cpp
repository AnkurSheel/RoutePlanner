/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  1-May-08 | REQ #033: Created
*****************************************************************************/

#include "stdafx.h"                                                 // REQ #033
#include "DCState.h"                                                // REQ #033
#include "ToString.h"                                               // REQ #033

/****************************************************************************
*                                   ToColor
* Inputs:
*       COLORREF c: Color description
* Result: CString
*       RGB(n, n, n);
****************************************************************************/

static CString ToColor(COLORREF c)                                  // REQ #033
    {                                                               // REQ #033
     return ToString(_T("RGB(%d, %d, %d)"),                         // REQ #033
           GetRValue(c),                                            // REQ #033
           GetGValue(c),                                            // REQ #033
           GetBValue(c));                                           // REQ #033
    } // ToColor                                                    // REQ #033

/****************************************************************************
*                                   BitCase
* Inputs:
*       DWORD flags: Flags value
*       DWORD mask: Mask to test
*       CString & s: String to append to
*       const LPCTSTR name: Name of bit
* Result: void
*       
* Effect: 
*       Updates s to have the name if the bit is present
*       Removes the tested bit from the flags
****************************************************************************/

static void BitCase(DWORD & flags, DWORD mask, CString & s, const LPCTSTR name)// REQ #033
    {                                                               // REQ #033
     ASSERT(mask != 0);                                             // REQ #033
     if( (flags & mask) == 0)                                       // REQ #033
        return;                                                     // REQ #033
     if(!s.IsEmpty())                                               // REQ #033
        s += _T(" | ");                                             // REQ #033
     s += name;                                                     // REQ #033
     flags &= ~mask;                                                // REQ #033
    } // BitCase                                                    // REQ #033


/****************************************************************************
*                                 ShowDCState
* Inputs:
*       LPCTSTR where: Place where it was called
*       CDC & dc: A DC
* Result: void
*       
* Effect: 
*       TRACE output of DC state
****************************************************************************/

#define LITCASE(s, x) case x: s = _T(#x); break                     // REQ #033
#define DEFCASE(s) defalult: s = _T("?"); break                     // REQ #033
#define DEFNUMCASE(s, n) default: s.Format(_T("%d"), n); break;     // REQ #033
#define BITCASE(value, s, name) BitCase(value, name, s, _T(#name))  // REQ #033
#define DEFBITCASE(value, s) if((value) != 0)                                 \
                                 {                                            \
                                  if(!s.IsEmpty())                            \
                                      s += _T(" | ");                         \
                                  s += ToString(_T("0x%x"), (value));         \
                                 }
                                                                    // REQ #033
void ShowDCState(LPCTSTR where, CDC & dc)                           // REQ #033
    {                                                               // REQ #033
     CString s;                                                     // REQ #033
     TRACE(_T("=====================%s=====================\n"), where); // REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // Mapping mode                                                // REQ #033
     //*************************************************************// REQ #033
     switch(dc.GetMapMode())                                        // REQ #033
        { /* map mode */                                            // REQ #033
         LITCASE(s, MM_TEXT);                                       // REQ #033
         LITCASE(s, MM_HIMETRIC);                                   // REQ #033
         LITCASE(s, MM_LOMETRIC);                                   // REQ #033
         LITCASE(s, MM_HIENGLISH);                                  // REQ #033
         LITCASE(s, MM_LOENGLISH);                                  // REQ #033
         LITCASE(s, MM_TWIPS);                                      // REQ #033
         LITCASE(s, MM_ISOTROPIC);                                  // REQ #033
         LITCASE(s, MM_ANISOTROPIC);                                // REQ #033
         DEFNUMCASE(s, dc.GetMapMode());                            // REQ #033
        } /* map mode */                                            // REQ #033
     TRACE(_T("Mapping mode        = %s\n"), s);                    // REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // Current position                                            // REQ #033
     //*************************************************************// REQ #033
                                                                    // REQ #033
     CPoint pt = dc.GetCurrentPosition();                           // REQ #033
     TRACE(_T("GetCurrentPosition  = [%d, %d]\n"), pt.x, pt.y);     // REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // Extents                                                     // REQ #033
     //*************************************************************// REQ #033
     TRACE(_T("GetWindowExt        = [%d, %d]\n"),                  // REQ #033
                    dc.GetWindowExt().cx, dc.GetWindowExt().cy);    // REQ #033
     TRACE(_T("GetViewportExt      = [%d, %d]\n"),                  // REQ #033
                    dc.GetViewportExt().cx, dc.GetViewportExt().cy);// REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // Origins                                                     // REQ #033
     //*************************************************************// REQ #033
     TRACE(_T("GetWindowOrg        = [%d, %d]\n"),                  // REQ #033
                      dc.GetWindowOrg().x, dc.GetWindowOrg().y);    // REQ #033
     TRACE(_T("GetViewportOrg      = [%d, %d]\n"),                  // REQ #033
                      dc.GetViewportOrg().x, dc.GetViewportOrg().y);// REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // Graphics Mode                                               // REQ #033
     //*************************************************************// REQ #033
     switch(::GetGraphicsMode(dc))                                  // REQ #033
        { /* gm */                                                  // REQ #033
         LITCASE(s, GM_COMPATIBLE);                                 // REQ #033
         LITCASE(s, GM_ADVANCED);                                   // REQ #033
         DEFNUMCASE(s, ::GetGraphicsMode(dc));                      // REQ #033
        } /* gm */                                                  // REQ #033
     TRACE(_T("Graphics mode       = %s\n"), s);                    // REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // Transformation Matrix                                       // REQ #033
     //*************************************************************// REQ #033
                                                                    // REQ #033
     XFORM M;                                                       // REQ #033
     ::GetWorldTransform(dc, &M);                                   // REQ #033
     TRACE(_T("Transform matrix    = [%f, %f, %f, %f, %f, %f]\n"),  // REQ #033
                      M.eM11, M.eM12, M.eM21, M.eM22, M.eDx, M.eDy);// REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // LOGFONT                                                     // REQ #033
     //*************************************************************// REQ #033
                                                                    // REQ #033
     CFont * f = dc.GetCurrentFont();                               // REQ #033
     LOGFONT lf;                                                    // REQ #033
     f->GetLogFont(&lf);                                            // REQ #033
     TRACE(_T("LOGFONT\n"));                                        // REQ #033
     TRACE(_T("    .lfHeight        = %d\n"), lf.lfHeight);         // REQ #033
     TRACE(_T("    .lfWidth         = %d\n"), lf.lfWidth);          // REQ #033
     TRACE(_T("    .lfEscapement    = %d\n"), lf.lfEscapement);     // REQ #033
     TRACE(_T("    .lfOrientation   = %d\n"), lf.lfOrientation);    // REQ #033
     switch(lf.lfWeight)                                            // REQ #033
        { /* weight */                                              // REQ #033
         LITCASE(s, FW_DONTCARE);                                   // REQ #033
         LITCASE(s, FW_THIN);                                       // REQ #033
         LITCASE(s, FW_EXTRALIGHT);                                 // REQ #033
         LITCASE(s, FW_LIGHT);                                      // REQ #033
         LITCASE(s, FW_NORMAL);                                     // REQ #033
         LITCASE(s, FW_MEDIUM);                                     // REQ #033
         LITCASE(s, FW_SEMIBOLD);                                   // REQ #033
         LITCASE(s, FW_BOLD);                                       // REQ #033
         LITCASE(s, FW_EXTRABOLD);                                  // REQ #033
         LITCASE(s, FW_BLACK);                                      // REQ #033
         DEFNUMCASE(s, lf.lfWeight);                                // REQ #033
        } /* weight */                                              // REQ #033
     TRACE(_T("    .lfWeight        = %s\n"), s);                   // REQ #033
     TRACE(_T("    .lfItalic        = 0x%02x\n"), lf.lfItalic);     // REQ #033
     TRACE(_T("    .lfUnderline     = 0x%02x\n"), lf.lfUnderline);  // REQ #033
     switch(lf.lfCharSet)                                           // REQ #033
        { /* charset */                                             // REQ #033
         LITCASE(s, ANSI_CHARSET);                                  // REQ #033
         LITCASE(s, BALTIC_CHARSET);                                // REQ #033
         LITCASE(s, CHINESEBIG5_CHARSET);                           // REQ #033
         LITCASE(s, DEFAULT_CHARSET);                               // REQ #033
         LITCASE(s, EASTEUROPE_CHARSET);                            // REQ #033
         LITCASE(s, GB2312_CHARSET);                                // REQ #033
         LITCASE(s, GREEK_CHARSET);                                 // REQ #033
         LITCASE(s, HANGUL_CHARSET);                                // REQ #033
         LITCASE(s, MAC_CHARSET);                                   // REQ #033
         LITCASE(s, OEM_CHARSET);                                   // REQ #033
         LITCASE(s, RUSSIAN_CHARSET);                               // REQ #033
         LITCASE(s, SHIFTJIS_CHARSET);                              // REQ #033
         LITCASE(s, SYMBOL_CHARSET);                                // REQ #033
         LITCASE(s, TURKISH_CHARSET);                               // REQ #033
         LITCASE(s, VIETNAMESE_CHARSET);                            // REQ #033
         LITCASE(s, JOHAB_CHARSET);                                 // REQ #033
         LITCASE(s, ARABIC_CHARSET);                                // REQ #033
         LITCASE(s, HEBREW_CHARSET);                                // REQ #033
         LITCASE(s, THAI_CHARSET);                                  // REQ #033
         DEFNUMCASE(s, lf.lfCharSet);                               // REQ #033
        } /* charset */                                             // REQ #033
     TRACE(_T("    .lfCharSet       = %s\n"), s);                   // REQ #033
                                                                    // REQ #033
     switch(lf.lfOutPrecision)                                      // REQ #033
        { /* outprecision */                                        // REQ #033
         LITCASE(s, OUT_CHARACTER_PRECIS);                          // REQ #033
         LITCASE(s, OUT_DEFAULT_PRECIS);                            // REQ #033
         LITCASE(s, OUT_DEVICE_PRECIS);                             // REQ #033
         LITCASE(s, OUT_OUTLINE_PRECIS);                            // REQ #033
         LITCASE(s, OUT_PS_ONLY_PRECIS);                            // REQ #033
         LITCASE(s, OUT_RASTER_PRECIS);                             // REQ #033
         LITCASE(s, OUT_STRING_PRECIS);                             // REQ #033
         LITCASE(s, OUT_STROKE_PRECIS);                             // REQ #033
         LITCASE(s, OUT_TT_ONLY_PRECIS);                            // REQ #033
         LITCASE(s, OUT_TT_PRECIS);                                 // REQ #033
         DEFNUMCASE(s, lf.lfOutPrecision);                          // REQ #033
        } /* outprecision */                                        // REQ #033
     TRACE(_T("    .lfOutPrecision  = %s\n"), s);                   // REQ #033
                                                                    // REQ #033
     DWORD t = lf.lfClipPrecision;                                  // REQ #033
     if(t == 0)                                                     // REQ #033
        s = _T("CLIP_DEFAULT_PRECIS");                              // REQ #033
     else                                                           // REQ #033
        { /* show bits */                                           // REQ #033
         BITCASE(t, s, CLIP_CHARACTER_PRECIS);                      // REQ #033
         //BITCASE(t, s, CLIP_DFA_DISABLE);                         // REQ #033
         BITCASE(t, s, CLIP_EMBEDDED);                              // REQ #033
         BITCASE(t, s, CLIP_LH_ANGLES);                             // REQ #033
         //BITCASE(t, s, CLIP_DFA_OVERRIDE);                        // REQ #033
         BITCASE(t, s, CLIP_STROKE_PRECIS);                         // REQ #033
         DEFBITCASE(t, s);                                          // REQ #033
        } /* show bits */                                           // REQ #033
     TRACE(_T("    .lfClipPrecision = %s\n"), s);                    // REQ #033
                                                                    // REQ #033
     switch(lf.lfQuality)                                           // REQ #033
        { /* quality */                                             // REQ #033
         LITCASE(s, ANTIALIASED_QUALITY);                           // REQ #033
         LITCASE(s, CLEARTYPE_QUALITY);                             // REQ #033
         LITCASE(s, DEFAULT_QUALITY);                               // REQ #033
         LITCASE(s, DRAFT_QUALITY);                                 // REQ #033
         LITCASE(s, NONANTIALIASED_QUALITY);                        // REQ #033
         LITCASE(s, PROOF_QUALITY);                                 // REQ #033
         DEFNUMCASE(s, lf.lfQuality);                               // REQ #033
        } /* quality */                                             // REQ #033
     TRACE(_T("    .lfQuality       = %s\n"), s);                   // REQ #033
                                                                    // REQ #033
     CString pitch;                                                 // REQ #033
     switch(lf.lfPitchAndFamily & 0x03) // The two low-order bits   // REQ #033
        { /* pitch */                                               // REQ #033
         LITCASE(pitch, DEFAULT_PITCH);                             // REQ #033
         LITCASE(pitch, FIXED_PITCH);                               // REQ #033
         LITCASE(pitch, VARIABLE_PITCH);                            // REQ #033
         DEFNUMCASE(pitch, lf.lfPitchAndFamily & 0x03);             // REQ #033
        } /* pitch */                                               // REQ #033
                                                                    // REQ #033
     CString family;                                                // REQ #033
     switch(lf.lfPitchAndFamily & 0xF0) // bits 4 through 7         // REQ #033
        { /* family */                                              // REQ #033
         LITCASE(family, FF_DECORATIVE);                            // REQ #033
         LITCASE(family, FF_DONTCARE);                              // REQ #033
         LITCASE(family, FF_MODERN);                                // REQ #033
         LITCASE(family, FF_ROMAN);                                 // REQ #033
         LITCASE(family, FF_SCRIPT);                                // REQ #033
         LITCASE(family, FF_SWISS);                                 // REQ #033
         DEFNUMCASE(family, lf.lfPitchAndFamily & 0xF0);            // REQ #033
        } /* family */                                              // REQ #033
                                                                    // REQ #033
     TRACE(_T("    .lfPitchAndFamily= %s | %s\n"), pitch, family);  // REQ #033
                                                                    // REQ #033
     TRACE(_T("    .lfFaceName      = \"%s\"\n"), lf.lfFaceName);   // REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // BRUSH                                                       // REQ #033
     //*************************************************************// REQ #033
                                                                    // REQ #033
     CBrush * br = dc.GetCurrentBrush();                            // REQ #033
     LOGBRUSH lb;                                                   // REQ #033
     br->GetLogBrush(&lb);                                          // REQ #033
     TRACE(_T("LOGBRUSH\n"));                                       // REQ #033
     switch(lb.lbStyle)                                             // REQ #033
        { /* style */                                               // REQ #033
         LITCASE(s, BS_DIBPATTERN);                                 // REQ #033
         LITCASE(s, BS_DIBPATTERN8X8);                              // REQ #033
         LITCASE(s, BS_DIBPATTERNPT);                               // REQ #033
         LITCASE(s, BS_HATCHED);                                    // REQ #033
         LITCASE(s, BS_NULL);                                       // REQ #033
         LITCASE(s, BS_PATTERN);                                    // REQ #033
         LITCASE(s, BS_PATTERN8X8);                                 // REQ #033
         LITCASE(s, BS_SOLID);                                      // REQ #033
         DEFNUMCASE(s, lb.lbStyle);                                 // REQ #033
        } /* style */                                               // REQ #033
                                                                    // REQ #033
     TRACE(_T("    .lbStyle = %s\n"), s);                           // REQ #033
     switch(lb.lbStyle)                                             // REQ #033
        { /* style+color */                                         // REQ #033
         case BS_HOLLOW:                                            // REQ #033
         case BS_PATTERN:                                           // REQ #033
         case BS_PATTERN8X8:                                        // REQ #033
            TRACE(_T("    .lbColor n/a\n"));                        // REQ #033
            break;                                                  // REQ #033
         case BS_DIBPATTERN:                                        // REQ #033
         case BS_DIBPATTERN8X8:                                     // REQ #033
         case BS_DIBPATTERNPT:                                      // REQ #033
            switch(lb.lbColor)                                      // REQ #033
               { /* pattern+color */                                // REQ #033
                LITCASE(s, DIB_PAL_COLORS);                         // REQ #033
                LITCASE(s, DIB_RGB_COLORS);                         // REQ #033
                DEFNUMCASE(s, lb.lbColor);                          // REQ #033
               } /* pattern+color */                                // REQ #033
            TRACE(_T("    .lbcolor = %s\n"), s);                    // REQ #033
            break;                                                  // REQ #033
         default:                                                   // REQ #033
            TRACE(_T("    .lbColor = %s\n"), ToColor(lb.lbColor));  // REQ #033
            break;                                                  // REQ #033
        } /* style+color */                                         // REQ #033
                                                                    // REQ #033
     switch(lb.lbStyle)                                             // REQ #033
        { /* lbstyle */                                             // REQ #033
         case BS_DIBPATTERN:                                        // REQ #033
         case BS_DIBPATTERN8X8:                                     // REQ #033
         case BS_PATTERN:                                           // REQ #033
         case BS_PATTERN8X8:                                        // REQ #033
            TRACE(_T("    .lbHatch = HANDLE(%p)\n"), lb.lbHatch);   // REQ #033
            break;                                                  // REQ #033
         case BS_DIBPATTERNPT:                                      // REQ #033
            TRACE(_T("    .lbHatch = 0x%p\n"), lb.lbHatch);         // REQ #033
            break;                                                  // REQ #033
         case BS_SOLID:                                             // REQ #033
         case BS_NULL:                                              // REQ #033
            TRACE(_T("    .lbHatch n/a\n"));                        // REQ #033
            break;                                                  // REQ #033
         case BS_HATCHED:                                           // REQ #033
            switch(lb.lbHatch)                                      // REQ #033
               { /* hatch */                                        // REQ #033
                LITCASE(s, HS_BDIAGONAL);                           // REQ #033
                LITCASE(s, HS_CROSS);                               // REQ #033
                LITCASE(s, HS_DIAGCROSS);                           // REQ #033
                LITCASE(s, HS_FDIAGONAL);                           // REQ #033
                LITCASE(s, HS_HORIZONTAL);                          // REQ #033
                LITCASE(s, HS_VERTICAL);                            // REQ #033
               } /* hatch */                                        // REQ #033
            TRACE(_T("    .lbHatch = %s\n"), s);                    // REQ #033
            break;                                                  // REQ #033
         default:                                                   // REQ #033
            TRACE(_T("    .lbHatch = %d\n"), lb.lbHatch);           // REQ #033
            break;                                                  // REQ #033
        } /* lbstyle */                                             // REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // PEN                                                         // REQ #033
     //*************************************************************// REQ #033
     CPen * pen = dc.GetCurrentPen();                               // REQ #033
     LOGPEN lp;                                                     // REQ #033
     pen->GetLogPen(&lp);                                           // REQ #033
                                                                    // REQ #033
     TRACE(_T("LOGPEN\n"));                                         // REQ #033
     switch(lp.lopnStyle)                                           // REQ #033
        { /* style */                                               // REQ #033
         LITCASE(s, PS_SOLID);                                      // REQ #033
         LITCASE(s, PS_DASH);                                       // REQ #033
         LITCASE(s, PS_DASHDOT);                                    // REQ #033
         LITCASE(s, PS_DASHDOTDOT);                                 // REQ #033
         LITCASE(s, PS_NULL);                                       // REQ #033
         LITCASE(s, PS_INSIDEFRAME);                                // REQ #033
         DEFNUMCASE(s, lp.lopnStyle);                               // REQ #033
        } /* style */                                               // REQ #033
     TRACE(_T("    .lopnStyle = %s\n"), s);                         // REQ #033
     TRACE(_T("    .lopnWidth = %d\n"), lp.lopnWidth);              // REQ #033
     TRACE(_T("    .lopnColor = %s\n"), ToColor(lp.lopnColor));     // REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // Background color                                            // REQ #033
     //*************************************************************// REQ #033
                                                                    // REQ #033
     TRACE(_T("Background color     = %s\n"), ToColor(dc.GetBkColor()));// REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // Background mode                                             // REQ #033
     //*************************************************************// REQ #033
                                                                    // REQ #033
     switch(dc.GetBkMode())                                         // REQ #033
        { /* bkmode */                                              // REQ #033
         LITCASE(s, OPAQUE);                                        // REQ #033
         LITCASE(s, TRANSPARENT);                                   // REQ #033
         DEFNUMCASE(s, dc.GetBkMode());                             // REQ #033
        } /* bkmode */                                              // REQ #033
     TRACE(_T("Background mode      = %s\n"), s);                   // REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // PolyFill mode                                               // REQ #033
     //*************************************************************// REQ #033
                                                                    // REQ #033
     switch(dc.GetPolyFillMode())                                   // REQ #033
        { /* polyfill */                                            // REQ #033
         LITCASE(s, ALTERNATE);                                     // REQ #033
         LITCASE(s, WINDING);                                       // REQ #033
         DEFNUMCASE(s, dc.GetPolyFillMode());                       // REQ #033
        } /* polyfill */                                            // REQ #033
     TRACE(_T("Polygon Fill mode    = %s\n"), s);                   // REQ #033
                                                                    // REQ #033
     switch(dc.GetROP2())                                           // REQ #033
        { /* rop2 */                                                // REQ #033
         LITCASE(s, R2_BLACK);                                      // REQ #033
         LITCASE(s, R2_WHITE);                                      // REQ #033
         LITCASE(s, R2_NOP);                                        // REQ #033
         LITCASE(s, R2_NOT);                                        // REQ #033
         LITCASE(s, R2_COPYPEN);                                    // REQ #033
         LITCASE(s, R2_NOTCOPYPEN);                                 // REQ #033
         LITCASE(s, R2_MERGEPENNOT);                                // REQ #033
         LITCASE(s, R2_MASKPENNOT);                                 // REQ #033
         LITCASE(s, R2_MERGENOTPEN);                                // REQ #033
         LITCASE(s, R2_MASKNOTPEN);                                 // REQ #033
         LITCASE(s, R2_NOTMERGEPEN);                                // REQ #033
         LITCASE(s, R2_MASKPEN);                                    // REQ #033
         LITCASE(s, R2_NOTMASKPEN);                                 // REQ #033
         LITCASE(s, R2_XORPEN);                                     // REQ #033
         LITCASE(s, R2_NOTXORPEN);                                  // REQ #033
         DEFNUMCASE(s, dc.GetROP2());                               // REQ #033
        } /* rop2 */                                                // REQ #033
     TRACE(_T("ROP2                 = %s\n"), s);                   // REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // Text color                                                  // REQ #033
     //*************************************************************// REQ #033
     TRACE(_T("Text color           = %s\n"), ToColor(dc.GetTextColor()));// REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // Text alignment                                              // REQ #033
     //*************************************************************// REQ #033
                                                                    // REQ #033
     DWORD align = dc.GetTextAlign();                               // REQ #033
     CString or;                                                    // REQ #033
                                                                    // REQ #033
     TRACE(_T("Text alignment       = "));                          // REQ #033
     if( (align & TA_UPDATECP) == TA_UPDATECP)                      // REQ #033
        { /* updatecp */                                            // REQ #033
         TRACE(_T("TA_UPDATECP"));                                  // REQ #033
         or = _T(" | ");                                            // REQ #033
        } /* updatecp */                                            // REQ #033
                                                                    // REQ #033
     switch(align & (TA_RIGHT | TA_CENTER))                         // REQ #033
        { /* lcr */                                                 // REQ #033
         case TA_RIGHT:                                             // REQ #033
            TRACE(_T("%sTA_RIGHT"), or);                            // REQ #033
            or = _T(" | ");                                         // REQ #033
            break;                                                  // REQ #033
         case TA_CENTER:                                            // REQ #033
            TRACE(_T("%sTA_CENTER"), or);                           // REQ #033
            or = _T(" | ");                                         // REQ #033
            break;                                                  // REQ #033
         case 0:                                                    // REQ #033
            TRACE(_T("%sTA_LEFT"), or);                             // REQ #033
            or = _T(" | ");                                         // REQ #033
            break;                                                  // REQ #033
        } /* lcr */                                                 // REQ #033
                                                                    // REQ #033
     switch(align & (TA_BOTTOM | TA_BASELINE))                      // REQ #033
        { /* tbb */                                                 // REQ #033
         case TA_BOTTOM:                                            // REQ #033
            TRACE(_T("%sTA_BOTTOM"), or);                           // REQ #033
            or = _T(" | ");                                         // REQ #033
            break;                                                  // REQ #033
         case TA_BASELINE:                                          // REQ #033
            TRACE(_T("%sTA_BOTTOM"), or);                           // REQ #033
            or = _T(" | ");                                         // REQ #033
            break;                                                  // REQ #033
         case 0:                                                    // REQ #033
            TRACE(_T("%sTA_TOP"), or);                              // REQ #033
            or = _T(" | ");                                         // REQ #033
            break;                                                  // REQ #033
        } /* tbb */                                                 // REQ #033
                                                                    // REQ #033
     if( (align & TA_RTLREADING) == TA_RTLREADING)                  // REQ #033
        TRACE(_T("%sTA_RTLREADING"), or);                           // REQ #033
                                                                    // REQ #033
     TRACE(_T("\n"));                                               // REQ #033
     //*************************************************************// REQ #033
     // StretchBlt mode                                             // REQ #033
     //*************************************************************// REQ #033
     switch(dc.GetStretchBltMode())                                 // REQ #033
        { /* stretchblt */                                          // REQ #033
         LITCASE(s, STRETCH_ANDSCANS);                              // REQ #033
         LITCASE(s, STRETCH_DELETESCANS);                           // REQ #033
         LITCASE(s, STRETCH_ORSCANS);                               // REQ #033
         DEFNUMCASE(s, dc.GetROP2());                               // REQ #033
        } /* stretchblt */                                          // REQ #033
     TRACE(_T("StretchBlt mode      = %s\n"), s);                   // REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // Layout                                                      // REQ #033
     //*************************************************************// REQ #033
     switch(dc.GetLayout())                                         // REQ #033
        { /* layout */                                              // REQ #033
         LITCASE(s, LAYOUT_BITMAPORIENTATIONPRESERVED);             // REQ #033
         LITCASE(s, LAYOUT_RTL);                                    // REQ #033
         //LITCASE(s, LAYOUT_LTR);                                  // REQ #033
         LITCASE(s, LAYOUT_VBH);                                    // REQ #033
         LITCASE(s, LAYOUT_BTT);                                    // REQ #033
         DEFNUMCASE(s, dc.GetLayout());                             // REQ #033
        } /* layout */                                              // REQ #033
     TRACE(_T("Layout mode          = %s\n"), s);                   // REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // Arc direction                                               // REQ #033
     //*************************************************************// REQ #033
     switch(dc.GetArcDirection())                                   // REQ #033
        { /* arc dir */                                             // REQ #033
         LITCASE(s, AD_COUNTERCLOCKWISE);                           // REQ #033
         LITCASE(s, AD_CLOCKWISE);                                  // REQ #033
         DEFNUMCASE(s, dc.GetArcDirection());                       // REQ #033
        } /* arc dir */                                             // REQ #033
     TRACE(_T("Arc direction        = %s\n"), s);                   // REQ #033
                                                                    // REQ #033
     //*************************************************************// REQ #033
     // Clipping rectangle                                          // REQ #033
     //*************************************************************// REQ #033
                                                                    // REQ #033
     CRect r;                                                       // REQ #033
     dc.GetClipBox(&r);                                             // REQ #033
     TRACE(_T("Clipping rectangle   = [%d, %d, %d, %d]\n"),         // REQ #033
                       r.left, r.top, r.right, r.bottom);           // REQ #033
                                                                    // REQ #033
    } // ShowDCState                                                // REQ #033
                                                                    // REQ #033
    

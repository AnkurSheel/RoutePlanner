/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  4-May-08 | Created change log
*  4-May-08 | REQ #037: Code cleanup
*  8-May-08 | REQ #042: Unicode support
*****************************************************************************/
#include "stdafx.h"
#include "logfont.h"
#include "resource.h"
#include "panose.h"

/****************************************************************************
*                               familyToString
* Inputs:
*       int paf: Pitch and family
* Result: CString
*       
* Effect: 
*       ²
****************************************************************************/

CString familyToString(int paf)
    {
     CString s;
     s = _T("");

     switch(paf & 0xF0)
        { /* family */
#define FFCASE(x) case x: s.Format(_T("%02x ") _T(#x), x)
         FFCASE(FF_DECORATIVE);
         FFCASE(FF_DONTCARE);
         FFCASE(FF_MODERN);
         FFCASE(FF_ROMAN);
         FFCASE(FF_SCRIPT);
         FFCASE(FF_SWISS);
        } /* family */

     return s;
    }

/****************************************************************************
*                                pitchToString
* Inputs:
*       int paf: Pitch and family
* Result: CString
*       
* Effect: 
*       ²
****************************************************************************/

CString pitchToString(int paf, int mask, int id)
    {
     CString s;
     s = _T("");


     if(paf & mask)
        { /* found it */
         CString t;
         t.LoadString(id);
         s.Format(_T("%02x %s"), mask, (LPCTSTR)t);                 // REQ #042
        } /* found it */

     return s;
    }


/****************************************************************************
*                            insertPitchAndFamily
* Inputs:
*       UINT pval: Pitch and family value
*       CTreeCtrl * tc: Tree control
*       HTREEITEM paf: Pitch and family item
* Result: void
*       
* Effect: 
*       Inserts the p-a-f values in the tree at node paf
****************************************************************************/

void insertPitchAndFamily(UINT pval, CTreeCtrl * tc, HTREEITEM paf)
    {
     CString s;
     if(pval != 0)
         { /* has paf */
          int id;
          CString t;
          id = pval;

          t.LoadString(IDS_PITCH);
          HTREEITEM pitch = tc->InsertItem(t, paf);

          s = pitchToString(id, TMPF_FIXED_PITCH, IDS_TMPF_FIXED_PITCH);
          if(!s.IsEmpty())                                          // REQ #037
             tc->InsertItem(s, pitch);

          s = pitchToString(id, TMPF_VECTOR, IDS_TMPF_VECTOR);
          if(!s.IsEmpty())                                          // REQ #037
             tc->InsertItem(s, pitch);

          s = pitchToString(id, TMPF_TRUETYPE, IDS_TMPF_TRUETYPE);
          if(!s.IsEmpty())                                          // REQ #037
             tc->InsertItem(s, pitch);

          s = pitchToString(id, TMPF_DEVICE, IDS_TMPF_DEVICE);
          if(!s.IsEmpty())                                          // REQ #037
             tc->InsertItem(s, pitch);

          if( (id & (TMPF_VECTOR | TMPF_TRUETYPE)) == 0)
             { /* raster */
              CString t;
              t.LoadString(IDS_TMPF_RASTER);
              s.Format(_T("%02x %s"), 0, t);
              tc->InsertItem(s, pitch);
             } /* raster */

          s = familyToString(pval);
          if(!s.IsEmpty())                                          // REQ #037
             tc->InsertItem(s, paf);

         } /* has paf */
     
    }

/****************************************************************************
*                               qualityToString
* Inputs:
*       BYTE lfq: Quality code
* Result: CString
*       
****************************************************************************/

CString qualityToString(BYTE lfq)
    {
     CString s;
     s = _T("");

     switch(lfq)
        { /* lfq */
#define QUALITY_CASE(x) case x: s = _T(#x); break                   // REQ #042
         
         QUALITY_CASE(DEFAULT_QUALITY);                             // REQ #042
         QUALITY_CASE(DRAFT_QUALITY);                               // REQ #042
         QUALITY_CASE(PROOF_QUALITY);                               // REQ #042
         QUALITY_CASE(NONANTIALIASED_QUALITY);                      // REQ #042
         QUALITY_CASE(ANTIALIASED_QUALITY);                         // REQ #042
         QUALITY_CASE(CLEARTYPE_QUALITY);                           // REQ #042
         QUALITY_CASE(CLEARTYPE_NATURAL_QUALITY);                   // REQ #042
#undef QUALITY_CASE                                                 // REQ #042
        } /* lfq */
     return s;
    }

/****************************************************************************
*                            clipprecisionToString
* Inputs:
*       BYTE op: clip precision
* Result: CString
*       
****************************************************************************/

CString clipprecisionToString(BYTE op)
    {
     CString s;
     s = _T("");
     switch(op)
        { /* op */
#define CLIPCASE(x) case x: s = _T(#x); break                       // REQ #042
         CLIPCASE(CLIP_CHARACTER_PRECIS);                           // REQ #042
         CLIPCASE(CLIP_DEFAULT_PRECIS);                             // REQ #042
         CLIPCASE(CLIP_EMBEDDED);                                   // REQ #042
         CLIPCASE(CLIP_LH_ANGLES);                                  // REQ #042
         CLIPCASE(CLIP_MASK);                                       // REQ #042
         CLIPCASE(CLIP_STROKE_PRECIS);                              // REQ #042
         CLIPCASE(CLIP_TT_ALWAYS);                                  // REQ #042
         CLIPCASE(CLIP_DFA_DISABLE);                                // REQ #042
#undef CLIPCASE
        } /* op */
     return s;
    }

/****************************************************************************
*                            outprecisionToString
* Inputs:
*       BYTE op: Output precision
* Result: CString
*       
****************************************************************************/

CString outprecisionToString(BYTE op)
    {
     CString s;
     s = _T("");
     switch(op)
        { /* op */
#define PRECISCASE(x) case x: s = _T(#x); break                     // REQ #042
         PRECISCASE(OUT_CHARACTER_PRECIS);                          // REQ #042
         PRECISCASE(OUT_DEFAULT_PRECIS);                            // REQ #042
         PRECISCASE(OUT_DEVICE_PRECIS);                             // REQ #042
         PRECISCASE(OUT_OUTLINE_PRECIS);                            // REQ #042
         PRECISCASE(OUT_PS_ONLY_PRECIS);                            // REQ #042
         PRECISCASE(OUT_RASTER_PRECIS);                             // REQ #042
         PRECISCASE(OUT_SCREEN_OUTLINE_PRECIS);                     // REQ #042
         PRECISCASE(OUT_STRING_PRECIS);                             // REQ #042
         PRECISCASE(OUT_STROKE_PRECIS);                             // REQ #042
         PRECISCASE(OUT_TT_PRECIS);                                 // REQ #042
         PRECISCASE(OUT_TT_ONLY_PRECIS);                            // REQ #042
#undef PRECISCASE                                                   // REQ #042
        } /* op */
     return s;
    }

/****************************************************************************
*                               charsetToString
* Inputs:
*       BYTE cs: charset code
* Result: CString
*       
****************************************************************************/

CString charsetToString(BYTE cs)
    {
     CString s;
     s = _T("");

     switch(cs)
        { /* cs */
#define CHARSETCASE(x) case x: s = _T(#x); break                    // REQ #042
         CHARSETCASE(ANSI_CHARSET);                                 // REQ #042
         CHARSETCASE(DEFAULT_CHARSET);                              // REQ #042
         CHARSETCASE(SYMBOL_CHARSET);                               // REQ #042
         CHARSETCASE(SHIFTJIS_CHARSET);                             // REQ #042
         CHARSETCASE(OEM_CHARSET);                                  // REQ #042
#undef CHARSETCASE                                                  // REQ #042
        } /* cs */
     return s;
    }

/****************************************************************************
*                               weightToString
* Inputs:
*       int weight: Weight of font
* Result: CString
*       String representing the weight
* Effect: 
*       ²
****************************************************************************/

CString weightToString(int weight)
    {
     switch(weight)
        { /* tmWeight */
#define FWCASE(x) case x: return CString(_T(#x))
         FWCASE(FW_DONTCARE);
         FWCASE(FW_THIN);
         FWCASE(FW_EXTRALIGHT);
         FWCASE(FW_LIGHT);
         FWCASE(FW_NORMAL);
         FWCASE(FW_MEDIUM);
         FWCASE(FW_SEMIBOLD);
         FWCASE(FW_BOLD);
         FWCASE(FW_EXTRABOLD);
         FWCASE(FW_HEAVY);
#undef FWCASE
        } /* tmWeight */

     int low = (weight / 100) * 100;
     int high = low / 100;

     if(FW_DONTCARE <= low && low <= FW_BLACK &&
        FW_DONTCARE <= high && high <= FW_BLACK)
           { /* make range */
            CString s;
            s.Format(_T("%s..%s"), weightToString(low), weightToString(high));
            return s;
           } /* make range */

     return _T("");
    }

/****************************************************************************
*                                 loadLogFont
* Inputs:
*       LOGFONT * lf: Font descriptor
*       CTreeCtrl * tc: Tree control
*       BOOL exlf: TRUE if structure passed in is an ExtLogFont, FALSE 
*                               otherwise
* Result: HTREEITEM
*       Handle to LOGFONT item
* Effect: 
*       Loads the LOGFONT information
****************************************************************************/

HTREEITEM loadLogFont(LOGFONT * lf, CTreeCtrl * tc, BOOL exlf)
    {
     CString s;
     
     HTREEITEM lfi;

#if 0
     if(exlf)
        lfi = tc->InsertItem(_T("EXTLOGFONT"));
     else
        lfi = tc->InsertItem(_T("LOGFONT"));
#else
     lfi = tc->InsertItem(_T("LOGFONT"));
#endif

     s.Format(_T("lfHeight %d"), lf->lfHeight);
     tc->InsertItem(s, lfi);

     s.Format(_T("lfWidth %d"), lf->lfWidth);
     tc->InsertItem(s, lfi);

     s.Format(_T("lfEscapement %d"), lf->lfEscapement);
     tc->InsertItem(s, lfi);
     
     s.Format(_T("lfOrientation %d"), lf->lfOrientation);
     tc->InsertItem(s, lfi);

     s.Format(_T("lfWeight %d"), lf->lfWeight);
     HTREEITEM wt = tc->InsertItem(s, lfi);
     s = weightToString(lf->lfWeight);
     if(!s.IsEmpty())                                               // REQ #037
        tc->InsertItem(s, wt);

     s.Format(_T("lfItalic %d"), lf->lfItalic);
     tc->InsertItem(s, lfi);

     s.Format(_T("lfUnderline %d"), lf->lfUnderline);
     tc->InsertItem(s, lfi);

     s.Format(_T("lfStrikeOut %d"), lf->lfStrikeOut);
     tc->InsertItem(s, lfi);

     s.Format(_T("lfCharSet %d"), lf->lfCharSet);
     HTREEITEM cs = tc->InsertItem(s, lfi);
        s = charsetToString(lf->lfCharSet);
        tc->InsertItem(s, cs);
        

     s.Format(_T("lfOutPrecision %d"), lf->lfOutPrecision);
     HTREEITEM op = tc->InsertItem(s, lfi);
        s = outprecisionToString(lf->lfOutPrecision);
        tc->InsertItem(s, op);

     s.Format(_T("lfClipPrecision %d"), lf->lfClipPrecision);
     HTREEITEM cp = tc->InsertItem(s, lfi);
         s = clipprecisionToString(lf->lfClipPrecision);
         tc->InsertItem(s, cp);

     s.Format(_T("lfQuality %d"), lf->lfQuality);
     HTREEITEM q = tc->InsertItem(s, lfi);
         s = qualityToString(lf->lfQuality);
         tc->InsertItem(s, q);

     s.Format(_T("lfPitchAndFamily 0x%02x"), lf->lfPitchAndFamily);
     HTREEITEM paf = tc->InsertItem(s, lfi);
     insertPitchAndFamily(lf->lfPitchAndFamily, tc, paf);

     s.Format(_T("lfFaceName \"%s\""), lf->lfFaceName);
     tc->InsertItem(s, lfi);

#if 0
     if(tt)
        { /* TrueType */
         LPEXTLOGFONT elf = (LPEXTLOGFONT)lf;
         
         s.Format(_T("elfFullName \"%s\""), elf->elfFullName);
         tc->InsertItem(s, lfi);

         s.Format(_T("elfStyle \"%s\""), elf->elfStyle);
         tc->InsertItem(s, lfi);

         s.Format(_T("elfVersion %d"), elf->elfVersion);
         tc->InsertItem(s, lfi);

         s.Format(_T("elfStyleSize %d"), elf->elfStyleSize);
         tc->InsertItem(s, lfi);

         s.Format(_T("elfMatch %d"), elf->elfMatch);
         tc->InsertItem(s, lfi);

         s.Format(_T("elfStyleSize %d"), elf->elfStyleSize);
         tc->InsertItem(s, lfi);

         s.Format(_T("elfVendorId %d = [0x%02x 0x%02x 0x%02x 0x%02x]"), 
                                elf->elfVendorId,
                                LOBYTE(LOWORD(elf->elfVendorId)),
                                HIBYTE(LOWORD(elf->elfVendorId)),
                                LOBYTE(HIWORD(elf->elfVendorId)),
                                HIBYTE(HIWORD(elf->elfVendorId)));
         tc->InsertItem(s, lfi);


         s.Format(_T("elfCulture %d"), elf->elfCulture);
         tc->InsertItem(s, lfi);
         
         HTREEITEM pi = tc->InsertItem(_T("elfPanose"), lfi);
         loadPanose(tc, pi, &elf->elfPanose);
        } /* TrueType */
#endif

     return lfi;
    }

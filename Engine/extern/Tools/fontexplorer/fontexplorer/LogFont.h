/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  2-Nov-08 | Created change log
*  2-Nov-08 | REQ #007: Added #pragma once
*****************************************************************************/

#pragma once                                                        // REQ #007

HTREEITEM loadLogFont(LOGFONT * lf, CTreeCtrl * tc, BOOL exlf);
CString weightToString(int weight);
CString charsetToString(BYTE cs);
CString outprecisionToString(BYTE op);
CString clipprecisionToString(BYTE op);
CString qualityToString(BYTE lfq);
void insertPitchAndFamily(UINT pval, CTreeCtrl * tc, HTREEITEM paf);
CString pitchToString(int paf, int mask, int id);
CString familyToString(int paf);

/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 24-Apr-08 | Created
* 24-Apr-08 | REQ #007: Added #pragma once
*  4-May-08 | REQ #035: Allow for GM_ADVANCED mode
* 22-Oct-08 | REQ #071: Added support for font smoothing option
* 23-Oct-08 | REQ #073: Added support for pair-kerning disable
*****************************************************************************/

#pragma once                                                        // REQ #007

class CFontDescriptor {
        public:
                CFontDescriptor(CWnd * wnd, CWnd * fontwnd = NULL, BOOL advanced = FALSE, DWORD quality = 0); // REQ #035// REQ #071
                ~CFontDescriptor();
                CFont * font;
                CDC * dc;
                LOGFONT lf;
                TEXTMETRIC tm;
                OUTLINETEXTMETRIC * otm;
                ABC abc;
                COLORREF color;
                DWORD GetFontLanguageInfo();                        // REQ #073
        private:
                int saved;
              };

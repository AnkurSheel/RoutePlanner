/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 24-Apr-08 | Created
* 24-Apr-08 | REQ #007: Added #pragma once
* 24-Apr-08 | REQ #010: Made display_options a class, added constructor
* 25-Apr-08 | REQ #011: Support multiple output modes to handle pair-kerning
* 27-Apr-08 | REQ #017: Add option to support detection of pair kerning
* 28-Apr-08 | REQ #022: Support vertical offset
* 29-Apr-08 | REQ #031: Option to ignore ABC widths
* 21-Oct-08 | REQ #066: Added ShowPath option
*  2-Nov-08 | REQ #081: Changed name from TEXTOUTEX to EXTTEXTOUT_
*****************************************************************************/

#pragma once                                                        // REQ #007

class display_options {
    public:
        typedef enum {NONE, TEXTOUT, EXTTEXTOUT_, IGNOREABC} OutputOptions; // REQ #011// REQ #031
        display_options() {                                         // REQ #010
           debug = FALSE;                                           // REQ #010
           hrule = FALSE;                                           // REQ #010
           vrule = FALSE;                                           // REQ #010
           chrule = FALSE;                                          // REQ #010
           colors = FALSE;                                          // REQ #010
           white = FALSE;                                           // REQ #010
           track = FALSE;                                           // REQ #010
           trackval = 0;                                            // REQ #010
           kerning = FALSE;                                         // REQ #010
           output = NONE;                                           // REQ #010
           advanced = FALSE;                                        // REQ #018
           DetectPairKerning = FALSE;                               // REQ #017
           VerticalOffset = 0;                                      // REQ #022
           ShowOverlay = TRUE;                                      // REQ #066
           ShowPixels = TRUE;                                       // REQ #066
           quality = 0;                                             // REQ #070
           OverlayX = 0;                                            // REQ #066
           OverlayY = 0;                                            // REQ #066
        }                                                           // REQ #010
        BOOL debug;             // debug mode enabled

        BOOL hrule;             // display horizontal rule
        BOOL vrule;             // display vertical rule
        BOOL chrule;            // display character rule

        BOOL colors;            // use colors for regions       
        BOOL white;             // use white background

        BOOL track;             // enable track kerning
        int  trackval;          // track kerning value (ignored if track FALSE)

        BOOL kerning;           // enable pair kerning
        BOOL ShowOverlay;       // enable path display              // REQ #066
        BOOL ShowPixels;                                            // REQ #066
        BOOL quality;                                               // REQ #070

        BOOL advanced;          // Use GM_ADVANCED                  // REQ #018
        OutputOptions output;                                       // REQ #011
        BOOL DetectPairKerning;                                     // REQ #017
        int VerticalOffset;                                         // REQ #022
        int OverlayX;                                               // REQ #066
        int OverlayY;                                               // REQ #066
//      BOOL basal;             // Use basal TextOut algorithm      // REQ #011
};

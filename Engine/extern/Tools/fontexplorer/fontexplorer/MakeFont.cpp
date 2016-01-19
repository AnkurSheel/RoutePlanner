/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  8-May-08 | Created change log
*  8-May-08 | REQ #042: Unicode conversion
*****************************************************************************/
#include "stdafx.h"
#include "errors.h"

#include "makefont.h"

/****************************************************************************
*                                  MakeFont
* Inputs:
*       CFont * font: Font descriptor
*       LPCSTR facename: Font face name
*       int height: Font height, in points
*       int weight: Font weight, FW_REGULAR or FW_BOLD
*       CDC * dc: Screen or printer DC for creating font
* Result: BOOL
*       TRUE if successful
*       FALSE if error
* Effect: 
*       Creates a font of the correct size for the device
* Notes:
*       Unlike previous edition of the code, this version actually knows
*       how to compute a font height correctly!
****************************************************************************/

BOOL MakeFont(CFont * font, LPCTSTR face, int height, int weight, CDC * dc)  // REQ #042
    {
     int factor = dc->GetDeviceCaps(LOGPIXELSX);
     int fontheight = -MulDiv(height, 72, factor);

     return font->CreateFont( fontheight,       // height
                              0,                // width 
                              0,                // escapement
                              0,                // rotation
                              weight,           // weight
                              0,                // italic
                              0,                // underline
                              0,                // strikeout
                              DEFAULT_CHARSET,  // character set
                              OUT_DEVICE_PRECIS,// precision
                              0,                // clip precision
                              PROOF_QUALITY,    // quality
                              VARIABLE_PITCH | FF_DONTCARE, // pitch and family
                              face);
    }

/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 21-Oct-08 | REQ #066: Created
*****************************************************************************/
#include "stdafx.h"
#include "bitmap.h"


/****************************************************************************
*                                  CreateBmp
* Inputs:
*       CDC & dc: DC to use
*       CSize sz: Size of bitmap
*       BOOL DIB: TRUE to create a DIBsection, FALSE to create a compatible bitmap
* Result: HBITMAP
*       A bitmap object
* Effect: 
*       Creates a bitmap
****************************************************************************/

HBITMAP CreateBmp(CDC & dc, CSize sz, BOOL DIB)
   {
    if(!DIB)
       { /* compatible */
       HBITMAP bmp = ::CreateCompatibleBitmap(dc, sz.cx, sz.cy);
        return bmp;
       } /* compatible */

    // Create a DIB
    BITMAPINFO bmpinfo;
    bmpinfo.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmpinfo.bmiHeader.biWidth = sz.cx;
    bmpinfo.bmiHeader.biHeight = sz.cy;
    bmpinfo.bmiHeader.biPlanes = 1;
    bmpinfo.bmiHeader.biBitCount = 24;
    bmpinfo.bmiHeader.biCompression = BI_RGB;
    bmpinfo.bmiHeader.biSizeImage = 0; // can be 0 for BI_RGB
    bmpinfo.bmiHeader.biClrUsed = 0;
    LPVOID bits; // will be ignored

    HBITMAP bmp = ::CreateDIBSection(dc, &bmpinfo, DIB_RGB_COLORS, &bits, NULL, 0);
    return bmp;
   } // CreateBmp

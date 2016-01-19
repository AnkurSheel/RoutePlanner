#include "stdafx.h"
#include "ToString.h" 


/****************************************************************************
*                                   ToString
* Inputs:
*       LPCTSTR fmt: Format code
*       DWORD value: Value to format
* Result: CString
*
* Effect:
*       The value formatted to a string
****************************************************************************/

CString ToString(LPCTSTR fmt, ...)
   {
    va_list args;
    va_start(args,fmt);

    CString s;
    s.FormatV(fmt, args);
    va_end(args);

    return s;
   } // ToString

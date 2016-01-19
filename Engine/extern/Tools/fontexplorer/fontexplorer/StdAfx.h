/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 23-Apr-08 | Created
* 23-Apr-08 | REQ #006: Changes required for 64-bit compatibility
* 23-Apr-08 | REQ #009: Defined _WIN32_IE
*  1-May-08 | REQ #033: Added WINVER so proper symbols are defined
*  4-May-08 | REQ #037: Support for flyover help
* 15-Oct-08 | REQ #042: Upgrade to VS2005
*****************************************************************************/
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers

#define _WIN32_IE 0x0600                                            // REQ #009
#define WINVER 0x0600                                               // REQ #033// REQ #042
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxtempl.h>                                               // REQ #037





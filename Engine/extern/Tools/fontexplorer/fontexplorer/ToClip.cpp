/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 29-Apr-08 | Created
* 29-Apr-08 | REQ #029: Allow clipping area of window's client area
*****************************************************************************/
#include "stdafx.h"
#include "toclip.h" 


/****************************************************************************
*                                 toClipboard
* Inputs:
*       CWnd * wnd: Window to clip
*       const CRect & bb: Clipping rectangle
*       BOOL FullWnd (=FALSE): TRUE to clip entire window, FALSE for just client area
* Result: void
*       
* Effect: 
*       Copies the specified area of the window to the clipboard
****************************************************************************/

void toClipboard(CWnd * wnd, const CRect & bb, BOOL FullWnd /* = FALSE */)                      // REQ #029
    {                                                                // REQ #029
     CDC dc;

     if(FullWnd)
        { /* full window */
         HDC hdc = ::GetWindowDC(wnd->m_hWnd);
         dc.Attach(hdc);
        } /* full window */
     else
        { /* client area only */
         HDC hdc = ::GetDC(wnd->m_hWnd);
         dc.Attach(hdc);
        } /* client area only */

     CDC memDC;
     memDC.CreateCompatibleDC(&dc);

     CBitmap bm;

     CString s;
     wnd->GetWindowText(s);

     CSize sz(bb.Width(), bb.Height());

     bm.CreateCompatibleBitmap(&dc, sz.cx, sz.cy);

     CBitmap * oldbm = memDC.SelectObject(&bm);

     memDC.BitBlt(0, 0, sz.cx, sz.cy, &dc, bb.left, bb.top, SRCCOPY);

     wnd->GetParent()->OpenClipboard();
     ::EmptyClipboard();
     ::SetClipboardData(CF_BITMAP, bm.m_hObject);
     CloseClipboard();

     memDC.SelectObject(oldbm);
     bm.Detach();  // make sure bitmap not deleted with CBitmap object
    } // toClipboard                                                // REQ #029

/****************************************************************************
*                                 toClipboard
* Inputs:
*       CWnd * wnd: Window whose contents are to be sent to clipboard
*       BOOL FullWnd: TRUE for entire window, FALSE for client area
* Result: void
*       
* Effect: 
*       Copies the contents of the client area or the window to the clipboard
*       in CF_BITMAP format.
****************************************************************************/

void toClipboard(CWnd * wnd, BOOL FullWnd)
    {
     CRect r;

     if(FullWnd)
        { /* entire window */                                       // REQ #029
         wnd->GetWindowRect(&r);
         wnd->ScreenToClient(&r);                                   // REQ #029
        } /* entire window */                                       // REQ #029
     else
        { /* client only */
         wnd->GetClientRect(&r);
        } /* client only */

     toClipboard(wnd, r, FullWnd);                                  // REQ #029
    }

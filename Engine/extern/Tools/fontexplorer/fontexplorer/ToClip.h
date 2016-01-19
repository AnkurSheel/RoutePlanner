/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 29-Apr-08 | Created
* 29-Apr-08 | REQ #029: Allow selective clipping of a window's client area
* 29-Apr-08 | REQ #007: Added #pragma once
* 29-Apr-08 | REQ #030: Default FullWnd parameter to FALSE
*****************************************************************************/
#pragma once

void toClipboard(CWnd * wnd, BOOL FullWnd = FALSE);                 // REQ #029
void toClipboard(CWnd * wnd, const CRect & bb, BOOL FullWnd = FALSE); // REQ #029

/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 24-Apr-08 | Created
* 24-Apr-08 | REQ #008: Removed FontExplorer.h
* 25-Apr-08 | REQ #012: Resize child window
* 19-Oct-08 | REQ #061: Remove FWS_ADDTOTITLE style
*****************************************************************************/
// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "resource.h"                                               // REQ #008

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
        //{{AFX_MSG_MAP(CChildFrame)
                // NOTE - the ClassWizard will add and remove mapping macros here.
                //    DO NOT EDIT what you see in these blocks of generated code !
        //}}AFX_MSG_MAP
        ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
        // TODO: add member initialization code here
        
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
   {
    cs.style &= ~FWS_ADDTOTITLE;                                    // REQ #061
    return CMDIChildWnd::PreCreateWindow(cs);
   }

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
        CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
        CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::OnSize(UINT nType, int cx, int cy)                // REQ #012
    {                                                               // REQ #012
     CMDIChildWnd::OnSize(nType, cx, cy);                           // REQ #012
                                                                    // REQ #012
     if(nType == SIZE_MINIMIZED)                                    // REQ #012
        return;                                                     // REQ #012
                                                                    // REQ #012
     // Just to be safe, make sure it is a CFormView                // REQ #012
     CWnd * wnd = GetWindow(GW_CHILD);                              // REQ #012
     ASSERT(wnd->IsKindOf(RUNTIME_CLASS(CFormView)));               // REQ #012
     if(!wnd->IsKindOf(RUNTIME_CLASS(CFormView)))                   // REQ #012
        return;                                                     // REQ #012
                                                                    // REQ #012
     wnd->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOZORDER);// REQ #012
                                                                    // REQ #012
    }                                                               // REQ #012

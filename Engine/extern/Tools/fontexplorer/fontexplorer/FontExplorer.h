/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 18-Oct-08 | Created change log
* 18-Oct-08 | REQ #005: Made Kerning Explorer be a view
* 18-Oct-08 | REQ #053: Made LogFontExplorer be a view
* 18-Oct-08 | REQ #054: Make RasterExplorer be a view
* 19-Oct-08 | REQ #055: Make Stock Font be a view
* 19-Oct-08 | REQ #056: free up templates on completion
* 31-Oct-08 | REQ #078: Added CFontDialogExplorer
*  2-Nov-08 | REQ #087: Added FontExplorerTemplate to template set
*****************************************************************************/
// FontExplorer.h : main header file for the FONTEXPLORER application
//

#ifndef __AFXWIN_H__
        #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFontExplorerApp:
// See FontExplorer.cpp for the implementation of this class
//

class CFontExplorerApp : public CWinApp {
    public:
       CFontExplorerApp();

// Overrides
// ClassWizard generated virtual function overrides
//{{AFX_VIRTUAL(CFontExplorerApp)
    public:
       virtual BOOL InitInstance();
       virtual int ExitInstance();                                  // REQ #056
//}}AFX_VIRTUAL

// Implementation
    protected:
       CMultiDocTemplate * FontExplorerTemplate;                    // REQ #087
       CMultiDocTemplate * KerningExplorerTemplate;                 // REQ #005
       CMultiDocTemplate * GetCharacterPlacementTemplate;
       CMultiDocTemplate * LogFontExplorerTemplate;                 // REQ #053
       CMultiDocTemplate * RasterExplorerTemplate;                  // REQ #054
       CMultiDocTemplate * StockFontTemplate;                       // REQ #055
       CMultiDocTemplate * FontDialogExplorerTemplate;              // REQ #078
       CDocument * NewItem(CMultiDocTemplate * templ);
    protected:
       //{{AFX_MSG(CFontExplorerApp)
       afx_msg void OnAppAbout();
       afx_msg void OnFontexplorer();
       afx_msg void OnLogfont();
       afx_msg void OnFontsetup();
       afx_msg void OnKernexp();
       afx_msg void OnGetcharplacement();
       afx_msg void OnUpdateGetcharplacement(CCmdUI* pCmdUI);
       afx_msg void OnRaster();
       afx_msg void OnStockfont();
       afx_msg void OnGetCFontDialogExplorer();                     // REQ #078
       //}}AFX_MSG
       DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

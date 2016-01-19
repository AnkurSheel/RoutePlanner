/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 23-Apr-08 | Created
* 23-Apr-08 | REQ #002: Handle Init3dControls
* 23-Apr-08 | REQ #005: Added Kerning Explorer as MDI page, converted
*           | GetCharacterPlacement to MDI page x
*  8-May-08 | REQ #042: Unicode conversion
* 18-Oct-08 | REQ #053: Made LogFontExplorer be a view
* 18-Oct-08 | REQ #054: Make RasterExplorer be a view
* 19-Oct-08 | REQ #055: Make Stock Font be a view
* 19-Oct-08 | REQ #056: Free up templates to avoid memory leak reports
* 31-Oct-08 | REQ #078: Added CFontDialog/ChooseFont explorer
*  1-Nov-08 | REQ #080: FontDisp.h => FontDisplay.h
*  2-Nov-08 | REQ #084: Renamed StockFnt.* to StockFont.*
*  2-Nov-08 | REQ #087: Explicitly delete FontExplorerTemplate since it is
*           | no longer added as a document template
*  2-Nov-08 | REQ #088: Removed FontSel dialog
*****************************************************************************/
// FontExplorer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FontExplorer.h"
#include <dlgs.h>

#include "IntEdit.h"
#include "about.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "FontExplorerDoc.h"
#include "FontExplorerView.h"
#include "KerningExplorer.h"                                        // REQ #005
#include "GetCharacterPlacement.h"                                  // REQ #005

#include "poplist.h"
#include "legendi.h"
#include "legend.h"
#include "dispopts.h"
#include "fontdesc.h"
//#include "fontmet.h"                                              // REQ #088
#include "fontdisplay.h"                                            // REQ #080
#include "fontexp.h"
#include "idcombo.h"
#include "degrees.h"
#include "rotation.h"
#include "message.h"
#include "sample.h"
#include "fontname.h"
#include "LogFontExplorer.h"
//#include "fontobj.h"                                              // REQ #088
//#include "fontsel.h"                                              // REQ #088
//#include "fontopt.h"                                              // REQ #088
//#include "kerning.h"                                              // REQ #005
//#include "cplace.h"
#include "raster.h"
#include "stockFont.h"                                              // REQ #084
#include "FontDialogExplorer.h"                                     // REQ #078

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//static CFontObj InfoFontObj(_T("Info"), MAKEINTRESOURCE(IDS_FONTINFO), NULL); // REQ #042 // REQ #088


/////////////////////////////////////////////////////////////////////////////
// CFontExplorerApp

BEGIN_MESSAGE_MAP(CFontExplorerApp, CWinApp)
        //{{AFX_MSG_MAP(CFontExplorerApp)
        ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
        ON_COMMAND(IDM_FONTEXPLORER, OnFontexplorer)
        ON_COMMAND(IDM_LOGFONT, OnLogfont)
//        ON_COMMAND(IDM_FONTSETUP, OnFontsetup)
        ON_COMMAND(IDM_KERNEXP, OnKernexp)
        ON_COMMAND(IDM_GETCHARPLACEMENT, OnGetcharplacement)
        ON_COMMAND(IDM_CFONTDIALOG_EXPLORER, OnGetCFontDialogExplorer)// REQ #078
        ON_COMMAND(ID_RASTER, OnRaster)
        ON_COMMAND(IDM_STOCKFONT, OnStockfont)
        //}}AFX_MSG_MAP
        // Standard file based document commands
        ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
        ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
        // Standard print setup command
        ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontExplorerApp construction

CFontExplorerApp::CFontExplorerApp()
   {
    StockFontTemplate = NULL;                                       // REQ #056
    RasterExplorerTemplate = NULL;                                  // REQ #056
    GetCharacterPlacementTemplate = NULL;                           // REQ #056
    LogFontExplorerTemplate = NULL;                                 // REQ #056
    KerningExplorerTemplate = NULL;                                 // REQ #056
    FontDialogExplorerTemplate = NULL;                              // REQ #078
    FontExplorerTemplate = NULL;                                    // REQ #087
   }

/////////////////////////////////////////////////////////////////////////////
// The one and only CFontExplorerApp object

CFontExplorerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFontExplorerApp initialization

BOOL CFontExplorerApp::InitInstance()
{
        // Standard initialization
        // If you are not using these features and wish to reduce the size
        //  of your final executable, you should remove from the following
        //  the specific initialization routines you do not need.

#if _MSC_VER < 1300                                                 // REQ #002
#ifdef _AFXDLL
        Enable3dControls();                     // Call this when using MFC in a shared DLL
#else
        Enable3dControlsStatic();       // Call this when linking to MFC statically
#endif
#endif                                                              // REQ #002
        LoadStdProfileSettings();  // Load standard INI file options (including MRU)

        // Register the application's document templates.  Document templates
        //  serve as the connection between documents, frame windows and views.

        FontExplorerTemplate = new CMultiDocTemplate(               // REQ #087
                IDR_FONTEXTYPE,
                RUNTIME_CLASS(CFontExplorerDoc),
                RUNTIME_CLASS(CChildFrame), // custom MDI child frame
                RUNTIME_CLASS(CFontExplorerView));

        KerningExplorerTemplate = new CMultiDocTemplate(            // REQ #005
           IDR_KERNINGEXPLORER,                                     // REQ #005
           RUNTIME_CLASS(CFontExplorerDoc),                         // REQ #005
           RUNTIME_CLASS(CChildFrame),                              // REQ #005
           RUNTIME_CLASS(CKerningExplorer));                        // REQ #005

        LogFontExplorerTemplate = new CMultiDocTemplate(            // REQ #053
           IDR_LOGFONTEXPLORER,                                     // REQ #053
           RUNTIME_CLASS(CFontExplorerDoc),                         // REQ #053
           RUNTIME_CLASS(CChildFrame),                              // REQ #053
           RUNTIME_CLASS(CLogFontExplorer));                        // REQ #053
        
        GetCharacterPlacementTemplate = new CMultiDocTemplate(      // REQ #005
           IDR_GETCHARACTERPLACEMENT,                               // REQ #005
           RUNTIME_CLASS(CFontExplorerDoc),                         // REQ #005
           RUNTIME_CLASS(CChildFrame),                              // REQ #005
           RUNTIME_CLASS(CGetCharacterPlacement));                  // REQ #005

        RasterExplorerTemplate = new CMultiDocTemplate(             // REQ #054
           IDR_RASTEREXPLORER,                                      // REQ #054
           RUNTIME_CLASS(CFontExplorerDoc),                         // REQ #054
           RUNTIME_CLASS(CChildFrame),                              // REQ #054
           RUNTIME_CLASS(CRaster));                                 // REQ #054

        StockFontTemplate = new CMultiDocTemplate(                  // REQ #055
           IDR_STOCKFONTEXPLORER,                                   // REQ #055
           RUNTIME_CLASS(CFontExplorerDoc),                         // REQ #055
           RUNTIME_CLASS(CChildFrame),                              // REQ #055
           RUNTIME_CLASS(CStockFont));                              // REQ #055

        FontDialogExplorerTemplate = new CMultiDocTemplate(         // REQ #078
           IDR_FONTDIALOGEXPLORER,                                  // REQ #078
           RUNTIME_CLASS(CFontExplorerDoc),                         // REQ #078
           RUNTIME_CLASS(CChildFrame),                              // REQ #078
           RUNTIME_CLASS(CFontDialogExplorer));                     // REQ #078
        
//        AddDocTemplate(pDocTemplate);                             // REQ #005

        // create main MDI Frame window
        CMainFrame* pMainFrame = new CMainFrame;
        if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
                return FALSE;
        m_pMainWnd = pMainFrame;

        // Parse command line for standard shell commands, DDE, file open
        CCommandLineInfo cmdInfo;
        ParseCommandLine(cmdInfo);

        // Dispatch commands specified on the command line
        if(cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
           cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing; 

        if (!ProcessShellCommand(cmdInfo))
                return FALSE;

        // The main window has been initialized, so show and update it.
        pMainFrame->ShowWindow(m_nCmdShow);
        pMainFrame->UpdateWindow();

        return TRUE;
}

/****************************************************************************
*                       CFontExplorerApp::ExitInstance
* Result: int
*       Return type
* Effect: 
*       Frees up templates
****************************************************************************/

int CFontExplorerApp::ExitInstance()                                // REQ #056
    {                                                               // REQ #056
     delete FontExplorerTemplate;                                   // REQ #087
     delete StockFontTemplate;                                      // REQ #056
     delete RasterExplorerTemplate;                                 // REQ #056
     delete GetCharacterPlacementTemplate;                          // REQ #056
     delete LogFontExplorerTemplate;                                // REQ #056
     delete KerningExplorerTemplate;                                // REQ #056
     delete FontDialogExplorerTemplate;                             // REQ #078
     return 0;                                                      // REQ #056
    } // CFontExplorerApp::ExitInstance                             // REQ #056

/****************************************************************************
*                        CFontExplorerApp::OnAppAbout
* Result: void
*       
* Effect: 
*       Creates an About dialog
****************************************************************************/

void CFontExplorerApp::OnAppAbout()
   {
    CAbout aboutDlg;
    aboutDlg.DoModal();
   }

/////////////////////////////////////////////////////////////////////////////
// CFontExplorerApp commands


/****************************************************************************
*                       CFontExplorerApp::OnFontexplorer
* Result: void
*       
* Effect: 
*       ¶
****************************************************************************/

void CFontExplorerApp::OnFontexplorer() 
{
 CFontExplorer dlg;

 dlg.m_cf.lpTemplateName = MAKEINTRESOURCE(FORMATDLGORD31);
 dlg.m_cf.hInstance = AfxGetInstanceHandle();
 dlg.m_cf.Flags |= CF_ENABLETEMPLATE;
 dlg.DoModal();
}


/****************************************************************************
*                         CFontExplorerApp::OnLogfont
* Result: void
*       
* Effect: 
*       ¶
****************************************************************************/

void CFontExplorerApp::OnLogfont() 
   {
    //CLogFontExplorer dlg;                                         // REQ #053
    //dlg.DoModal();                                                // REQ #053
    NewItem(LogFontExplorerTemplate);                               // REQ #053
}


/****************************************************************************
*                        CFontExplorerApp::OnFontsetup
* Result: void
*       
* Effect: 
*       Sets font options
****************************************************************************/

void CFontExplorerApp::OnFontsetup() 
{
// FontOptions(AfxGetMainWnd());  
}

/****************************************************************************
*                          CFontExplorerApp::NewItem
* Inputs:
*       CMultiDocTemplate * templ
* Result: void
*       
* Effect: 
*       Creates a new doc/view pair based on the template
****************************************************************************/

CDocument * CFontExplorerApp::NewItem(CMultiDocTemplate * templ)    // REQ #005
    {                                                               // REQ #005
     CDocument * doc = templ->CreateNewDocument();                  // REQ #005
     ASSERT(doc != NULL);                                           // REQ #005
     if(doc == NULL)                                                // REQ #005
        return NULL;                                                // REQ #005
                                                                    // REQ #005
     CFrameWnd * frame = templ->CreateNewFrame(doc, NULL);          // REQ #005
     if(frame == NULL)                                              // REQ #005
        { /* failed to create */                                    // REQ #005
         delete doc;                                                // REQ #005
         return NULL;                                               // REQ #005
        } /* failed to create */                                    // REQ #005
                                                                    // REQ #005
     templ->InitialUpdateFrame(frame, doc, TRUE);                   // REQ #005
     return doc;                                                    // REQ #005
    } // CFontExplorerApp::NewItem                                  // REQ #005


/****************************************************************************
*                         CFontExplorerApp::OnKernexp
* Result: void
*       
* Effect: 
*       Creates a new kering explorer dialog
****************************************************************************/

void CFontExplorerApp::OnKernexp() 
   {
    // CKerning dlg;                                                // REQ #005
    // dlg.DoModal();                                               // REQ #005
    NewItem(KerningExplorerTemplate);                               // REQ #005
}

/****************************************************************************
*                    CFontExplorerApp::OnGetcharplacement
* Result: void
*       
* Effect: 
*       Launches a GetCharPlacement explorer
****************************************************************************/

void CFontExplorerApp::OnGetcharplacement() 
   {
    // CCharacterPlacement dlg;                                     // REQ #005
    //dlg.DoModal();                                                // REQ #005
    NewItem(GetCharacterPlacementTemplate);                         // REQ #005
   }

/****************************************************************************
*                         CFontExplorerApp::OnRaster
* Result: void
*       
* Effect: 
*       Shows the raster font explorer
****************************************************************************/

void CFontExplorerApp::OnRaster() 
   {
    // CRaster dlg;                                                 // REQ #054
    // dlg.DoModal();                                               // REQ #054
    NewItem(RasterExplorerTemplate);                                // REQ #054
   }

/****************************************************************************
*                        CFontExplorerApp::OnStockFont
* Result: void
*       
* Effect: 
*       Shows the "stock font" selector
****************************************************************************/

void CFontExplorerApp::OnStockfont() 
   {
    //CStockFont dlg;                                               // REQ #055
    //dlg.DoModal();                                                // REQ #055
    NewItem(StockFontTemplate);                                     // REQ #055
}

/****************************************************************************
*                 CFontExplorerApp::OnGetCFontDialogExplorer
* Result: void
*       
* Effect: 
*       Creates a new CHOOSEFONT/CFontDialog explorer
****************************************************************************/

void CFontExplorerApp::OnGetCFontDialogExplorer()                   // REQ #078
    {                                                               // REQ #078
     NewItem(FontDialogExplorerTemplate);                           // REQ #078
    } // CFontExplorerApp::OnGetCFontDialogExplorer                 // REQ #078



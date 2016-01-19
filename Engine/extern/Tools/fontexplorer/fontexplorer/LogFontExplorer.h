/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 15-Oct-08 | Created change log
* 15-Oct-08 | REQ #045: Added code display and resizing
* 18-Oct-08 | REQ #053: Made it a view
* 19-Oct-08 | REQ #058: Allow sample text change
* 19-Oct-08 | REQ #059: Show Grid for origin
* 19-Oct-08 | REQ #060: Control TextOut alignment
*  2-Nov-08 | REQ #083: Added copy button
*  2-Nov-08 | REQ #088: Removed fontmet.h
*  4-Nov-08 | REQ #090: Allow "locking" orientation and escapement
*****************************************************************************/
// LogFontExplorer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogFontExplorer dialog
#include "IDCombo.h"                                                // REQ #060
#include "degrees.h"
#include "rotation.h"
#include "message.h"
#include "sample.h"
#include "fontname.h"
//#include "fontmet.h"                                              // REQ #088
#include "ImageButton.h"                                            // REQ #083
#include "LockButton.h"                                             // REQ #090


class CLogFontExplorer : public CFormView // CDialog                // REQ #053
{
    DECLARE_DYNCREATE(CLogFontExplorer)
// Construction
public:
        CLogFontExplorer();   // standard constructor               // REQ #053
        virtual ~CLogFontExplorer();                                // REQ #053
// Dialog Data
        enum { IDD = IDD_LOGFONT };
#ifdef _DEBUG
        virtual void AssertValid() const;
        virtual void Dump(CDumpContext& dc) const;
#endif

protected:
        void ResizeWindows();                                       // REQ #045

//        CFontMetrics    c_Data;                                   // REQ #088
        CTreeCtrl c_Data;                                           // REQ #088
        CFontName       c_lfFaceName;
        CSample c_Sample;
        CMessage        c_Result;
        CEdit   c_lfWidth;
        CEdit   c_lfHeight;
        CDegrees        c_lfEscapement;
        CDegrees        c_lfOrientation;
        CRotation       c_SpinOrientation;
        CRotation       c_SpinEscapement;
        CStatic c_c_lfOrientation;
        CButton c_GM_ADVANCED;
        CIDCombo        c_lfFamily;
        CIDCombo        c_lfPitch;
        CIDCombo        c_lfWeight;
        CIDCombo        c_lfQuality;
        CIDCombo        c_lfOutPrecision;
        CIDCombo        c_lfCharSet;
        CIDCombo        c_lfClipPrecision;
        CButton c_lfUnderline;
        CButton c_lfItalic;
        CButton c_lfStrikeOut;
        CStatic c_Frame;                                            // REQ #045
        CEdit   c_Code;                                             // REQ #045
        CIDCombo c_Language;                                        // REQ #045
        CButton c_ShowZero;                                         // REQ #045
        CEdit   c_Text;                                             // REQ #058
        CButton  c_ShowGrid;                                        // REQ #059
        CIDCombo c_Vert;                                            // REQ #060
        CIDCombo c_Horz;                                            // REQ #060
        CImageButton c_Copy;                                        // REQ #083
        CLockButton c_Locked;                                       // REQ #090


// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CLogFontExplorer)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

// Implementation
protected:
        LOGFONT lf;
        HFONT font;
        void updateFont();                                          // REQ #057
        
        static int CALLBACK LoadFontProc(const LOGFONT * elf, const TEXTMETRIC * ntm, DWORD type, LPARAM lParam); // REQ #053
        int vgap;                                                   // REQ #045
        int hgap;                                                   // REQ #045
        BOOL initialized;                                           // REQ #045
        void updateControls();                                      // REQ #045
        CFont CodeFont;                                             // REQ #045

        void setMessage(DWORD result);
        BOOL Is95();
        void controls_to_lf();
        BOOL AvoidLockedControlRecursion;                           // REQ #090

        void updateCode();                                          // REQ #045
        // Generated message map functions
        virtual void OnInitialUpdate();                             // REQ #053
        afx_msg void OnEnChangelfHeight();                          // REQ #045
        afx_msg void OnEnChangelfWidth();                           // REQ #045
        afx_msg void OnEnChangelfEscapement();                      // REQ #045
        afx_msg void OnEnChangelfOrientation();                     // REQ #045
        afx_msg void OnBnClickedlfItalic();                         // REQ #045
        afx_msg void OnBnClickedlfUnderline();                      // REQ #045
        afx_msg void OnBnClickedlfStrikeout();                      // REQ #045
        afx_msg void OnCbnSelendOkLanguage();                       // REQ #045
        afx_msg void OnCbnSelendOkWeight();                         // REQ #045
        afx_msg void OnCbnSelendOkCharSet();                        // REQ #045
        afx_msg void OnCbnSelendOkOutPrecision();                   // REQ #045
        afx_msg void OnCbnSelendOkClipPrecision();                  // REQ #045
        afx_msg void OnCbnSelendOkFaceName();                       // REQ #045
        afx_msg void OnCbnSelendOkQuality();                        // REQ #045
        afx_msg void OnCbnSelendOkPitch();                          // REQ #045
        afx_msg void OnCbnSelendOkFamily();                         // REQ #045
        afx_msg void OnBnClickedShowZero();                         // REQ #045
        afx_msg void OnDestroy();
        afx_msg void OnCbnSelendokLffamily();                       // REQ #045
        afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        afx_msg void OnGmAdvanced();
        afx_msg void    OnSize(UINT nType, int cx, int cy);         // REQ #045
        afx_msg void    OnGetMinMaxInfo(MINMAXINFO* lpMMI);         // REQ #045
        afx_msg void OnEnChangeText();                              // REQ #058
        afx_msg void OnBnClickedShowGrid();                         // REQ #059
        afx_msg void OnCbnSelendOkHorz();                           // REQ #060
        afx_msg void OnCbnSelendOkVert();                           // REQ #060
        afx_msg void OnBnClickedCopy();                             // REQ #083
        afx_msg void OnBnClickedLock();                             // REQ #090
        DECLARE_MESSAGE_MAP()
              
};

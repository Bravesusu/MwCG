// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MwCG.h"

#include "MainFrm.h"
#include "MwNumberEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_WINDOWS_7);

	CreateDocumentColors();
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	//BOOL bNameValid;

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // other styles available...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // set to FALSE to place close button at right of tab area
	mdiTabParams.m_bTabIcons = FALSE;    // set to TRUE to enable document icons on MDI taba
	mdiTabParams.m_bAutoColor = TRUE;    // set to FALSE to disable auto-coloring of MDI tabs
	mdiTabParams.m_bDocumentMenu = TRUE; // enable the document menu at the right edge of the tab area
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!CreateStatusBar())
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!CreateDynamicRibbon())
	{
		TRACE0("Failed to create dynamic ribbon components\n");
		return -1;      // fail to create
	}

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Navigation pane will be created at left, so temporary disable docking at the left side:
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

#ifdef MW_ENABLE_NAVIGATION_BAR
	// Create and setup "Outlook" navigation bar:
	if (!CreateOutlookBar(m_wndNavigationBar, ID_VIEW_NAVIGATION, m_wndTree, m_wndCalendar, 250))
	{
		TRACE0("Failed to create navigation pane\n");
		return -1;      // fail to create
	}
#endif

//#ifdef MW_ENABLE_CAPTION_BAR
	// Create a caption bar:
	if (!CreateCaptionBar())
	{
		TRACE0("Failed to create caption bar\n");
		return -1;      // fail to create
	}
//#endif

	// Outlook bar is created and docking on the left side should be allowed.
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);

	// Load menu item image (not placed on any standard toolbars):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// create docking windows
	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}
	
#ifdef MW_ENABLE_FILE_VIEW
	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
#endif
	
#ifdef MW_ENABLE_CLASS_VIEW
	m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
#endif
	
#ifdef MW_ENABLE_FILE_VIEW
	DockPane(&m_wndFileView);
	CDockablePane* pTabbedBar = NULL;
#ifdef MW_ENABLE_CLASS_VIEW
	m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
#endif
#endif

#ifdef MW_ENABLE_CLASS_VIEW
#ifndef MW_ENABLE_FILE_VIEW
	DockPane(&m_wndClassView);
#endif
#endif
	
#ifdef MW_ENABLE_OUTPUT
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
#endif

	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

	// Enable enhanced windows management dialog
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// Switch the order of document name and application name on the window title bar. This
	// improves the usability of the taskbar because the document name is visible with the thumbnail.
	ModifyStyle(0, FWS_PREFIXTITLE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

#ifdef MW_ENABLE_CLASS_VIEW
	// Create class view
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Class View window\n");
		return FALSE; // failed to create
	}
#endif

#ifdef MW_ENABLE_FILE_VIEW
	// Create file view
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create File View window\n");
		return FALSE; // failed to create
	}
#endif

#ifdef MW_ENABLE_OUTPUT
	// Create output window
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Output window\n");
		return FALSE; // failed to create
	}
#endif

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
#ifdef MW_ENABLE_FILE_VIEW
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);
#endif

#ifdef MW_ENABLE_OUTPUT
	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);
#endif

#ifdef MW_ENABLE_OUTPUT	
	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);
#endif

	UpdateMDITabbedBarsIcons();
}

BOOL CMainFrame::CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CMFCShellTreeCtrl& tree, CCalendarBar& calendar, int nInitialWidth)
{
	bar.SetMode2003();

	BOOL bNameValid;
	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_SHORTCUTS);
	ASSERT(bNameValid);
	if (!bar.Create(strTemp, this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		return FALSE; // fail to create
	}

	CMFCOutlookBarTabCtrl* pOutlookBar = (CMFCOutlookBarTabCtrl*)bar.GetUnderlyingWindow();

	if (pOutlookBar == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	pOutlookBar->EnableInPlaceEdit(TRUE);

	static UINT uiPageID = 1;

	// can float, can autohide, can resize, CAN NOT CLOSE
	DWORD dwStyle = AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE;

	CRect rectDummy(0, 0, 0, 0);
	const DWORD dwTreeStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	tree.Create(dwTreeStyle, rectDummy, &bar, 1200);
	bNameValid = strTemp.LoadString(IDS_FOLDERS);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&tree, strTemp, 2, TRUE, dwStyle);

	calendar.Create(rectDummy, &bar, 1201);
	bNameValid = strTemp.LoadString(IDS_CALENDAR);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&calendar, strTemp, 3, TRUE, dwStyle);

	bar.SetPaneStyle(bar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	pOutlookBar->SetImageList(theApp.m_bHiColorIcons ? IDB_PAGES_HC : IDB_PAGES, 24);
	pOutlookBar->SetToolbarImageList(theApp.m_bHiColorIcons ? IDB_PAGES_SMALL_HC : IDB_PAGES_SMALL, 16);
	pOutlookBar->RecalcLayout();

	BOOL bAnimation = theApp.GetInt(_T("OutlookAnimation"), TRUE);
	CMFCOutlookBarTabCtrl::EnableAnimation(bAnimation);

	bar.SetButtonsFont(&afxGlobalData.fontBold);

	return TRUE;
}

BOOL CMainFrame::CreateCaptionBar()
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("Failed to create caption bar\n");
		return FALSE;
	}

	BOOL bNameValid;

	CString strTemp, strTemp2;
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);

	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
	ASSERT(bNameValid);
	bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}
#ifdef MW_ENABLE_OUTPUT	
	m_wndOutput.UpdateFonts();
#endif
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}

void CMainFrame::OnOptions()
{
	CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
	ASSERT(pOptionsDlg != NULL);

	pOptionsDlg->DoModal();
	delete pOptionsDlg;
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CMDIFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}


void CMainFrame::SetCaptionBarText(const CString& strText)
{
	//TODO: bug here. Not updating
	m_wndCaptionBar.SetText(strText);
	m_wndCaptionBar.RedrawWindow();
}

BOOL CMainFrame::CreateDynamicRibbon(void)
{
	CMFCRibbonCategory* pInsert = m_wndRibbonBar.GetCategory(1);
	CMFCRibbonPanel* pPanel = pInsert->GetPanel(2);
	CMFCRibbonColorButton* pColorBtn = CreateRibbonColorButton(ID_BUTTON_COLOR);
	pPanel->Add(pColorBtn);

	CMFCRibbonCategory* pCanvas = m_wndRibbonBar.GetCategory(3);
	CMFCRibbonPanel* pCvsPanel = pCanvas->GetPanel(0);
	CMFCRibbonColorButton* pCvsColorBtn = CreateRibbonColorButton(ID_CLEAR_COLOR);
	pCvsPanel->Add(pCvsColorBtn);

	
	/*CMFCRibbonCategory* pFloatyCate = m_wndRibbonBar.getcontext(_T("Floaty"), _T("Floaty"), ID_TEMP_CATEGORY, AFX_CategoryColor_Yellow, 0, 0);

	CMFCRibbonPanel* pPosPanel = pFloatyCate->AddPanel(_T("Pos"));
	CMFCRibbonEdit* pXEdit = new CMFCRibbonEdit(ID_EDIT_POS_X, 50, _T("X"));
	CMFCRibbonEdit* pYEdit = new CMFCRibbonEdit(ID_EDIT_POS_Y, 50, _T("Y"));

	pPosPanel->Add(pXEdit);
	pPosPanel->Add(pYEdit);*/

	//CMFCRibbonComboBox* pStrokeList = theApp.FindRibbonUIById<CMFCRibbonComboBox>(ID_STROKE_GALLERY);
	//pStrokeList->SelectItem(0);

	return TRUE;
}

BOOL CMainFrame::CreateStatusBar(void)
{
	BOOL bNameValid;

	if (!m_wndStatusBar.Create(this))
	{
		return FALSE;      // fail to create
	}

	CString strPosPanel;
	CString strRectPanel;
	CString strProgress;
	CString strZoomBtn;
	CString strZoomSlider;
	CString strUiMode;

	bNameValid = strPosPanel.LoadString(IDS_STATUS_POS);
	ASSERT(bNameValid);
	bNameValid =strRectPanel.LoadString(IDS_STATUS_RECT);
	ASSERT(bNameValid);
	bNameValid = strProgress.LoadString(IDS_STATUS_PROGRESS);
	ASSERT(bNameValid);
	bNameValid = strZoomBtn.LoadString(IDS_STATUS_ZOOM);
	ASSERT(bNameValid);
	bNameValid = strZoomSlider.LoadString(IDS_STATUS_ZOOM_SLIDER);
	ASSERT(bNameValid);
	bNameValid = strUiMode.LoadString(IDS_STATUS_MODE);
	ASSERT(bNameValid);

	//TODO: check CMFCRibbonCustomizeDialog

	m_wndStatusBar.AddElement(
		new CMFCRibbonStatusBarPane(IDS_STATUS_MODE, strUiMode, TRUE, 0, _T("Long name")),
		strUiMode
		);

	m_wndStatusBar.AddSeparator();

	m_wndStatusBar.AddElement(
		new CMFCRibbonStatusBarPane(IDS_STATUS_POS, _T("0, 0"), TRUE, 0, _T("000000000.000000000, 000000000.000000000")),
		strPosPanel
		);
	m_wndStatusBar.AddSeparator();

	m_wndStatusBar.AddElement(
		new CMFCRibbonStatusBarPane(IDS_STATUS_RECT, _T("(0, 0)x(0, 0)"), TRUE, 0, _T("(0000.0000, 0000.0000)x(0000.0000, 0000.0000)")),
		strPosPanel
		);
	m_wndStatusBar.AddSeparator();

	m_wndStatusBar.AddExtendedElement(
		new CMFCRibbonStatusBarPane(IDS_STATUS_ZOOM, _T("100%"), FALSE, 0, _T("1000%")), 
		strZoomBtn);
	CMFCRibbonSlider* pSlider = new CMFCRibbonSlider(IDS_STATUS_ZOOM_SLIDER);
	pSlider->SetZoomButtons();
	pSlider->SetRange(10, 200);
	pSlider->SetPos(100);

	m_wndStatusBar.AddExtendedElement(pSlider, strZoomSlider);

	return TRUE;
}

void CMainFrame::CreateDocumentColors()
{
	typedef struct
	{
		COLORREF color;
		TCHAR* szName;
	}
	ColorTableEntry;

	int i = 0;
	int nNumColours = 0;

	static ColorTableEntry colorsMain [] = 
	{
		{	RGB (255, 255, 255),	_T("White, Background 1")	},
		{	RGB (0, 0, 0),			_T("Black, Text 1")			},
		{	RGB (238, 236, 225),	_T("Tan, Background 2")		},
		{	RGB (31, 73, 125),		_T("Dark Blue, Text 2")		},
		{	RGB (79, 129, 189),		_T("Blue, Accent 1")		},
		{	RGB (192, 80, 77),		_T("Red, Accent 2")			},
		{	RGB (155, 187, 89),		_T("Olive Green, Accent 3")	},
		{	RGB (128, 100, 162),	_T("Purple, Accent 4")		},
		{	RGB (75, 172, 198),		_T("Aqua, Accent 5")		},
		{	RGB (245, 150, 70),		_T("Orange, Accent 6")		}
	};

	static ColorTableEntry colorsAdditional [] = 
	{
		{	RGB (242, 242, 242),	_T("White, Background 1, Darker 5%")	},
		{	RGB (127, 127, 127),	_T("Black, Text 1, Lighter 50%")		},
		{	RGB (214, 212, 202),	_T("Tan, Background 2, Darker 10%")		},
		{	RGB (210, 218, 229),	_T("Dark Blue, Text 2, Lighter 80%")	},
		{	RGB (217, 228, 240),	_T("Blue, Accent 1, Lighter 80%")		},
		{	RGB (244, 219, 218),	_T("Red, Accent 2, Lighter 80%")		},
		{	RGB (234, 241, 221),	_T("Olive Green, Accent 3, Lighter 80%")},
		{	RGB (229, 223, 235),	_T("Purple, Accent 4, Lighter 80%")		},
		{	RGB (216, 237, 242),	_T("Aqua, Accent 5, Lighter 80%")		},
		{	RGB (255, 234, 218),	_T("Orange, Accent 6, Lighter 80%")		},

		{	RGB (215, 215, 215),	_T("White, Background 1, Darker 15%")	},
		{	RGB (89, 89, 89),		_T("Black, Text 1, Lighter 35%")		},
		{	RGB (177, 176, 167),	_T("Tan, Background 2, Darker 25%")		},
		{	RGB (161, 180, 201),	_T("Dark Blue, Text 2, Lighter 60%")	},
		{	RGB (179, 202, 226),	_T("Blue, Accent 1, Lighter 60%")		},
		{	RGB (233, 184, 182),	_T("Red, Accent 2, Lighter 60%")		},
		{	RGB (213, 226, 188),	_T("Olive Green, Accent 3, Lighter 60%")},
		{	RGB (203, 191, 215),	_T("Purple, Accent 4, Lighter 60%")		},
		{	RGB (176, 220, 231),	_T("Aqua, Accent 5, Lighter 60%")		},
		{	RGB (255, 212, 181),	_T("Orange, Accent 6, Lighter 60%")		},

		{	RGB (190, 190, 190),	_T("White, Background 1, Darker 25%")	},
		{	RGB (65, 65, 65),		_T("Black, Text 1, Lighter 25%")		},
		{	RGB (118, 117, 112),	_T("Tan, Background 2, Darker 35%")		},
		{	RGB (115, 143, 175),	_T("Dark Blue, Text 2, Lighter 40%")	},
		{	RGB (143, 177, 213),	_T("Blue, Accent 1, Lighter 40%")		},
		{	RGB (222, 149, 147),	_T("Red, Accent 2, Lighter 40%")		},
		{	RGB (192, 213, 155),	_T("Olive Green, Accent 3, Lighter 40%")},
		{	RGB (177, 160, 197),	_T("Purple, Accent 4, Lighter 40%")		},
		{	RGB (137, 203, 218),	_T("Aqua, Accent 5, Lighter 40%")		},
		{	RGB (255, 191, 145),	_T("Orange, Accent 6, Lighter 40%")		},

		{	RGB (163, 163, 163),	_T("White, Background 1, Darker 35%")	},
		{	RGB (42, 42, 42),		_T("Black, Text 1, Lighter 15%")		},
		{	RGB (61, 61, 59),		_T("Tan, Background 2, Darker 50%")		},
		{	RGB (20, 57, 92),		_T("Dark Blue, Text 2, Darker 25%")		},
		{	RGB (54, 96, 139),		_T("Blue, Accent 1, Darker 25%")		},
		{	RGB (149, 63, 60),		_T("Red, Accent 2, Darker 25%")			},
		{	RGB (114, 139, 71),		_T("Olive Green, Accent 3, Darker 25%")	},
		{	RGB (97, 76, 119),		_T("Purple, Accent 4, Darker 25%")		},
		{	RGB (41, 128, 146),		_T("Aqua, Accent 5, Darker 25%")		},
		{	RGB (190, 112, 59),		_T("Orange, Accent 6, Darker 25%")		},

		{	RGB (126, 126, 126),	_T("White, Background 1, Darker 50%")	},
		{	RGB (20, 20, 20),		_T("Black, Text 1, Lighter 5%")			},
		{	RGB (29, 29, 28),		_T("Tan, Background 2, Darker 90%")		},
		{	RGB (17, 40, 64),		_T("Dark Blue, Text 2, Darker 50%")		},
		{	RGB (38, 66, 94),		_T("Blue, Accent 1, Darker 50%")		},
		{	RGB (100, 44, 43),		_T("Red, Accent 2, Darker 50%")			},
		{	RGB (77, 93, 49),		_T("Olive Green, Accent 3, Darker 50%")	},
		{	RGB (67, 53, 81),		_T("Purple, Accent 4, Darker 50%")		},
		{	RGB (31, 86, 99),		_T("Aqua, Accent 5, Darker 50%")		},
		{	RGB (126, 77, 42),		_T("Orange, Accent 6, Darker 50%")		},
	};

	static ColorTableEntry colorsStandard [] = 
	{
		{	RGB (200, 15, 18),		_T("Dark Red")		},
		{	RGB (255, 20, 24),		_T("Red")			},
		{	RGB (255, 191, 40),		_T("Orange")		},
		{	RGB (255, 255, 49),		_T("Yellow")		},
		{	RGB (138, 207, 87),		_T("Light Green")	},
		{	RGB (0, 175, 84),		_T("Green")			},
		{	RGB (0, 174, 238),		_T("Light Blue")	},
		{	RGB (0, 111, 189),		_T("Blue")			},
		{	RGB (0, 36, 95),		_T("Black")			},
		{	RGB (114, 50, 157),		_T("Purple")		},
	};

	m_lstMainColors.RemoveAll();
	nNumColours = sizeof(colorsMain) / sizeof(ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstMainColors.AddTail(colorsMain [i].color);
		CMFCRibbonColorButton::SetColorName(colorsMain [i].color, colorsMain [i].szName);
	};

	m_lstAdditionalColors.RemoveAll();
	nNumColours = sizeof(colorsAdditional) / sizeof(ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstAdditionalColors.AddTail(colorsAdditional [i].color);
		CMFCRibbonColorButton::SetColorName(colorsAdditional [i].color, colorsAdditional [i].szName);
	};

	m_lstStandardColors.RemoveAll();
	nNumColours = sizeof(colorsStandard) / sizeof(ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstStandardColors.AddTail(colorsStandard [i].color);
		CMFCRibbonColorButton::SetColorName(colorsStandard [i].color, colorsStandard [i].szName);
	};
}

void CMainFrame::ActivateContextCategory( UINT uiCategoryID, bool active )
{
	m_wndRibbonBar.ShowContextCategories(uiCategoryID);
	if (active)
	{
		m_wndRibbonBar.ActivateContextCategory(uiCategoryID);
	}
	//if (uiCategoryID == ID_CONTEXT_ELEMENT)
	//{
	//	CMFCRibbonCategory* pElement = DYNAMIC_DOWNCAST(CMFCRibbonCategory, m_wndRibbonBar.FindByID(ID_CONTEXT_ELEMENT));
	//	TRACE("Panel#%d\n", pElement->GetPanelCount());
	//}
}

void CMainFrame::HideContextCategory( UINT uiCategoryID )
{
	m_wndRibbonBar.ShowContextCategories(uiCategoryID, 0);
}

CMFCRibbonColorButton* CMainFrame::CreateRibbonColorButton( UINT nCmdId )
{
	CMFCRibbonColorButton* pColorBtn = new CMFCRibbonColorButton(nCmdId, _T("Color"), 0, 0);
	pColorBtn->EnableAutomaticButton(_T("&Automatic"), RGB(0, 0, 0));
	pColorBtn->EnableOtherButton(_T("&More Colors..."), _T("More Colors"));
	pColorBtn->SetColumns(10);
	pColorBtn->SetColor(RGB(255, 0, 0));
	pColorBtn->SetColorBoxSize(CSize(32, 32));

	pColorBtn->AddColorsGroup(_T("Theme Colors"), m_lstMainColors);
	pColorBtn->AddColorsGroup(_T(""), m_lstAdditionalColors, TRUE /* Contiguous Columns*/);
	pColorBtn->AddColorsGroup(_T("Standard Colors"), m_lstStandardColors);
	return pColorBtn;
}

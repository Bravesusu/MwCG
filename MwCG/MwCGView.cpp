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

// MwCGView.cpp : implementation of the CMwCGView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MwCG.h"
#endif

#include "MwCGDoc.h"
#include "MwCGView.h"

#include "MwCanvas.h"
#include "PointTool.h"
#include "LineTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMwCGView

IMPLEMENT_DYNCREATE(CMwCGView, CView)

	BEGIN_MESSAGE_MAP(CMwCGView, CView)
		// Standard printing commands
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMwCGView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_WM_CREATE()
		ON_WM_DESTROY()
		ON_WM_SIZE()
		ON_WM_ERASEBKGND()
		ON_UPDATE_COMMAND_UI(ID_CLEAR_COLOR, &CMwCGView::OnUpdateClearColor)
		//		ON_COMMAND(ID_CANVAS_HEIGHT, &CMwCGView::OnCanvasHeight)
		//ON_COMMAND(ID_CANVAS_WIDTH, &CMwCGView::OnCanvasWidth)
		//ON_COMMAND(ID_CANVAS_HEIGHT, &CMwCGView::OnCanvasHeight)
		ON_UPDATE_COMMAND_UI(ID_SHAPE_GALLERY, &CMwCGView::OnUpdateShapeGallery)
		ON_WM_MOUSEMOVE()
		ON_UPDATE_COMMAND_UI(IDS_STATUS_POS, &CMwCGView::OnUpdateIdsStatusPos)
		ON_UPDATE_COMMAND_UI(IDS_STATUS_ZOOM, &CMwCGView::OnUpdateIdsStatusZoom)
		//ON_COMMAND(IDS_STATUS_ZOOM_SLIDER, &CMwCGView::OnIdsStatusZoomSlider)
		ON_UPDATE_COMMAND_UI(IDS_STATUS_ZOOM_SLIDER, &CMwCGView::OnUpdateIdsStatusZoomSlider)
		ON_COMMAND(IDS_STATUS_ZOOM_SLIDER, &CMwCGView::OnIdsStatusZoomSlider)
//		ON_WM_MBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_WM_LBUTTONDOWN()
		ON_WM_KEYDOWN()
		ON_WM_KEYUP()
		ON_UPDATE_COMMAND_UI(IDS_STATUS_MODE, &CMwCGView::OnUpdateIdsStatusMode)
//		ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CMwCGView::OnUpdateFilePrintPreview)
ON_UPDATE_COMMAND_UI(ID_CHECK_GIRD, &CMwCGView::OnUpdateCheckGird)
ON_UPDATE_COMMAND_UI(IDS_STATUS_RECT, &CMwCGView::OnUpdateIdsStatusRect)
ON_COMMAND(ID_EDIT_UNDO, &CMwCGView::OnEditUndo)
ON_COMMAND(ID_EDIT_REDO, &CMwCGView::OnEditRedo)
ON_COMMAND(ID_TOOL_SELECT, &CMwCGView::OnToolSelect)
ON_UPDATE_COMMAND_UI(ID_TOOL_SELECT, &CMwCGView::OnUpdateToolSelect)
ON_COMMAND(ID_SHAPE_GALLERY, &CMwCGView::OnShapeGallery)
	END_MESSAGE_MAP()

	// CMwCGView construction/destruction

	CMwCGView::CMwCGView()
	{
		// TODO: add construction code here
	}

	CMwCGView::~CMwCGView()
	{
	}

	BOOL CMwCGView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: Modify the Window class or styles here by modifying
		//  the CREATESTRUCT cs

		cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
		return CView::PreCreateWindow(cs);
	}

	// CMwCGView drawing

	void CMwCGView::OnDraw(CDC* pDC)
	{
		CMwCGDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: add draw code for native data here
		if (m_render.IsValid())
		{
			m_render.Draw(content_);
			m_render.Draw(uiState_);
			SwapBuffers(pDC->GetSafeHdc());
		}
	}


	// CMwCGView printing


	void CMwCGView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CMwCGView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// default preparation
		return DoPreparePrinting(pInfo);
	}

	void CMwCGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: add extra initialization before printing
	}

	void CMwCGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: add cleanup after printing
	}

	void CMwCGView::OnRButtonUp(UINT  nFlags , CPoint point)
	{
		uiState_->OnRButtonUp(nFlags, point);
		//ClientToScreen(&point);
		//OnContextMenu(this, point);
	}

	void CMwCGView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// CMwCGView diagnostics

#ifdef _DEBUG
	void CMwCGView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CMwCGView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CMwCGDoc* CMwCGView::GetDocument() const // non-debug version is inline
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMwCGDoc)));
		return (CMwCGDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CMwCGView message handlers


	int CMwCGView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;

		//Get DC and initialize the MwGLRenderer
		//TODO: check result
		m_bMouseDown = false;
		zoom_level_ = 100;
		HWND hWnd = GetSafeHwnd();  
		m_hDC = ::GetDC(hWnd);
		if (!m_render.Initialize(m_hDC))
		{
			CString strInitFailed;
			BOOL bStrValid = strInitFailed.LoadStringW(ID_RENDER_INIT_FAILED);
			ASSERT(bStrValid);

			CMainFrame* pMainFrm = (CMainFrame*)GetParent();
			pMainFrm->SetCaptionBarText(strInitFailed);
		}
		CMwCGDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return -1;

		//state_.Initilize(this, pDoc);
		uiNavState_.reset(new UiNav());
		uiEditState_.reset(new UiEdit());
		uiNavState_->Initialize(pDoc, this);
		uiEditState_->Initialize(pDoc, this);
		
		toolPoint_.reset(new PointTool());
		toolLine_.reset(new LineTool());

		SwitchToEditMode();

		return 0;
	}


	void CMwCGView::OnDestroy()
	{
		CView::OnDestroy();

		//Finalize the MwGLRenderer
		m_render.Finalize();
		::ReleaseDC(GetSafeHwnd(), m_hDC);
	}


	void CMwCGView::OnSize(UINT nType, int cx, int cy)
	{
		CView::OnSize(nType, cx, cy);

		// TODO: Add your message handler code here
		//m_render.SetViewSize(cx, cy);
		//m_render.SetViewSize(0, 0, cx, cy);

		CMwCGDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		shared_ptr<GlContent> pGlContent = pDoc->glContent();
		shared_ptr<GlScreen> scr = pGlContent->screen();
		scr->set(cx, cy);
		scr->update_xy();
	}


	BOOL CMwCGView::OnEraseBkgnd(CDC* pDC)
	{
		// TODO: Add your message handler code here and/or call default

		//return CView::OnEraseBkgnd(pDC);
		return TRUE;
	}


	void CMwCGView::OnInitialUpdate()
	{
		CView::OnInitialUpdate();

		// TODO: Add your specialized code here and/or call the base class
		CMFCRibbonColorButton* pColorBtn = theApp.GetClearColorButton();

		CMwCGDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		content_ = pDoc->glContent();
		screen_ = content_->screen();
		canvas_ = content_->canvas();
		pColorBtn->SetColor(canvas_->color().get_color_ref());

		CRect rect;
		GetClientRect(rect);

		shared_ptr<GlScreen> scr = content_->screen();
		scr->set(rect.Width(), rect.Height());
		scr->set_xy(0, 0, 1);

		//m_render.SetViewSize(0, 0, rect.Width(), rect.Height());
	}


	void CMwCGView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
	{
		// TODO: Add your specialized code here and/or call the base class

		CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

		if (bActivate)
		{
			m_render.Activate(m_hDC);
		}
	}

	void CMwCGView::OnUpdateClearColor(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_render.IsValid());
	}


	void CMwCGView::OnUpdateCanvasWidth(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(FALSE);
	}


	void CMwCGView::OnUpdateCanvasHeight(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(FALSE);
	}


	void CMwCGView::OnUpdateShapeGallery(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_render.IsValid());
	}


	void CMwCGView::OnUpdateIdsStatusPos(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_render.IsValid());
		CString strPos;
		strPos.Format(_T("%.4f, %.4f"), mouse_xy_.x(), mouse_xy_.y());
		pCmdUI->SetText(strPos);
	}


	void CMwCGView::OnUpdateIdsStatusZoom(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		//pCmdUI->Enable(m_render.IsValid());
		CString strZoom;
		strZoom.Format(_T("%d%%"), zoom_level_);
		pCmdUI->SetText(strZoom);
	}


	void CMwCGView::OnUpdateIdsStatusZoomSlider(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_render.IsValid());
	}


	void CMwCGView::OnUpdateIdsStatusMode(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->SetText(uiState_->name());
	}

	void CMwCGView::OnIdsStatusZoomSlider()
	{
		// TODO: Add your command handler code here
		CMFCRibbonStatusBar* pStatusBar = (CMFCRibbonStatusBar*) AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
		ASSERT_VALID(pStatusBar);
		CMFCRibbonSlider* pSlider = DYNAMIC_DOWNCAST(CMFCRibbonSlider, pStatusBar->FindByID(IDS_STATUS_ZOOM_SLIDER));
		ASSERT_VALID(pSlider);
		zoom_level_ = pSlider->GetPos();

		CMwCGDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		float zoom_scale(100 / (float)zoom_level_);

		screen_->set_scale(zoom_scale);

		Invalidate();
	}


//	void CMwCGView::OnMButtonDown(UINT nFlags, CPoint point)
//	{
//		// TODO: Add your message handler code here and/or call default
//
//		CView::OnMButtonDown(nFlags, point);
//
//		
//	}


	void CMwCGView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: Add your message handler code here and/or call default

		CView::OnLButtonUp(nFlags, point);

		uiState_->OnLButtonUp(nFlags, point);

		m_bMouseDown = false;

		//FooFloaty(point);
	}


	void CMwCGView::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: Add your message handler code here and/or call default

		CView::OnMouseMove(nFlags, point);

		uiState_->OnMouseMove(nFlags, point);

		/*CMwCGDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
		return;*/

		mouse_xy_ = screen_->ScreenToXY(point.x, point.y);

		Invalidate();
	}


	void CMwCGView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: Add your message handler code here and/or call default

		CView::OnLButtonDown(nFlags, point);

		uiState_->OnLButtonDown(nFlags, point);

		//CMwCGDoc* pDoc = GetDocument();
		//ASSERT_VALID(pDoc);
		//if (!pDoc)
			//return;

		m_bMouseDown = true;
	}


	void CMwCGView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		// TODO: Add your message handler code here and/or call default

		uiState_->OnKeyDown(nChar, nRepCnt, nFlags);

		CView::OnKeyDown(nChar, nRepCnt, nFlags);
	}


	void CMwCGView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		// TODO: Add your message handler code here and/or call default

		uiState_->OnKeyUp(nChar, nRepCnt, nFlags);

		CView::OnKeyUp(nChar, nRepCnt, nFlags);
	}

	void CMwCGView::SwitchToEditMode()
	{
		//TODO: assert current state
		uiState_ = uiEditState_;
	}

	void CMwCGView::SwitchToNavMode()
	{
		//TODO: assert current state
		uiState_ = uiNavState_;
	}



//	void CMwCGView::OnUpdateFilePrintPreview(CCmdUI *pCmdUI)
//	{
//		// TODO: Add your command update UI handler code here
//	}


	void CMwCGView::OnUpdateCheckGird(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_render.IsValid());
		pCmdUI->SetCheck(canvas_->gird_enabled());
	}


	void CMwCGView::OnUpdateIdsStatusRect(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_render.IsValid());
		CString strRect;
		strRect.Format(
			_T("(%4.4f, %4.4f)x(%4.4f, %4.4f)"), 
			screen_->top(),
			screen_->left(),
			screen_->right(),
			screen_->bottom() 
			);
		pCmdUI->SetText(strRect);
	}

	void CMwCGView::FooFloaty( CPoint point )
	{
		CMFCRibbonMiniToolBar* pFloaty = new CMFCRibbonMiniToolBar;

		InitFloaty(pFloaty);

		ClientToScreen(&point);
		pFloaty->Show(point.x, point.y);
	}

	void CMwCGView::InitFloaty( CMFCRibbonMiniToolBar* pFloaty )
	{
		ASSERT_VALID(pFloaty);

		CList<UINT, UINT> lstCmds;
		lstCmds.AddTail(ID_EDIT_PASTE);
		lstCmds.AddTail(ID_SHAPE_GALLERY);
		lstCmds.AddTail(ID_CHECK_GIRD);
		lstCmds.AddTail(ID_EDIT_POS_X);
		lstCmds.AddTail(ID_EDIT_POS_Y);
		pFloaty->SetCommands(((CMainFrame*) GetTopLevelFrame())->GetRibbonBar(), lstCmds);
	}


	void CMwCGView::OnEditUndo()
	{
		// TODO: Add your command handler code here
		CMwCGDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		pDoc->Undo();

		Invalidate();
	}


	void CMwCGView::OnEditRedo()
	{
		// TODO: Add your command handler code here
		CMwCGDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		
		pDoc->Redo();
		Invalidate();
	}


	void CMwCGView::OnToolSelect()
	{
		// TODO: Add your command handler code here
		uiEditState_->use_selector();
	}


	void CMwCGView::OnUpdateToolSelect(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_render.IsValid());
	}


	void CMwCGView::OnShapeGallery()
	{
		// TODO: Add your command handler code here
		int shape_index = CMFCRibbonGallery::GetLastSelectedItem(ID_SHAPE_GALLERY);
		switch (shape_index)
		{
		case 0:
			uiEditState_->set_tool(toolPoint_);
			break;
		case 1:
			uiEditState_->set_tool(toolLine_);
			break;
		default:
			break;
		}
	}

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

#include "MwMiniToolBar.h"

#include "MwCGDoc.h"
#include "MwCGView.h"

#include "MwGlScreen.h"

#include "MwCanvas.h"
#include "PointTool.h"
//#include "LineTool.h"
#include "CircleTool.h"
#include "PolygonTool.h"

#include "ChangeElementStroke.h"
#include "ChangeElementSize.h"
#include "MoveElement.h"
#include "ChangeElementColor.h"
#include "EditAnchor.h"

#include "AnchorTool.h"

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
		ON_COMMAND(ID_BUTTON_COLOR, &CMwCGView::OnButtonColor)
		ON_UPDATE_COMMAND_UI(ID_BUTTON_COLOR, &CMwCGView::OnUpdateButtonColor)
		//ON_COMMAND(ID_EDIT_SIZE, &CMwCGView::OnEditSize)
		//ON_UPDATE_COMMAND_UI(ID_EDIT_SIZE, &CMwCGView::OnUpdateEditSize)
		ON_UPDATE_COMMAND_UI(ID_EDIT_SIZE, &CMwCGView::OnUpdateEditSize)
		ON_COMMAND(ID_EDIT_SIZE, &CMwCGView::OnEditSize)
		ON_UPDATE_COMMAND_UI(ID_EDIT_POS_X, &CMwCGView::OnUpdateEditPosX)
		ON_COMMAND(ID_EDIT_POS_Y, &CMwCGView::OnEditPosY)
		ON_UPDATE_COMMAND_UI(ID_EDIT_POS_Y, &CMwCGView::OnUpdateEditPosY)
		ON_COMMAND(ID_EDIT_POS_X, &CMwCGView::OnEditPosX)
		ON_UPDATE_COMMAND_UI(ID_STROKE_GALLERY, &CMwCGView::OnUpdateStrokeGallery)
		ON_COMMAND(ID_STROKE_GALLERY, &CMwCGView::OnStrokeGallery)
		ON_WM_LBUTTONDBLCLK()
		ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, &CMwCGView::OnUpdateEditDelete)
		ON_COMMAND(ID_EDIT_DELETE, &CMwCGView::OnEditDelete)
		ON_UPDATE_COMMAND_UI(ID_ELEMENT_SIZE, &CMwCGView::OnUpdateElementSize)
		ON_COMMAND(ID_ELEMENT_STROKE, &CMwCGView::OnElementStroke)
		ON_UPDATE_COMMAND_UI(ID_ELEMENT_STROKE, &CMwCGView::OnUpdateElementStroke)
		ON_COMMAND(ID_ELEMENT_SIZE, &CMwCGView::OnElementSize)
		ON_UPDATE_COMMAND_UI(ID_ELEMENT_POS_X, &CMwCGView::OnUpdateElementPosX)
		ON_UPDATE_COMMAND_UI(ID_ELEMENT_POS_Y, &CMwCGView::OnUpdateElementPosY)
		ON_COMMAND(ID_ELEMENT_POS_X, &CMwCGView::OnElementPosX)
		ON_COMMAND(ID_ELEMENT_POS_Y, &CMwCGView::OnElementPosY)
		ON_UPDATE_COMMAND_UI(ID_ELEMENT_COLOR, &CMwCGView::OnUpdateElementColor)
		ON_COMMAND(ID_ELEMENT_COLOR, &CMwCGView::OnElementColor)
		ON_UPDATE_COMMAND_UI(ID_ANCHOR_POS_X, &CMwCGView::OnUpdateAnchorPosX)
		ON_UPDATE_COMMAND_UI(ID_ANCHOR_POS_Y, &CMwCGView::OnUpdateAnchorPosY)
		ON_COMMAND(ID_ANCHOR_POS_X, &CMwCGView::OnAnchorPosX)
		ON_COMMAND(ID_ANCHOR_POS_Y, &CMwCGView::OnAnchorPosY)
	END_MESSAGE_MAP()

	// CMwCGView construction/destruction

	CMwCGView::CMwCGView()
	{
		// TODO: add construction code here
		transform_changed = false;
		anchor_changed = false;
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
	CMainFrame* CMwCGView::MainFrame() const
	{
		return (CMainFrame*) GetTopLevelFrame();
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

			MainFrame()->SetCaptionBarText(strInitFailed);
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


		return 0;
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
		InitializeTools();

		SwitchToEditMode();
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
		if (pGlContent == NULL)
			return;
		shared_ptr<GlScreen> scr = pGlContent->screen();
		if (scr == NULL)
			return;
		scr->set(cx, cy);
		scr->update_xy();
	}


	BOOL CMwCGView::OnEraseBkgnd(CDC* pDC)
	{
		// TODO: Add your message handler code here and/or call default

		//return CView::OnEraseBkgnd(pDC);
		return TRUE;
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
		CMFCRibbonGallery* shape = theApp.FindRibbonUIById<CMFCRibbonGallery>(ID_SHAPE_GALLERY);

		shape->SelectItem(-1);
	}


	void CMwCGView::OnUpdateToolSelect(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		bool enabled = m_render.IsValid();
		pCmdUI->Enable(enabled);
		if (enabled)
		{
			CMFCRibbonGallery* shape = theApp.FindRibbonUIById<CMFCRibbonGallery>(ID_SHAPE_GALLERY);

			pCmdUI->SetCheck(shape->GetSelectedItem() == -1);
		}
	}


	void CMwCGView::OnShapeGallery()
	{
		// TODO: Add your command handler code here
		int shape_index = CMFCRibbonGallery::GetLastSelectedItem(ID_SHAPE_GALLERY);

		if (shape_index < tools_.size())
		{
			uiEditState_->set_tool(tools_[shape_index]);
		}

		else
		{
			TRACE("Invalid tool index %d\n", shape_index);
		}
		//switch (shape_index)
		//{
		//case 0:
		//	uiEditState_->set_tool(toolPoint_);
		//	break;
		//case 1:
		//	uiEditState_->set_tool(toolLine_);
		//	break;
		//case 2:
		//	uiEditState_->set_tool(toolCircle_);
		//default:
		//	break;
		//}
	}

	void CMwCGView::SendMouseMove( UINT nFlags, CPoint screenPoint )
	{
		ScreenToClient(&screenPoint);
		OnMouseMove(nFlags, screenPoint);
	}


	void CMwCGView::OnButtonColor()
	{
		// TODO: Add your command handler code here
		CMFCRibbonColorButton* pColorButton = theApp.FindRibbonUIById<CMFCRibbonColorButton>(ID_BUTTON_COLOR);
		UpdateToolColor(pColorButton->GetColor());

		Invalidate();
	}


	void CMwCGView::OnUpdateButtonColor(CCmdUI *pCmdUI)
	{
		pCmdUI->Enable(m_render.IsValid());
	}

	void CMwCGView::InitializeTools()
	{
		toolPoint_.reset(new PointTool());
		tools_.push_back(toolPoint_);

		toolLine_.reset(new LineTool<Line>());
		tools_.push_back(toolLine_);

		toolCircle_.reset(new CircleTool());
		tools_.push_back(toolCircle_);

		LineFactory* lineFac = new LineFactory();
		toolPolygon_.reset(new PolygonTool(lineFac));
		tools_.push_back(toolPolygon_);


		toolBresLine_.reset(new LineTool<BresLine>());
		tools_.push_back(toolBresLine_);

		shared_ptr<AnchorTool> anchorTool;
		anchorTool.reset(new AnchorTool(ElementFactory<Line>()));

		OnToolSelect();
		OnButtonColor();
		OnEditSize();
		OnStrokeGallery();
	}

	void CMwCGView::UpdateToolColor( const COLORREF elementColor )
	{
		for (vector<shared_ptr<UiEditorTool>>::iterator it = tools_.begin();
			it != tools_.end(); it++)
		{
			(*it)->UpdateElementColor(elementColor);
		}
	}


	void CMwCGView::OnUpdateEditSize(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_render.IsValid());
	}


	void CMwCGView::OnEditSize()
	{
		// TODO: Add your command handler code here

		CMFCRibbonEdit* pEdit = theApp.FindRibbonUIById<CMFCRibbonEdit>(ID_EDIT_SIZE);
		int size = _ttoi(pEdit->GetEditText());
		//TRACE(pEdit->GetText());
		TRACE("Size: %d\n", size);

		UpdateToolSize(size);

		Invalidate();
	}

	void CMwCGView::UpdateToolSize( int size )
	{
		for (vector<shared_ptr<UiEditorTool>>::iterator it = tools_.begin();
			it != tools_.end(); it++)
		{
			(*it)->UpdateElementSize(size);
		}
	}

	void CMwCGView::ShowFloaty( int inputIndex, UINT nFlags, CPoint point )
	{

		MainFrame()->ActivateContextCategory(ID_CONTEXT_ELEMENT);

		if ((nFlags & MK_CONTROL) == MK_CONTROL)
			return;
		//Store index
		floaty_input_index_ = inputIndex;

		//New floaty
		MwMiniToolBar* pFloaty = new MwMiniToolBar(this);

		//Default floaty component
		InitFloaty(pFloaty);

		//TODO: Tool specific component

		//Show floaty
		ClientToScreen(&point);
		pFloaty->Show(point.x, point.y);

	}

	void CMwCGView::InitFloaty( MwMiniToolBar* pFloaty )
	{
		ASSERT_VALID(pFloaty);
		Vector2 pos;
		if (uiEditState_->tool()->GetInput(floaty_input_index_, pos))
		{
			CMFCRibbonEdit* pEditX = theApp.FindRibbonUIById<CMFCRibbonEdit>(ID_EDIT_POS_X);
			CMFCRibbonEdit* pEditY = theApp.FindRibbonUIById<CMFCRibbonEdit>(ID_EDIT_POS_Y);
			CString str;
			str.Format(_T("%f"), pos.x());
			pEditX->SetEditText(str);
			str.Format(_T("%f"), pos.y());
			pEditY->SetEditText(str);
		}

		CList<UINT, UINT> lstCmds;
		lstCmds.AddTail(ID_EDIT_SIZE);
		lstCmds.AddTail(ID_BUTTON_COLOR);
		lstCmds.AddTail(ID_STROKE_GALLERY);
		lstCmds.AddTail(ID_EDIT_POS_X);
		lstCmds.AddTail(ID_EDIT_POS_Y);
		CMFCRibbonBar* pRibbon = MainFrame()->GetRibbonBar();
		pFloaty->SetCommands(pRibbon, lstCmds);


	}


	void CMwCGView::OnUpdateEditPosX(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		Vector2 pos;
		bool enabled = ValidateFloatyInput(pos);
		pCmdUI->Enable(enabled);

	}

	void CMwCGView::OnUpdateEditPosY(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		Vector2 pos;
		bool enabled = ValidateFloatyInput(pos);
		pCmdUI->Enable(enabled);
	}

	void CMwCGView::OnEditPosY()
	{
		// TODO: Add your command handler code here
		CMFCRibbonEdit* pEdit = theApp.FindRibbonUIById<CMFCRibbonEdit>(ID_EDIT_POS_Y);

		float y = _ttof(pEdit->GetEditText());
		shared_ptr<UiEditorTool> currentTool = uiEditState_->tool();
		Vector2 pos;
		if (currentTool->GetInput(floaty_input_index_, pos))
		{
			pos.set_y(y);
			currentTool->FixInput(floaty_input_index_, pos);
		}

		Invalidate();
	}


	void CMwCGView::OnEditPosX()
	{
		// TODO: Add your command handler code here
		CMFCRibbonEdit* pEdit = theApp.FindRibbonUIById<CMFCRibbonEdit>(ID_EDIT_POS_X);

		float x = _ttof(pEdit->GetEditText());
		shared_ptr<UiEditorTool> currentTool = uiEditState_->tool();
		Vector2 pos;
		if (currentTool->GetInput(floaty_input_index_, pos))
		{
			pos.set_x(x);
			currentTool->FixInput(floaty_input_index_, pos);
		}

		Invalidate();
	}

	bool CMwCGView::ValidateFloatyInput( Vector2& pos )
	{

		if (uiEditState_->tool()->GetInput(floaty_input_index_, pos))
		{
			return true;
		}

		return false;
	}


	void CMwCGView::OnUpdateStrokeGallery(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_render.IsValid());
	}


	void CMwCGView::OnStrokeGallery()
	{
		// TODO: Add your command handler code here
		CMFCRibbonComboBox* pCombo = theApp.FindRibbonUIById<CMFCRibbonComboBox>(ID_STROKE_GALLERY);
		int index = pCombo->GetCurSel();

		if (index >= 0 && index < StrokeCount)
		{
			UpdateToolStroke(Strokes[index]);
		}

		Invalidate();
	}

	void CMwCGView::UpdateToolStroke( const Stroke stroke )
	{
		for (vector<shared_ptr<UiEditorTool>>::iterator it = tools_.begin();
			it != tools_.end(); it++)
		{
			(*it)->UpdateElementStroke(stroke);
		}
	}


	void CMwCGView::OnLButtonDblClk(UINT nFlags, CPoint point)
	{
		// TODO: Add your message handler code here and/or call default

		__super::OnLButtonDblClk(nFlags, point);
		uiState_->OnLButtonDblClk(nFlags, point);
	}

	void CMwCGView::ShowElementContext( shared_ptr<GlElement> element )
	{
		set_context_element(element);
		MainFrame()->ActivateContextCategory(ID_CONTEXT_ELEMENT, true);
	}

	void CMwCGView::ShowAnchorContext( shared_ptr<GlElement> element, int anchor_index )
	{
		set_context_element(element);
		anchor_index_ = anchor_index;
		MainFrame()->ActivateContextCategory(ID_CONTEXT_ANCHOR, true);
	}

	void CMwCGView::set_context_element( shared_ptr<GlElement> element )
	{
		//TODO: point for more setups
		context_element_ = element;
	}

	void CMwCGView::ClearElementContext()
	{
		MainFrame()->HideContextCategory(ID_CONTEXT_ELEMENT);
		context_element_.reset();
	}

	void CMwCGView::ClearAnchorContext()
	{
		MainFrame()->HideContextCategory(ID_CONTEXT_ANCHOR);
		anchor_index_ = -1;
		if (!context_element_.expired())
		{
			MainFrame()->ActivateContextCategory(ID_CONTEXT_ELEMENT, true);
		}
	}


	void CMwCGView::OnUpdateEditDelete(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(!context_element_.expired());
	}


	void CMwCGView::OnEditDelete()
	{
		// TODO: Add your command handler code here
		uiState_->OnCommand(ID_EDIT_DELETE);
		Invalidate();
	}


	void CMwCGView::OnUpdateElementSize(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(!context_element_.expired());
	}


	void CMwCGView::OnUpdateElementStroke(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(!context_element_.expired());
	}


	void CMwCGView::OnElementStroke()
	{
		// TODO: Add your command handler code here
		if (context_element_.expired())
			return;
		CMFCRibbonComboBox* pCombo = theApp.FindRibbonUIById<CMFCRibbonComboBox>(ID_ELEMENT_STROKE);

		int index = pCombo->GetCurSel();
		if (index >= 0 && index < StrokeCount)
		{
			GetDocument()->CommitOperation(OperationPtr(
				new ChangeElementStroke(context_element_.lock(), Strokes[index])
				));
		}

		Invalidate();
	}


	void CMwCGView::OnElementSize()
	{
		// TODO: Add your command handler code here
		if (context_element_.expired())
			return;

		CMFCRibbonEdit* pEdit = theApp.FindRibbonUIById<CMFCRibbonEdit>(ID_ELEMENT_SIZE);
		int size = _ttoi(pEdit->GetEditText());
		//TRACE(pEdit->GetText());
		TRACE("Size: %d\n", size);

		//TODO: wrap in operation
		GetDocument()->CommitOperation(OperationPtr(
			new ChangeElementSize(context_element_.lock(), size)
			));

		Invalidate();
	}


	void CMwCGView::OnUpdateElementPosX(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(ValidateElementTransform());
	}


	void CMwCGView::OnUpdateElementPosY(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(ValidateElementTransform());

	}


	void CMwCGView::OnElementPosX()
	{
		MoveSelElement();
	}


	void CMwCGView::OnElementPosY()
	{
		// TODO: Add your command handler code here
		MoveSelElement();
	}

	Vector2 CMwCGView::ValidateAndGetPos(const Vector2& pos, UINT nCmdIdX, UINT nCmdIdY)
	{
		Vector2 new_pos = pos;
		CString str;

		CMFCRibbonEdit* pEditX = theApp.FindRibbonUIById<CMFCRibbonEdit>(nCmdIdX);
		float x = 0;
		if (!pEditX->HasFocus())
		{
			x = pos.x();
		}
		else
		{
			x = _ttof(pEditX->GetEditText());
			new_pos.set_x(x);
		}
		str.Format(_T("%f"), x);
		pEditX->SetEditText(str);

		CMFCRibbonEdit* pEditY = theApp.FindRibbonUIById<CMFCRibbonEdit>(nCmdIdY);
		float y = 0;
		if (!pEditY->HasFocus())
		{
			y = pos.y();
		}
		else
		{
			y = _ttof(pEditY->GetEditText());
			new_pos.set_y(y);
		}
		str.Format(_T("%f"), y);
		pEditY->SetEditText(str);

		return new_pos;
	}

	bool CMwCGView::ValidateElementTransform() 
	{
		bool bEnabled = !context_element_.expired();

		if (bEnabled)
		{
			Vector2 pos = context_element_.lock()->transform().position();
			Vector2 new_pos = ValidateAndGetPos(pos, ID_ELEMENT_POS_X, ID_ELEMENT_POS_Y);

			//Changed
			if (pos != new_pos)
			{
				if (transform_changed)
				{
					//update operation
					move_op_->set_move_to_position(new_pos);
					GetDocument()->UpdatePreviewOperation();
				}
				else
				{
					//reset operation
					move_op_.reset(new MoveElement(content_, context_element_.lock()));
					move_op_->set_initial_position(context_element_.lock()->transform().position());
					move_op_->set_move_to_position(new_pos);
					//begin preview
					GetDocument()->BeginPreviewOperation(OperationPtr(move_op_));
					transform_changed = true;
				}
				Invalidate();
			}
		}
		return bEnabled;
	}

	void CMwCGView::MoveSelElement()
	{
		if (transform_changed)
		{
			//TODO: Commit preview
			transform_changed = false;
			GetDocument()->CommitPreviewOperation();
		} 
		Invalidate();
	}

	float CMwCGView::ValidateAndGetFloat( UINT nCmdId )
	{
		CMFCRibbonEdit* pEdit = theApp.FindRibbonUIById<CMFCRibbonEdit>(nCmdId);
		float f = _ttof(pEdit->GetEditText());
		CString valid_str;
		valid_str.Format(_T("%f"), f);
		pEdit->SetEditText(valid_str);
		return f;
	}


	void CMwCGView::OnUpdateElementColor(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(!context_element_.expired());
	}


	void CMwCGView::OnElementColor()
	{
		// TODO: Add your command handler code here

		CMFCRibbonColorButton* pColorButton = theApp.FindRibbonUIById<CMFCRibbonColorButton>(ID_ELEMENT_COLOR);
		Color newColor(pColorButton->GetColor());

		GetDocument()->CommitOperation(OperationPtr(
			new ChangeElementColor(context_element_.lock(), newColor)
			));

		Invalidate();
	}

	void CMwCGView::ShowElementFloaty()
	{
		if (context_element_.expired())
			return;
		//New floaty
		MwMiniToolBar* pFloaty = new MwMiniToolBar(this);

		//Default floaty component
		InitElementFloaty(pFloaty);

		//Show floaty
		CPoint point = uiState_->screen_point();
		ClientToScreen(&point);
		pFloaty->Show(point.x, point.y);
	}

	void CMwCGView::InitElementFloaty( MwMiniToolBar* pFloaty )
	{
		ASSERT_VALID(pFloaty);

		CList<UINT, UINT> lstCmds;
		lstCmds.AddTail(ID_ELEMENT_COLOR);
		lstCmds.AddTail(ID_ELEMENT_SIZE);
		lstCmds.AddTail(ID_ELEMENT_STROKE);
		lstCmds.AddTail(ID_ELEMENT_POS_X);
		lstCmds.AddTail(ID_ELEMENT_POS_Y);
		lstCmds.AddTail(ID_EDIT_DELETE);
		CMFCRibbonBar* pRibbon = MainFrame()->GetRibbonBar();
		pFloaty->SetCommands(pRibbon, lstCmds);
	}


	void CMwCGView::OnUpdateAnchorPosX(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(ValidateElementAnchor());

	}


	void CMwCGView::OnUpdateAnchorPosY(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(ValidateElementAnchor());
	}


	void CMwCGView::OnAnchorPosX()
	{
		// TODO: Add your command handler code here
		MoveSelAnchor();
	}


	void CMwCGView::OnAnchorPosY()
	{
		// TODO: Add your command handler code here
		MoveSelAnchor();
	}

	bool CMwCGView::ValidateElementAnchor()
	{
		bool bEnabled = !context_element_.expired() && anchor_index_ >= 0;

		if (bEnabled)
		{
			shared_ptr<GlElement> lockElement = context_element_.lock();
			Vector2 pos = lockElement->anchor(anchor_index_);
			lockElement->transform().LocalToWorld(pos);
			Vector2 new_pos = ValidateAndGetPos(pos, ID_ANCHOR_POS_X, ID_ANCHOR_POS_Y);

			//Changed
			if (pos != new_pos)
			{
				if (anchor_changed)
				{
					//update operation
					anchor_op_->set_new_anchor(new_pos);
					GetDocument()->UpdatePreviewOperation();
				}
				else
				{
					//reset operation
					anchor_op_.reset(new EditAnchor(lockElement, anchor_index_));
					anchor_op_->set_old_anchor(pos);
					anchor_op_->set_new_anchor(new_pos);
					//begin preview
					GetDocument()->BeginPreviewOperation(OperationPtr(anchor_op_));
					anchor_changed = true;
				}
				Invalidate();
			}
		}

		return bEnabled;
	}

	void CMwCGView::MoveSelAnchor()
	{
		if (anchor_changed)
		{
			GetDocument()->CommitPreviewOperation();
			anchor_changed = false;
		}
		Invalidate();
		return;
		float x = ValidateAndGetFloat(ID_ANCHOR_POS_X);
		float y = ValidateAndGetFloat(ID_ANCHOR_POS_Y);

		shared_ptr<GlElement> lockElement = context_element_.lock();
		shared_ptr<EditAnchor> anchor_op(new EditAnchor(lockElement, anchor_index_));
		Vector2 old_world_pos = lockElement->anchor(anchor_index_);
		lockElement->transform().LocalToWorld(old_world_pos);
		anchor_op->set_old_anchor(old_world_pos);
		anchor_op->set_new_anchor(Vector2(x, y));

		GetDocument()->CommitOperation(anchor_op);

		Invalidate();
	}

	void CMwCGView::ShowAnchorFloaty()
	{
		if (context_element_.expired() || anchor_index_ < 0)
			return;
		//New floaty
		MwMiniToolBar* pFloaty = new MwMiniToolBar(this);

		//Default floaty component
		InitAnchorFloaty(pFloaty);

		//Show floaty
		CPoint point = uiState_->screen_point();
		ClientToScreen(&point);
		pFloaty->Show(point.x, point.y);
	}

	void CMwCGView::InitAnchorFloaty( MwMiniToolBar* pFloaty )
	{
		ASSERT_VALID(pFloaty);

		CList<UINT, UINT> lstCmds;
		lstCmds.AddTail(ID_ANCHOR_POS_X);
		lstCmds.AddTail(ID_ANCHOR_POS_Y);
		CMFCRibbonBar* pRibbon = MainFrame()->GetRibbonBar();
		pFloaty->SetCommands(pRibbon, lstCmds);
	}

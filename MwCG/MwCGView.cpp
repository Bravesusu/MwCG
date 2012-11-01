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
ON_UPDATE_COMMAND_UI(ID_CANVAS_WIDTH, &CMwCGView::OnUpdateCanvasWidth)
ON_UPDATE_COMMAND_UI(ID_CANVAS_HEIGHT, &CMwCGView::OnUpdateCanvasHeight)
ON_UPDATE_COMMAND_UI(ID_SHAPE_GALLERY, &CMwCGView::OnUpdateShapeGallery)
ON_WM_MOUSEMOVE()
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
			m_render.Draw(pDoc->GetGLContent());
			SwapBuffers(pDC->GetSafeHdc());
		}
		//CRect rect;
		//GetClientRect(rect);
		//pDC->MoveTo(0, m_ptMouse.y);
		//pDC->LineTo(rect.Width(), m_ptMouse.y);
		//pDC->MoveTo(m_ptMouse.x, 0);
		//pDC->MoveTo(m_ptMouse.x, rect.Height());
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

	void CMwCGView::OnRButtonUp(UINT /* nFlags */, CPoint point)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
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
		m_render.SetViewSize(0, 0, cx, cy);
	}


	BOOL CMwCGView::OnEraseBkgnd(CDC* pDC)
	{
		// TODO: Add your message handler code here and/or call default

		//return CView::OnEraseBkgnd(pDC);
		return TRUE;
	}


	void CMwCGView::OnUpdateClearColor(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_render.IsValid());
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

		MwGLContent* pGlContent = pDoc->GetGLContent();
		MwCanvas* pCanvas = pGlContent->GetCanvas();
		pColorBtn->SetColor(pCanvas->Color.GetColorRef());
		
		CRect rect;
		GetClientRect(rect);
		
		m_render.SetViewSize(0, 0, rect.Width(), rect.Height());
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


	void CMwCGView::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: Add your message handler code here and/or call default

		CView::OnMouseMove(nFlags, point);
		GetDocument()->SetMousePos(point);
		m_ptMouse = point;
		Invalidate();
	}

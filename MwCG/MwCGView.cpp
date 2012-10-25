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

IMPLEMENT_DYNCREATE(CMwCGView, CScrollView)

	BEGIN_MESSAGE_MAP(CMwCGView, CScrollView)
		// Standard printing commands
		ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
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
		return CScrollView::PreCreateWindow(cs);
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
		CScrollView::AssertValid();
	}

	void CMwCGView::Dump(CDumpContext& dc) const
	{
		CScrollView::Dump(dc);
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
		if (CScrollView::OnCreate(lpCreateStruct) == -1)
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
		CScrollView::OnDestroy();

		//Finalize the MwGLRenderer
		m_render.Finalize();
		::ReleaseDC(GetSafeHwnd(), m_hDC);
	}


	void CMwCGView::OnSize(UINT nType, int cx, int cy)
	{
		CScrollView::OnSize(nType, cx, cy);

		// TODO: Add your message handler code here
		//m_render.SetViewSize(cx, cy);
	}


	BOOL CMwCGView::OnEraseBkgnd(CDC* pDC)
	{
		// TODO: Add your message handler code here and/or call default

		//return CScrollView::OnEraseBkgnd(pDC);
		return TRUE;
	}


	void CMwCGView::OnUpdateClearColor(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		pCmdUI->Enable(m_render.IsValid());
	}


	void CMwCGView::OnInitialUpdate()
	{
		CScrollView::OnInitialUpdate();

		// TODO: Add your specialized code here and/or call the base class
		CMFCRibbonColorButton* pColorBtn = theApp.GetClearColorButton();
		
		CMwCGDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		MwGLContent* pGlContent = pDoc->GetGLContent();
		MwCanvas* pCanvas = pGlContent->GetCanvas();
		int cWidth = pCanvas->Width;
		int cHeight = pCanvas->Height;
		pColorBtn->SetColor(pCanvas->ClearColor->GetColorRef());
		SetScrollSizes(MM_TEXT, CSize(cWidth, cHeight));
		m_render.SetViewSize(0, 0, cWidth, cHeight);
	}


	void CMwCGView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
	{
		// TODO: Add your specialized code here and/or call the base class

		CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);

		if (bActivate)
		{
			m_render.Activate(m_hDC);
		}
	}


	BOOL CMwCGView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll)
	{
		// TODO: Add your specialized code here and/or call the base class
		CMwCGDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);

		MwGLContent* pGlContent = pDoc->GetGLContent();
		MwCanvas* pCanvas = pGlContent->GetCanvas();
		int cWidth = pCanvas->Width;
		int cHeight = pCanvas->Height;

		CPoint scrollPos = GetScrollPosition();
		m_render.SetViewSize(-scrollPos.x, scrollPos.y, cWidth, cHeight);
		Invalidate();
		return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
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

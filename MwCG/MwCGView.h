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

// MwCGView.h : interface of the CMwCGView class
//

#pragma once
#include "MwGLRenderer.h"
#include "MainFrm.h"

#include "UiState.h"
#include "UiNav.h"
#include "UiEdit.h"
#include "IRecvView.h"
#include "LineTool.h"
#include "BresLine.h"

using namespace mw;

namespace mw
{
	class PointTool;
	class CircleTool;
	class PolygonTool;
	class UiEditorTool;
}

class MwMiniToolBar;
class CMwCGView : public CView, public IRecvView
{
protected: // create from serialization only
	CMwCGView();
	DECLARE_DYNCREATE(CMwCGView)

	// Attributes
public:
	CMwCGDoc* GetDocument() const;
	CMainFrame* MainFrame() const;
private:
	weak_ptr<GlElement> context_element_;
	int anchor_index;
protected:
	void set_context_element(shared_ptr<GlElement> element);
public:
	void ShowElementContext(shared_ptr<GlElement> element);
	void ShowAnchorContext(shared_ptr<GlElement> element, int anchor_index);
	void ClearElementContext();
	void ClearAnchorContext();
protected:
	GlRenderer m_render;
	HDC m_hDC;
	Vector2 mouse_xy_;
	int zoom_level_;
	bool m_bMouseDown;
	shared_ptr<GlContent> content_;
	shared_ptr<Canvas> canvas_;
	shared_ptr<GlScreen> screen_;
	shared_ptr<UiState> uiState_;
	shared_ptr<UiNav> uiNavState_;
	shared_ptr<UiEdit> uiEditState_;

private:
	vector<shared_ptr<UiEditorTool>> tools_;
	shared_ptr<PointTool> toolPoint_;
	shared_ptr<LineTool<Line>> toolLine_;
	shared_ptr<CircleTool> toolCircle_;
	shared_ptr<PolygonTool> toolPolygon_;
	shared_ptr<LineTool<BresLine>> toolBresLine_;
	int floaty_input_index_;
	void InitializeTools();
	void UpdateToolColor(const COLORREF elementColor);
	void UpdateToolStroke(const Stroke stroke);
	bool ValidateFloatyInput(Vector2& pos);
	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	virtual ~CMwCGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnUpdateClearColor(CCmdUI *pCmdUI);
	virtual void OnInitialUpdate();
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//	afx_msg void OnCanvasHeight();
	//	afx_msg void OnCanvasWidth();
	//	afx_msg void OnCanvasHeight();
	afx_msg void OnUpdateCanvasWidth(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCanvasHeight(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShapeGallery(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnUpdateIdsStatusPos(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIdsStatusZoom(CCmdUI *pCmdUI);
	//	afx_msg void OnIdsStatusZoomSlider();
	afx_msg void OnUpdateIdsStatusZoomSlider(CCmdUI *pCmdUI);
	afx_msg void OnIdsStatusZoomSlider();
	//	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	void SwitchToEditMode();
	void SwitchToNavMode();
	afx_msg void OnUpdateIdsStatusMode(CCmdUI *pCmdUI);
//	afx_msg void OnUpdateFilePrintPreview(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCheckGird(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIdsStatusRect(CCmdUI *pCmdUI);
	void InitFloaty( MwMiniToolBar* pFloaty );
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnToolSelect();
	afx_msg void OnUpdateToolSelect(CCmdUI *pCmdUI);
	afx_msg void OnShapeGallery();

	virtual void SendMouseMove( UINT nFlags, CPoint screenPoint );

	afx_msg void OnButtonColor();
	afx_msg void OnUpdateButtonColor(CCmdUI *pCmdUI);
//	afx_msg void OnEditSize();
//	afx_msg void OnUpdateEditSize(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditSize(CCmdUI *pCmdUI);
	afx_msg void OnEditSize();
	void UpdateToolSize( int size );
	void ShowFloaty( int inputIndex, UINT nFlags, CPoint point );
	afx_msg void OnUpdateEditPosX(CCmdUI *pCmdUI);
	afx_msg void OnEditPosY();
	afx_msg void OnUpdateEditPosY(CCmdUI *pCmdUI);
	afx_msg void OnEditPosX();
	afx_msg void OnUpdateStrokeGallery(CCmdUI *pCmdUI);
	afx_msg void OnStrokeGallery();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnUpdateEditDelete(CCmdUI *pCmdUI);
	afx_msg void OnEditDelete();
};

#ifndef _DEBUG  // debug version in MwCGView.cpp
inline CMwCGDoc* CMwCGView::GetDocument() const
{ return reinterpret_cast<CMwCGDoc*>(m_pDocument); }
#endif


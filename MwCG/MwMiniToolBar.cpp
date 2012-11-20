#include "stdafx.h"
#include "MwMiniToolBar.h"


MwMiniToolBar::MwMiniToolBar(void) : m_pView(NULL)
{
}

MwMiniToolBar::MwMiniToolBar( IRecvView* pWnd )
{
	m_pView = pWnd;
}


MwMiniToolBar::~MwMiniToolBar(void)
{
}


//BOOL MwMiniToolBar::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO: Add your specialized code here and/or call the base class
//	//cs.style
//	return CMFCRibbonMiniToolBar::PreCreateWindow(cs);
//}
BEGIN_MESSAGE_MAP(MwMiniToolBar, CMFCRibbonMiniToolBar)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void MwMiniToolBar::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CMFCRibbonMiniToolBar::OnMouseMove(nFlags, point);

	ClientToScreen(&point);
	if (m_pView)
		m_pView->SendMouseMove(nFlags, point);
	//ClientToScreen()
}


BOOL MwMiniToolBar::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	//cs.dwExStyle |= WS_EX_TRANSPARENT;
	return CMFCRibbonMiniToolBar::PreCreateWindow(cs);
}

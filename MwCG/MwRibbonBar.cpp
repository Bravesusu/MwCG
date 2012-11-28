#include "stdafx.h"
#include "MwRibbonBar.h"


MwRibbonBar::MwRibbonBar(void)
{
}


MwRibbonBar::~MwRibbonBar(void)
{
}
BEGIN_MESSAGE_MAP(MwRibbonBar, CMFCRibbonBar)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


void MwRibbonBar::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CMFCRibbonBar::OnLButtonDblClk(nFlags, point);
	ToggleMimimizeState();
}

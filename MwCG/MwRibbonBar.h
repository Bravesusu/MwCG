#pragma once
#include "afxribbonbar.h"
class MwRibbonBar :
	public CMFCRibbonBar
{
public:
	MwRibbonBar(void);
	~MwRibbonBar(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


#pragma once
#include "afxribbonminitoolbar.h"
#include "IRecvView.h"

class MwMiniToolBar :
	public CMFCRibbonMiniToolBar
{
private:
	IRecvView* m_pView;
public:
	MwMiniToolBar(void);
	MwMiniToolBar(IRecvView* pWnd);
	~MwMiniToolBar(void);
	//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


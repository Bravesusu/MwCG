#pragma once
#include "afxribbonedit.h"

class MwNumberEdit :
	public CMFCRibbonEdit
{
public:
	MwNumberEdit( UINT nID, int nWidth, LPCTSTR lpszLabel ) : 
		CMFCRibbonEdit(nID, nWidth, lpszLabel) {};
	~MwNumberEdit(void);


};


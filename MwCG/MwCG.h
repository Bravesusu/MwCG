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

// MwCG.h : main header file for the MwCG application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMwCGApp:
// See MwCG.cpp for the implementation of this class
//

class CMwCGApp : public CWinAppEx
{
public:
	CMwCGApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	CMFCRibbonColorButton* GetClearColorButton();
	CMFCRibbonBar* GetRibbonBar();
	template<class UI>
	UI* FindRibbonUIById(UINT uiCmdId)
	{
		CMFCRibbonBar* pRibbon = GetRibbonBar();
		UI* pUI = DYNAMIC_DOWNCAST(UI, pRibbon->FindByID(uiCmdId));
		ASSERT_VALID(pUI);
		return pUI;
	}
};

extern CMwCGApp theApp;

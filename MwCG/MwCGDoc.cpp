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

// MwCGDoc.cpp : implementation of the CMwCGDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MwCG.h"
#endif

#include "MwCGDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMwCGDoc

IMPLEMENT_DYNCREATE(CMwCGDoc, CDocument)

	BEGIN_MESSAGE_MAP(CMwCGDoc, CDocument)
		ON_COMMAND(ID_CLEAR_COLOR, &CMwCGDoc::OnClearColor)
		ON_COMMAND(ID_CANVAS_WIDTH, &CMwCGDoc::OnCanvasWidth)
		ON_COMMAND(ID_CANVAS_HEIGHT, &CMwCGDoc::OnCanvasHeight)
	END_MESSAGE_MAP()


	// CMwCGDoc construction/destruction

	CMwCGDoc::CMwCGDoc()
	{
		// TODO: add one-time construction code here
		
	}

	CMwCGDoc::~CMwCGDoc()
	{
	}

	BOOL CMwCGDoc::OnNewDocument()
	{
		if (!CDocument::OnNewDocument())
			return FALSE;

		// TODO: add reinitialization code here
		// (SDI documents will reuse this document)

		glContent_.reset(new GlContent());
		FooDocument();

		return TRUE;
	}

	// CMwCGDoc serialization

	void CMwCGDoc::Serialize(CArchive& ar)
	{
		glContent_->Serialize(ar);
		if (ar.IsStoring())
		{
			// TODO: add storing code here
		}
		else
		{
			// TODO: add loading code here
		}
	}

#ifdef SHARED_HANDLERS

	// Support for thumbnails
	void CMwCGDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
	{
		// Modify this code to draw the document's data
		dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

		CString strText = _T("TODO: implement thumbnail drawing here");
		LOGFONT lf;

		CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
		pDefaultGUIFont->GetLogFont(&lf);
		lf.lfHeight = 36;

		CFont fontDraw;
		fontDraw.CreateFontIndirect(&lf);

		CFont* pOldFont = dc.SelectObject(&fontDraw);
		dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
		dc.SelectObject(pOldFont);
	}

	// Support for Search Handlers
	void CMwCGDoc::InitializeSearchContent()
	{
		CString strSearchContent;
		// Set search contents from document's data. 
		// The content parts should be separated by ";"

		// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
		SetSearchContent(strSearchContent);
	}

	void CMwCGDoc::SetSearchContent(const CString& value)
	{
		if (value.IsEmpty())
		{
			RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
		}
		else
		{
			CMFCFilterChunkValueImpl *pChunk = NULL;
			ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
			if (pChunk != NULL)
			{
				pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
				SetChunkValue(pChunk);
			}
		}
	}

#endif // SHARED_HANDLERS

	// CMwCGDoc diagnostics

#ifdef _DEBUG
	void CMwCGDoc::AssertValid() const
	{
		CDocument::AssertValid();
	}

	void CMwCGDoc::Dump(CDumpContext& dc) const
	{
		CDocument::Dump(dc);
	}
#endif //_DEBUG


	// CMwCGDoc commands

	void CMwCGDoc::OnCloseDocument()
	{
		// TODO: Add your specialized code here and/or call the base class
		
		CDocument::OnCloseDocument();
	}


	void CMwCGDoc::OnClearColor()
	{
		// TODO: Add your command handler code here
		CMFCRibbonColorButton* pColorBtn = theApp.GetClearColorButton();
		COLORREF clr = pColorBtn->GetColor();
		glContent_->canvas()->set_color(clr);
		UpdateAllViews(NULL);
	}


	BOOL CMwCGDoc::OnOpenDocument(LPCTSTR lpszPathName)
	{
		if (!CDocument::OnOpenDocument(lpszPathName))
			return FALSE;
		return TRUE;

		FooDocument();
	}


	void CMwCGDoc::OnCanvasWidth()
	{
		// TODO: Add your command handler code here

		//int newWidth = atoi(widthEdit->GetText());
	}


	void CMwCGDoc::OnCanvasHeight()
	{
		// TODO: Add your command handler code here
		//CMFCRibbonEdit* heightEdit = theApp.FindRibbonUIById<CMFCRibbonEdit>(ID_CANVAS_HEIGHT);

	}

	//Create a dummy document
	void CMwCGDoc::FooDocument()
	{		
		shared_ptr<Canvas> canvas = glContent_->canvas();
		int width = 800;
		int height = 600;
		int hw = width / 2;
		int hh = height / 2;
		for (int y = -hh; y < hh; y += 10)
		{
			Line* ln = new Line(
				0, 
				static_cast<float>(y), 
				static_cast<float>(width), 
				static_cast<float>(y));
			ln->set_color(MW_RED);
			glContent_->Elements.push_back(MwElementSafePtr(ln));
		}

		for (int x = -hw; x < hw; x += 100)
		{
			for (int y = -hh; y < hh; y += 100)
			{
				Point* pt = new Point(
					static_cast<float>(x), 
					static_cast<float>(y), 
					5.0);
				pt->set_color(MW_BLUE);
				glContent_->Elements.push_back(MwElementSafePtr(pt));
			}
		}

		Sierpinski* sk = new Sierpinski();
		sk->set_point_count(10000);
		sk->set_color(MW_GREEN);
		(*sk)[0] = Vector2(100.0, 50.0);
		(*sk)[1] = Vector2(400.0, 400.0);
		(*sk)[2] = Vector2(700.0, 50.0);

		glContent_->Elements.push_back(MwElementSafePtr(sk));
	}
	
	void CMwCGDoc::SetMousePos(CPoint& point)
	{
		int width = 800;
		int height = 600;
		shared_ptr<Canvas> canvas = glContent_->canvas();
		float hw = static_cast<float>(width / 2);
		float hh = static_cast<float>(height / 2);
		glContent_->Mouse.set_position(point.x - hw, hh - point.y); 
	}
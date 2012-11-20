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

// MwCGDoc.h : interface of the CMwCGDoc class
//


#pragma once


namespace mw
{
	class IOperation;
	class GlContent;
}

using namespace mw;

class CMwCGDoc : public CDocument
{
protected: // create from serialization only
	CMwCGDoc();
	DECLARE_DYNCREATE(CMwCGDoc)

private:
	vector<shared_ptr<IOperation>> ops_;
	//Point to current op [-1, ops_.size())
	int op_index;
public:
	bool CanUndo() const;
	bool CanRedo() const;
	void CommitOperation(shared_ptr<IOperation> operation);
	void Redo();
	void Undo();

// Attributes
public:

private:
	shared_ptr<GlContent> glContent_;
	//void FooDocument();
// Operations
public:
	Vector2 SetMousePos(CPoint& point);
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMwCGDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	const shared_ptr<GlContent>& glContent(void) const { return glContent_; }
	virtual void OnCloseDocument();
	afx_msg void OnClearColor();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void OnCanvasWidth();
	afx_msg void OnCanvasHeight();
//	afx_msg void OnUpdateIdsStatusPos(CCmdUI *pCmdUI);
	afx_msg void OnCheckGird();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
};

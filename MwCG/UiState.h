#pragma once
#include "IDrawable.h"
class CMwCGView;
class CMwCGDoc;

namespace mw
{
	class UiState :
		public IDrawable
	{
	private:
		CMwCGView* pView_;
		CMwCGDoc* pDoc_;
	protected:
		CString name_;
	private:
		virtual void InitializeName() = 0;
	public:
		void Initialize(CMwCGDoc* pDoc, CMwCGView* pView);
		CMwCGDoc* doc() const { return pDoc_; }
		CMwCGView* view() const { return pView_; }
	public:
		UiState(void);
		~UiState(void);
	public:
		virtual void OnMouseMove(UINT nFlags, CPoint point) = 0;
		virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;
		virtual void OnLButtonUp(UINT nFlags, CPoint point) = 0;
		virtual void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags ) = 0;
		virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
		virtual void OnRButtonUp( UINT nFlags, CPoint point ) = 0;
		virtual void OnLButtonDblClk( UINT nFlags, CPoint point ) = 0;
	public:
		CString name() const { return name_; }
	};
}

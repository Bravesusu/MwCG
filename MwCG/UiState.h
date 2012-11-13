#pragma once
#include "MwCGDoc.h"
#include "MwCGView.h"

namespace mw
{
	class UiState
	{
	private:
		CMwCGView* pView_;
		CMwCGDoc* pDoc_;
	public:
		void Initialize(CMwCGDoc* pDoc, CMwCGView* pView);
		const CMwCGDoc* doc() const { return pDoc_; }
		const CMwCGView* view() const { return pView_; }
	public:
		UiState(void);
		~UiState(void);
	public:
		virtual void OnMouseMove(UINT nFlags, CPoint point) = 0;
		virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;
		virtual void OnLButtonUp(UINT nFlags, CPoint point) = 0;
	};
}

#pragma once

class CMwCGDoc;
class CMwCGView;
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
		virtual void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags ) = 0;
		virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
	};
}

#pragma once
#include "IDrawable.h"
#include "MwVector2.h"
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
		CPoint scr_pt_;
		Vector2 mouse_xy_;
	protected:
		CString name_;
		void UpdateMouseInput(UINT nFlags, CPoint point);
		Vector2 mouse_xy() const { return mouse_xy_; }
	private:
		virtual void InitializeName() = 0;
	public:
		void Initialize(CMwCGDoc* pDoc, CMwCGView* pView);
		CMwCGDoc* doc() const { return pDoc_; }
		CMwCGView* view() const { return pView_; }
	public:
		UiState(void);
		virtual ~UiState(void) = 0;
		CPoint screen_point() const { return scr_pt_; }
	public:
		virtual void OnMouseMove(UINT nFlags, CPoint point) = 0;
		virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;
		virtual void OnLButtonUp(UINT nFlags, CPoint point) = 0;
		virtual void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags ) = 0;
		virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
		virtual void OnRButtonUp( UINT nFlags, CPoint point ) = 0;
		virtual void OnLButtonDblClk( UINT nFlags, CPoint point ) = 0;
		virtual void OnCommand( UINT nCmdId ) = 0;
	public:
		CString name() const { return name_; }
	};
}

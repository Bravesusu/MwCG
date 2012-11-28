#pragma once
#include "uistate.h"
//#include "MwVector2.h"

namespace mw
{
	class UiNav :
		public UiState
	{
	public:
		UiNav(void);
		~UiNav(void);

		virtual void OnMouseMove( UINT nFlags, CPoint point );

		virtual void OnLButtonDown( UINT nFlags, CPoint point );

		virtual void OnLButtonUp( UINT nFlags, CPoint point );

		virtual void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );

		virtual void OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );

		virtual void InitializeName();
		virtual void OnRButtonUp( UINT nFlags, CPoint point );

	public:
		virtual void Draw();

		virtual void OnLButtonDblClk( UINT nFlags, CPoint point );

		virtual void OnCommand( UINT nCmdId );


	private:
		bool m_bMouseDown;
		CPoint last_mouse_point_;
	};
}
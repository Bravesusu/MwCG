#pragma once
#include "uistate.h"

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

	private:
		bool m_bSpaceDown;

	};
}
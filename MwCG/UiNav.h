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

	};
}
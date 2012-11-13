#pragma once
#include "uistate.h"

namespace mw
{
	class UiEdit :
		public UiState
	{
	public:
		UiEdit(void);
		~UiEdit(void);

		virtual void OnMouseMove( UINT nFlags, CPoint point );

		virtual void OnLButtonDown( UINT nFlags, CPoint point );

		virtual void OnLButtonUp( UINT nFlags, CPoint point );

	};
}



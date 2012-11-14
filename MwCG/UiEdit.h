#pragma once
#include <memory>
#include "uistate.h"
#include "MwVector2.h"

using namespace std;

namespace mw
{
	class UiEditor;

	class UiEdit :
		public UiState
	{
	private:
		shared_ptr<UiEditor> editor_;
		Vector2 mouse_xy_;
		void UpdateMouseInput(UINT nFlags, CPoint point);
	public:
		
	public:
		UiEdit(void);
		~UiEdit(void);

		virtual void OnMouseMove( UINT nFlags, CPoint point );

		virtual void OnLButtonDown( UINT nFlags, CPoint point );

		virtual void OnLButtonUp( UINT nFlags, CPoint point );

		virtual void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );

		virtual void OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );

		virtual void InitializeName();

	public:

	};
}



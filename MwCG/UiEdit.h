#pragma once
#include <memory>
#include "uistate.h"
#include "MwVector2.h"

using namespace std;

namespace mw
{
	class UiEditorTool;
	class UiSelector;

	class UiEdit :
		public UiState
	{
	private:
		shared_ptr<UiEditorTool> tool_;
		shared_ptr<UiSelector> selector_;
		Vector2 mouse_xy_;
		bool mouse_left_down_;
		void UpdateMouseInput(UINT nFlags, CPoint point);
	public:
		//Get default selector
		shared_ptr<UiSelector> selector() const { return selector_; }
		//Set tool from command
		void set_tool(shared_ptr<UiEditorTool> tool);
		void use_selector();
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



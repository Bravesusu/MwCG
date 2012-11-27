#pragma once
#include <memory>
#include "uistate.h"
#include "MwVector2.h"

using namespace std;

namespace mw
{
	class UiEditorTool;
	class UiSelector;
	class PointTool;
	class IOperation;

	class UiEdit :
		public UiState//,
		//public enable_shared_from_this<UiEdit>
	{
	private:
		shared_ptr<PointTool> point_;
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
		const shared_ptr<UiEditorTool> tool() const { return tool_; }
		void use_selector();
	public:
		//void NotifyToolFinished();
	//	void NotifyToolOperation(const shared_ptr<IOperation>& operation);
	//	void NotifyToolPreview(const shared_ptr<IOperation>& operation);
	//	void NotifyToolUpdatePreview();
	//	void NotifyToolCommitPreview();
	//	void NotifyToolCancelPreview();
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
		virtual void Draw();

		virtual void OnRButtonUp( UINT nFlags, CPoint point );

	private:
		//bool TryFinishTool();

		virtual void OnLButtonDblClk( UINT nFlags, CPoint point );

	public:

	};
}



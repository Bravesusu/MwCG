#pragma once
#include "MwGLContent.h"
#include "IDrawable.h"
#include "IOperation.h"
#include  "IMouseInput.h"

namespace mw
{
	//enum InputStatus { AcceptUpdate, AcceptFix, AcceptNone };
	class Point;
	class UiEdit;
	class UiEditorTool :
		public IDrawable,
		public IMouseInput
	{
	private:
		shared_ptr<GlContent> content_;
		//InputStatus status_;
		vector<Vector2> inputs_;
		int input_index;
		Vector2 mouse_;
		Vector2 mouse_down_;
		Vector2 mouse_last_;
		//Vector2 current_;
		shared_ptr<UiEdit> ui_;
		bool just_finished_;
	protected:
		const shared_ptr<UiEdit> ui() const { return ui_; }
	public:
		void set_ui(shared_ptr<UiEdit> ui) { ui_ = ui; }
	protected:
		virtual shared_ptr<GlElement> GetEditingElement() { return NULL; }
	protected:
		int input_count() const { return inputs_.size(); }

		int currentIndex() const { return input_index; }
		Vector2 current() const { return inputs_.at(input_index); }
		//The pos of last update
		Vector2 mouse_last_pos() const { return mouse_last_; }
		Vector2 mouse_down_pos() const { return mouse_down_; }
		Vector2 mouse_pos() const { return mouse_; }
		Vector2 mouse_delta() const { return mouse_ - mouse_down_; }
		Vector2 mouse_inst_delta() const { return mouse_ - mouse_last_; }
		//void set_status(InputStatus status) {status_ = status; }
	protected:
		virtual void OnContentInitialized() {};
	public:
		//InputStatus status() const { return status_; }
		shared_ptr<GlContent> content() const { return content_; }
		void set_content(const shared_ptr<GlContent>& content) { content_ = content; OnContentInitialized(); }
		bool GetInput(int index, Vector2& worldPos) const;
	public:
		UiEditorTool(void);
		~UiEditorTool(void);
	protected:
		Color elementColor_;
		int elementSize_;
		Stroke elementStroke_;
	protected:
		virtual void DoNew() {};
		virtual void DoNextInput() {};
		virtual void DoBeginInput() {};
		virtual void DoUpdateInput() {};
		virtual void DoEndInput() {};
		virtual void DoFixInput(const int index) {};
		virtual void DidCancel() {};
		virtual void DoDoubleClick() {}
		int NextInput();
	public:
		virtual OperationPtr PopNewOperation() = 0;

		virtual bool IsFinished() const = 0;
		//Called when receving enter key. Return true and set IsFinished if can
		virtual bool CanFinishByEnter() { return IsFinished(); };
		//virtual bool CanFixInput() const { return false; }
		void New();
		void Cancel();

		void BeginInput(const Vector2& worldPos);
		void UpdateInput(const Vector2& worldPos);
		void EndInput(const Vector2& worldPos);

		void DoubleClick(const Vector2& worldPos);

		void FixInput(const int index, const Vector2& worldPos);


		void UpdateElementColor( const COLORREF elementColor );
		void UpdateElementSize( int size );
		void UpdateElementStroke(Stroke stroke);
	protected:
		void HandleInput( const Vector2& worldPos );
		void TrySetElementColor();
		void TrySetElementSize();
		void TrySetElementStroke();
		shared_ptr<Point> inputPoint_;
		void DrawInputPoint(int maxCount) const;
	protected:
		Vector2 get_input(const int index) const;
	};
}


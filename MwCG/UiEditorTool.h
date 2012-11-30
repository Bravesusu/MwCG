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
		weak_ptr<GlContent> content_;
		//InputStatus status_;
		vector<Vector2> inputs_;
		int input_index;
		Vector2 mouse_;
		Vector2 mouse_down_;
		Vector2 mouse_last_;
		//Vector2 current_;
		shared_ptr<UiEdit> ui_;
		bool just_finished_;
		CMwCGDoc* doc_;
		CMwCGView* view_;
		bool is_new_;
	protected:
		//const shared_ptr<UiEdit> ui() const { return ui_; }
		CMwCGDoc* doc() const { return doc_; }
		CMwCGView* view() const { return view_; }
	public:
		void set_doc(CMwCGDoc* doc);
		void set_view(CMwCGView* view);
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
		void set_content(const shared_ptr<GlContent>& content) { content_ = content; OnContentInitialized(); }
	public:
		//InputStatus status() const { return status_; }
		shared_ptr<GlContent> content() const { return content_.lock(); }
		bool GetInput(size_t index, Vector2& worldPos) const;
	public:
		UiEditorTool(void);
		virtual ~UiEditorTool(void) = 0;
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
		bool IsNew() const { return is_new_; }
		void Cancel();

		void BeginInput(const Vector2& worldPos);
		void UpdateInput(const Vector2& worldPos);
		void EndInput(const Vector2& worldPos);

		virtual void OnDelete() {};

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
		void DrawInputPoint(size_t maxCount) const;
	protected:
		Vector2 get_input(const int index) const;
	public:
		bool TryFinish();
	protected:
		void NotifyToolOperation(const shared_ptr<IOperation>& operation);
		void NotifyToolPreview(const shared_ptr<IOperation>& operation);
		void NotifyToolUpdatePreview();
		void NotifyToolCommitPreview();
		void NotifyToolCancelPreview();
	};
}


#pragma once
#include "MwGLContent.h"
#include "IDrawable.h"
#include "IOperation.h"

namespace mw
{
	//enum InputStatus { AcceptUpdate, AcceptFix, AcceptNone };
	class UiEditorTool :
		public IDrawable
	{
	private:
		shared_ptr<GlContent> content_;
		//InputStatus status_;
		vector<Vector2> inputs_;
		int input_index;
		//Vector2 current_;
	protected:
		virtual shared_ptr<GlElement> GetEditingElement() { return NULL; }
	protected:
		int input_count() const { return inputs_.size(); }

		int currentIndex() const { return input_index; }
		Vector2 current() const { return inputs_.at(input_index); }

		//void set_status(InputStatus status) {status_ = status; }
	public:
		//InputStatus status() const { return status_; }
		shared_ptr<GlContent> content() const { return content_; }
		void set_content(const shared_ptr<GlContent>& content) { content_ = content; }
	public:
		UiEditorTool(void);
		~UiEditorTool(void);
	protected:
		Color elementColor_;
		int elementSize_;
	public:
		virtual OperationPtr PopNewOperation() = 0;
		virtual void DoNew() {};
		virtual void DoNextInput() {};
		virtual void DoUpdateInput() {};
		virtual void DoFixInput(const int index) {};
		virtual void DidCancel() {};
		virtual bool IsFinished() const = 0;
		void New();
		void Cancel();
		void UpdateInput(const Vector2& pos);
		void FixInput(const int index, const Vector2& pos);
		int NextInput();
		void UpdateElementColor( const COLORREF elementColor );
		void UpdateElementSize( int size );
	protected:
		void TrySetElementColor();
		void TrySetElementSize();
	};
}


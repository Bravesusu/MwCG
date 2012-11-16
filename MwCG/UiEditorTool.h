#pragma once
#include "MwGLContent.h"
#include "IDrawable.h"
#include "IOperation.h"

namespace mw
{
	enum InputStatus { AcceptUpdate, AcceptFix, AcceptNone };
	class UiEditorTool :
		public IDrawable
	{
	private:
		shared_ptr<GlContent> content_;
		InputStatus status_;
		Vector2 current_;
	protected:
		Vector2 current() const { return current_; }
		void set_status(InputStatus status) {status_ = status; }
	public:
		InputStatus status() const { return status_; }
		shared_ptr<GlContent> content() const { return content_; }
		void set_content(const shared_ptr<GlContent>& content) { content_ = content; }
	public:
		UiEditorTool(void);
		~UiEditorTool(void);
	public:
		virtual OperationPtr PopNewOperation() = 0;
		virtual void DoNew() {};
		virtual void DoNextInput() {};
		virtual void DoUpdateInput() {};
		virtual void DoCommitInput() {};
		virtual void DoFixInput() {};
		virtual void DidCancel() {};
		void New();
		void Cancel();
		bool IsFinished() const { return status_ == AcceptNone; }
		void NextInput(const Vector2& pos);
		void UpdateInput(const Vector2& pos);
		void FixInput(const Vector2& pos);
		void CommitInput();
	};
}


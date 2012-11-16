#pragma once
#include "MwGLContent.h"
#include "IDrawable.h"
#include "IOperation.h"

namespace mw
{
	class UiEditorTool :
		public IDrawable
	{
	private:
		shared_ptr<GlContent> content_;
		bool inputting_;
		Vector2 current_;
	protected:
		Vector2 current() const { return current_; }
	public:
		shared_ptr<GlContent> content() const { return content_; }
		void set_content(const shared_ptr<GlContent>& content) { content_ = content; }
	public:
		UiEditorTool(void);
		~UiEditorTool(void);
	public:
		virtual OperationPtr PopNewOperation() = 0;
		virtual void New() = 0;
		virtual bool IsFinished() const = 0;
		virtual bool IsIdle() const = 0;
		virtual void Cancel() = 0;
		virtual void DoBeginInput() = 0;
		virtual void DoUpdateInput() = 0;
		virtual void DoEndInput() = 0;
		bool IsInputting() const { return inputting_; }
		void BeginInput(const Vector2& pos);
		void UpdateInput(const Vector2& pos);
		void EndInput();
	};
}


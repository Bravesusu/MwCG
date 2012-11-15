#pragma once
#include "MwGLContent.h"
#include "IOperation.h"

namespace mw
{
	class UiEditorTool
	{
	private:
		shared_ptr<GlContent> content_;
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
		virtual bool IsInputting() const = 0;
		virtual void BeginInput(const Vector2& pos) = 0;;
		virtual void UpdateInput(const Vector2& pos) = 0;;
		virtual void EndInput() = 0;;
		virtual void Cancel() = 0;;
	};
}


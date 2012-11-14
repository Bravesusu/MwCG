#pragma once
#include "MwGLContent.h"

namespace mw
{
	class UiEditor
	{
	private:
		shared_ptr<GlContent> content_;
	public:
		shared_ptr<GlContent> content() const { return content_; }
		void set_content(const shared_ptr<GlContent>& content) { content_ = content; }
	public:
		UiEditor(void);
		~UiEditor(void);
	public:
		virtual void MouseLUp(const Vector2& pos) = 0;
		virtual void MouseMove(const Vector2& pos) = 0;
		virtual void MouseLDown(const Vector2& pos) = 0;

		virtual void KeyUp() = 0;
		virtual void KeyDown() = 0;
	};
}


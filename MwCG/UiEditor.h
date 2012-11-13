#pragma once

namespace mw
{
	class UiEditor
	{
	public:
		UiEditor(void);
		~UiEditor(void);
	public:
		virtual void MouseUp() = 0;
		virtual void MouseMouse() = 0;
		virtual void MouseDown() = 0;

		virtual void KeyUp() = 0;
		virtual void KeyDown() = 0;
	};
}


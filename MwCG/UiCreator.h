#pragma once
#include "UiEditorTool.h"

namespace mw
{
	class UiCreator :
		public UiEditorTool
	{
	public:
		UiCreator(void);
		~UiCreator(void);
	public:
		virtual void CommitInput() = 0;
		virtual bool IsFinished() const = 0;

		virtual void MouseLUp( const Vector2& pos );

		virtual void MouseMove( const Vector2& pos );

		virtual void MouseLDown( const Vector2& pos );

	};
}


#pragma once
#include "UiEditorTool.h"

namespace mw
{
	class UiSelector :
		public UiEditorTool
	{
	public:
		UiSelector(void);
		~UiSelector(void);

		virtual OperationPtr PopNewOperation();

		virtual void New();

		virtual bool IsFinished() const;

		virtual bool IsIdle() const;

		virtual bool IsInputting() const;

		virtual void BeginInput( const Vector2& pos );

		virtual void UpdateInput( const Vector2& pos );

		virtual void EndInput();

		virtual void Cancel();

	};
}


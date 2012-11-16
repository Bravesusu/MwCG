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

		virtual void Cancel();

		virtual void DoBeginInput();

		virtual void DoUpdateInput();

		virtual void DoEndInput();

		virtual void Draw();

	};
}


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

		virtual bool IsFinished() const;

		virtual void Draw();

	};
}


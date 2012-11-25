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

		virtual void DoNew();

		virtual void DoNextInput();

		virtual void DoUpdateInput();

		virtual void DoFixInput( const int index );

	};
}


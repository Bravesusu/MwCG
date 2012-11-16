#pragma once
#include "uieditortool.h"

namespace mw
{
	class Line;
	class LineTool :
		public UiEditorTool
	{
	private:
		shared_ptr<Line> line_;
		int input_count_;
		void DoInput();
	public:
		LineTool(void);
		~LineTool(void);

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

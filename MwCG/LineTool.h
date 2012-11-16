#pragma once
#include "uieditortool.h"

namespace mw
{
	class Line;
	class Point;
	class LineTool :
		public UiEditorTool
	{
	private:
		shared_ptr<Point> ptFrom_, ptTo_;
		shared_ptr<Line> line_;
		void DoInput();
	public:
		LineTool(void);
		~LineTool(void);

		virtual OperationPtr PopNewOperation();

		virtual void Draw();

		virtual void DoNew();

		virtual void DoUpdateInput();

		virtual void DoFixInput();

		virtual bool IsFinished() const;

	};
	
}

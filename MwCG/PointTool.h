#pragma once
#include "uieditortool.h"

namespace mw
{
	class Point;
	class PointDecorator;
	class PointTool :
		public UiEditorTool
	{
	private:
		bool isIdle_;
		shared_ptr<Point> point_;
		shared_ptr<PointDecorator> decorator_;
	public:
		PointTool(void);
		~PointTool(void);

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

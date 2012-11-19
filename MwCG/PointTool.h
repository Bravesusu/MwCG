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
		bool isFinished_;
		shared_ptr<Point> point_;
		shared_ptr<PointDecorator> decorator_;
	public:
		PointTool(void);
		~PointTool(void);

		virtual OperationPtr PopNewOperation();


		virtual void Draw();

		virtual void DoNew();

		virtual void DoNextInput();

		virtual void DoUpdateInput();

		virtual void DoFixInput();

		virtual bool IsFinished() const;

		virtual shared_ptr<GlElement> GetEditingElement();

	};
	
}

#pragma once
#include "TwoPointTool.h"

namespace mw
{
	class Line;
	class Point;
	class LineTool :
		public TwoPointTool
	{
	private:
		shared_ptr<Line> line_;
	public:
		LineTool(void);
		~LineTool(void);

		virtual OperationPtr PopNewOperation();

		virtual void OnFirstPoint( const Vector2& point );

		virtual void OnSecondPoint( const Vector2& point );

		virtual void OnNew();

		virtual void OnDraw();

	};
	
}

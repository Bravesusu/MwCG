#pragma once
#include "twopointtool.h"

namespace mw
{
	class Circle;
	class CircleTool :
		public TwoPointTool
	{
	private:
		shared_ptr<Circle> circle_;
	public:
		CircleTool(void);
		~CircleTool(void);

		virtual void OnFirstPoint( const Vector2& worldPos );

		virtual void OnSecondPoint( const Vector2& worldPos );

		virtual void OnNew();

		virtual void OnDraw();

		virtual OperationPtr PopNewOperation();

		virtual shared_ptr<GlElement> GetEditingElement();

	};
}


#pragma once
#include "TwoPointTool.h"
#include "AddElementToContent.h"

namespace mw
{
	//class Line;
	//class Point;
	template<class TLine>
	class LineTool :
		public TwoPointTool
	{
	private:
		shared_ptr<TLine> line_;
	public:
		LineTool(void)
		{
			//static_assert(is_base_of(Line, TLine)::value);
		}

		~LineTool(void)
		{

		}

		virtual OperationPtr PopNewOperation()
		{
			//TRACE("Try pop operation\n");
			if (!IsFinished())
				return NULL;
			return OperationPtr(new AddElementToContent(content(), line_));
		}

		virtual void OnFirstPoint( const Vector2& point )
		{
			line_->set_position(point);
			line_->set_from(0, 0);
			line_->set_to(0, 0);
		}

		virtual void OnSecondPoint( const Vector2& point )
		{
			Vector2 pos = point;
			line_->transform().WorldToLocal(pos);
			line_->set_to(pos);
		}

		virtual void OnNew()
		{
			line_.reset(new TLine());
		}

		virtual void OnDraw()
		{
			line_->Draw();
		}

		virtual shared_ptr<GlElement> GetEditingElement()
		{
			return line_;
		}

	};
	
}

#pragma once
#include "uieditortool.h"

namespace mw
{
	class Line;
	class Point;
	class TwoPointTool :
		public UiEditorTool
	{
	private:
		shared_ptr<Point> ptFrom_, ptTo_;
		void DoInput();
	public:
		TwoPointTool(void);
		~TwoPointTool(void);
	public:
		void Draw();

		void DoNew();

		void DoUpdateInput();

		void DoFixInput();

		bool IsFinished() const;
	private:
		virtual void OnFirstPoint(const Vector2& point) {};
		virtual void OnSecondPoint(const Vector2& point) {};
		virtual void OnNew() {};
		virtual void OnDraw() {};
	};
	
}

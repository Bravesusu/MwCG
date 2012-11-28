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
		shared_ptr<Point> first_, second_;
		void DoInput(int index);
	public:
		Vector2 first() const;
		Vector2 second() const;
	public:
		TwoPointTool(void);
		~TwoPointTool(void);
	public:
		void Draw();

		void DoNew();

		void DoUpdateInput();

		virtual void DoFixInput( const int index );

		bool IsFinished() const;
	private:
		virtual void OnFirstPoint(const Vector2& worldPos) {};
		virtual void OnSecondPoint(const Vector2& worldPos) {};
		virtual void OnNew() {};
		virtual void OnDraw() {};
	};
	
}

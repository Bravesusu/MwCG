#pragma once
#include "mwglelement.h"
#include "MwVector2.h"
#include "MwLine.h"

namespace mw
{
	class GlScreen;
	class Line;
	class Mouse :
		public GlElement
	{
	public:
		Mouse(void);
		~Mouse(void);
	private:
		Vector2 position_;
		Line line_v_, line_h_;
	public:
		Vector2 position() const { return position_; }
		void set_position(float x, float y) { position_.set(x, y); }
		void set_position(const Vector2& pos) { position_.set(pos); }
	private:
		void DoDraw();

		virtual Rect bound() const;

	};
};


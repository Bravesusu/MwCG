#pragma once
#include "mwglelement.h"

namespace mw
{
	class Circle :
		public GlElement
	{
	private:
		Vector2 center_;
		float radius_;
	public:
		Vector2 center() const { return center_; }
		void set_center(const Vector2& center) { center_ = center; }
		float radius() const { return radius_; }
		void set_radius(float radius) { radius_ = radius; }
	public:
		Circle(void);
		~Circle(void);

		virtual void DoDraw();

		virtual bool HitTest();

		virtual Rect bound() const;

		virtual void Draw();

	};
	
}

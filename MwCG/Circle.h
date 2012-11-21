#pragma once
#include "mwglelement.h"
#include "PixelStroker.h"

namespace mw
{
	class Circle :
		public GlElement
	{
		DECLARE_SERIAL(Circle);
	private:
		Vector2 center_;
		float radius_;
		PixelStroker stroker_;
	public:
		Vector2 center() const { return center_; }
		void set_center(const Vector2& center) { center_ = center; }
		float radius() const { return radius_; }
		void set_radius(float radius) { radius_ = radius; }
	public:
		Circle(void);
		~Circle(void);

		virtual void DoDraw();

		//virtual bool HitTest();

		virtual Rect bound() const;

		virtual void Serialize( CArchive& ar );

	private:
		void MidPointCircle(int cx, int cy, int radius);
		void Plot8Points(int cx, int cy, int x, int y);
		void Plot4Points(int cx, int cy, int x, int y);

	};
	
}

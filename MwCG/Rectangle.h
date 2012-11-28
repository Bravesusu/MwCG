#pragma once
#include "mwglelement.h"
#include "RectBase.h"

namespace mw
{
	class Rect;
	class Rectangle :
		public GlElement,
		public RectBase
	{
	public:
		Rectangle(void);
		Rectangle(const Rectangle& rect) : RectBase(rect) {}
		Rectangle(float left, float right, float top, float bottom);
		Rectangle(const Vector2& point1, const Vector2& point2);
		~Rectangle(void);

		virtual void Serialize( CArchive& ar );

		virtual void DoDraw();

		//virtual bool HitTest();

		virtual Rect bound() const;

	};
}

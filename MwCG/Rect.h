#pragma once
#include "RectBase.h"

namespace mw
{
	class Vector2;
	class GlObject;
	class Rect :
		public GlObject,
		public RectBase
	{
		DECLARE_SERIAL(Rect);
	public:
		Rect(void);
		Rect(float left, float right, float top, float bottom);
		Rect(const Vector2& point1, const Vector2& point2);
		Rect(const Rect& rect) : RectBase(rect) {}
		~Rect(void);

		virtual void Serialize( CArchive& ar );

		virtual void GL();

	};
}


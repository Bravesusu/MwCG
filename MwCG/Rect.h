#pragma once

namespace mw
{
	class Vector2;
	class MwGLObject;
	class Rect :
		public MwGLObject
	{
		DECLARE_SERIAL(Rect);
	private:
		float left_, right_, top_, bottom_;
	public:
		Rect(void);
		Rect(float left, float right, float top, float bottom);
		Rect(const Vector2& point1, const Vector2& point2);
		~Rect(void);

		virtual void Serialize( CArchive& ar );

		virtual void GL();

	};
}


#pragma once
#include "mwglelement.h"
#include "MwVector2.h"
#include <vector>

namespace mw
{
	class Point :
		public GlElement
	{
		DECLARE_SERIAL(Point)
		vector<int> test;
	public:
		Point(void) {};
		~Point(void);
		Point(float x, float y, float size = 1.0) { transform().position().set(x, y); } ;
		//Serialization
	public:
		virtual void Serialize(CArchive& ar);
	private:
		void DoDraw();

		virtual bool HitTest( const Vector2& worldPos ) const;

		virtual Rect bound() const;

	};

	
}

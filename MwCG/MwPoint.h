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
		Point(float x, float y, float size = 1.0) : position_(x, y) {} ;
		//Serialization
	private:
		Vector2 position_;
	public:
		Vector2 position() const { return position_; }
		void set_position(float x, float y) { position_.set(x, y); }
		void set_position(const Vector2& pos) { position_.set(pos); }
	public:
		virtual void Serialize(CArchive& ar);
	private:
		void DoDraw();
	};

	
}

#pragma once
#include "mwglelement.h"
#include "MwVector2.h"

namespace mw
{
	class Sierpinski :
		public GlElement
	{
		DECLARE_SERIAL(Sierpinski);
	private:
		int point_count_;
		Vector2 vertex_[3];
	public:
		Vector2& operator[] (int index);
		const Vector2& operator[] (int index) const;
		Sierpinski(void) : point_count_(5000) {};
		Sierpinski(const Vector2& v1, const Vector2& v2, const Vector2& v3);
		~Sierpinski(void);
		int point_count() { return point_count_; }
		void set_point_count(int count) { point_count_ = count; }
		//Serialization
	public:
		virtual void Serialize(CArchive& ar);
		void Draw();
	};
	
}

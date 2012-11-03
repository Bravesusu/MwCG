#pragma once
#include "mwx.h"

#define VECTOR2F(x, y) new MwVector2(x, y)

namespace mw
{
	class MwVector2 :
		public MwGLObject
	{
		DECLARE_SERIAL(MwVector2)
	private:
		float x_;
		float y_;
	public:
		MwVector2(void) : x_(0), y_(0) {};
		MwVector2(float fx, float fy) : x_(fx), y_(fy){};
		MwVector2(const MwVector2 & v2) : x_(v2.x_), y_(v2.y_) {}
		~MwVector2(void);
	public:
		float x() const { return x_; }
		float y() const { return y_; }
		float set_x(float fx) { x_ = fx; }
		float set_y(float fy) { y_ = fy; }
		void set(float fx, float fy) { x_ = fx; y_ = fy; }
	public:
		inline void GL();
		void Trace();
		void Serialize(CArchive& ar);
	public:
		MwVector2 operator+(const MwVector2& rhs) const;
		MwVector2& operator+=(const MwVector2& rhs);
		MwVector2 operator/(float f) const;
		MwVector2& operator/=(float f);
		MwVector2& operator =(const MwVector2 & rhs);
	};
	
}

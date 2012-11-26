#pragma once
#include "mwx.h"

#define VECTOR2F(x, y) new Vector2(x, y)

namespace mw
{
	class Vector2 :
		public GlObject
	{
		DECLARE_SERIAL(Vector2)
	private:
		float x_;
		float y_;
	public:
		Vector2(void) : x_(0), y_(0) {};
		Vector2(float fx, float fy) : x_(fx), y_(fy){};
		Vector2(const Vector2 & v2) : x_(v2.x_), y_(v2.y_) {}
		~Vector2(void);
	public:
		float x() const { return x_; }
		float y() const { return y_; }
		void set_x(float fx) { x_ = fx; }
		void set_y(float fy) { y_ = fy; }
		void set(float fx, float fy) { x_ = fx; y_ = fy; }
		void set(const Vector2& pos) { x_ = pos.x_; y_ = pos.y_; }
	public:
		void GL();
		void Trace();
		void Serialize(CArchive& ar);
	public:
		float magnitude() const;
		Vector2 operator+(const Vector2& rhs) const;
		Vector2& operator+=(const Vector2& rhs);
		Vector2 operator-(const Vector2& rhs) const;
		Vector2& operator-=(const Vector2& rhs);
		Vector2 operator/(float f) const;
		Vector2& operator/=(float f);
		Vector2& operator =(const Vector2 & rhs);
		Vector2 operator*(float f) const;
		Vector2& operator*=(float f);
		float Dot(const Vector2& rhs) const;
	public:
		void Vertex() const;
	};

	Vector2 operator*(float lhs, const Vector2& rhs);
	
	void glVertex(const Vector2& vector);
}

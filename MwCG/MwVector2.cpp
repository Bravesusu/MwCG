#include "stdafx.h"
#include "MwVector2.h"

using namespace mw;

IMPLEMENT_SERIAL(Vector2, GlObject, 1);

Vector2::~Vector2(void)
{
}

void Vector2::Serialize(CArchive& ar)
{
	GlObject::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar<<x_<<y_;
	}
	else
	{	// loading code
		ar>>x_>>y_;
	}
}

void Vector2::GL() 
{ 
	glVertex2f(x_, y_); 
}

void Vector2::Trace() 
{ 
	TRACE("%f, %f\n", x_, y_); 
}


Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x_ + other.x_, y_ + other.y_);
}


Vector2& Vector2::operator+=(const Vector2& other) 
{
	x_ += other.x_;
	y_ += other.y_;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x_ - other.x_, y_ - other.y_);
}


Vector2& Vector2::operator-=(const Vector2& other) 
{
	x_ -= other.x_;
	y_ -= other.y_;
	return *this;
}

Vector2 Vector2::operator/(float f) const
{
	return Vector2(x_ / f, y_ / f);
}


Vector2& Vector2::operator/=(float f)
{
	x_ /= f;
	y_ /= f;
	return *this;
}


Vector2& Vector2::operator =(const Vector2 & rhs)
{
	set(rhs.x_, rhs.y_);
	return *this;
}

void Vector2::Vertex() const
{
	glVertex2f(x_, y_);
}

void Vertex(const Vector2& vector) 
{
	vector.Vertex();
}

float mw::Vector2::magnitude() const
{
	return sqrt(x_ * x_ + y_ * y_);
}

float mw::Vector2::Dot( const Vector2& rhs ) const
{
	return x_ * rhs.x_ + y_ * rhs.y_;
}

mw::Vector2 mw::Vector2::operator*( float f ) const
{
	return Vector2(x_ * f, y_ * f);
}

Vector2& mw::Vector2::operator*=( float f )
{
	x_ *= f;
	y_ *= f;
	return *this;
}

bool mw::Vector2::operator==( const Vector2& rhs ) const
{
	return x_ == rhs.x_ && y_ == rhs.y_;
}

bool mw::Vector2::operator!=( const Vector2& rhs ) const
{
	return x_ != rhs.x_ || y_ != rhs.y_;
}

Vector2 mw::operator*( float lhs, const Vector2& rhs )
{
	return Vector2(lhs * rhs.x(), lhs * rhs.y());
}

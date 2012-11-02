#include "stdafx.h"
#include "MwVector2.h"

IMPLEMENT_SERIAL(MwVector2, MwGLObject, 1);

MwVector2::~MwVector2(void)
{
}

void MwVector2::Serialize(CArchive& ar)
{
	MwGLObject::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar<<x_<<y_;
	}
	else
	{	// loading code
		ar>>x_>>y_;
	}
}

void MwVector2::GL() 
{ 
	glVertex2f(x_, y_); 
}

void MwVector2::Trace() 
{ 
	TRACE("%f, %f\n", x_, y_); 
}


MwVector2 MwVector2::operator+(const MwVector2& other) const
{
	return MwVector2(x_ + other.x_, y_ + other.y_);
}


MwVector2& MwVector2::operator+=(const MwVector2& other) 
{
	x_ += other.x_;
	y_ += other.y_;
	return *this;
}

MwVector2 MwVector2::operator/(float f) const
{
	return MwVector2(x_ / f, y_ / f);
}


MwVector2& MwVector2::operator/=(float f)
{
	x_ /= f;
	y_ /= f;
	return *this;
}


MwVector2& MwVector2::operator =(const MwVector2 & rhs)
{
	set(rhs.x_, rhs.y_);
	return *this;
}
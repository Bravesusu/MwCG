#include "stdafx.h"
#include "Circle.h"
#include "Rect.h"

using namespace mw;
Circle::Circle(void)
{
}


Circle::~Circle(void)
{
}

void FooCircle(float x, float y, float r, int segments)
{
	glBegin( GL_LINE_LOOP );
	glVertex2f(x, y);
	for( int n = 0; n <= segments; ++n ) {
		float const t = 2*3.14*(float)n/(float)segments;
		glVertex2f(x + sin(t)*r, y + cos(t)*r);
	}
	glEnd();
}


void mw::Circle::DoDraw()
{
	FooCircle(center_.x(), center_.y(), radius_, 100);
}

//bool mw::Circle::HitTest()
//{
//	return false;
//}

Rect mw::Circle::bound() const
{
	return Rect(
		center_.x() - radius_, 
		center_.x() + radius_,
		center_.y() + radius_,
		center_.y() - radius_
		);
}
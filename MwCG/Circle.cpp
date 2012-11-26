#include "stdafx.h"
#include "Circle.h"
#include "Rect.h"

using namespace mw;

IMPLEMENT_SERIAL(Circle, GlElement, 1);

Circle::Circle(void)
{
	stroker_.set_auto(false);
}


Circle::~Circle(void)
{
}

// 'cx' and 'cy' denote the offset of the circle center from the origin.
void Circle::MidPointCircle(int cx, int cy, int radius)
{
	int error = -radius;
	int x = radius;
	int y = 0;

	// The following while loop may be altered to 'while (x > y)' for a
	// performance benefit, as long as a call to 'plot4points' follows
	// the body of the loop. This allows for the elimination of the
	// '(x != y)' test in 'plot8points', providing a further benefit.
	//
	// For the sake of clarity, this is not shown here.
	while (x >= y)
	{
		stroker_++;
		Plot8Points(cx, cy, x, y);

		error += y;
		++y;
		error += y;

		// The following test may be implemented in assembly language in
		// most machines by testing the carry flag after adding 'y' to
		// the value of 'error' in the previous step, since 'error'
		// nominally has a negative value.
		if (error >= 0)
		{
			error -= x;
			--x;
			error -= x;
		}
	}
}

void Circle::Plot8Points(int cx, int cy, int x, int y)
{
	Plot4Points(cx, cy, x, y);
	if (x != y) Plot4Points(cx, cy, y, x);
}

// The '(x != 0 && y != 0)' test in the last line of this function
// may be omitted for a performance benefit if the radius of the
// circle is known to be non-zero.
void Circle::Plot4Points(int cx, int cy, int x, int y)
{
	stroker_.SetPixel(cx + x, cy + y);
	if (x != 0) stroker_.SetPixel(cx - x, cy + y);
	if (y != 0) stroker_.SetPixel(cx + x, cy - y);
	if (x != 0 && y != 0) stroker_.SetPixel(cx - x, cy - y);
}

void mw::Circle::DoDraw()
{
	//glEnable(GL_LINE_STIPPLE);
	//glLineWidth(size());
	//glLineStipple(size(), stroke().pattern);
	//FooCircle(center_.x(), center_.y(), radius_, 100);
	//glDisable(GL_LINE_STIPPLE);
	stroker_.set_stroke(stroke());
	glPointSize(size());
	stroker_.Reset();
	MidPointCircle(0, 0, radius_);
}

//bool mw::Circle::HitTest()
//{
//	return false;
//}

Rect mw::Circle::bound() const
{
	return Rect(
		-radius_, 
		radius_,
		radius_,
		-radius_
		);
}

void mw::Circle::Serialize( CArchive& ar )
{
	GlElement::Serialize(ar);

	if (ar.IsStoring())
	{
		ar<<radius_;
	}
	else
	{
		ar>>radius_;
	}
}

bool mw::Circle::HitTest( const Vector2& worldPos ) const
{
	Vector2 delta = worldPos - center();

	float dist = delta.magnitude();

	return dist < 3 || (dist > radius_ - 3 && dist < radius_ + 3);
}

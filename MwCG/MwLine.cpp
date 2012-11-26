#include "stdafx.h"
#include "MwLine.h"
#include "Rect.h"

using namespace mw;

IMPLEMENT_SERIAL(Line, GlElement, 1);

Line::Line(void)
{
}

Line::~Line(void)
{
}


Line::Line(float x1, float y1, float x2, float y2)
{
	point_from_.set(x1, y1);
	point_to_.set(x2, y2);
}

void Line::Serialize(CArchive& ar)
{
	GlElement::Serialize(ar);

	point_from_.Serialize(ar);
	point_to_.Serialize(ar);
	if (ar.IsStoring())
	{	
	}
	else
	{	
		// loading code
	}
}

void Line::DoDraw()
{
	//color()();
	glLineWidth(size());

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(size(), stroke().pattern);
	glBegin(GL_LINES);
	point_from_();
	point_to_();
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

Rect mw::Line::bound() const
{
	//TODO: cache result and update only when changed
	return Rect(point_from_, point_to_);
}

bool mw::Line::HitTest( const Vector2& worldPos ) const
{
	//Ref: http://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
	Vector2 n = point_to_ - point_from_;
	Vector2 a = transform().position();
	Vector2 p = worldPos;
	Vector2 a_p = a - p;
	Vector2 n1 = n / n.magnitude();
	float dist = (a_p - (n1 * (a_p.Dot(n1)))).magnitude();
	TRACE("Dist: %.2f\n", dist);
	return dist < 3;
}

#include "stdafx.h"
#include "MwPoint.h"
#include "Rect.h"

using namespace mw;

IMPLEMENT_SERIAL(Point, GlElement, 1);

Point::~Point(void)
{
}

void Point::Serialize(CArchive& ar)
{
	GlElement::Serialize(ar);

}

void Point::DoDraw()
{
	//color()();
	glPointSize(size_f());
	glBegin(GL_POINTS);
	glVertex2i(0, 0);
	//Vertex(position_);
	glEnd();
}

bool mw::Point::HitTest( const Vector2& worldPos ) const
{
	Vector2 delta = worldPos - transform().position();
	return delta.magnitude() < 2 * size();
}

Rect mw::Point::bound() const
{
	float s = size() * 0.6f;
	return Rect(-s, s, s, -s);
}

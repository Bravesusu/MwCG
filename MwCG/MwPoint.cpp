#include "stdafx.h"
#include "MwPoint.h"

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
	glPointSize(size());
	glBegin(GL_POINTS);
	glVertex2i(0, 0);
	//Vertex(position_);
	glEnd();
}
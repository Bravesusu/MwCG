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

	position_.Serialize(ar);

	if (ar.IsStoring())
	{	
		// storing code
		ar<<size_;
	}
	else
	{	
		// loading code
		ar>>size_;
	}
}

void Point::Draw()
{
	color()();
	glPointSize(size_);
	glBegin(GL_POINTS);
	position_();
	glEnd();
}
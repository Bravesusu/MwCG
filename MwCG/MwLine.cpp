#include "stdafx.h"
#include "MwLine.h"
#include "Rect.h"

using namespace mw;

IMPLEMENT_SERIAL(Line, GlElement, 1);

Line::Line(void) :  pattern_(0xFFFF)
{
}

Line::~Line(void)
{
}


Line::Line(float x1, float y1, float x2, float y2) : pattern_(0xFFFF)
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
	glLineStipple(1, pattern_);
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

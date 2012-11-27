#include "stdafx.h"
#include "Rectangle.h"
#include "Rect.h"

using namespace mw;

Rectangle::Rectangle(void)
{
}


Rectangle::~Rectangle(void)
{
}

void mw::Rectangle::Serialize( CArchive& ar )
{
}

void mw::Rectangle::DoDraw()
{
	//DoGL();
	glEnable(GL_LINE_STIPPLE);
	glLineWidth(size());
	glLineStipple(size(), stroke().pattern);
	glBegin(GL_LINE_LOOP);
	glVertex2f(left(), top());
	glVertex2f(right(), top());
	glVertex2f(right(), bottom());
	glVertex2f(left(), bottom());
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

//bool mw::Rectangle::HitTest()
//{
//}

Rect mw::Rectangle::bound() const
{
	return get<Rect>();
}
#include "stdafx.h"
#include "MwLine.h"

IMPLEMENT_SERIAL(MwLine, MwGLElement, 1);

MwLine::MwLine(void)
{
}

MwLine::~MwLine(void)
{
}


MwLine::MwLine(float x1, float y1, float x2, float y2)
{
	point_from_.set(x1, y1);
	point_to_.set(x2, y2);
}

void MwLine::Serialize(CArchive& ar)
{
	MwGLElement::Serialize(ar);

	if (ar.IsStoring())
	{	
		// storing code
	}
	else
	{	
		// loading code
	}
}

void MwLine::Draw()
{
	color()();
	glBegin(GL_LINES);
	point_from_();
	//glVertex2f(Point1.x, Point1.y);
	point_to_();
	//glVertex2f(Point2.x, Point2.y);
	glEnd();
}
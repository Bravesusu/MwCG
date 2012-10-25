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
	Point1.x = x1;
	Point1.y = y1;
	Point2.x = x2;
	Point2.y = y2;
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
	glBegin(GL_LINE);
	Color();
	Point1();
	Point2();
	glEnd();
}
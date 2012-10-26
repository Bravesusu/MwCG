#include "stdafx.h"
#include "MwPoint.h"

IMPLEMENT_SERIAL(MwPoint, MwGLElement, 1);

MwPoint::MwPoint(void)
{
	Size = 1;
}

MwPoint::MwPoint(float x, float y, float size)
{
	Position.x = x;
	Position.y = y;
	this->Size = size;
}


MwPoint::~MwPoint(void)
{
}

void MwPoint::Serialize(CArchive& ar)
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

void MwPoint::Draw()
{
	Color();
	glPointSize(Size);
	glBegin(GL_POINTS);
	Position();
	glEnd();
}
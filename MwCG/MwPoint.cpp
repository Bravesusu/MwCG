#include "stdafx.h"
#include "MwPoint.h"

IMPLEMENT_SERIAL(MwPoint, MwGLElement, 1);

MwPoint::MwPoint(void)
{
}

MwPoint::MwPoint(float x, float y)
{
	Position.x = x;
	Position.y = y;
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
	glBegin(GL_POINT);
	Color();
	Position();
	glEnd();
}
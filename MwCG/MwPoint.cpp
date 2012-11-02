#include "stdafx.h"
#include "MwPoint.h"

IMPLEMENT_SERIAL(MwPoint, MwGLElement, 1);

MwPoint::~MwPoint(void)
{
}

void MwPoint::Serialize(CArchive& ar)
{
	MwGLElement::Serialize(ar);

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

void MwPoint::Draw()
{
	color()();
	glPointSize(size_);
	glBegin(GL_POINTS);
	position_();
	glEnd();
}
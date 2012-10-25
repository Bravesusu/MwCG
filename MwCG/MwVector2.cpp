#include "stdafx.h"
#include "MwVector2.h"

IMPLEMENT_SERIAL(MwVector2, MwGLObject, 1);

MwVector2::MwVector2(void)
{
}


MwVector2::~MwVector2(void)
{
}

MwVector2::MwVector2(float fx, float fy) 
{ 
	x = fx; 
	y = fy;
}

void MwVector2::Serialize(CArchive& ar)
{
	MwGLObject::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar<<x<<y;
	}
	else
	{	// loading code
		ar>>x>>y;
	}
}

void MwVector2::GL() 
{ 
	glVertex2f(x, y); 
}

void MwVector2::Trace() 
{ 
	TRACE("%f, %f", x, y); 
}
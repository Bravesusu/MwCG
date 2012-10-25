#include "stdafx.h"
#include "MwGLContent.h"

IMPLEMENT_SERIAL(MwGLContent, CObject, 1)

MwGLContent::MwGLContent(void)
{
	FooPoint = VECTOR2F(0, 0);
	ClearColor = RGB(1.0, 1.0, 1.0);
}


MwGLContent::~MwGLContent(void)
{
	delete FooPoint;
	delete ClearColor;
}


void MwGLContent::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{	// storing code
		ar<<ClearColor<<FooPoint;
	}
	else
	{	// loading code
		ar>>ClearColor>>FooPoint;
	}
}

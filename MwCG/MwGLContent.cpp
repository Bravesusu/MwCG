#include "stdafx.h"
#include "MwGLContent.h"

IMPLEMENT_SERIAL(MwGLContent, CObject, 1)

MwGLContent::MwGLContent(void)
{
	FooPoint = new MwVector2();
}


MwGLContent::~MwGLContent(void)
{
	delete FooPoint;
}


void MwGLContent::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{	// storing code
		ar<<FooPoint;
	}
	else
	{	// loading code
		ar>>FooPoint;
	}
}

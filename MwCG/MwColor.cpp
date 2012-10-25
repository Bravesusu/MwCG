#include "stdafx.h"
#include "MwColor.h"

IMPLEMENT_SERIAL(MwColor, MwGLObject, 1);

MwColor::MwColor(void)
{
}


MwColor::~MwColor(void)
{
}

void MwColor::GL()
{
	glColor4f(r, g, b, a);
}

void MwColor::GL(bool clear)
{
	if (!clear)
		GL();
	else 
		glClearColor(r, g, b, a);
}

void MwColor::Serialize(CArchive& ar)
{
	MwGLObject::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar<<r<<g<<b<<a;
	}
	else
	{	// loading code
		ar>>r>>g>>b>>a;
	}
}
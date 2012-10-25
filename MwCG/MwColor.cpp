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
void MwColor::SetColorRef(COLORREF color)
{
	r = GetRValue(color) / (float)256;
	g = GetGValue(color) / (float)256;
	b = GetBValue(color) / (float)256;
}
COLORREF MwColor::GetColorRef()
{
	return RGB(r, g, b);
}
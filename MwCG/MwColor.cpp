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
	glColor3f(r_, g_, b_);
}

void MwColor::Serialize(CArchive& ar)
{
	MwGLObject::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar<<r_<<g_<<b_<<a_;
	}
	else
	{	// loading code
		ar>>r_>>g_>>b_>>a_;
	}
}
void MwColor::set(COLORREF color)
{
	r_ = GetRValue(color) / (float)256;
	g_ = GetGValue(color) / (float)256;
	b_ = GetBValue(color) / (float)256;
	a_ = 1.0;
}



void MwColor::set(const MwColor& color)
{
	r_ = color.r_;
	g_ = color.g_;
	b_ = color.b_;
	a_ = color.a_;
}


void MwColor::set(float r, float g, float b, float a)
{
	r_ = r;
	g_ = g;
	b_ = b;
	a_ = a;
}

COLORREF MwColor::get_color_ref()
{
	return RGB(r_, g_, b_);
}


MwColor& MwColor::operator =(const MwColor & rhs)
{
	set(rhs);
	return *this;
}
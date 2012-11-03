#include "stdafx.h"
#include "MwColor.h"

using namespace mw;

IMPLEMENT_SERIAL(Color, MwGLObject, 1);

Color::Color(void)
{
}


Color::~Color(void)
{
}

void Color::GL()
{
	glColor3f(r_, g_, b_);
}

void Color::Serialize(CArchive& ar)
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
void Color::set(COLORREF color)
{
	r_ = GetRValue(color) / (float)256;
	g_ = GetGValue(color) / (float)256;
	b_ = GetBValue(color) / (float)256;
	a_ = 1.0;
}



void Color::set(const Color& color)
{
	r_ = color.r_;
	g_ = color.g_;
	b_ = color.b_;
	a_ = color.a_;
}


void Color::set(float r, float g, float b, float a)
{
	r_ = r;
	g_ = g;
	b_ = b;
	a_ = a;
}

COLORREF Color::get_color_ref()
{
	return RGB(r_, g_, b_);
}


Color& Color::operator =(const Color & rhs)
{
	set(rhs);
	return *this;
}
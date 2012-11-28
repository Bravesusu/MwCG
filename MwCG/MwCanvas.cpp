#include "stdafx.h"
#include "MwCanvas.h"

#include "MwGlScreen.h"
#include "Rect.h"

using namespace mw;

IMPLEMENT_SERIAL(Canvas, GlElement, 1);

Canvas::Canvas(void)
{
	gird_line_.set_color(0, 0, 0);
}

Canvas::~Canvas(void)
{
}

void Canvas::Serialize(CArchive& ar)
{
	GlElement::Serialize(ar);

	if (ar.IsStoring())
	{	
		// storing code
	}
	else
	{	
		// loading code
	}
}

void Canvas::DoDraw()
{
	color().Clear();
	::glClear(GL_COLOR_BUFFER_BIT);
	if (enable_gird_)
		DrawAxisGird();
}

void Canvas::DrawAxisGird() 
{
	float left = screen()->left();
	float right = screen()->right();
	float top = screen()->top();
	float bottom = screen()->bottom();

	//Draw axis
	gird_line_.set_size(2);

	gird_line_.set(0, top, 0, bottom);
	gird_line_.Draw();
	gird_line_.set(left, 0, right, 0);
	gird_line_.Draw();

	int gird_unit = 100;
	int x_min = (int)left / gird_unit * gird_unit;
	int x_max = (int)right / gird_unit * gird_unit;

	gird_line_.set_size(1);
	for (int x = x_min; x <= x_max; x += gird_unit)
	{
		gird_line_.set(x, top, x, bottom);
		gird_line_.Draw();
	}

	int y_max = (int)top / gird_unit * gird_unit;
	int y_min = (int)bottom / gird_unit * gird_unit;

	for (int y = y_min; y <= y_max; y += gird_unit)
	{
		gird_line_.set(left, y, right, y);
		gird_line_.Draw();
	}
}

Rect mw::Canvas::bound() const
{
	return GlElement::bound();
}

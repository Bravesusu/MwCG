#include "stdafx.h"
#include "MwCanvas.h"

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

void Canvas::Draw()
{
	color().Clear();
	::glClear(GL_COLOR_BUFFER_BIT);
	DrawAxisGird();
}

void Canvas::DrawAxisGird() 
{
	float left = screen()->left();
	float right = screen()->right();
	float top = screen()->top();
	float bottom = screen()->bottom();

	//Draw axis
	gird_line_.set_width(2);

	gird_line_.set(0, top, 0, bottom);
	gird_line_.Draw();
	gird_line_.set(left, 0, right, 0);
	gird_line_.Draw();

	int x_min = (int)left;
	int x_max = (int)right;

	gird_line_.set_width(1);
	if (x_min < 0)
	{
		for (int x = 0; x > x_min; x -= 100)
		{
			gird_line_.set(x, top, x, bottom);
			gird_line_.Draw();
		}
		if (x_max > 0)
			for (int x = 0; x < x_max; x += 100)
			{
				gird_line_.set(x, top, x, bottom);
				gird_line_.Draw();
			}
	}
}
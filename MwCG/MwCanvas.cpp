#include "stdafx.h"
#include "MwCanvas.h"

using namespace mw;

IMPLEMENT_SERIAL(Canvas, GlElement, 1);

Canvas::Canvas(void)
{
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
}
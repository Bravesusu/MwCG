#include "stdafx.h"
#include "MwCanvas.h"


IMPLEMENT_SERIAL(MwCanvas, MwGLElement, 1);
MwCanvas::MwCanvas(void) : Width(DefaultWidth), Height(DefaultHeight)
{
	ClearColor = MwRGB(1, 1, 1);
}

MwCanvas::MwCanvas(int width, int height) : Width(width), Height(height)
{
	ClearColor = MwRGB(1, 1, 1);
}

MwCanvas::MwCanvas(int width, int height, MwColor& color) : Width(width), Height(height)
{
	ClearColor = MwRGBA(color.r, color.g, color.b, color.a);
}

MwCanvas::~MwCanvas(void)
{
	delete ClearColor;
}

void MwCanvas::Serialize(CArchive& ar)
{
	MwGLElement::Serialize(ar);

	if (ar.IsStoring())
	{	
		// storing code
		ar<<Width<<Height<<ClearColor;
	}
	else
	{	
		// loading code
		ar>>Width>>Height>>ClearColor;
	}
}

void MwCanvas::Draw()
{
	(*ClearColor)(true);
    glClear(GL_COLOR_BUFFER_BIT);
}
#include "stdafx.h"
#include "MwCanvas.h"


IMPLEMENT_SERIAL(MwCanvas, MwGLElement, 1);
MwCanvas::MwCanvas(void) : Width(DefaultWidth), Height(DefaultHeight)
{
}

MwCanvas::MwCanvas(int width, int height) : Width(width), Height(height)
{
}

MwCanvas::~MwCanvas(void)
{
}

void MwCanvas::Serialize(CArchive& ar)
{
	MwGLElement::Serialize(ar);

	if (ar.IsStoring())
	{	
		// storing code
		ar<<Width<<Height;
	}
	else
	{	
		// loading code
		ar>>Width>>Height;
	}
}

void MwCanvas::Draw()
{
	glClearColor(Color.r, Color.g, Color.b, Color.a);
	//Color.GL(true);
    glClear(GL_COLOR_BUFFER_BIT);
}
#include "stdafx.h"
#include "MwCanvas.h"

using namespace mw;

IMPLEMENT_SERIAL(MwCanvas, MwGLElement, 1);

MwCanvas::MwCanvas(void)
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
	}
	else
	{	
		// loading code
	}
}

void MwCanvas::Draw()
{
	color().Clear();
    glClear(GL_COLOR_BUFFER_BIT);
}
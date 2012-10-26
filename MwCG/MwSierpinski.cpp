#include "stdafx.h"
#include "MwSierpinski.h"

IMPLEMENT_SERIAL(MwSierpinski, MwGLElement, 1);

MwSierpinski::MwSierpinski(void)
{
}


MwSierpinski::~MwSierpinski(void)
{
}

void MwSierpinski::Serialize(CArchive& ar)
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

void MwSierpinski::Draw()
{
	Color();
	glBegin(GL_POINTS);
	MwVector2 p(50.0, 50.0);
	for (int i = 0; i < 5000; i++)
	{
		int v = rand() % 3;
		p += Vertex[v];
		p /= 2.0;
		p();
	}
	glEnd();
}
#include "stdafx.h"
#include "MwSierpinski.h"

IMPLEMENT_SERIAL(MwSierpinski, MwGLElement, 1);

MwSierpinski::MwSierpinski(void)
{
	PointCount = 5000;
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
	glPointSize(1);
	glBegin(GL_POINTS);
	MwVector2 p(50.0, 50.0);
	for (int i = 0; i < PointCount; i++)
	{
		int v = rand() % 3;
		p += Vertex[v];
		p /= 2.0;
		p();
	}
	glEnd();
}
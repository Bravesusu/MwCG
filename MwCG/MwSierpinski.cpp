#include "stdafx.h"
#include "MwSierpinski.h"

using namespace mw;

IMPLEMENT_SERIAL(Sierpinski, GlElement, 1);

Sierpinski::~Sierpinski(void)
{
}

Sierpinski::Sierpinski(const Vector2& v1, const Vector2& v2, const Vector2& v3) : 
	point_count_(5000)
{
	vertex_[0] = v1;
	vertex_[1] = v2;
	vertex_[2] = v3;
}

void Sierpinski::Serialize(CArchive& ar)
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

void Sierpinski::DoDraw()
{
	//color()();
	glPointSize(1);
	glBegin(GL_POINTS);
	Vector2 p(50.0, 50.0);
	for (int i = 0; i < point_count_; i++)
	{
		int v = rand() % 3;
		p += vertex_[v];
		p /= 2.0;
		p();
	}
	glEnd();
}

Vector2& Sierpinski::operator[] (int index)
{
	return const_cast<Vector2&>(static_cast<const Sierpinski&>(*this)[index]);	
}

const Vector2& Sierpinski::operator[] (int index) const
{
	return vertex_[index];
}
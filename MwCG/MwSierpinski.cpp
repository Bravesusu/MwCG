#include "stdafx.h"
#include "MwSierpinski.h"

using namespace mw;

IMPLEMENT_SERIAL(MwSierpinski, MwGLElement, 1);

MwSierpinski::~MwSierpinski(void)
{
}

MwSierpinski::MwSierpinski(const MwVector2& v1, const MwVector2& v2, const MwVector2& v3) : 
	point_count_(5000)
{
	vertex_[0] = v1;
	vertex_[1] = v2;
	vertex_[2] = v3;
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
	color()();
	glPointSize(1);
	glBegin(GL_POINTS);
	MwVector2 p(50.0, 50.0);
	for (int i = 0; i < point_count_; i++)
	{
		int v = rand() % 3;
		p += vertex_[v];
		p /= 2.0;
		p();
	}
	glEnd();
}

MwVector2& MwSierpinski::operator[] (int index)
{
	return const_cast<MwVector2&>(static_cast<const MwSierpinski&>(*this)[index]);	
}

const MwVector2& MwSierpinski::operator[] (int index) const
{
	return vertex_[index];
}
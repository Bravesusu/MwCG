#include "stdafx.h"
#include "Polygon.h"
#include "Rect.h"

using namespace mw;

Polygon::Polygon(void)
{
}


Polygon::~Polygon(void)
{
}

void mw::Polygon::Serialize( CArchive& ar )
{
	throw std::exception("The method or operation is not implemented.");
}

void mw::Polygon::DoDraw()
{
	throw std::exception("The method or operation is not implemented.");
}

bool mw::Polygon::HitTest()
{
	throw std::exception("The method or operation is not implemented.");
}

Rect mw::Polygon::bound() const
{
	float left = vertex_.begin()->x();
	float right = left;
	float top = vertex_.begin()->y();
	float bottom = top;

	for(list<Vector2>::iterator it = vertex_.begin(); it != vertex_.end(); it++)
	{
		left = min(left, it->x());
		right = max(right, it->x());
		top = max(top, it->y());
		bottom = min(bottom, it->y());
	}

	return Rect(left, right, top, bottom);
}

void mw::Polygon::Draw()
{
	throw std::exception("The method or operation is not implemented.");
}

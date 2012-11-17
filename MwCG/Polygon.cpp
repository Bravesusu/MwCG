#include "stdafx.h"
#include "Polygon.h"

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
	throw std::exception("The method or operation is not implemented.");
}

void mw::Polygon::Draw()
{
	throw std::exception("The method or operation is not implemented.");
}

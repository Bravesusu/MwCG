#include "stdafx.h"
#include "Rectangle.h"
#include "Rect.h"

using namespace mw;

Rectangle::Rectangle(void)
{
}


Rectangle::~Rectangle(void)
{
}

void mw::Rectangle::Serialize( CArchive& ar )
{
	throw std::exception("The method or operation is not implemented.");
}

void mw::Rectangle::DoDraw()
{
	DoGL();
}

bool mw::Rectangle::HitTest()
{
	throw std::exception("The method or operation is not implemented.");
}

Rect mw::Rectangle::bound() const
{
	return get<Rect>();
}
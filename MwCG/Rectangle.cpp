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
}

void mw::Rectangle::DoDraw()
{
	DoGL();
}

//bool mw::Rectangle::HitTest()
//{
//}

Rect mw::Rectangle::bound() const
{
	return get<Rect>();
}
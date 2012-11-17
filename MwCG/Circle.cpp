#include "stdafx.h"
#include "Circle.h"
#include "Rect.h"

using namespace mw;
Circle::Circle(void)
{
}


Circle::~Circle(void)
{
}

void mw::Circle::DoDraw()
{
	throw std::exception("The method or operation is not implemented.");
}

bool mw::Circle::HitTest()
{
	throw std::exception("The method or operation is not implemented.");
}

Rect mw::Circle::bound() const
{
	return Rect(
		center_.x() - radius_, 
		center_.x() + radius_,
		center_.y() + radius_,
		center_.y() - radius_
		);
}

void mw::Circle::Draw()
{
	throw std::exception("The method or operation is not implemented.");
}

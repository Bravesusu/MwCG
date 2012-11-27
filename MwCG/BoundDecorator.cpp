#include "stdafx.h"
#include "BoundDecorator.h"
#include "Rect.h"

#include "MwGLElement.h"
#include "Rectangle.h"

using namespace mw;

IMPLEMENT_DECORATOR_OP(GlElement, BoundDecorator);

BoundDecorator::BoundDecorator(void)
{
	rectangle_.reset(new Rectangle());
}


BoundDecorator::~BoundDecorator(void)
{
}

void mw::BoundDecorator::DoDecorate()
{
	rectangle_->set(decoratee()->bound());
	rectangle_->set_color(color_);
	rectangle_->Draw();
}

mw::Stroke mw::BoundDecorator::stroke() const
{
	return rectangle_->stroke();
}

void mw::BoundDecorator::set_stroke( const Stroke& stroke )
{
	rectangle_->set_stroke(stroke);
}

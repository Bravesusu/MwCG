#include "stdafx.h"
#include "PointDecorator.h"
#include "MwPoint.h"

using namespace mw;

IMPLEMENT_DECORATOR_OP(Point, PointDecorator);

void mw::PointDecorator::DoDecorate()
{
	if (decoratee() == NULL)
		return;
	dec_->Draw();
}

mw::PointDecorator::PointDecorator( void )
{
	dec_.reset(new Point());
	dec_->set_color(1, 0, 0);
	dec_->set_size(10);
}

mw::PointDecorator::~PointDecorator( void )
{

}

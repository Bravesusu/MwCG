#include "stdafx.h"
#include "PointDecorator.h"
#include "MwPoint.h"

using namespace mw;

void mw::PointDecorator::DoDecorate()
{
	if (!point_)
		return;
	dec_->set_position(point_->position());
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

shared_ptr<Point> mw::PointDecorator::operator+( shared_ptr<Point> rhs )
{
	rhs->AddDecorator(DecoratorPtr(this));
	set(rhs);
	return rhs;
}

shared_ptr<Point> mw::operator+( shared_ptr<Point> lhs, shared_ptr<PointDecorator> rhs )
{
	lhs->AddDecorator(DecoratorPtr(rhs));
	rhs->set(lhs);
	return lhs;
}

shared_ptr<Point> mw::operator-( shared_ptr<Point> lhs, shared_ptr<PointDecorator> rhs )
{
	lhs->RemoveDecorator(DecoratorPtr(rhs));
	rhs->set(NULL);
	return lhs;
}

shared_ptr<Point> mw::operator+=( shared_ptr<Point> lhs, shared_ptr<PointDecorator> rhs )
{
	return lhs + rhs;
}

shared_ptr<Point> mw::operator-=( shared_ptr<Point> lhs, shared_ptr<PointDecorator> rhs )
{
	return lhs - rhs;
}

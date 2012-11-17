#include "stdafx.h"
#include "BoundDecorator.h"

#include "MwGLElement.h"

using namespace mw;

BoundDecorator::BoundDecorator(void)
{
}


BoundDecorator::~BoundDecorator(void)
{
}

void mw::BoundDecorator::DoDecorate()
{
	throw std::exception("The method or operation is not implemented.");
}

shared_ptr<GlElement> mw::BoundDecorator::operator+( shared_ptr<GlElement> rhs )
{
	rhs->AddDecorator(DecoratorPtr(this));
	return rhs;
}

shared_ptr<GlElement> mw::operator+( shared_ptr<GlElement> lhs, shared_ptr<BoundDecorator> rhs )
{
	lhs->AddDecorator(rhs);
	return lhs;
}

shared_ptr<GlElement> mw::operator-( shared_ptr<GlElement> lhs, shared_ptr<BoundDecorator> rhs )
{
	lhs->RemoveDecorator(rhs);
	return lhs;
}

shared_ptr<GlElement> mw::operator+=( shared_ptr<GlElement> lhs, shared_ptr<BoundDecorator> rhs )
{
	return lhs + rhs;
}

shared_ptr<GlElement> mw::operator-=( shared_ptr<GlElement> lhs, shared_ptr<BoundDecorator> rhs )
{
	return lhs - rhs;

}

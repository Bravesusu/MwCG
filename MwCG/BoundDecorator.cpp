#include "stdafx.h"
#include "BoundDecorator.h"
#include "Rect.h"

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
	Rect bd = dec_->bound();

}

shared_ptr<GlElement> mw::BoundDecorator::operator+( shared_ptr<GlElement> rhs )
{
	rhs->AddDecorator(DecoratorPtr(this));
	set(rhs);
	return rhs;
}

void mw::BoundDecorator::set( shared_ptr<GlElement> element )
{
	dec_ = element;
}

shared_ptr<GlElement> mw::operator+( shared_ptr<GlElement> lhs, shared_ptr<BoundDecorator> rhs )
{
	lhs->AddDecorator(rhs);
	rhs->set(lhs);
	return lhs;
}

shared_ptr<GlElement> mw::operator-( shared_ptr<GlElement> lhs, shared_ptr<BoundDecorator> rhs )
{
	lhs->RemoveDecorator(rhs);
	rhs->set(NULL);
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

#include "stdafx.h"
#include "RectBase.h"

using namespace mw;

RectBase::RectBase(void) :
	left_(0),
	right_(0),
	top_(0),
	bottom_(0)
{
}


RectBase::~RectBase(void)
{
}

mw::RectBase::RectBase( float left, float right, float top, float bottom ) :
	left_(left),
	right_(right),
	top_(top),
	bottom_(bottom)
{

}

mw::RectBase::RectBase( const Vector2& point1, const Vector2& point2 )
{
	left_ = min(point1.x(),point2.x());
	right_ = max(point1.x(),point2.x());
	top_ = max(point1.y(),point2.y());
	bottom_ = min(point1.y(),point2.y());
}

mw::RectBase::RectBase(const RectBase& rect)
{
	set(rect);
}

void mw::RectBase::set( float left, float right, float top, float bottom )
{
	left_ = left;
	right_ = right;
	top_ = top;
	bottom_ = bottom;
}

void mw::RectBase::set( const RectBase& rect )
{
	set(rect.left(), rect.right(), rect.top(), rect.bottom());
}

void mw::RectBase::DoGL() const
{
	glRectf(left_, top_, right_, bottom_);
}

void mw::RectBase::DoSerialize( CArchive& ar )
{
	if (ar.IsStoring())
	{
		ar<<left_<<right_<<top_<<bottom_;
	}
	else
	{
		ar>>left_>>right_>>top_>>bottom_;
	}
}

#include "stdafx.h"
#include "Rect.h"

#include "MwGLObject.h"
#include "MwVector2.h"

using namespace mw;

IMPLEMENT_SERIAL(Rect, MwGLObject, 1);

Rect::Rect(void) :
	left_(0),
	right_(0),
	top_(0),
	bottom_(0)
{
}


Rect::~Rect(void)
{
}

void mw::Rect::Serialize( CArchive& ar )
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

void mw::Rect::GL()
{
}

mw::Rect::Rect( float left, float right, float top, float bottom ) :
	left_(left),
	right_(right),
	top_(top),
	bottom_(bottom)
{

}

mw::Rect::Rect( const Vector2& point1, const Vector2& point2 )
{
	left_ = min(point1.x(),point2.x());
	right_ = max(point1.x(),point2.x());
	top_ = max(point1.y(),point2.y());
	bottom_ = min(point1.y(),point2.y());
}
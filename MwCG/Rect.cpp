#include "stdafx.h"
#include "Rect.h"

#include "MwGLObject.h"
#include "MwVector2.h"

using namespace mw;

IMPLEMENT_SERIAL(Rect, GlObject, 1);

Rect::Rect(void) : RectBase()
{
}


Rect::~Rect(void)
{
}

void mw::Rect::Serialize( CArchive& ar )
{
	DoSerialize(ar);
}

void mw::Rect::GL()
{
	DoGL();
}

mw::Rect::Rect( float left, float right, float top, float bottom ) : RectBase(left, right, top, bottom)
{
}

mw::Rect::Rect( const Vector2& point1, const Vector2& point2 ) : RectBase(point1, point2)
{
}
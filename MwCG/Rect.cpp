#include "stdafx.h"
#include "Rect.h"

#include "MwGLObject.h"

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

#include "stdafx.h"
#include "MwGLElement.h"

#include "Rect.h"

using namespace mw;

IMPLEMENT_SERIAL(GlElement, CObject, 1);

GlElement::GlElement(void)
{
}


GlElement::~GlElement(void)
{
}

void GlElement::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	color_.Serialize(ar);
}

Rect mw::GlElement::bound() const
{
	return Rect();
}

void mw::GlElement::Draw()
{
	DoDraw();
}

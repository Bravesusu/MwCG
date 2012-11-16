#include "stdafx.h"
#include "MwGLElement.h"

#include "Rect.h"
#include "Decorator.h"

using namespace mw;

IMPLEMENT_SERIAL(GlElement, CObject, 1);

GlElement::GlElement(void) : hidden_(false)
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
	if (!hidden_)
		DoDraw();
	for (list<shared_ptr<Decorator>>::iterator it = decorators_.begin(); it != decorators_.end(); it++)
	{
		(*it)->Draw();
	}
}

void mw::GlElement::RemoveDecorator( const shared_ptr<Decorator> decorator )
{
	decorators_.remove(decorator);
}

void mw::GlElement::AddDecorator( const shared_ptr<Decorator> decorator )
{
	decorators_.push_back(decorator);
}

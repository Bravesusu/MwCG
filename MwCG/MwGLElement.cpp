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
	if (hidden_)
		return;
	//TODO: do coloring
	color()();
	//TODO: do sizing

	DoDraw();
	for (list<shared_ptr<Decorator>>::iterator it = decorators_.begin(); it != decorators_.end(); it++)
	{
		(*it)->Decorate();
	}
}

void mw::GlElement::RemoveDecorator( shared_ptr<Decorator> decorator )
{
	decorators_.remove(decorator);
}

void mw::GlElement::AddDecorator( shared_ptr<Decorator> decorator )
{
	decorators_.push_back(decorator);
}


void mw::GlElement::ClearAllDecorators()
{
	decorators_.clear();
}

//shared_ptr<GlElement> mw::GlElement::operator+( shared_ptr<Decorator> decorator )
//{
//	AddDecorator(decorator);
//	return shared_ptr<GlElement>(this);
//}
//
//shared_ptr<GlElement> mw::GlElement::operator+( Decorator* decorator )
//{
//	AddDecorator(shared_ptr<Decorator>(decorator));
//	return shared_ptr<GlElement>(this);
//}
//
//GlElement& mw::GlElement::operator+( Decorator& decorator )
//{
//	AddDecorator(shared_ptr<Decorator>(&decorator));
//	return *this;
//}
//
//shared_ptr<GlElement> mw::GlElement::operator-( shared_ptr<Decorator> decorator )
//{
//	RemoveDecorator(decorator);
//	return shared_ptr<GlElement>(this);
//}
//
//GlElement& mw::GlElement::operator-( Decorator& decorator )
//{
//	RemoveDecorator(shared_ptr<Decorator>(&decorator));
//	return *this;
//}



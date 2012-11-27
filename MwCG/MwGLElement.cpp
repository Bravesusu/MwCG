#include "stdafx.h"
#include "MwGLElement.h"

#include "Rect.h"
#include "Decorator.h"
#include "MwGlScreen.h"

using namespace mw;

IMPLEMENT_SERIAL(GlElement, GlObject, 1);

GlElement::GlElement(void) : hidden_(false), size_(1), stroke_(FullStroke)
{
}


GlElement::~GlElement(void)
{
}

void GlElement::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	transform_.Serialize(ar);
	color_.Serialize(ar);
	if (ar.IsStoring())
	{
		ar<<size_<<stroke_.pattern;
	}
	else
	{
		ar>>size_>>stroke_.pattern;
	}
}

Rect mw::GlElement::bound() const
{
	return Rect();
}

void mw::GlElement::Draw()
{
	if (hidden_)
		return;

	transform_.Push();
	//TODO: do coloring
	color()();
	//TODO: do sizing

	DoDraw();
	for (list<weak_ptr<Decorator>>::iterator it = decorators_.begin(); it != decorators_.end(); it++)
	{
		(*it).lock()->Decorate();
	}
	transform_.Pop();
}

void mw::GlElement::RemoveDecorator( shared_ptr<Decorator> decorator )
{
	decorators_.remove_if(
		[&] (weak_ptr<Decorator> wp) 
	{
		return wp.lock() == decorator;
	}
		);
}

void mw::GlElement::AddDecorator( shared_ptr<Decorator> decorator )
{
	decorators_.push_back(decorator);
}


void mw::GlElement::ClearAllDecorators()
{
	decorators_.clear();
}

int mw::GlElement::anchor_count() const
{
	return 1;
}

void mw::GlElement::set_anchor( int index, const Vector2& localPos )
{
	if (index == 0)
	{
		transform().position() += localPos;
	}
	else
	{
		throw std::exception("The anchor index is out of range");
	}
}

mw::Vector2 mw::GlElement::anchor( int index ) const
{
	if (index == 0)
	{
		//Local coordinate system is defined by the position.
		//Anchor pos of position is alway Zero in local
		return Vector2();
	}
	else
		throw std::exception("The anchor index is out of range");
}
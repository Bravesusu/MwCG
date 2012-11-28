#include "stdafx.h"
#include "ChangeElementColor.h"

#include "MwGLElement.h"


using namespace mw;

ChangeElementColor::ChangeElementColor(shared_ptr<GlElement> element, const Color& color)
{
	Initialize(element);
	oldColor_ = element->color();
	newColor_ = color;
}


ChangeElementColor::~ChangeElementColor(void)
{
}

void mw::ChangeElementColor::Undo()
{
	element()->set_color(oldColor_);
}

void mw::ChangeElementColor::Redo()
{
	element()->set_color(newColor_);
}

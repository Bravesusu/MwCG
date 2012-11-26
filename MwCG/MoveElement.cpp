#include "stdafx.h"
#include "MoveElement.h"

#include "MwGLElement.h"

using namespace mw;

MoveElement::~MoveElement(void)
{
}

mw::MoveElement::MoveElement( shared_ptr<GlContent> content, shared_ptr<GlElement> element )
{
	Initialize(content, element);
	if (element != NULL)
	{
		last_pos_ = element->transform().position();
	}
}

void mw::MoveElement::Undo()
{
	element()->set_position(last_pos_);
}

void mw::MoveElement::Redo()
{
	element()->set_position(move_to_pos_);
}

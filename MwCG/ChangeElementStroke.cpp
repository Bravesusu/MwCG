#include "stdafx.h"
#include "ChangeElementStroke.h"

#include "MwGLElement.h"

using namespace mw;

ChangeElementStroke::ChangeElementStroke(shared_ptr<GlElement> element, Stroke stroke)
{
	Initialize(element);
	old_stroke_ = element->stroke();
	new_stroke_ = stroke;
}


ChangeElementStroke::~ChangeElementStroke(void)
{
}

void mw::ChangeElementStroke::Undo()
{
	element()->set_stroke(old_stroke_);
}

void mw::ChangeElementStroke::Redo()
{
	element()->set_stroke(new_stroke_);
}

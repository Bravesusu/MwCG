#include "stdafx.h"
#include "ChangeElementSize.h"

#include "MwGLElement.h"

using namespace mw;

ChangeElementSize::ChangeElementSize(shared_ptr<GlElement> element, int size)
{
	Initialize(element);
	old_size_ = element->size();
	new_size_ = size;
}


ChangeElementSize::~ChangeElementSize(void)
{
}

void mw::ChangeElementSize::Undo()
{
	element()->set_size(old_size_);
}

void mw::ChangeElementSize::Redo()
{
	element()->set_size(new_size_);
}

#include "stdafx.h"
#include "SingleDeselection.h"

#include "MwGLContent.h"

using namespace mw;

SingleDeselection::~SingleDeselection(void)
{
}

mw::SingleDeselection::SingleDeselection( shared_ptr<GlContent> content, shared_ptr<GlElement> element )
{
	Initialize(content, element);
}

void mw::SingleDeselection::Undo()
{
	content()->SingleSelect(element());
}

void mw::SingleDeselection::Redo()
{
	content()->Deselect(element());
}

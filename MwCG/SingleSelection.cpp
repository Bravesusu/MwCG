#include "stdafx.h"
#include "SingleSelection.h"

#include "MwGLContent.h"
#include "MwGLElement.h"

using namespace mw;


SingleSelection::~SingleSelection(void)
{
}

mw::SingleSelection::SingleSelection( shared_ptr<GlContent> content, shared_ptr<GlElement> element )
{
	Initialize(content, element);
}

void mw::SingleSelection::Undo()
{
	content()->Deselect(element());
}

void mw::SingleSelection::Redo()
{
	content()->SingleSelect(element());
}

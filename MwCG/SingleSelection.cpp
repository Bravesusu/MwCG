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
	//content()->Deselect(element());
	content()->DeselectAll();
	for (list<shared_ptr<GlElement>>::iterator it = last_selection_.begin(); it != last_selection_.end(); it++)
	{
		content()->Select(*it);
	}
}

void mw::SingleSelection::Redo()
{
	last_selection_ = content()->selected_elements();
	content()->SingleSelect(element());
}

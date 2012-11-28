#include "stdafx.h"
#include "RemoveElementFromContent.h"
#include "MwGLContent.h"
#include "MwGLElement.h"

using namespace mw;

RemoveElementFromContent::RemoveElementFromContent(shared_ptr<GlContent> content, shared_ptr<GlElement> element)
{
	Initialize(content, element);
}


RemoveElementFromContent::~RemoveElementFromContent(void)
{
}

void mw::RemoveElementFromContent::Undo()
{
	content()->AddElement(element());
}

void mw::RemoveElementFromContent::Redo()
{
	content()->RemoveElement(element());
}

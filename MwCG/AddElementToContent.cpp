#include "stdafx.h"
#include "AddElementToContent.h"
#include "MwGLContent.h"
#include "MwGLElement.h"

using namespace std;
using namespace mw;

AddElementToContent::~AddElementToContent(void)
{
}

mw::AddElementToContent::AddElementToContent( shared_ptr<GlContent> content, shared_ptr<GlElement> element )
{
	Initialize(content, element);
}

void mw::AddElementToContent::Undo()
{
	content()->RemoveElement(element());
}

void mw::AddElementToContent::Redo()
{
	content()->AddElement(element());
}

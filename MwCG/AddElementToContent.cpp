#include "stdafx.h"
#include "AddElementToContent.h"
#include "MwGLContent.h"
#include "MwGLElement.h"

using namespace std;
using namespace mw;

AddElementToContent::~AddElementToContent(void)
{
}

mw::AddElementToContent::AddElementToContent( shared_ptr<GlContent> content, shared_ptr<GlElement> element ) :
	content_(content),
	element_(element)
{
	ASSERT(content_);
	ASSERT(element_);
}

void mw::AddElementToContent::Undo()
{
	content_->RemoveElement(element_);
}

void mw::AddElementToContent::Redo()
{
	content_->AddElement(element_);
}

#include "stdafx.h"
#include "ContentElementOperation.h"

#include "MwGLContent.h"
#include "MwGLElement.h"

using namespace mw;

void mw::ContentElementOperation::Initialize( shared_ptr<GlContent> content, shared_ptr<GlElement> element )
{
	//ASSERT(content);
	//ASSERT(element);
	content_ = content;
	element_ = element;
}

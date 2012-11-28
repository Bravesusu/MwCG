#include "stdafx.h"
#include "ElementOperation.h"

#include "MwGLElement.h"

using namespace mw;


void mw::ElementOperation::Initialize( shared_ptr<GlElement> element )
{
	ASSERT(element);
	element_ = element;
}

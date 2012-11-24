#include "stdafx.h"
#include "MwGLObject.h"

using namespace mw;

IMPLEMENT_SERIAL(GlObject, CObject, 1)

GlObject::GlObject(void)
{
}


GlObject::~GlObject(void)
{
}

void GlObject::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
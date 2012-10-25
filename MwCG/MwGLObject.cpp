#include "stdafx.h"
#include "MwGLObject.h"

IMPLEMENT_SERIAL(MwGLObject, CObject, 1)

MwGLObject::MwGLObject(void)
{
}


MwGLObject::~MwGLObject(void)
{
}

void MwGLObject::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
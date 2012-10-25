#include "stdafx.h"
#include "MwGLContent.h"

IMPLEMENT_SERIAL(MwGLContent, CObject, 1)

MwGLContent::MwGLContent(void)
{
}


MwGLContent::~MwGLContent(void)
{
}


void MwGLContent::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

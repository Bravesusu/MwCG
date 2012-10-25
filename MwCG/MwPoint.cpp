#include "stdafx.h"
#include "MwPoint.h"

IMPLEMENT_SERIAL(MwPoint, MwGLElement, 1);

MwPoint::MwPoint(void)
{
}


MwPoint::~MwPoint(void)
{
}

void MwPoint::Serialize(CArchive& ar)
{
	MwGLElement::Serialize(ar);

	if (ar.IsStoring())
	{	
		// storing code
	}
	else
	{	
		// loading code
	}
}
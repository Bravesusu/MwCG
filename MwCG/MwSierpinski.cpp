#include "stdafx.h"
#include "MwSierpinski.h"

IMPLEMENT_SERIAL(MwSierpinski, MwGLElement, 1);

MwSierpinski::MwSierpinski(void)
{
}


MwSierpinski::~MwSierpinski(void)
{
}

void MwSierpinski::Serialize(CArchive& ar)
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
#include "stdafx.h"
#include "MwLine.h"

IMPLEMENT_SERIAL(MwLine, MwGLElement, 1);

MwLine::MwLine(void)
{
}


MwLine::~MwLine(void)
{
}

void MwLine::Serialize(CArchive& ar)
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
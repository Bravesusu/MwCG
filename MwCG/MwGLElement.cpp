#include "stdafx.h"
#include "MwGLElement.h"

IMPLEMENT_SERIAL(MwGLElement, MwGLObject, 1);

MwGLElement::MwGLElement(void)
{
}


MwGLElement::~MwGLElement(void)
{
}

void MwGLElement::Serialize(CArchive& ar)
{
	MwGLObject::Serialize(ar);

	if (ar.IsStoring())
	{	
		// storing code
		ar<<index<<name<<&Color;
	}
	else
	{	
		// loading code
		MwColor* pColor;
		ar>>index>>name>>pColor;
		Color.SetColor(*pColor);
		delete pColor;
	}
}
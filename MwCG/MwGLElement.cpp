#include "stdafx.h"
#include "MwGLElement.h"

using namespace mw;

IMPLEMENT_SERIAL(MwGLElement, CObject, 1);

MwGLElement::MwGLElement(void)
{
}


MwGLElement::~MwGLElement(void)
{
}

void MwGLElement::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	color_.Serialize(ar);
}
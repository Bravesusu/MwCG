#include "stdafx.h"
#include "MwGLContent.h"

using namespace mw;

IMPLEMENT_SERIAL(MwGLContent, CObject, 1);

MwGLContent::MwGLContent(void)
{
	Mouse.set_color(1, 0, 0);
	Mouse.set_size(10);
	m_pCanvas = new MwCanvas();
	m_pCanvas->set_color(MW_WHITE);
	Elements.push_back(MwElementSafePtr(m_pCanvas));
}


MwGLContent::~MwGLContent(void)
{
	delete m_pCanvas;
}


void MwGLContent::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	m_pCanvas->Serialize(ar);
}

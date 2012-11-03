#include "stdafx.h"
#include "MwGLContent.h"

using namespace mw;

IMPLEMENT_SERIAL(GlContent, CObject, 1);

GlContent::GlContent(void)
{
	Mouse.set_color(1, 0, 0);
	Mouse.set_size(10);
	m_pCanvas = new Canvas();
	m_pCanvas->set_color(MW_WHITE);
	Elements.push_back(MwElementSafePtr(m_pCanvas));
}


GlContent::~GlContent(void)
{
	delete m_pCanvas;
}


void GlContent::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	m_pCanvas->Serialize(ar);
}

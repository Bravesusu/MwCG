#include "stdafx.h"
#include "MwGLContent.h"

using namespace mw;

IMPLEMENT_SERIAL(GlContent, GlElement, 1);

GlContent::GlContent(void)
{
	Mouse.set_color(1, 0, 0);
	Mouse.set_size(10);
	canvas_.reset(new Canvas());
	canvas_->set_color(MW_WHITE);
	Elements.push_back(GlElementPtr(canvas_));
}


GlContent::~GlContent(void)
{
}


void GlContent::Serialize(CArchive& ar)
{
	//GlElement::Serialize(ar);

	canvas_->Serialize(ar);
}

void GlContent::Draw()
{
	//Contents
	for (UINT i = 0; i < Elements.size(); i++)
	{
		Elements.at(i)->Draw();
	}

	//Decorator & interaction layer
	Mouse.Draw();
}
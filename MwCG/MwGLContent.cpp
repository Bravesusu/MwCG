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
	//This function is called every time when updating a frame
	//Events should be coming before

	//Handle events
	HitTest();
	//TODO: keyboard

	//Contents
	for (UINT i = 0; i < Elements.size(); i++)
	{
		Elements.at(i)->Draw();
	}

	//Decorator & interaction layer
	Mouse.Draw();
}

bool GlContent::HitTest()
{
	//TODO: point of optimization

	for (UINT i = 0; i < Elements.size(); i++)
	{
		if (Elements.at(i)->HitTest())
			return true;
	}
	return false;
}

void GlContent::set_mouse(const CPoint& viewPoint) const
{
	//Translate to canvas coordinate system

}
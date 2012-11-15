#include "stdafx.h"
#include "MwGLContent.h"

using namespace mw;

IMPLEMENT_SERIAL(GlContent, GlElement, 1);

GlContent::GlContent(void)
{
	screen_.reset(new GlScreen());
	set_screen(screen_);

	canvas_.reset(new Canvas());
	canvas_->set_color(MW_WHITE);
	canvas_->set_screen(screen_);

	mouse_.reset(new Mouse());
	mouse_->set_color(0, 0, 0);
	mouse_->set_screen(screen_);
}


GlContent::~GlContent(void)
{
}


void GlContent::Serialize(CArchive& ar)
{
	GlElement::Serialize(ar);
	canvas_->Serialize(ar);
	CObArray arr;

	if (ar.IsStoring())
	{
		for (int i = 0; i < Elements.size(); i++)
		{
			arr.Add(Elements.at(i).get());
		}
		arr.Serialize(ar);
	}
	else
	{
		arr.Serialize(ar);
		for (int i = 0; i < arr.GetSize(); i++)
		{
			Elements.push_back(GlElementPtr(dynamic_cast<GlElement*>(arr[i])));
		}
	}
}

void GlContent::Draw()
{
	//This function is called every time when updating a frame
	//Events should be coming before
	//Update screen
	screen_->GL();

	//Handle events
	HitTest();
	//TODO: keyboard

	//Canvas
	canvas_->Draw();

	//Contents
	for (UINT i = 0; i < Elements.size(); i++)
	{
		Elements.at(i)->Draw();
	}

	//Decorator & interaction layer
	mouse_->Draw();
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

//Set current mouse position with in view coordinate and return screen coordinate.
Vector2 GlContent::set_mouse(const CPoint& viewPoint) const
{
	//Translate to canvas coordinate system
	Vector2 xyPos = screen_->ScreenToXY(viewPoint.x, viewPoint.y);
	mouse_->set_position(xyPos);
	return xyPos;
}

void mw::GlContent::AddElement(GlElementPtr element)
{
	Elements.push_back(element);
	element->set_screen(screen_);
}

void mw::GlContent::RemoveElement( GlElementPtr element )
{
	//TODO: remove element from hierarchy
}

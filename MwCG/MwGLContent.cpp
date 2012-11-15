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
		for (list<GlElementPtr>::iterator i = elements_.begin(); i != elements_.end(); i++)
		{
			arr.Add(i->get());
		}
		arr.Serialize(ar);
	}
	else
	{
		arr.Serialize(ar);
		for (int i = 0; i < arr.GetSize(); i++)
		{
			elements_.push_back(GlElementPtr(dynamic_cast<GlElement*>(arr[i])));
		}
	}
}

void GlContent::DoDraw()
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
	for (list<GlElementPtr>::iterator i = elements_.begin(); i != elements_.end(); i++)
	{
		(*i)->Draw();
	}

	//Decorator & interaction layer
	mouse_->Draw();
}

bool GlContent::HitTest()
{
	//TODO: point of optimization

	for (list<GlElementPtr>::iterator i = elements_.begin(); i != elements_.end(); i++)
	{
		if ((*i)->HitTest())
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
	elements_.push_back(element);
	element->set_screen(screen_);
}

void mw::GlContent::RemoveElement( GlElementPtr element )
{
	//remove element from hierarchy
	elements_.remove(element);
	//TO REMOVE: hide element for the result, not final implementations
	//WARNING: possible hazard for duplications
	//element->set_hidden(true);
}

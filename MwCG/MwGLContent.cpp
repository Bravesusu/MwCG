#include "stdafx.h"
#include "MwGLContent.h"

#include "MwCanvas.h"
#include "MwPoint.h"
#include "MwMouse.h"
#include "MwGlScreen.h"
#include "Rect.h"

using namespace mw;

IMPLEMENT_SERIAL(GlContent, GlElement, 1);

GlContent::GlContent(void)
{
	theScreen_.reset(new GlScreen());
	set_screen(theScreen_);

	canvas_.reset(new Canvas());
	canvas_->set_color(MW_WHITE);
	canvas_->set_screen(screen());

	mouse_.reset(new Mouse());
	mouse_->set_color(0, 0, 0);
	mouse_->set_screen(screen());

	elements_.push_back(canvas_);
	//elements_.pop_back();
}


GlContent::~GlContent(void)
{
}


void GlContent::Serialize(CArchive& ar)
{

	GlElement::Serialize(ar);
	canvas_->Serialize(ar);
	theScreen_->Serialize(ar);

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
		set_screen(theScreen_);

		canvas_->set_screen(screen());

		arr.Serialize(ar);
		for (int i = 0; i < arr.GetSize(); i++)
		{			
			GlElementPtr element = GlElementPtr(DYNAMIC_DOWNCAST(GlElement, arr[i]));
			AddElement(element);
		}

		mouse_.reset(new Mouse());
		mouse_->set_color(0, 0, 0);
		mouse_->set_screen(screen());
	}
}

void GlContent::DoDraw()
{
	//This function is called every time when updating a frame
	//Events should be coming before
	//Update screen
	screen()->GL();

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

//Set current mouse position with in view coordinate and return screen coordinate.
Vector2 GlContent::set_mouse(const CPoint& viewPoint) const
{
	//Translate to canvas coordinate system
	Vector2 xyPos = screen()->ScreenToXY(viewPoint.x, viewPoint.y);
	mouse_->set_position(xyPos);
	return xyPos;
}

void mw::GlContent::AddElement(GlElementPtr element)
{
	elements_.push_back(element);
	element->set_screen(screen());
}

void mw::GlContent::RemoveElement( GlElementPtr element )
{
	//remove element from hierarchy
	elements_.remove(element);
	selectedElements_.remove(element);
}

bool mw::GlContent::HitTest( const Vector2& worldPos ) const
{
	for (list<GlElementPtr>::const_iterator it = elements_.begin(); it != elements_.end(); it++)
	{
		if ((*it)->HitTest(worldPos))
			return true;
	}

	return false;
}

bool mw::GlContent::HitTest( const Vector2& worldPos, shared_ptr<GlElement>& hit ) const
{
	try
	{
		if (!elements_.empty())
		{

			for (list<GlElementPtr>::const_iterator it = elements_.begin(); it != elements_.end(); it++)
			{
				if ((*it)->HitTest(worldPos))
				{
					hit = *it;
					return true;
				}
			}
		}
	}
	catch (CException* e)
	{
	}

	hit = NULL;
	return false;
}

bool mw::GlContent::IsAlreadySelected( const shared_ptr<GlElement>& element) const
{
	list<shared_ptr<GlElement>>::const_iterator it = find(elements_.begin(), elements_.end(), element);

	//Not even an element
	if (it == elements_.end())
		return false;

	list<shared_ptr<GlElement>>::const_iterator sel_it = find(selectedElements_.begin(), selectedElements_.end(), element);

	return sel_it != selectedElements_.end();
}

void mw::GlContent::Select( const shared_ptr<GlElement>& element )
{

	if (!IsAlreadySelected(element))
	{
		selectedElements_.push_back(element);
		//TODO: select event
		InvokeSelectHandler(element);
	}
}

void mw::GlContent::Deselect( const shared_ptr<GlElement>& element )
{
	if (IsAlreadySelected(element))
	{
		selectedElements_.remove(element);
		//TODO: deselect event
		InvokeDeselectHandler(element);
	}
}

void mw::GlContent::SingleSelect( const shared_ptr<GlElement>& element )
{
	DeselectAll();
	Select(element);
}

void mw::GlContent::DeselectAll()
{
	if (selectedElements_.empty())
		return;
	for (list<shared_ptr<GlElement>>::iterator it = selectedElements_.begin(); it != selectedElements_.end(); it++)
	{
		InvokeDeselectHandler(*it);
	}

	selectedElements_.clear();
}

void mw::GlContent::InvokeSelectHandler( const shared_ptr<GlElement>& element )
{
	if (onSelectEvtHandler_ != NULL)
		onSelectEvtHandler_(element);
}

void mw::GlContent::InvokeDeselectHandler( const shared_ptr<GlElement>& element )
{
	if (onDeselectEvtHandler_ != NULL)
		onDeselectEvtHandler_(element);
}

Rect mw::GlContent::bound() const
{
	return GlElement::bound();
}

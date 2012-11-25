#include "stdafx.h"
#include "UiSelector.h"

using namespace mw;

UiSelector::UiSelector(void)
{
}


UiSelector::~UiSelector(void)
{
}

mw::OperationPtr mw::UiSelector::PopNewOperation()
{
	throw std::exception("The method or operation is not implemented.");
}

bool mw::UiSelector::IsFinished() const
{
	return false;
	//throw std::exception("The method or operation is not implemented.");
}

void mw::UiSelector::Draw()
{
}

void mw::UiSelector::DoNew()
{
}

void mw::UiSelector::DoNextInput()
{
}

void mw::UiSelector::DoFixInput( const int index )
{
}

void mw::UiSelector::DoBeginInput()
{
	shared_ptr<GlElement> newHit;
	content()->HitTest(mouse_pos(), newHit);
	//clean up old hit
	Deselect(click_hit_);
	//Select new one 
	Select(newHit);
	//Store (if no hit, hit_ = newHit <- NULL)
	click_hit_ = newHit;
}

void mw::UiSelector::DoUpdateInput()
{
	//Do hover hit if no click hit
	if (click_hit_ == NULL)
	{
		shared_ptr<GlElement> newHit;
		content()->HitTest(mouse_pos(), newHit);
		//Leave old one
		Leave(hover_hit_);
		//Enter new one
		Enter(newHit);
		//Assign (Can be NULL)
		hover_hit_ = newHit;
	}
	else
	{
		//TODO: pipe inputs to editor
		//(transform editor from click)
		//(anchor points editor from dbl-click)
	}
}

void mw::UiSelector::DoEndInput()
{
}

void mw::UiSelector::Select( shared_ptr<GlElement> element )
{
	if (element == NULL)
		return;
}

void mw::UiSelector::Deselect( shared_ptr<GlElement> element )
{
	if (element == NULL)
		return;

}

void mw::UiSelector::Enter( shared_ptr<GlElement> element )
{
	if (element == NULL)
		return;
}

void mw::UiSelector::Leave( shared_ptr<GlElement> element )
{
	if (element == NULL)
		return;
}

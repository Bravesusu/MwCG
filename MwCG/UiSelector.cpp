#include "stdafx.h"
#include "UiSelector.h"

#include "BoundDecorator.h"
#include "SingleSelection.h"
#include "SingleDeselection.h"
#include "AnchorDecorator.h"

#include "MoveElement.h"

using namespace mw;

UiSelector::UiSelector(void)
{
	moving_ = false;
	dbl_clicked_ = false;
	selDec_.reset(new BoundDecorator());
	selDec_->color().set(0, 0, 1, 0.5);
	hoverDec_.reset(new BoundDecorator());
	hoverDec_->color().set(0, 1, 0, 0.5);
	anchroDec_.reset(new AnchorDecorator());
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

void mw::UiSelector::DoDoubleClick()
{
	shared_ptr<GlElement> newHit;
	content()->HitTest(mouse_pos(), newHit);
	//Hit changed
	if (click_hit_ != newHit)
	{
		//No hit, exit
		if (newHit == NULL)
		{
			click_hit_ -= anchroDec_;
			dbl_clicked_ = false;
		}
		click_hit_ = newHit;
	}
	else if (click_hit_ != NULL)
	{
		//TODO: apply anchor decorator
		//Mark decorated
		click_hit_ += anchroDec_;
		dbl_clicked_ = true;
	}
}

void mw::UiSelector::DoBeginInput()
{
	if (content() == NULL)
		return;
	if (dbl_clicked_)
	{
		anchroDec_->BeginInput(mouse_pos());
	}
	else
	{
		shared_ptr<GlElement> newHit;
		content()->HitTest(mouse_pos(), newHit);
		//Hit changed
		if (click_hit_ != newHit)
		{
			if (newHit == NULL)
			{
				//clean up old hit
				Deselect(click_hit_);
			}
			else
			{
				//Select new one 
				SingleSelect(newHit);
				//TODO: apply transformer
				move_op_.reset(new MoveElement(content(), newHit));
				move_op_->set_element(newHit);
				move_op_->set_initial_position(newHit->transform().position());
				move_op_->set_move_to_position(newHit->transform().position());
				NotifyToolPreview(move_op_);
				moving_ = true;

			}
			//Store (if no hit, hit_ = newHit <- NULL)
			click_hit_ = newHit;
		}
		else
		{
			if (click_hit_ != NULL)
			{
				//TODO: send msg to transformer
				move_op_->set_element(newHit);
				move_op_->set_initial_position(newHit->transform().position());
				move_op_->set_move_to_position(newHit->transform().position());
				NotifyToolPreview(move_op_);
				moving_ = true;
			}
		}
	}
}

void mw::UiSelector::DoUpdateInput()
{
	if (content() == NULL)
		return;

	if (dbl_clicked_)
	{
		anchroDec_->UpdateInput(mouse_pos());
	}
	else
	{
		if (click_hit_ != NULL)
		{
			//TODO: pipe inputs to editor
			//(transform editor from click)
			//(anchor points editor from dbl-click)
			//TEMP CODE: concept demo
			if (moving_)
			{
				//click_hit_->set_position(mouse_pos());
				move_op_->set_move_to_position(click_hit_->transform().position() + mouse_inst_delta());
				NotifyToolUpdatePreview();
			}
		}
		//Handle hover all the time
		shared_ptr<GlElement> newHit;
		content()->HitTest(mouse_pos(), newHit);
		if (hover_hit_ != newHit)
		{
			//Leave old one
			Leave(hover_hit_);
			//Enter new one
			Enter(newHit);
			//Assign (Can be NULL)
			hover_hit_ = newHit;
		}
	}
}

void mw::UiSelector::DoEndInput()
{
	if (dbl_clicked_)
	{
		anchroDec_->EndInput(mouse_pos());
	}
	else
	{
		moving_ = false;
		NotifyToolCommitPreview();
	}
}

void mw::UiSelector::SingleSelect( shared_ptr<GlElement> element )
{
	if (element == NULL)
		return;
	//element += selDec_;
	NotifyToolOperation(OperationPtr(
		new SingleSelection(content(), element)
		));
}

void mw::UiSelector::Deselect( shared_ptr<GlElement> element )
{
	if (element == NULL)
		return;
	//element -= selDec_;
	NotifyToolOperation(OperationPtr(
		new SingleDeselection(content(), element)
		));
}

void mw::UiSelector::Enter( shared_ptr<GlElement> element )
{
	if (element == NULL)
		return;
	element += hoverDec_;
}

void mw::UiSelector::Leave( shared_ptr<GlElement> element )
{
	if (element == NULL)
		return;
	element -= hoverDec_;
}

void mw::UiSelector::OnElementSelect(shared_ptr<GlElement> element )
{
	if (element == NULL)
		return;
	element += selDec_;
}

void mw::UiSelector::OnElementDeselect(shared_ptr<GlElement> element )
{
	if (element == NULL)
		return;
	element -= selDec_;
}

void mw::UiSelector::OnContentInitialized()
{
	GlContentCallback sel_callback = 
		[this] ( shared_ptr<GlElement> element) 
	{ 
		OnElementSelect(element); 
	};

	GlContentCallback desel_callback = 
		[this] ( shared_ptr<GlElement> element)
	{
		OnElementDeselect(element);
	};

	content()->set_on_select(sel_callback);
	content()->set_on_deselect(desel_callback);


}

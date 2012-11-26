#include "stdafx.h"
#include "UiEditorTool.h"

#include "MwPoint.h"

using namespace mw;

UiEditorTool::UiEditorTool(void) : input_index(-1), just_finished_(true)
{
	inputPoint_.reset(new Point());
	//inputPoint_->set_hidden(true);
	inputPoint_->set_size(10);
	inputPoint_->set_color(1, 0, 0);
}


UiEditorTool::~UiEditorTool(void)
{
}

void mw::UiEditorTool::New()
{
	just_finished_ = false;
	input_index = 0;
	inputs_.clear();
	DoNew();
	TrySetElementColor();
	TrySetElementSize();
	TrySetElementStroke();
}

void mw::UiEditorTool::Cancel()
{
	DidCancel();
	New();
}

void mw::UiEditorTool::FixInput( const int index, const Vector2& worldPos )
{
	inputs_[index] = worldPos;
	DoFixInput(index);
}

void mw::UiEditorTool::UpdateElementColor( const COLORREF elementColor )
{
	elementColor_.set(elementColor);
	TrySetElementColor();
}

void mw::UiEditorTool::TrySetElementColor()
{
	if (GetEditingElement() != NULL)
		GetEditingElement()->set_color(elementColor_);
}

void mw::UiEditorTool::UpdateElementSize( int size )
{
	elementSize_ = size;
	TrySetElementSize();
}

void mw::UiEditorTool::TrySetElementSize()
{

	if (GetEditingElement() != NULL)
		GetEditingElement()->set_size(elementSize_);
}

bool mw::UiEditorTool::GetInput( int index, Vector2& worldPos ) const
{
	if (index < 0 || index >= inputs_.size())
		return false;
	worldPos = inputs_.at(index);
	return true;
}

void mw::UiEditorTool::UpdateElementStroke( Stroke stroke )
{
	elementStroke_ = stroke;
	TrySetElementStroke();
}

void mw::UiEditorTool::TrySetElementStroke()
{
	if (GetEditingElement() != NULL)
		GetEditingElement()->set_stroke(elementStroke_);

}

void mw::UiEditorTool::DrawInputPoint( int maxCount ) const
{
	for (int i = 0; i < min(maxCount, inputs_.size()); i++)
	{
		inputPoint_->set_position(inputs_.at(i));
		inputPoint_->Draw();
	}
}

mw::Vector2 mw::UiEditorTool::get_input( const int index ) const
{
	return inputs_.at(index);
}

int mw::UiEditorTool::NextInput()
{
	input_index++;
	DoNextInput();
	return input_index - 1;
}

void mw::UiEditorTool::BeginInput( const Vector2& worldPos )
{
	if (just_finished_)
	{
		//New() if just finished
		New();
	}
	else
	{
		//NextInput() to begin new one
		NextInput();
	}

	//Handle the input
	HandleInput(worldPos);
	mouse_down_ = mouse_;
	mouse_last_ = mouse_;
	DoBeginInput();
}

void mw::UiEditorTool::UpdateInput( const Vector2& worldPos )
{
	HandleInput(worldPos);

	DoUpdateInput();
	mouse_last_ = mouse_;
}

void mw::UiEditorTool::EndInput( const Vector2& worldPos )
{
	//Handle the input
	HandleInput(worldPos);
	//Try finish and notify ui_
	if (IsFinished())
	{
		if (ui_ != NULL)
		{
			ui_->NotifyToolFinished();
		}
		just_finished_ = true;
	}
	DoEndInput();
}

void mw::UiEditorTool::HandleInput( const Vector2& worldPos )
{
	mouse_ = worldPos;
	if (input_index >= inputs_.size())
		inputs_.push_back(worldPos);
	else
	{
		inputs_[input_index] = worldPos;
	}
	ASSERT(input_index == inputs_.size() - 1);
}

#include "stdafx.h"
#include "UiEditorTool.h"

using namespace mw;

UiEditorTool::UiEditorTool(void) : input_index(-1)
{
}


UiEditorTool::~UiEditorTool(void)
{
}

void mw::UiEditorTool::UpdateInput( const Vector2& pos )
{
	if (input_index >= inputs_.size())
		inputs_.push_back(pos);
	else
	{
		inputs_[input_index] = pos;
	}
	ASSERT(input_index == inputs_.size() - 1);
	DoUpdateInput();
}

void mw::UiEditorTool::New()
{
	input_index = 0;
	inputs_.clear();
	DoNew();
	TrySetElementColor();
	TrySetElementSize();
	TrySetElementStroke();
}

int mw::UiEditorTool::NextInput()
{
	input_index++;
	DoNextInput();
	return input_index - 1;
}

void mw::UiEditorTool::Cancel()
{
	DidCancel();
	New();
}

void mw::UiEditorTool::FixInput( const int index, const Vector2& pos )
{
	inputs_[index] = pos;
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

bool mw::UiEditorTool::GetInput( int index, Vector2& pos ) const
{
	if (index < 0 && index >= inputs_.size())
		return false;
	pos = inputs_.at(index);
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

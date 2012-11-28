#include "stdafx.h"
#include "UiEditorTool.h"

#include "MwCGDoc.h"

#include "MwPoint.h"

using namespace mw;

UiEditorTool::UiEditorTool(void) : input_index(-1), just_finished_(true),is_new_(false)
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
	is_new_ = true;
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
	is_new_ = false;
}

void mw::UiEditorTool::UpdateInput( const Vector2& worldPos )
{
	HandleInput(worldPos);

	//is_new_ = false;
	DoUpdateInput();
	mouse_last_ = mouse_;
}

void mw::UiEditorTool::EndInput( const Vector2& worldPos )
{
	//Handle the input
	HandleInput(worldPos);
	//is_new_ = false;
	//Try finish and notify ui_
	if (IsFinished())
	{
		TryFinish();
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
	//ASSERT(input_index == inputs_.size() - 1);
}

void mw::UiEditorTool::DoubleClick( const Vector2& worldPos )
{
	DoDoubleClick();
}

void mw::UiEditorTool::set_doc( CMwCGDoc* doc )
{
	doc_ = doc;
	set_content(doc_->glContent());
}

void mw::UiEditorTool::NotifyToolOperation( const shared_ptr<IOperation>& operation )
{
	doc()->CommitOperation(operation);
}

void mw::UiEditorTool::NotifyToolPreview( const shared_ptr<IOperation>& operation )
{
	doc()->BeginPreviewOperation(operation);
}

void mw::UiEditorTool::NotifyToolUpdatePreview()
{
	doc()->UpdatePreviewOperation();
}

void mw::UiEditorTool::NotifyToolCommitPreview()
{
	doc()->CommitPreviewOperation();
}

void mw::UiEditorTool::NotifyToolCancelPreview()
{
	doc()->CancelPreviewOperation();
}

bool mw::UiEditorTool::TryFinish()
{
	if (IsFinished())
	{
		doc()->CommitOperation(PopNewOperation());
		return true;
	}
	return false;
}

void mw::UiEditorTool::set_view( CMwCGView* view )
{
	view_ = view;
}

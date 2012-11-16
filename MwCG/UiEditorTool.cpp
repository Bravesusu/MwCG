#include "stdafx.h"
#include "UiEditorTool.h"

using namespace mw;

UiEditorTool::UiEditorTool(void) : inputting_(false)
{
}


UiEditorTool::~UiEditorTool(void)
{
}

void mw::UiEditorTool::BeginInput( const Vector2& pos )
{
	if (!inputting_)
	{
		inputting_ = true;
		current_ = pos;
		DoBeginInput();
	}
	else 
	{
		UpdateInput(pos);
	}
}

void mw::UiEditorTool::UpdateInput( const Vector2& pos )
{
	current_ = pos;
	DoUpdateInput();
}

void mw::UiEditorTool::EndInput()
{
	if (inputting_)
	{
		inputting_ = false;
		DoEndInput();
	}
}

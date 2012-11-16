#include "stdafx.h"
#include "UiEditorTool.h"

using namespace mw;

UiEditorTool::UiEditorTool(void) : status_(AcceptUpdate)
{
}


UiEditorTool::~UiEditorTool(void)
{
}

void mw::UiEditorTool::UpdateInput( const Vector2& pos )
{
	if (status_ != AcceptUpdate)
		return;
	current_ = pos;
	DoUpdateInput();
}

void mw::UiEditorTool::CommitInput()
{
	status_ = AcceptFix;
	DoCommitInput();
}

void mw::UiEditorTool::New()
{
	status_ = AcceptUpdate;
	DoNew();
}

void mw::UiEditorTool::NextInput( const Vector2& pos )
{
	status_ = AcceptUpdate;
	current_ = pos;
	DoNextInput();
}

void mw::UiEditorTool::Cancel()
{
	DidCancel();
	New();
}

void mw::UiEditorTool::FixInput( const Vector2& pos )
{
	if (status_ == AcceptNone)
		return;
	current_ = pos;
	DoFixInput();
}

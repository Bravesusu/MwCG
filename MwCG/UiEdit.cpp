#include "stdafx.h"
#include "UiEdit.h"

#include "MwCGDoc.h"
#include "MwCGView.h"

#include "UiEditorTool.h"
#include "UiSelector.h"
#include "LineTool.h"
#include "PointTool.h"

using namespace mw;

UiEdit::UiEdit(void) : mouse_left_down_(false), just_finished_(false)
{
	selector_.reset(new UiSelector());
}


UiEdit::~UiEdit(void)
{
}

void mw::UiEdit::OnMouseMove( UINT nFlags, CPoint point )
{
	UpdateMouseInput(nFlags, point);

	if (tool_ == NULL)
		return;
	if (!tool_->IsFinished())
		tool_->UpdateInput(mouse_xy_);
}

void mw::UiEdit::OnLButtonDown( UINT nFlags, CPoint point )
{
	mouse_left_down_ = true;
	UpdateMouseInput(nFlags, point);
	if (tool_ == NULL)
		return;

	if (TryFinishTool())
	{
		just_finished_ = true;
		tool_->New();
		view()->Invalidate();
	}
}

void mw::UiEdit::OnLButtonUp( UINT nFlags, CPoint point )
{
	UpdateMouseInput(nFlags, point);
	if (tool_ == NULL)
		return;

	tool_->UpdateInput(mouse_xy_);

	//A click
	if (mouse_left_down_)
	{
		if (just_finished_)
		{
			just_finished_ = false;
		}
		else if (!tool_->IsFinished())
		{
			int oldIndex = tool_->NextInput();
			view()->ShowFloaty(oldIndex, nFlags, point);
		}
	}

	mouse_left_down_ = false;
	view()->Invalidate();
}

void mw::UiEdit::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if (' ' == nChar)
	{
		//TODO: switch to nav mode
		view()->SwitchToNavMode();
	}
}

void mw::UiEdit::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{

	if (13 == nChar)
	{
		if (tool_ == NULL)
			return;
		if (!tool_->IsFinished())
		{
			if (tool_->CanFinishByEnter() && TryFinishTool())
			{
				if (mouse_left_down_)
					just_finished_ = true;
				tool_->New();
				view()->Invalidate();
			}
		}
	}
}

void mw::UiEdit::InitializeName()
{
	name_.LoadString(IDS_UI_EDIT);
	ASSERT(name_);
}

void mw::UiEdit::UpdateMouseInput( UINT nFlags, CPoint point )
{
	mouse_xy_ = doc()->SetMousePos(point);
}

void mw::UiEdit::set_tool( shared_ptr<UiEditorTool> tool )
{
	//Cancel current one
	if (tool_)
	{
		if (!TryFinishTool())
			tool_->Cancel();
		else
		{
			tool_->New();
		}
	}

	tool->set_content(doc()->glContent());
	tool_ = tool;

	//Initialize new one
	tool_->New();
}

void mw::UiEdit::use_selector()
{
	set_tool(selector_);
}

void mw::UiEdit::Draw()
{
	if (tool_)
		tool_->Draw();
}

void mw::UiEdit::OnRButtonUp( UINT nFlags, CPoint point )
{
	tool_->Cancel();
}

bool mw::UiEdit::TryFinishTool()
{
	if (tool_->IsFinished())
	{
		TRACE("Finish\n");
		doc()->CommitOperation(tool_->PopNewOperation());

		return true;
	}
	return false;
}


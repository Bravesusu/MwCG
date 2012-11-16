#include "stdafx.h"
#include "UiEdit.h"

#include "MwCGDoc.h"
#include "MwCGView.h"

#include "UiEditorTool.h"
#include "UiSelector.h"
#include "LineTool.h"
#include "PointTool.h"

using namespace mw;

UiEdit::UiEdit(void) : mouse_left_down_(false)
{
	selector_.reset(new UiSelector());
	line_.reset(new LineTool());
	point_.reset(new PointTool());
}


UiEdit::~UiEdit(void)
{
}

void mw::UiEdit::OnMouseMove( UINT nFlags, CPoint point )
{
	UpdateMouseInput(nFlags, point);
	//editor_->MouseMove(mouse_xy_);
	if (!tool_)
		return;
	//TRACE("Mouse Move\n");
	if (!tool_->IsIdle())
	{
		//TRACE("Tool not idle\n");
		if (mouse_left_down_)
		{
			//TRACE("Did down. Do update.\n");
			tool_->UpdateInput(mouse_xy_);
		}
	}
	else
	{
		tool_->BeginInput(mouse_xy_);
	}
}

void mw::UiEdit::OnLButtonDown( UINT nFlags, CPoint point )
{
	mouse_left_down_ = true;
	UpdateMouseInput(nFlags, point);
	if (!tool_)
		return;
	//Idle->Inputting

	TRACE("Mouse Down\n");

	if (tool_->IsIdle())
	{
		//TRACE("Tool idle\n");
		tool_->BeginInput(mouse_xy_);
	}
	//Inputting
	else
	{
		if (tool_->IsInputting())
		{
			//TRACE("Tool inputting\n");
			//End last one
			tool_->EndInput();

			//Is Finished?
			if (tool_->IsFinished())
			{

				//TRACE("Tool Finished\n");
				doc()->CommitOperation(tool_->PopNewOperation());
				//New input
				//TODO: configurable behavior
				tool_->New();
			}
			//Begin new input
			else 
			{
				//TRACE("Tool not finished.\n");
				tool_->BeginInput(mouse_xy_);
			}
		}
		else
		{
			//TRACE("Tool not inputting\n");
		}
	}
}

void mw::UiEdit::OnLButtonUp( UINT nFlags, CPoint point )
{
	mouse_left_down_ = false;
	UpdateMouseInput(nFlags, point);

	TRACE("Mouse Up\n");
	//editor_->MouseLUp(mouse_xy_);
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
	if (tool_ && !tool->IsIdle())
		tool_->Cancel();

	tool->set_content(doc()->glContent());
	tool_ = tool;

	//Initialize new one
	tool_->New();
}

void mw::UiEdit::use_selector()
{
	//set_tool(selector_);
	//set_tool(line_);
	set_tool(point_);
}

void mw::UiEdit::Draw()
{
	if (tool_)
		tool_->Draw();
}


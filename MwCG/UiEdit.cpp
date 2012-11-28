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
}


UiEdit::~UiEdit(void)
{
}

void mw::UiEdit::OnLButtonDown( UINT nFlags, CPoint point )
{
	mouse_left_down_ = true;
	UpdateMouseInput(nFlags, point);
	if (tool_ == NULL)
		return;

	tool_->BeginInput(mouse_xy());

	view()->Invalidate();
}

void mw::UiEdit::OnMouseMove( UINT nFlags, CPoint point )
{
	UpdateMouseInput(nFlags, point);

	if (tool_ == NULL)
		return;
	if (!tool_->IsFinished())
		tool_->UpdateInput(mouse_xy());
}

void mw::UiEdit::OnLButtonUp( UINT nFlags, CPoint point )
{
	UpdateMouseInput(nFlags, point);
	if (tool_ == NULL)
		return;

	//A click
	if (mouse_left_down_)
	{
		tool_->EndInput(mouse_xy());
	}

	mouse_left_down_ = false;
	view()->Invalidate();
}

void mw::UiEdit::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	UpdateMouseInput(nFlags, point);
	if (tool_ == NULL)
		return;

	tool_->DoubleClick(mouse_xy());

	view()->Invalidate();
}


void mw::UiEdit::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	switch (nChar)
	{
	case ' ':
		view()->SwitchToNavMode();
		break;
	case VK_DELETE:
		//No repeat
		if (nRepCnt == 1)
		{
			OnCommand(ID_EDIT_DELETE);
		}
		break;
	case VK_ESCAPE:
		if (nRepCnt == 1)
		{
			DoCancel();
		}
		break;
	default:
		break;
	}
}

void mw::UiEdit::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	switch (nChar)
	{
	case 13:
		if (tool_ == NULL)
			return;
		if (!tool_->IsFinished())
		{
			if (tool_->CanFinishByEnter() && tool_->TryFinish())
			{
				tool_->New();
				view()->Invalidate();
			}
		}
		break;;
	default:
		break;
	}
}

void mw::UiEdit::InitializeName()
{
	name_.LoadString(IDS_UI_EDIT);
	ASSERT(name_);
}

//void mw::UiEdit::UpdateMouseInput( UINT nFlags, CPoint point )
//{
//	scr_pt_ = point;
//	mouse_xy_ = doc()->SetMousePos(point);
//}

void mw::UiEdit::set_tool( shared_ptr<UiEditorTool> tool )
{
	//Cancel current one
	if (tool_ != NULL)
	{
		if (!tool_->TryFinish())
			tool_->Cancel();
		else
		{
			tool_->New();
		}
	}

	tool->set_doc(doc());
	tool->set_view(view());
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
	DoCancel();

}

void mw::UiEdit::OnCommand( UINT nCmdId )
{
	switch (nCmdId)
	{
	case ID_EDIT_DELETE:
		if (tool_ != NULL)
			tool_->OnDelete();
		break;
	default:
		break;
	}
}

void mw::UiEdit::DoCancel()
{
	if (tool_->IsNew())
	{
		view()->OnToolSelect();
	}
	else
	{
		tool_->Cancel();
	}
}

#include "stdafx.h"
#include "UiEdit.h"

#include "MwCGDoc.h"
#include "MwCGView.h"

#include "UiEditor.h"

using namespace mw;

UiEdit::UiEdit(void)
{
}


UiEdit::~UiEdit(void)
{
}

void mw::UiEdit::OnMouseMove( UINT nFlags, CPoint point )
{
	UpdateMouseInput(nFlags, point);
	//editor_->MouseMove(mouse_xy_);
}

void mw::UiEdit::OnLButtonDown( UINT nFlags, CPoint point )
{
	UpdateMouseInput(nFlags, point);
	//editor_->MouseLDown(mouse_xy_);
}

void mw::UiEdit::OnLButtonUp( UINT nFlags, CPoint point )
{
	UpdateMouseInput(nFlags, point);
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

#include "stdafx.h"
#include "UiNav.h"

using namespace mw;

#include "MwCGDoc.h"
#include "MwCGView.h"

UiNav::UiNav(void) : m_bMouseDown(false)
{
}


UiNav::~UiNav(void)
{
}

void mw::UiNav::OnMouseMove( UINT nFlags, CPoint point )
{
	if (m_bMouseDown)
	{
		doc()->
			glContent()->
			screen()->
			translate_xy_scr(point.x - last_mouse_point_.x, point.y - last_mouse_point_.y);

		last_mouse_point_ = point;
	}
}

void mw::UiNav::OnLButtonDown( UINT nFlags, CPoint point )
{
	last_mouse_point_ = point;
	m_bMouseDown = true;
}

void mw::UiNav::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_bMouseDown = false;
}

void mw::UiNav::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
}

void mw::UiNav::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if (' ' == nChar)
	{
		view()->SwitchToEditMode();
	}
}

void mw::UiNav::InitializeName()
{
	name_.LoadString(IDS_UI_NAVIGATION);
	ASSERT(name_);
}

void mw::UiNav::Draw()
{
}

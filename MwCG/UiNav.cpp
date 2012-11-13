#include "stdafx.h"
#include "UiNav.h"

using namespace mw;

#include "MwCGDoc.h"
#include "MwCGView.h"

UiNav::UiNav(void)
{
}


UiNav::~UiNav(void)
{
}

void mw::UiNav::OnMouseMove( UINT nFlags, CPoint point )
{
}

void mw::UiNav::OnLButtonDown( UINT nFlags, CPoint point )
{
}

void mw::UiNav::OnLButtonUp( UINT nFlags, CPoint point )
{
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

#include "stdafx.h"
#include "UiNav.h"

using namespace mw;

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
	if (' ' == nChar)
	{
		m_bSpaceDown = true;
	}
}

void mw::UiNav::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if (' ' == nChar)
	{
		//TODO: mark space up
		if (!m_bSpaceDown)
		{
			//TODO: switch back to edit mode
		}
		m_bSpaceDown = false;
	}
}

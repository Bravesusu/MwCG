#include "stdafx.h"
#include "UiEdit.h"

using namespace mw;

UiEdit::UiEdit(void)
{
}


UiEdit::~UiEdit(void)
{
}

void mw::UiEdit::OnMouseMove( UINT nFlags, CPoint point )
{
}

void mw::UiEdit::OnLButtonDown( UINT nFlags, CPoint point )
{
}

void mw::UiEdit::OnLButtonUp( UINT nFlags, CPoint point )
{
}

void mw::UiEdit::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if (' ' == nChar)
	{
		//TODO: switch to nav mode
	}
}

void mw::UiEdit::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
}

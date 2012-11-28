#include "stdafx.h"
#include "UiState.h"

#include "MwCGDoc.h"
#include "MwCGView.h"

using namespace mw;

UiState::UiState(void)
{
}


UiState::~UiState(void)
{
}

void mw::UiState::Initialize( CMwCGDoc* pDoc, CMwCGView* pView )
{
	pDoc_ = pDoc;
	pView_ = pView;
	ASSERT_VALID(pDoc_);
	ASSERT_VALID(pView_);
	InitializeName();
}

void mw::UiState::UpdateMouseInput( UINT nFlags, CPoint point )
{
	scr_pt_ = point;
	mouse_xy_ = doc()->SetMousePos(point);
}

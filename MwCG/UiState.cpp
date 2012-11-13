#include "stdafx.h"
#include "UiState.h"

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
}

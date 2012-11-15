#include "stdafx.h"
#include "UiSelector.h"

using namespace mw;

UiSelector::UiSelector(void)
{
}


UiSelector::~UiSelector(void)
{
}

mw::OperationPtr mw::UiSelector::PopNewOperation()
{
	throw std::exception("The method or operation is not implemented.");
}

void mw::UiSelector::New()
{
	throw std::exception("The method or operation is not implemented.");
}

bool mw::UiSelector::IsFinished() const
{
	throw std::exception("The method or operation is not implemented.");
}

bool mw::UiSelector::IsIdle() const
{
	throw std::exception("The method or operation is not implemented.");
}

bool mw::UiSelector::IsInputting() const
{
	throw std::exception("The method or operation is not implemented.");
}

void mw::UiSelector::BeginInput( const Vector2& pos )
{
	throw std::exception("The method or operation is not implemented.");
}

void mw::UiSelector::UpdateInput( const Vector2& pos )
{
	throw std::exception("The method or operation is not implemented.");
}

void mw::UiSelector::EndInput()
{
	throw std::exception("The method or operation is not implemented.");
}

void mw::UiSelector::Cancel()
{
	throw std::exception("The method or operation is not implemented.");
}

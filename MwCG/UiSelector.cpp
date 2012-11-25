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

bool mw::UiSelector::IsFinished() const
{
	return false;
	//throw std::exception("The method or operation is not implemented.");
}

void mw::UiSelector::Draw()
{
}

void mw::UiSelector::DoNew()
{
}

void mw::UiSelector::DoNextInput()
{
}

void mw::UiSelector::DoUpdateInput()
{
}

void mw::UiSelector::DoFixInput( const int index )
{
}

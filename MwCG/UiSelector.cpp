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
	throw std::exception("The method or operation is not implemented.");
}

void mw::UiSelector::DoNextInput()
{
	throw std::exception("The method or operation is not implemented.");
}

void mw::UiSelector::DoUpdateInput()
{
	throw std::exception("The method or operation is not implemented.");
}

void mw::UiSelector::DoFixInput( const int index )
{
	throw std::exception("The method or operation is not implemented.");
}

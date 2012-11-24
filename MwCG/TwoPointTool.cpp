#include "stdafx.h"
#include "TwoPointTool.h"
#include "MwLine.h"
#include "MwPoint.h"
#include "AddElementToContent.h"
#include "Rect.h"
#include "Rectangle.h"

using namespace mw;

TwoPointTool::TwoPointTool(void) 
{
	first_.reset(new Point());
	first_->set_hidden(true);
	first_->set_size(10);
	first_->set_color(1, 0, 0);

	second_.reset(new Point());
	second_->set_hidden(true);
	second_->set_size(10);
	second_->set_color(1, 0, 0);
}


TwoPointTool::~TwoPointTool(void)
{
}

void mw::TwoPointTool::DoInput(int index)
{
	Vector2 pos = get_input(index);
	switch (index)
	{
	case 0:
		//TRACE("Set from(%.3f, %.3f)\n", curent().x(), curent().y());
		first_->set_position(pos);
		first_->set_hidden(false);
		OnFirstPoint(pos);
		break;
	case 1:
		//TRACE("Set to(%.3f, %.3f)\n", current().x(), current().y());
		second_->set_position(pos);
		second_->set_hidden(false);
		OnSecondPoint(pos);
		break;
	default:
		break;
	}
}

void mw::TwoPointTool::DoNew()
{
	first_->set_hidden(true);
	second_->set_hidden(true);
	OnNew();
}

void mw::TwoPointTool::DoUpdateInput()
{
	DoInput(currentIndex());
}

void mw::TwoPointTool::DoFixInput( const int index )
{
	DoInput(index);
}

void mw::TwoPointTool::Draw()
{
	OnDraw();
	//first_->Draw();
	//second_->Draw();
	DrawInputPoint(2);
}

bool mw::TwoPointTool::IsFinished() const
{
	return input_count() == 3;
}

mw::Vector2 mw::TwoPointTool::first() const
{
	return first_->transform().position();
}

mw::Vector2 mw::TwoPointTool::second() const
{
	return second_->transform().position();
}

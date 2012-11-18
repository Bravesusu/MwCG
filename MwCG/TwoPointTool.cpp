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
	ptFrom_.reset(new Point());
	ptFrom_->set_hidden(true);
	ptFrom_->set_size(10);
	ptFrom_->set_color(1, 0, 0);

	ptTo_.reset(new Point());
	ptTo_->set_hidden(true);
	ptTo_->set_size(10);
	ptTo_->set_color(1, 0, 0);
}


TwoPointTool::~TwoPointTool(void)
{
}

void mw::TwoPointTool::DoInput()
{
	switch (currentIndex())
	{
	case 0:
		//TRACE("Set from(%.3f, %.3f)\n", curent().x(), curent().y());
		ptFrom_->set_position(current());
		ptFrom_->set_hidden(false);
		OnFirstPoint(current());
		break;
	case 1:
		TRACE("Set to(%.3f, %.3f)\n", current().x(), current().y());
		ptTo_->set_position(current());
		ptTo_->set_hidden(false);
		OnSecondPoint(current());
		break;
	default:
		break;
	}
}

void mw::TwoPointTool::DoNew()
{
	ptFrom_->set_hidden(true);
	ptTo_->set_hidden(true);
	OnNew();
}

void mw::TwoPointTool::DoUpdateInput()
{
	DoInput();
}

void mw::TwoPointTool::DoFixInput()
{
	//TODO:
}

void mw::TwoPointTool::Draw()
{
	OnDraw();
	ptFrom_->Draw();
	ptTo_->Draw();
}

bool mw::TwoPointTool::IsFinished() const
{
	return input_count() == 3;
}

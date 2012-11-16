#include "stdafx.h"
#include "LineTool.h"
#include "MwLine.h"
#include "MwPoint.h"
#include "AddElementToContent.h"

using namespace mw;

LineTool::LineTool(void) 
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


LineTool::~LineTool(void)
{
}

mw::OperationPtr mw::LineTool::PopNewOperation()
{
	//TRACE("Try pop operation\n");
	if (!IsFinished())
		return NULL;
	TRACE("Operation Poped\n");
	return OperationPtr(new AddElementToContent(content(), line_));
}


void mw::LineTool::DoInput()
{
	switch (currentIndex())
	{
	case 0:
		//TRACE("Set from(%.3f, %.3f)\n", curent().x(), curent().y());
		ptFrom_->set_position(current());
		ptFrom_->set_hidden(false);
		line_->set_from(current());
		line_->set_to(current());
		break;
	case 1:
		TRACE("Set to(%.3f, %.3f)\n", current().x(), current().y());
		ptTo_->set_position(current());
		ptTo_->set_hidden(false);
		line_->set_to(current());
		break;
	default:
		break;
	}
}

void mw::LineTool::DoNew()
{
	line_.reset(new Line());
	ptFrom_->set_hidden(true);
	ptTo_->set_hidden(true);
}

void mw::LineTool::DoUpdateInput()
{
	DoInput();
}

void mw::LineTool::DoFixInput()
{
	//TODO:
}

void mw::LineTool::Draw()
{
	line_->Draw();
	ptFrom_->Draw();
	ptTo_->Draw();
}

bool mw::LineTool::IsFinished() const
{
	return input_count() == 3;
}

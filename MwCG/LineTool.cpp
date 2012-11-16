#include "stdafx.h"
#include "LineTool.h"
#include "MwLine.h"
#include "AddElementToContent.h"

using namespace mw;

LineTool::LineTool(void) : input_count_(0)
{
}


LineTool::~LineTool(void)
{
}

mw::OperationPtr mw::LineTool::PopNewOperation()
{
	if (!IsFinished())
		return NULL;
	return OperationPtr(new AddElementToContent(content(), line_));
}

void mw::LineTool::New()
{
	line_.reset(new Line());
	input_count_ = 0;
}

bool mw::LineTool::IsFinished() const
{
	return input_count_ == 2;
}

bool mw::LineTool::IsIdle() const
{
	return input_count_ == 0 && !IsInputting();
}

void mw::LineTool::Cancel()
{
	New();
}

void mw::LineTool::DoBeginInput()
{
	DoInput();
}

void mw::LineTool::DoUpdateInput()
{
	DoInput();
	input_count_++;
}

void mw::LineTool::DoEndInput()
{
}

void mw::LineTool::DoInput()
{
	switch (input_count_)
	{
	case 0:
		line_->set_from(curent());
		break;
	case 1:
		line_->set_to(curent());
		break;
	default:
		break;
	}
}

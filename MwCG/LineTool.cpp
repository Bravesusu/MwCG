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
	//TRACE("Try pop operation\n");
	if (!IsFinished())
		return NULL;
	TRACE("Operation Poped\n");
	return OperationPtr(new AddElementToContent(content(), line_));
}

void mw::LineTool::New()
{
	line_.reset(new Line());
	input_count_ = 0;
	TRACE("New Line\n");
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
		//TRACE("Set from(%.3f, %.3f)\n", curent().x(), curent().y());
		line_->set_from(current());
		break;
	case 1:
		//TRACE("Set to(%.3f, %.3f)\n", curent().x(), curent().y());
		line_->set_to(current());
		break;
	default:
		break;
	}
}

void mw::LineTool::Draw()
{
	line_->Draw();
}

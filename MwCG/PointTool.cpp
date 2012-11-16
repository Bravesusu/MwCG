#include "stdafx.h"
#include "PointTool.h"

#include "AddElementToContent.h"
#include "MwPoint.h"
#include "PointDecorator.h"

using namespace mw;

PointTool::PointTool(void) : isIdle_(true)
{
	decorator_.reset(new PointDecorator());
}


PointTool::~PointTool(void)
{
}

mw::OperationPtr mw::PointTool::PopNewOperation()
{
	point_ -= decorator_;
	return OperationPtr(new AddElementToContent(content(), point_));
}

void mw::PointTool::DoUpdateInput()
{
	point_->set_position(current());
}

void mw::PointTool::Draw()
{
	point_->Draw();
}

void mw::PointTool::DoNew()
{
	point_.reset(new Point());
	point_->set_size(5);
	point_ += decorator_;
}

void mw::PointTool::DoNextInput()
{
	set_status(AcceptNone);
	TRACE("WTF\n");
}

void mw::PointTool::DoFixInput()
{
	point_->set_position(current());
}

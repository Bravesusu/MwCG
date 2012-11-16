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

void mw::PointTool::New()
{
	point_.reset(new Point());
	point_->set_size(5);
	point_ += decorator_;
	isIdle_ = true;
}

bool mw::PointTool::IsFinished() const
{
	return !isIdle_ && !IsInputting();
}

bool mw::PointTool::IsIdle() const
{
	return isIdle_;
}

void mw::PointTool::Cancel()
{
	New();
}

void mw::PointTool::DoBeginInput()
{
	isIdle_ = false;
	point_->set_position(current());
}

void mw::PointTool::DoUpdateInput()
{
	point_->set_position(current());
}

void mw::PointTool::DoEndInput()
{
}

void mw::PointTool::Draw()
{
	point_->Draw();
}

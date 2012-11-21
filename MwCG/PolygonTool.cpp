#include "stdafx.h"
#include "PolygonTool.h"

#include "Polygon.h"
#include "AddElementToContent.h"

using namespace mw;

PolygonTool::PolygonTool(void)
{
}


PolygonTool::~PolygonTool(void)
{
}

shared_ptr<GlElement> mw::PolygonTool::GetEditingElement()
{
	return polygon_;
}

mw::OperationPtr mw::PolygonTool::PopNewOperation()
{
	if (!IsFinished())
		return NULL;
	return OperationPtr(new AddElementToContent(content(), polygon_));
}

void mw::PolygonTool::DoNew()
{
	polygon_.reset(new Polygon());
	recvEnter_ = false;
}

void mw::PolygonTool::DoNextInput()
{
	polygon_->NewVertex(mouse_pos());
}

void mw::PolygonTool::DoUpdateInput()
{
	polygon_->UpdateLastVertext(current());
}

void mw::PolygonTool::DoFixInput( const int index )
{
}

bool mw::PolygonTool::IsFinished() const
{
	return recvEnter_;
}

void mw::PolygonTool::Draw()
{
	//TODO: add decorator
	polygon_->Draw();
}

bool mw::PolygonTool::CanFinishByEnter()
{
	if (polygon_ == NULL || polygon_->count() < 3)
		return false;

	recvEnter_ = true;
	return true;
}

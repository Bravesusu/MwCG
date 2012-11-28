#include "stdafx.h"
#include "PolygonTool.h"

#include "Polygon.h"
#include "AddElementToContent.h"

using namespace mw;

PolygonTool::PolygonTool(LineFactory* lineFactory)
{
	line_factory_.reset(lineFactory);
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
	polygon_.reset(new MwPolygon(line_factory_));
	recvEnter_ = false;
}

void mw::PolygonTool::DoNextInput()
{
	polygon_->NewVertex(polygon_->transform().WorldToLocal(mouse_pos()));
}

void mw::PolygonTool::DoUpdateInput()
{
	Vector2 localPos;
	if (currentIndex() == 0)
	{
		polygon_->transform().position().set(current());
	}
	else
	{
		localPos = polygon_->transform().WorldToLocal(current());
	}
	polygon_->UpdateLastVertex(localPos);
}

void mw::PolygonTool::DoFixInput( const int index )
{
	Vector2 localPos = polygon_->transform().WorldToLocal(get_input(index));
	polygon_->SetVertex(index, localPos);
}

bool mw::PolygonTool::IsFinished() const
{
	return recvEnter_;
}

void mw::PolygonTool::Draw()
{
	//TODO: add decorator
	polygon_->Draw();
	DrawInputPoint(input_count());
}

bool mw::PolygonTool::CanFinishByEnter()
{
	if (polygon_ == NULL || polygon_->count() < 3)
		return false;

	recvEnter_ = true;
	return true;
}

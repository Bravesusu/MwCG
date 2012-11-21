#include "stdafx.h"
#include "CircleTool.h"

#include "Circle.h"
#include "AddElementToContent.h"

using namespace mw;

CircleTool::CircleTool(void)
{
}


CircleTool::~CircleTool(void)
{
}

void mw::CircleTool::OnFirstPoint( const Vector2& point )
{
	circle_->set_center(point);
}

void mw::CircleTool::OnSecondPoint( const Vector2& point )
{
	float radius = (second() - first()).magnitude();
	//TRACE("Radius: %.2f\n", radius);
	circle_->set_radius(radius);
}

void mw::CircleTool::OnNew()
{
	circle_.reset(new Circle());
	circle_->set_radius(0);
}

void mw::CircleTool::OnDraw()
{
	circle_->Draw();
}

mw::OperationPtr mw::CircleTool::PopNewOperation()
{
	if (!IsFinished())
		return NULL;
	return OperationPtr(new AddElementToContent(content(), circle_));
}

shared_ptr<GlElement> mw::CircleTool::GetEditingElement()
{
	return circle_;
}

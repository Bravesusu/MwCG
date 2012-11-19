#include "stdafx.h"
#include "LineTool.h"
#include "MwLine.h"
#include "MwPoint.h"
#include "AddElementToContent.h"
#include "Rect.h"
#include "Rectangle.h"

using namespace mw;

LineTool::LineTool(void) 
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
	return OperationPtr(new AddElementToContent(content(), line_));
}

void mw::LineTool::OnFirstPoint( const Vector2& point )
{
	line_->set_from(current());
	line_->set_to(current());
}

void mw::LineTool::OnSecondPoint( const Vector2& point )
{
	line_->set_to(current());
}

void mw::LineTool::OnNew()
{
	line_.reset(new Line());
}

void mw::LineTool::OnDraw()
{
	line_->Draw();
}

shared_ptr<GlElement> mw::LineTool::GetEditingElement()
{
	return line_;
}

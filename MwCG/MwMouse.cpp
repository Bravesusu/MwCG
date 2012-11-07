#include "stdafx.h"
#include "MwMouse.h"

using namespace mw;

Mouse::Mouse(void)
{
}


Mouse::~Mouse(void)
{
}

void mw::Mouse::Draw()
{
	if (!screen_)
		return;
	color()();
	glBegin(GL_LINES);
	glVertex2f(position_.x(), screen_->top());
	glVertex2f(position_.x(), screen_->bottom());
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(screen_->left(), position_.y());
	glVertex2f(screen_->right(), position_.y());
	glEnd();
}

#include "stdafx.h"
#include "MwMouse.h"

using namespace mw;

Mouse::Mouse(void)
{
}


Mouse::~Mouse(void)
{
}

void mw::Mouse::DoDraw()
{
	if (!screen())
		return;
	color()();
	glBegin(GL_LINES);
	glVertex2f(position_.x(), screen()->top());
	glVertex2f(position_.x(), screen()->bottom());
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(screen()->left(), position_.y());
	glVertex2f(screen()->right(), position_.y());
	glEnd();
}

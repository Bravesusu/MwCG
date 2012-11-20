#include "stdafx.h"
#include "MwMouse.h"

#include "MwGlScreen.h"
#include "MwLine.h"

using namespace mw;

Mouse::Mouse(void)
{
	line_h_.set_pattern(0xAAAA);
	line_v_.set_pattern(0xAAAA);
}


Mouse::~Mouse(void)
{
}

void mw::Mouse::DoDraw()
{
	if (!screen())
		return;
	//color()();
	line_v_.set(position_.x(), screen()->top(), position_.x(), screen()->bottom());
	line_h_.set(screen()->left(), position_.y(), screen()->right(), position_.y());
	
	line_h_.Draw();
	line_v_.Draw();
}

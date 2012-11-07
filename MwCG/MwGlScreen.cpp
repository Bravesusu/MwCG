#include "stdafx.h"
#include "MwGlScreen.h"

using namespace mw;

GlScreen::~GlScreen(void)
{
}

void GlScreen::set(int width, int height)
{
	width_ = width;
	height_ = height;
}

void GlScreen::set_xy(float x0, float y0, float scale)
{
	left_ = x0;
	top_ = y0;
	scale_ = scale;
	bottom_ = y0 - scale * height_;
	right_ = x0 + scale * width_;
}

void GlScreen::update_xy()
{
	set_xy(left_, top_, scale_);
}

void GlScreen::GL()
{
	glViewport(0, 0, width_, height_);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left_, right_, bottom_, top_);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
#include "stdafx.h"
#include "MwGlScreen.h"

using namespace mw;

IMPLEMENT_SERIAL(GlScreen, GlObject, 1);

GlScreen::~GlScreen(void)
{
}

void GlScreen::set(int width, int height)
{
	width_ = width;
	height_ = height;
}

//Set coordinate system with center point and scale
void GlScreen::set_xy(float x0, float y0, float scale)
{
	float half_width = scale * width_ / 2;
	float half_height = scale * height_ / 2;
	scale_ = scale;
	x0_ = x0;
	y0_ = y0;

	left_ = x0 - half_width;
	right_ = x0 + half_width;

	top_ = y0 + half_height;
	bottom_ = y0 - half_height;
}

//Update coordinate system to make sure the center remain fixed
void GlScreen::update_xy()
{
	set_xy(x0_, y0_, scale_);
}


Vector2 GlScreen::ScreenToXY(int sx, int sy)
{
	float x = left_ + sx * scale_;
	float y = top_ - sy * scale_;
	return Vector2(x, y);
}

Vector2 GlScreen::XYToScreen(int x, int y)
{
	float sx = (x - left_) / scale_;
	float sy = (top_ - y) / scale_;
	return Vector2(sx, sy);
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

void mw::GlScreen::set_scale( float scale )
{
	set_xy(x0_, y0_, scale);
}

void mw::GlScreen::translate_xy( float dx, float dy )
{
	set_xy(x0_ - dx, y0_ - dy, scale_);
}

void mw::GlScreen::translate_xy_scr( int dx, int dy )
{
	float dx0 = (float)dx * scale_;
	float dy0 = (float)dy * scale_;
	set_xy(x0_ - dx0, y0_ + dy0, scale_);
}

void mw::GlScreen::Serialize( CArchive& ar )
{
	GlObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar<<width_<<height_<<x0_<<y0_<<scale_;
	}
	else
	{
		ar>>width_>>height_>>x0_>>y0_>>scale_;

		set(width_, height_);
		set_xy(x0_, y0_, scale_);
	}
}

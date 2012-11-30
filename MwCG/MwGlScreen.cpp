#include "stdafx.h"
#include "MwGlScreen.h"

using namespace mw;

IMPLEMENT_SERIAL(GlScreen, GlObject, 1);

GlScreen::~GlScreen(void)
{
}

//Set screen (view) width & height
void GlScreen::set(int width, int height)
{
	width_ = width;
	height_ = height;
}

//Set X-Y space with center point (x0, y0) 
//and scale (the length corresponding to 1 pixel in screen space)
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

//Update X-Y space to make sure the center remain fixed
void GlScreen::update_xy()
{
	set_xy(x0_, y0_, scale_);
}

//Transform a vector from screen space to X-Y space
Vector2 GlScreen::ScreenToXY(int sx, int sy)
{
	float x = left_ + sx * scale_;
	float y = top_ - sy * scale_;
	return Vector2(x, y);
}

//Transform a vector from X-Y space to screen space 
Vector2 GlScreen::XYToScreen(int x, int y)
{
	float sx = (x - left_) / scale_;
	float sy = (top_ - y) / scale_;
	return Vector2(sx, sy);
}

//GL command
void GlScreen::GL()
{
	//Match view port size to view size
	glViewport(0, 0, width_, height_);

	//Modify Projection matrix
	glMatrixMode(GL_PROJECTION);
	//Reset to identity
	glLoadIdentity();
	//Define X-Y plane
	gluOrtho2D(left_, right_, bottom_, top_);

	//Modify ModelView matrix
	glMatrixMode(GL_MODELVIEW);
	//Reset to identity
	glLoadIdentity();
}

//Set the length in X-Y space corresponding to 1 Pixel in screen space
void mw::GlScreen::set_scale( float scale )
{
	set_xy(x0_, y0_, scale);
}

//Apply a movement in X-Y space defined by vector (dx, dy)
void mw::GlScreen::translate_xy( float dx, float dy )
{
	set_xy(x0_ - dx, y0_ - dy, scale_);
}

//Apply a movement in screen space defined by vector (dx, dy)
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

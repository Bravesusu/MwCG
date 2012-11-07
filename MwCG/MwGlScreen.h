#pragma once
#include "MwGLObject.h"
#include "MwVector2.h"

namespace mw
{
	class GlScreen : public MwGLObject
	{
	private:
		int width_;
		int height_;
		float left_;
		float top_;
		float scale_;

		float bottom_, right_;
		float x0_, y0_;
	public:
		//Accessors
		int width() const { return width_; }
		int height() const { return height_; }
		void set(int width, int height);
		void set_xy(float x0, float y0, float scale);
		void update_xy();
	public:
		//Transform
		Vector2 ScreenToXY(int sx, int sy);
		Vector2 XYToScreen(int x, int y);
	public:
		GlScreen(void) : width_(0), height_(0), scale_(1), x0_(0), y0_(0) {};
		GlScreen(int width, int height) : width_(width), height_(height), scale_(1), x0_(0), y0_(0) {};
		~GlScreen(void);
	public:
		void GL();
	};
}


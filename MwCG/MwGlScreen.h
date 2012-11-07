#pragma once
#include "MwGLObject.h"

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
	public:
		int width() const { return width_; }
		int height() const { return height_; }
		void set(int width, int height);
		void set_xy(float x0, float y0, float scale);
		void update_xy();
	public:
		GlScreen(void) : width_(0), height_(0) {};
		GlScreen(int width, int height) : width_(width), height_(height) {};
		~GlScreen(void);
	public:
		void GL();
	};
}


#pragma once
#include "MwGLObject.h"
#include "MwVector2.h"

namespace mw
{
	//Defines and manage a X-Y space. 
	//Provides transformation from screen space to the X-Y space.
	//Provides methods to manipulate the space.
	class GlScreen : public GlObject
	{
		DECLARE_SERIAL(GlScreen);
	private:
		int width_;
		int height_;
		float left_;
		float top_;
		float scale_;

		float bottom_, right_;
		float x0_, y0_;

	public:
		//Gets the width of the view
		int width() const { return width_; }
		//Gets the height of the view
		int height() const { return height_; }
		//Sets the width and height of the view
		void set(int width, int height);
		//Set X-Y space with center point (x0, y0) 
		//and scale (the length corresponding to 1 pixel in screen space)
		void set_xy(float x0, float y0, float scale);
		//Apply a movement in screen space defined by vector (dx, dy)
		void translate_xy_scr(int dx, int dy);
		//Apply a movement in X-Y space defined by vector (dx, dy)
		void translate_xy(float dx, float dy);
		//Set the length in X-Y space corresponding to 1 Pixel in screen space
		void set_scale(float scale);
		//Update X-Y space to make sure the center remain fixed
		void update_xy();
		//The x coordinate of left-most point
		float left() const { return left_; }
		//The x coordinate of right-most point
		float right() const { return right_; }
		//The y coordinate of up-most point
		float top() const { return top_; }
		//The y coordinate of down-most point
		float bottom() const { return bottom_; }
	public:
		//Transform a vector from screen space to X-Y space
		Vector2 ScreenToXY(int sx, int sy);
		//Transform a vector from X-Y space to screen space 
		Vector2 XYToScreen(int x, int y);
	public:
		GlScreen(void) : width_(0), height_(0), scale_(1), x0_(0), y0_(0) {};
		GlScreen(int width, int height) : width_(width), height_(height), scale_(1), x0_(0), y0_(0) {};
		virtual ~GlScreen(void);
	public:
		void GL();

		virtual void Serialize( CArchive& ar );

	};
}


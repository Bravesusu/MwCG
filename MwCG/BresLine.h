#pragma once
#include "mwline.h"

namespace mw
{
	class PixelStroker
	{
	private:
		Stroke stroke_;
		int pixel_count_;
	public:
		void set_stroke(const Stroke stroke) { stroke_ = stroke; }
		Stroke stroke() const { return stroke_; }
	public:
		PixelStroker() : stroke_(FullStroke), pixel_count_(0) {};
		PixelStroker(Stroke stroke) : stroke_(stroke), pixel_count_(0) {};
		void SetPixel(int px, int py)
		{
			pixel_count_++;
			if ((1 << (pixel_count_ % StrokePatternLength)) & stroke_.pattern)
			{
				glBegin(GL_POINTS);
				glVertex2i(px, py);
				glEnd();
			}
		}
		void Reset() { pixel_count_ = 0; }
	};

	class BresLine :
		public Line
	{
	private:
		PixelStroker stroker_;
		void lineBresenham(int p1x, int p1y, int p2x, int p2y);
	public:
		BresLine(void);
		~BresLine(void);

		virtual void DoDraw();

	};

}

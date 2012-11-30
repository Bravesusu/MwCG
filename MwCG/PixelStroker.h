#pragma once
#include "Stroke.h"

namespace mw
{
	class PixelStroker
	{
	private:
		Stroke stroke_;
		int pixel_count_;
		bool auto_;
	public:
		void set_stroke(const Stroke stroke) { stroke_ = stroke; }
		Stroke stroke() const { return stroke_; }
		void set_auto(bool isAuto) { auto_ = isAuto; }
		bool IsAuto() const { return auto_; }
	public:
		PixelStroker() : stroke_(FullStroke), pixel_count_(0), auto_(true) {};
		PixelStroker(Stroke stroke) : stroke_(stroke), pixel_count_(0), auto_(true) {};
		void SetPixel(int px, int py)
		{
			if (auto_)
				pixel_count_++;
			if ((1 << (pixel_count_ % StrokePatternLength)) & stroke_.pattern)
			{
				glBegin(GL_POINTS);
				glVertex2i(px, py);
				glEnd();
			}
		}
		void Reset() { pixel_count_ = 0; }

		PixelStroker& operator++() 
		{
			pixel_count_++;
			return *this;
		}

		PixelStroker& operator--() 
		{
			pixel_count_--;
			return *this;
		}

		PixelStroker operator++(int) 
		{
			pixel_count_++;
			return *this;
		}

		PixelStroker operator--(int) 
		{
			pixel_count_--;
			return *this;
		}
	};
}
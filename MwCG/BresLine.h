#pragma once
#include "mwline.h"

#include "PixelStroker.h"

namespace mw
{
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

#pragma once
#include "mwline.h"

namespace mw
{
	class BresLine :
		public Line
	{
	public:
		BresLine(void);
		~BresLine(void);

		virtual void DoDraw();

	};
	
}

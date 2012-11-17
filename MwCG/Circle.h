#pragma once
#include "mwglelement.h"

namespace mw
{
	class Circle :
		public GlElement
	{
	public:
		Circle(void);
		~Circle(void);

		virtual void DoDraw();

		virtual bool HitTest();

		virtual Rect bound() const;

		virtual void Draw();

	};
	
}

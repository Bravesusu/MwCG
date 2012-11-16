#pragma once
#include "idrawable.h"

namespace mw
{
	class Decorator :
		public IDrawable
	{
	public:
		Decorator(void);
		~Decorator(void);

		void Draw();

		virtual void DoDraw() = 0;

	};
}

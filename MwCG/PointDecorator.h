#pragma once
#include "decorator.h"

namespace mw
{
	class PointDecorator :
		public Decorator
	{
	public:
		PointDecorator(void);
		~PointDecorator(void);

		virtual void DoDecorate( const shared_ptr<GlElement> element );

	};
	
}

#pragma once
#include "ioperation.h"

namespace mw
{
	class GlElement;
	class ElementOperation :
		public IOperation
	{
	private:
		shared_ptr<GlElement> element_;
	protected:
		void Initialize(shared_ptr<GlElement> element);
		shared_ptr<GlElement> element() const { ASSERT(element_); return element_; }
	};
	
}

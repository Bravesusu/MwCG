#pragma once
#include "ioperation.h"

namespace mw
{
	class GlContent;
	class GlElement;
	class ContentElementOperation :
		public IOperation
	{
	private:
		shared_ptr<GlContent> content_;
		shared_ptr<GlElement> element_;
	protected:
		void Initialize(shared_ptr<GlContent> content, shared_ptr<GlElement> element);
		shared_ptr<GlContent> content() const { ASSERT(content_); return content_; }
		shared_ptr<GlElement> element() const { ASSERT(element_); return element_; }
	};

}

#pragma once
#include "IOperation.h"

namespace mw
{
	class GlContent;
	class GlElement;
	class AddElementToContent :
		public IOperation
	{
	private:
		shared_ptr<GlContent> content_;
		shared_ptr<GlElement> element_;
	public:
		AddElementToContent(shared_ptr<GlContent> content, shared_ptr<GlElement> element);
		~AddElementToContent(void);

		virtual void Undo();

		virtual void Redo();

	};
	
}

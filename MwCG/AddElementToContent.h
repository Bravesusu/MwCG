#pragma once
#include "ContentElementOperation.h"

namespace mw
{
	class AddElementToContent :
		public ContentElementOperation
	{
	public:
		AddElementToContent(shared_ptr<GlContent> content, shared_ptr<GlElement> element);
		~AddElementToContent(void);

		virtual void Undo();

		virtual void Redo();

	};
	
}

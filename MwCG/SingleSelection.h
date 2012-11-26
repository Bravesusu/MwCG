#pragma once
#include "ContentElementOperation.h"

namespace mw
{
	class SingleSelection :
		public ContentElementOperation
	{
	public:
		SingleSelection(shared_ptr<GlContent> content, shared_ptr<GlElement> element);
		~SingleSelection(void);

		virtual void Undo();

		virtual void Redo();

	};
}


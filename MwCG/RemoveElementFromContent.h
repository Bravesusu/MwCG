#pragma once
#include "ContentElementOperation.h"

namespace mw
{
	class RemoveElementFromContent :
		public ContentElementOperation
	{
	public:
		RemoveElementFromContent(shared_ptr<GlContent> content, shared_ptr<GlElement> element);
		~RemoveElementFromContent(void);

		virtual void Undo();

		virtual void Redo();

	};
}

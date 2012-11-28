#pragma once
#include "contentelementoperation.h"

namespace mw
{
	class SingleDeselection :
		public ContentElementOperation
	{
	public:
		~SingleDeselection(void);
		SingleDeselection( shared_ptr<GlContent> content, shared_ptr<GlElement> element );

		virtual void Undo();

		virtual void Redo();

	};
	
}

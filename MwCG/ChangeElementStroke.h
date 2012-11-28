#pragma once
#include "elementoperation.h"
#include "Stroke.h"

namespace mw
{
	class ChangeElementStroke :
		public ElementOperation
	{
	private:
		Stroke old_stroke_;
		Stroke new_stroke_;
	public:
		ChangeElementStroke(shared_ptr<GlElement> element, Stroke stroke);
		~ChangeElementStroke(void);

		virtual void Undo();

		virtual void Redo();

	};
	
}

#pragma once
#include "elementoperation.h"
#include "MwColor.h"

namespace mw
{
	class ChangeElementColor :
		public ElementOperation
	{
	private:
		Color oldColor_;
		Color newColor_;
	public:
		ChangeElementColor(shared_ptr<GlElement> element, const Color& color);
		~ChangeElementColor(void);

		virtual void Undo();

		virtual void Redo();

	};
}

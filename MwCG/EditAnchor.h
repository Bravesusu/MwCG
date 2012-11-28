#pragma once
#include "elementoperation.h"

namespace mw
{
	class EditAnchor :
		public ElementOperation
	{
	private:
		//Store world pos to avoid origin transform
		Vector2 old_world_pos_;
		Vector2 new_world_pos_;
		int anchor_index_;
	public:
		void set_old_anchor(const Vector2& worldPos);
		void set_new_anchor(const Vector2& worldPos);
		void set_anchor_index(int anchor_index) { anchor_index_ = anchor_index; }
	public:
		EditAnchor(shared_ptr<GlElement> element, int anchor_index);
		~EditAnchor(void);

		virtual void Undo();

		virtual void Redo();

	};
	
}

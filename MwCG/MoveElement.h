#pragma once
#include "contentelementoperation.h"

namespace mw
{
	class MoveElement :
		public ContentElementOperation
	{
	private:
		Vector2 last_pos_;
		Vector2 move_to_pos_;
	public:
		Vector2 move_to_position() const { return move_to_pos_; }
		void set_move_to_position(const Vector2& worldPos) { move_to_pos_ = worldPos; }
		void set_initial_position(const Vector2& worldPos) { last_pos_ = worldPos; }
	public:
		MoveElement( shared_ptr<GlContent> content, shared_ptr<GlElement> element );
		~MoveElement(void);

		virtual void Undo();

		virtual void Redo();

	};
	
}

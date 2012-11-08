#pragma once
#include "mwglelement.h"
#include "MwVector2.h"
#include "MwGlScreen.h"

namespace mw
{
	class Mouse :
		public GlElement
	{
	public:
		Mouse(void);
		~Mouse(void);
	private:
		Vector2 position_;
	public:
		Vector2 position() const { return position_; }
		void set_position(float x, float y) { position_.set(x, y); }
		void set_position(const Vector2& pos) { position_.set(pos); }
	public:
		void Draw();
	};
};


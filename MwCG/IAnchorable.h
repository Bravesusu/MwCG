#pragma once

namespace mw
{
	class IAnchorable
	{
	public:
		virtual int anchor_count() const = 0;
		virtual void set_anchor(int index, const Vector2& worldPos) = 0;
		virtual Vector2 anchor(int index) const = 0;
	};
}


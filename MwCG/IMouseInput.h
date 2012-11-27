#pragma once

namespace mw
{
	class IMouseInput
	{
	public:
		virtual void BeginInput(const Vector2& worldPos) = 0;
		virtual void UpdateInput(const Vector2& worldPos) = 0;
		virtual void EndInput(const Vector2& worldPos) = 0;
	};
}


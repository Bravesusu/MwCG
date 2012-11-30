#pragma once

namespace mw
{
	//The interface of all drawable objects
	class IDrawable
	{
	public:
		virtual void Draw() = 0;
	};
}


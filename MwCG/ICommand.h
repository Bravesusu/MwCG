#pragma once

namespace mw
{
	class ICommand
	{
	public:
		virtual void Undo() = 0;
		virtual void Redo() = 0;
	};
}


#pragma once

namespace mw
{
	class IOperation
	{
	public:
		virtual void Undo() = 0;
		virtual void Redo() = 0;
	};

	typedef shared_ptr<IOperation> OperationPtr;
}


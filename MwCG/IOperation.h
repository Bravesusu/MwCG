#pragma once

namespace mw
{
	class IOperation
	{
	private:
		shared_ptr<CObject> recevier_;
	public:
		shared_ptr<CObject> receiver() const { return recevier_; }
		void set_receiver(const shared_ptr<CObject> recv) { recevier_ = recv; }
	public:
		virtual void Undo() = 0;
		virtual void Redo() = 0;
	};

	typedef shared_ptr<IOperation> OperationPtr;
}


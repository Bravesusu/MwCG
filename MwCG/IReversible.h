#pragma once
#include <memory>
using namespace std;
namespace mw
{
	class Slice {};
	
	class IReversible
	{
	public:
		virtual shared_ptr<Slice> Snapshot() = 0;
		virtual bool Reverse(const Slice& slice) = 0;
	};
}


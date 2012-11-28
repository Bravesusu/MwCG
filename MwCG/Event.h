#pragma once
#include <functional>
#include <list>

using namespace std;
namespace mw
{
	//template <class T> class Event {};
	//template <class TRet, class TParams, ...>
	class Event//<TRet(TParams, ...)>
	{
	//private:
		//list<function<TRet(TParams, ...)>> handlers_;
	public:
		Event(void);
		~Event(void);
	public:
		//TRet operator()(TParams, ...) {};
	};
}

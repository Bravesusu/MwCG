#pragma once
#include "elementoperation.h"
namespace mw
{
	//template <class TProp>
	//class ChangeElementProperty :
	//	public ElementOperation
	//{
	//private:
	//	TProp new_prop_;
	//public:
	//	ChangeElementProperty(shared_ptr<GlElement> element, TProp newProp)
	//	{
	//		Initialize(element);
	//		new_prop_ = newProp;
	//	}
	//};

	class ChangeElementSize :
		public ElementOperation
	{
	private:
		int new_size_;
		int old_size_;
	public:
		ChangeElementSize(shared_ptr<GlElement> element, int size);
		~ChangeElementSize(void);

		virtual void Undo();

		virtual void Redo();

	};
	
}

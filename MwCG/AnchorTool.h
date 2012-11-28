#pragma once
#include "uieditortool.h"

using namespace std;

namespace mw
{
	class IElementFactory
	{
	public:
		virtual shared_ptr<GlElement> Make() { return NULL; };
	};

	template <class TElement>
	class ElementFactory: 
		public IElementFactory
	{
	public:
		shared_ptr<GlElement> Make()
		{
			return shared_ptr<GlElement>(new TElement());
		}
	};

	class AnchorTool :
		public UiEditorTool
	{

	public:
		AnchorTool(IElementFactory factory);
		~AnchorTool(void);

		virtual void DoNew();

		virtual void DoBeginInput();

		virtual void DoUpdateInput();

		virtual void DoEndInput();

		virtual OperationPtr PopNewOperation();

		virtual bool IsFinished() const;

		virtual bool CanFinishByEnter();

		virtual void Draw();

	};
}

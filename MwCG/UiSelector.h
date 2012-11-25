#pragma once
#include "UiEditorTool.h"

namespace mw
{
	class BoundDecorator;
	class UiSelector :
		public UiEditorTool
	{
	private:
		shared_ptr<GlElement> click_hit_;
		shared_ptr<GlElement> hover_hit_;
	private:
		shared_ptr<BoundDecorator> selDec_;
		shared_ptr<BoundDecorator> hoverDec_;
	protected:
		void Select(shared_ptr<GlElement> element);
		void Deselect(shared_ptr<GlElement> element);
		void Enter(shared_ptr<GlElement> element);
		void Leave(shared_ptr<GlElement> element);
	public:
		UiSelector(void);
		~UiSelector(void);

		virtual OperationPtr PopNewOperation();

		virtual bool IsFinished() const;

		virtual void Draw();

		virtual void DoNew();

		virtual void DoNextInput();

		virtual void DoUpdateInput();

		virtual void DoFixInput( const int index );

		virtual void DoBeginInput();

		virtual void DoEndInput();

	};
}


#pragma once
#include "decorator.h"
#include "IMouseInput.h"

namespace mw
{
	class Point;
	class EditAnchor;
	class AnchorDecorator :
		public Decorator,
		public DecoratorOp<GlElement>,
		public IMouseInput
	{
	private:
		int hit_anchor_index_;
		shared_ptr<Point> anchor_;
		Vector2 local_pos_;
		bool draging_;
		shared_ptr<EditAnchor> op_;
	public:
		shared_ptr<EditAnchor> operation() const { return op_; }
		void reset_operation() { op_.reset(); }
	protected:
		void InitializeAnchor();
	public:
		AnchorDecorator(void);
		~AnchorDecorator(void);

		virtual void DoDecorate();

		virtual void BeginInput( const Vector2& worldPos );

		virtual void UpdateInput( const Vector2& worldPos );

		virtual void EndInput( const Vector2& worldPos );

	};
	
	DECLARE_DECORATOR_OP(GlElement, AnchorDecorator);
}

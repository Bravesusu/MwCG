#pragma once
#include "decorator.h"
#include "IMouseInput.h"

namespace mw
{
	class AnchorDecorator :
		public Decorator,
		public DecoratorOp<GlElement>,
		public IMouseInput
	{
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

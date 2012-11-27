#pragma once
#include "decorator.h"
#include "MwColor.h"

namespace mw
{
	class GlElement;
	class Rectangle;
	class BoundDecorator :
		public Decorator,
		public DecoratorOp<GlElement>
	{
	private:
		shared_ptr<Rectangle> rectangle_;
		Color color_;
	public:
		Color& color() { return color_; }
		const Color& color() const { return color_; }
	public:
		BoundDecorator(void);
		~BoundDecorator(void);

		virtual void DoDecorate();
	};

	DECLARE_DECORATOR_OP(GlElement, BoundDecorator);
	//shared_ptr<GlElement> operator +(shared_ptr<GlElement> lhs, shared_ptr<BoundDecorator> rhs);
	//shared_ptr<GlElement> operator -(shared_ptr<GlElement> lhs, shared_ptr<BoundDecorator> rhs);
	//shared_ptr<GlElement> operator +=(shared_ptr<GlElement> lhs, shared_ptr<BoundDecorator> rhs);
	//shared_ptr<GlElement> operator -=(shared_ptr<GlElement> lhs, shared_ptr<BoundDecorator> rhs);
}


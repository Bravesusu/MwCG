#pragma once
#include "decorator.h"
#include "MwColor.h"
#include "Stroke.h"

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
		Stroke stroke() const;
		void set_stroke(const Stroke& stroke);
	public:
		BoundDecorator(void);
		~BoundDecorator(void);

		virtual void DoDecorate();
	};

	DECLARE_DECORATOR_OP(GlElement, BoundDecorator);
}


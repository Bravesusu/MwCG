#pragma once
#include "decorator.h"
#include "MwColor.h"

namespace mw
{
	class GlElement;
	class Rectangle;
	class BoundDecorator :
		public Decorator
	{
	private:
		shared_ptr<Rectangle> rectangle_;
		Color color_;
	private:
		shared_ptr<GlElement> dec_;
	public:
		void set(shared_ptr<GlElement> element);
		Color& color() { return color_; }
		const Color& color() const { return color_; }
	public:
		BoundDecorator(void);
		~BoundDecorator(void);

		virtual void DoDecorate();
	public:
		shared_ptr<GlElement> operator +(shared_ptr<GlElement> rhs);
	};

	shared_ptr<GlElement> operator +(shared_ptr<GlElement> lhs, shared_ptr<BoundDecorator> rhs);
	shared_ptr<GlElement> operator -(shared_ptr<GlElement> lhs, shared_ptr<BoundDecorator> rhs);
	shared_ptr<GlElement> operator +=(shared_ptr<GlElement> lhs, shared_ptr<BoundDecorator> rhs);
	shared_ptr<GlElement> operator -=(shared_ptr<GlElement> lhs, shared_ptr<BoundDecorator> rhs);
}


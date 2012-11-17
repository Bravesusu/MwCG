#pragma once
#include "decorator.h"

namespace mw
{
	class GlElement;
	class BoundDecorator :
		public Decorator
	{
	private:
		shared_ptr<GlElement> dec_;
	public:
		void set(shared_ptr<GlElement> element);
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


#pragma once
#include "idrawable.h"

//#define DECORATOR_OP()

namespace mw
{
	class GlElement;

	class Decorator
	{
	public:
		Decorator(void);
		~Decorator(void);

		void Decorate();

		virtual void DoDecorate() = 0;
		virtual void Removed() {};
	//public:
	//	shared_ptr<GlElement>& operator+(shared_ptr<GlElement>& rhs);
	//	GlElement& operator+(GlElement& rhs);
	};
	
	template<class TDecoratee>
	class DecoratorOp
	{
	private:
		shared_ptr<TDecoratee> decoratee_;
	public:
		void set(const shared_ptr<TDecoratee> decoratee) { decoratee_ = decoratee; }
		shared_ptr<TDecoratee> decoratee() const { return decoratee_; }
	public:
		shared_ptr<TDecoratee> operator+(shared_ptr<TDecoratee> rhs)
		{
			rhs->AddDecorator(DecoratorPtr(this));
			set(rhs);
			return rhs;
		}
	};

	typedef shared_ptr<Decorator> DecoratorPtr;
}

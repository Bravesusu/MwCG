#pragma once
#include "idrawable.h"

//#define DECORATOR_OP()

namespace mw
{
	class GlElement;

	//The base class of all decorators
	//Steps to create a concrete decorator:
	//1. Inherited from Decorator
	//2. Inherited from DecoratorOp<>, which will specify the decorated class
	//		and generate the data field and accessors, and operators.
	//3. Use DECLARE_DECORATOR_OP in the header file
	//4. Use IMPLEMENT_DECORATOR_OP in the implementation file
	class Decorator
	{
	public:
		Decorator(void);
		~Decorator(void);

		void Decorate();

		virtual void DoDecorate() = 0;
		virtual void Removed() {};
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

#define DECLARE_DECORATOR_OP(decoratee_class, decorator_class) \
	shared_ptr<decoratee_class> operator +(shared_ptr<decoratee_class> lhs, shared_ptr<decorator_class> rhs);\
	shared_ptr<decoratee_class> operator -(shared_ptr<decoratee_class> lhs, shared_ptr<decorator_class> rhs);\
	shared_ptr<decoratee_class> operator +=(shared_ptr<decoratee_class> lhs, shared_ptr<decorator_class> rhs);\
	shared_ptr<decoratee_class> operator -=(shared_ptr<decoratee_class> lhs, shared_ptr<decorator_class> rhs);

#define IMPLEMENT_DECORATOR_OP(decoratee_class, decorator_class) \
	shared_ptr<decoratee_class> mw::operator+( shared_ptr<decoratee_class> lhs, shared_ptr<decorator_class> rhs )\
	{\
		lhs->AddDecorator(rhs);\
		rhs->set(lhs);\
		return lhs;\
	}\
	\
	shared_ptr<decoratee_class> mw::operator-( shared_ptr<decoratee_class> lhs, shared_ptr<decorator_class> rhs )\
	{\
		lhs->RemoveDecorator(rhs);\
		rhs->set(NULL);\
		return lhs;\
	}\
	\
	shared_ptr<decoratee_class> mw::operator+=( shared_ptr<decoratee_class> lhs, shared_ptr<decorator_class> rhs )\
	{\
		return lhs + rhs;\
	}\
	\
	shared_ptr<decoratee_class> mw::operator-=( shared_ptr<decoratee_class> lhs, shared_ptr<decorator_class> rhs )\
	{\
		return lhs - rhs;\
	}
}
